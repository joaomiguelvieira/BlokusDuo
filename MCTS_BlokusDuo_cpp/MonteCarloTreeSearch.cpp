//
// Created by joaovieira on 12/25/19.
//

#include <chrono>
#include "MonteCarloTreeSearch.h"
#include "UCT.h"
#include <climits>
#include <iostream>

MonteCarloTreeSearch::MonteCarloTreeSearch(int moveDurationMillis) {
    this->moveDurationMillis = moveDurationMillis;
    this->gameTree = new Tree();
    this->gameTree->getRoot()->getState()->setOpponent(new Player);
    this->gameTree->getRoot()->getState()->setPlayer(new Player());
}

MonteCarloTreeSearch::~MonteCarloTreeSearch() {
    delete gameTree;
}

int MonteCarloTreeSearch::checkStatus() {
    return gameTree->getRoot()->getState()->checkStatus();
}

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
        node->getChildArray()->push_back(newNode);
    }

    delete possibleStates;
}

int MonteCarloTreeSearch::simulateRandomPlayout(Node *node) {
    Node *tempNode = new Node(node);
    State *tempState = tempNode->getState();
    int status = tempState->checkStatus();

    auto opponent = gameTree->getRoot()->getState()->getPlayer();
    if (status == opponent->getPlayerId()) {
        tempNode->getParent()->getState()->setWinScore(INT_MIN);
        //delete tempNode
        return status;
    }
    while (status == State::IN_PROGRESS) {
        tempState->togglePlayer();
        tempState->randomPlay();
        status = tempState->checkStatus();
    }

    //delete tempNode;

    return status;
}

void MonteCarloTreeSearch::backPropagation(Node *nodeToExplore, int playerId) {
    Node *tempNode = nodeToExplore;
    while (tempNode != nullptr) {
        tempNode->getState()->incrementVisit();
        if (tempNode->getState()->getPlayer()->getPlayerId() == playerId)
            tempNode->getState()->addScore(WIN_SCORE);
        tempNode = tempNode->getParent();
    }
}

// TODO optimize does not need to expand node
void MonteCarloTreeSearch::performNextMove(Move *move) {
    if (gameTree->getRoot()->getChildArray()->empty())
        expandNode(gameTree->getRoot());

    for (auto & child : *gameTree->getRoot()->getChildArray()) {
        if (Move::isEqual(child->getState()->getMove(), move)) {
            gameTree->setRoot(child);

            return;
        }
    }

    std::cout << "ERROR! Move could not be predicted!\n";
    exit(-1);
}

void MonteCarloTreeSearch::printStatus() {
    auto status = checkStatus();

    if (checkStatus() == State::IN_PROGRESS)
        std::cout << "Status: in progress...\n";
    else if (checkStatus() == State::DRAW)
        std::cout << "Status: game draw.\n";
    else
        std::cout << "Status: player " << status << " wins!\n";
}
