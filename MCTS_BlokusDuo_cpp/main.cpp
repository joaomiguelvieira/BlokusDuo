#include <iostream>
#include "GamePiece.h"
#include "MonteCarloTreeSearch.h"
#include <pthread.h>
#include <mutex>

#define NUM_THREADS 8

Tree *gameTree;
int nNodes;
std::mutex mtx;

void expandGameSubtree(Node *node) {
    mtx.lock();
    nNodes++;
    if (nNodes % (1024 * 1024) == 0)
        std::cout << nNodes / 1024 / 1024 << "Mi Nodes" << std::endl;
    mtx.unlock();

    // if node is terminal do not expand
    if (node->getState()->checkStatus() != State::IN_PROGRESS) {
        //std::cout << "Reached terminal node!\n";
        return;
    }

    // expand node
    MonteCarloTreeSearch::expandNode(node);

    // expand each of the node's children
    for (auto & child : *node->getChildArray())
        expandGameSubtree(child);
}

void *expandGameSubtreeMultithread(void *id) {
    auto childArray = gameTree->getRoot()->getChildArray();
    auto it = childArray->begin();

    for (long i = 0; i < childArray->size(); ++i) {
        if (i % NUM_THREADS == (long) id) {
            expandGameSubtree(*it);
        }

        it++;
    }

    return nullptr;
}

void calculateGameTree() {
    gameTree = new Tree();

    auto gamePieceSet1 = GamePiece::getInitialSetOfGamePieces();
    gameTree->getRoot()->getState()->setOpponent(new Player(gamePieceSet1));

    auto gamePieceSet2 = GamePiece::getInitialSetOfGamePieces();
    gameTree->getRoot()->getState()->setPlayer(new Player(gamePieceSet2));

    MonteCarloTreeSearch::expandNode(gameTree->getRoot());

    nNodes = 1;
    pthread_t threads[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_create(&threads[i], nullptr, expandGameSubtreeMultithread, (void *) i);
    }

    for (int j = 0; j < NUM_THREADS; ++j) {
        pthread_join(threads[j], nullptr);
    }
}

void playGame() {
    auto mcts = new MonteCarloTreeSearch();

    while (mcts->checkStatus() == State::IN_PROGRESS) {
        auto bestMove = mcts->findNextMove();
        mcts->performNextMove(bestMove);
        //mcts->printStatus();
    }

    delete mcts;
}

int main() {
    calculateGameTree();

    return 0;
}
