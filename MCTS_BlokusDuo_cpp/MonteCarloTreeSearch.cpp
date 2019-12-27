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
    this->gamePieceSet1 = GamePiece::getInitialSetOfGamePieces();
    this->gameTree->getRoot()->getState()->setOpponent(new Player(gamePieceSet1));
    this->gamePieceSet2 = GamePiece::getInitialSetOfGamePieces();
    this->gameTree->getRoot()->getState()->setPlayer(new Player(gamePieceSet2));
}

MonteCarloTreeSearch::~MonteCarloTreeSearch() {
    for (auto & gamePiece : *gamePieceSet1) {
        for (auto & variant : *gamePiece)
            delete variant;
        delete gamePiece;
    }
    delete gamePieceSet1;

    for (auto & gamePiece : *gamePieceSet2) {
        for (auto & variant : *gamePiece)
            delete variant;
        delete gamePiece;
    }
    delete gamePieceSet2;

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

    std::cout << "Simulations: " << gameTree->getRoot()->getState()->getVisitCount() << "\n";

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
        delete tempNode;
        return status;
    }
    while (status == State::IN_PROGRESS) {
        tempState->togglePlayer();
        tempState->randomPlay();
        status = tempState->checkStatus();
    }

    delete tempNode;

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
    auto actualState = gameTree->getRoot()->getState();

    auto player1 = actualState->getPlayer()->getPlayerId() == 1 ? actualState->getPlayer() : actualState->getOpponent();
    auto player2 = actualState->getPlayer()->getPlayerId() == 2 ? actualState->getPlayer() : actualState->getOpponent();

    std::cout << "================= PLAYER " << unsigned(actualState->getPlayer()->getPlayerId()) << "'S TURN =================\n";

    if (player1->getQuited())
        std::cout << "Player 1 has quited with ";
    else
        std::cout << "Player 1 is playing with ";
    std::cout << player1->getRemainingGamePieces()->size() << " remaining game pieces.\n";

    if (player2->getQuited())
        std::cout << "Player 2 has quited with ";
    else
        std::cout << "Player 2 is playing with ";
    std::cout << player2->getRemainingGamePieces()->size() << " remaining game pieces.\n\n";

    std::cout << "Actual board:\n";
    actualState->getBoard()->printBoard();

    /*auto status = checkStatus();
    if (checkStatus() == State::IN_PROGRESS)
        std::cout << "Status: game in progress...\n";
    else if (checkStatus() == State::DRAW)
        std::cout << "Status: game draw.\n";
    else
        std::cout << "Status: player " << status << " wins!\n";*/
}
