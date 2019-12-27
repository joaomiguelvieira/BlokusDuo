//
// Created by joaovieira on 12/25/19.
//

#include <chrono>
#include "MonteCarloTreeSearch.h"

MonteCarloTreeSearch::MonteCarloTreeSearch(int moveDurationMillis) {
    this->moveDurationMillis = moveDurationMillis;
    this->gameTree = new Tree();
}

MonteCarloTreeSearch::~MonteCarloTreeSearch() {
    delete gameTree;
}

int MonteCarloTreeSearch::checkStatus() {
    return gameTree->getRoot()->getState()->checkStatus();
}

/*
Move *MonteCarloTreeSearch::findNextMove() {
    auto start = std::chrono::high_resolution_clock::now();
    long elapsed;

    do {
        // selection
        Node *promisingNode = selectPromisingNode(gameTree->getRoot());

        // expansion
        if (promisingNode->getState()->checkStatus() == State::IN_PROGRESS)
            expandNode(promisingNode);

        // simulation
        Node *nodeToExplore = promisingNode;
        if (!promisingNode->getChildArray()->empty())
            nodeToExplore = promisingNode->getRandomChildNode();

        int playoutResult = simulateRandomPlayout(nodeToExplore);

        // update
        backPropagation(nodeToExplore, playoutResult);

        auto end = std::chrono::high_resolution_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    } while (elapsed < moveDurationMillis);

    auto winnerNode = gameTree->getRoot()->getChildWithMaxScore();
    return winnerNode->getState()->getMove();
}
*/
