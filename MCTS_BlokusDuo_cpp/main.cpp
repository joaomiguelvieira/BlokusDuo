#include <iostream>
#include "GamePiece.h"
#include "MonteCarloTreeSearch.h"
#include <pthread.h>
#include <mutex>
#include <sstream>

#define NUM_THREADS 12

Tree *gameTree;
long nNodes;
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
    for (auto & child : *node->getChildArray()) {
        expandGameSubtree(child);
        delete child;
    }

    node->resetChildArray();
}

void *expandGameSubtreeMultithread(void *id) {
    auto childArray = gameTree->getRoot()->getChildArray();
    auto it = childArray->begin();

    for (int i = 0; i < childArray->size(); ++i) {
        if (i % NUM_THREADS == *((int *) id)) {
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
        pthread_create(&threads[i], nullptr, expandGameSubtreeMultithread, (void *) &i);
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
        mcts->printMove();
    }

    delete mcts;
}

void interactiveGame() {
    auto mcts = new MonteCarloTreeSearch();

    std::string last_move;
    while (mcts->checkStatus() == State::IN_PROGRESS) {
        mcts->printStatus();
        std::string move;
        std::cin >> move;

        if (move == "hint")
            mcts->printValidMoves();
        else if (move == "simulate")
            std::cout << "MCTS advises move " << mcts->findNextMove() << std::endl;
        else if (move == "last")
            std::cout << "Last move was " << last_move << std::endl;
        else
            if (mcts->performNextMove(move) == 0)
                last_move = move;
    }

    delete mcts;
}

int main() {
    playGame();

    return 0;
}
