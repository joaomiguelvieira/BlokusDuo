//
// Created by João Vieira on 22/12/2019.
//

#include "MonteCarloTreeSearch.h"
#include "Tree.h"
#include "UCT.h"
#include <chrono>
#include <iostream>
#include <climits>

MonteCarloTreeSearch::MonteCarloTreeSearch() {
    this->level = 3;
}

Board *MonteCarloTreeSearch::findNextMove(Board *board, int playerNo) {
    auto start = std::chrono::high_resolution_clock::now();
    long elapsed;
    long duration = 60 * getMillisForCurrentLevel();

    opponent = 3 - playerNo;
    auto tree = new Tree();
    Node *rootNode = tree->getRoot();
    rootNode->getState()->setBoard(board);
    rootNode->getState()->setPlayerNo(opponent);

    auto simulations = 0;
    do {
        // Phase 1 - Selection
        Node *promisingNode = selectPromisingNode(rootNode);

        // Phase 2 - Expansion
        if (promisingNode->getState()->getBoard()->checkStatus() == Board::IN_PROGRESS)
            expandNode(promisingNode);

        // Phase 3 - Simulation
        Node *nodeToExplore = promisingNode;
        if (!promisingNode->getChildArray()->empty()) {
            nodeToExplore = promisingNode->getRandomChildNode();
        }
        int playoutResult = simulateRandomPlayout(nodeToExplore);
        // Phase 4 - Update
        backPropagation(nodeToExplore, playoutResult);

        auto end = std::chrono::high_resolution_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        simulations++;
    } while (elapsed < duration);

    std::cout << "Simulations: " << simulations << "\n";

    Node *winnerNode = rootNode->getChildWithMaxScore();
    tree->setRoot(winnerNode);
    return winnerNode->getState()->getBoard();
}

int MonteCarloTreeSearch::getMillisForCurrentLevel() {
    return 2 * (this->level - 1) + 1;
}

Node *MonteCarloTreeSearch::selectPromisingNode(Node *rootNode) {
    Node *node = rootNode;
    while (!node->getChildArray()->empty()) {
        node = UCT::findBestNodeWithUCT(node);
    }

    return node;
}

void MonteCarloTreeSearch::expandNode(Node *node) {
    auto possibleStates = node->getState()->getAllPossibleStates();

    for (auto & possibleState : *possibleStates) {
        auto newNode = new Node(possibleState);
        newNode->setParent(node);
        newNode->getState()->setPlayerNo(node->getState()->getOpponent());
        node->getChildArray()->push_back(newNode);
    }
}

int MonteCarloTreeSearch::simulateRandomPlayout(Node *node) {
    Node *tempNode = new Node(node);
    State *tempState = tempNode->getState();
    int boardStatus = tempState->getBoard()->checkStatus();

    if (boardStatus == opponent) {
        tempNode->getParent()->getState()->setWinScore(INT_MIN);
        return boardStatus;
    }
    while (boardStatus == Board::IN_PROGRESS) {
        tempState->togglePlayer();
        tempState->randomPlay();
        boardStatus = tempState->getBoard()->checkStatus();
    }

    return boardStatus;
}

void MonteCarloTreeSearch::backPropagation(Node *nodeToExplore, int playerNo) {
    Node *tempNode = nodeToExplore;
    while (tempNode != nullptr) {
        tempNode->getState()->incrementVisit();
        if (tempNode->getState()->getPlayerNo() == playerNo)
            tempNode->getState()->addScore(WIN_SCORE);
        tempNode = tempNode->getParent();
    }
}

void MonteCarloTreeSearch::setLevel(int i) {
    level = i;
}
