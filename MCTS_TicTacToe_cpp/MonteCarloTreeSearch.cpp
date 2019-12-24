//
// Created by João Vieira on 22/12/2019.
//

#include "MonteCarloTreeSearch.h"
#include "Tree.h"
#include "UCT.h"
#include <chrono>
#include <iostream>
#include <climits>

MonteCarloTreeSearch::MonteCarloTreeSearch(Board *initialBoard, int initialPlayer) {
    level = 3;

    gameTree = new Tree();
    gameTree->getRoot()->getState()->setBoard(initialBoard);
    gameTree->getRoot()->getState()->setPlayerNo(3 - initialPlayer);
}

Board *MonteCarloTreeSearch::findNextMove() {
    auto start = std::chrono::high_resolution_clock::now();
    long elapsed;
    long duration = 60 * getMillisForCurrentLevel();

    do {
        // Phase 1 - Selection
        Node *promisingNode = selectPromisingNode(gameTree->getRoot());

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
    } while (elapsed < duration);

    //std::cout << "Simulations: " << gameTree->getRoot()->getState()->getVisitCount() << "\n";

    Node *winnerNode = gameTree->getRoot()->getChildWithMaxScore();
    gameTree->setRoot(winnerNode);
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

    delete possibleStates;
}

int MonteCarloTreeSearch::simulateRandomPlayout(Node *node) {
    Node *tempNode = new Node(node);
    State *tempState = tempNode->getState();
    int boardStatus = tempState->getBoard()->checkStatus();

    auto opponent = gameTree->getRoot()->getState()->getPlayerNo();
    if (boardStatus == opponent) {
        tempNode->getParent()->getState()->setWinScore(INT_MIN);
        delete tempNode;
        return boardStatus;
    }
    while (boardStatus == Board::IN_PROGRESS) {
        tempState->togglePlayer();
        tempState->randomPlay();
        boardStatus = tempState->getBoard()->checkStatus();
    }

    delete tempNode;

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

MonteCarloTreeSearch::~MonteCarloTreeSearch() {
    delete gameTree;
}
