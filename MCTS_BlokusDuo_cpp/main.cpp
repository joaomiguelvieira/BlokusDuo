#include <algorithm>
#include <iostream>
#include "GamePiece.h"
#include "Player.h"
#include "MonteCarloTreeSearch.h"

/*
void playGame() {
    auto mcts = new MonteCarloTreeSearch(1000);

    while (mcts->checkStatus() == State::IN_PROGRESS) {
        auto bestMove = mcts->findNextMove();
        mcts->performBestMove(bestMove)
    }

    mcts->printStatus();

    delete mcts;
}
 */

int nNodes;

void expandGameSubtree(Node *node) {
    auto state = node->getState();

    //auto player1 = state->getPlayer()->getPlayerId() == 1 ? state->getPlayer() : state->getOpponent();
    //auto player2 = state->getPlayer()->getPlayerId() == 2 ? state->getPlayer() : state->getOpponent();

    //auto player1_RemainingPieces = player1->getRemainingGamePieces()->size();
    //auto player2_RemainingPieces = player2->getRemainingGamePieces()->size();

    nNodes++;
    std::cout << nNodes << std::endl;

    if (state->checkStatus() != State::IN_PROGRESS)
        return;

    for (auto & possibleState : *state->getAllPossibleStates()) {
        auto child = new Node(possibleState);
        node->getChildArray()->push_back(child);
        expandGameSubtree(child);
    }
}

int main() {
    auto gameTree = new Tree();
    auto initialState = gameTree->getRoot()->getState();

    initialState->setOpponent(new Player());
    initialState->setPlayer(new Player());

    nNodes = 1;

    expandGameSubtree(gameTree->getRoot());
    std::cout << nNodes << std::endl;

    return 0;
}
