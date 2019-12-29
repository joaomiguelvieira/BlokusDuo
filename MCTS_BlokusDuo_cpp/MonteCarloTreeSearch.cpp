//
// Created by joaovieira on 12/25/19.
//

#include <chrono>
#include "MonteCarloTreeSearch.h"
#include "UCT.h"
#include <climits>
#include <iostream>
#include <algorithm>
#include <cfloat>

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

std::string MonteCarloTreeSearch::findNextMove() {
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

        int playoutScore = 0;
        int playoutResult = simulateRandomPlayout(nodeToExplore, &playoutScore);

        // update
        backPropagation(nodeToExplore, playoutResult, playoutScore);

        auto end = std::chrono::high_resolution_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    } while (elapsed < moveDurationMillis);

    std::cout << "Simulations: " << gameTree->getRoot()->getState()->getVisitCount() << "\n";

    auto winnerNode = gameTree->getRoot()->getChildWithMaxScore();
    return Move::moveToString(winnerNode->getState()->getMove());
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

int MonteCarloTreeSearch::simulateRandomPlayout(Node *node, int *score) {
    Node *tempNode = new Node(node);
    State *tempState = tempNode->getState();
    int status = tempState->checkStatus();

    auto opponent = gameTree->getRoot()->getState()->getPlayer();
    if (status == opponent->getPlayerId()) {
        tempNode->getParent()->getState()->setWinScore(-DBL_MAX);
        delete tempNode;
        return status;
    }
    while (status == State::IN_PROGRESS) {
        tempState->togglePlayer();
        tempState->randomPlay();
        status = tempState->checkStatus();
    }

    *score = tempState->getScore();

    delete tempNode;

    return status;
}

void MonteCarloTreeSearch::backPropagation(Node *nodeToExplore, int playerId, int winScore) {
    Node *tempNode = nodeToExplore;
    while (tempNode != nullptr) {
        tempNode->getState()->incrementVisit();
        if (tempNode->getState()->getPlayer()->getPlayerId() == playerId) {
            tempNode->getState()->addScore(winScore);
            tempNode->getState()->incrementWinCount();
        }
        tempNode = tempNode->getParent();
    }
}

// TODO optimize does not need to expand node
int MonteCarloTreeSearch::performNextMove(const std::string& move) {
    if (gameTree->getRoot()->getChildArray()->empty())
        expandNode(gameTree->getRoot());

    for (auto & child : *gameTree->getRoot()->getChildArray()) {
        if (Move::moveToString(child->getState()->getMove()) == move) {
            gameTree->setRoot(child);

            return 0;
        }
    }

    std::cout << "ERROR! Move could not be predicted! Doing nothing!" << std::endl;

    return -1;
}

void MonteCarloTreeSearch::printValidMoves() {
    if (gameTree->getRoot()->getChildArray()->empty())
        expandNode(gameTree->getRoot());

    std::cout << "Here's all valid moves: ";
    for (auto & child : *gameTree->getRoot()->getChildArray())
        std::cout << Move::moveToString(child->getState()->getMove()) << " ";
    std::cout << std::endl;
}

void MonteCarloTreeSearch::printStatus() {
    auto actualState = gameTree->getRoot()->getState();

    auto player1 = actualState->getPlayer()->getPlayerId() == 1 ? actualState->getPlayer() : actualState->getOpponent();
    auto player2 = actualState->getPlayer()->getPlayerId() == 2 ? actualState->getPlayer() : actualState->getOpponent();

    std::cout << "----------------- Available Tiles -----------------" << std::endl;

    std::vector<char> allGamePieces = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u'};
    std::cout << "          ";
    for (auto & gamePiece : allGamePieces)
        std::cout << gamePiece << " ";
    std::cout << std::endl;

    std::list<char> remainingGamePieces1;
    for (auto & remainingGamePiece : *player1->getRemainingGamePieces())
        remainingGamePieces1.push_back((*remainingGamePiece)[0]->getCodeName());
    std::cout << "Player 1: ";
    for (auto & gamePiece : allGamePieces) {
        if (std::find(remainingGamePieces1.begin(), remainingGamePieces1.end(), gamePiece) != remainingGamePieces1.end())
            std::cout << "1 ";
        else
            std::cout << "0 ";
    }
    std::cout << std::endl;

    std::list<char> remainingGamePieces2;
    for (auto & remainingGamePiece : *player2->getRemainingGamePieces())
        remainingGamePieces2.push_back((*remainingGamePiece)[0]->getCodeName());
    std::cout << "Player 2: ";
    for (auto & gamePiece : allGamePieces) {
        if (std::find(remainingGamePieces2.begin(), remainingGamePieces2.end(), gamePiece) != remainingGamePieces2.end())
            std::cout << "1 ";
        else
            std::cout << "0 ";
    }
    std::cout << std::endl;

    std::cout << "---------------------------------------------------" << std::endl;

    if (player1->getScore() > player2->getScore())
        std::cout << "Player 2 is winning!" << std::endl;
    else if (player1->getScore() < player2->getScore())
        std::cout << "Player 1 is winning!" << std::endl;
    else
        std::cout << "Game is a draw!" << std::endl;

    std::cout << "---------------------- Board ----------------------" << std::endl;

    actualState->getBoard()->printBoard();

    std::cout << "---------------------------------------------------" << std::endl;

    std::cout << "Player " << unsigned(actualState->getOpponent()->getPlayerId()) << ": ";

    return;

    std::cout << "================= PLAYER " << unsigned(actualState->getPlayer()->getPlayerId()) << "'S TURN =================\n";

    auto move = Move::moveToString(actualState->getMove());
    std::cout << "Move: " << Move::moveToString(actualState->getMove()) << std::endl;

    if (player1->getQuited())
        std::cout << "Player 1 has quited with ";
    else
        std::cout << "Player 1 is playing with ";
    std::cout << player1->getRemainingGamePieces()->size() << " remaining game pieces." << std::endl;

    if (player2->getQuited())
        std::cout << "Player 2 has quited with ";
    else
        std::cout << "Player 2 is playing with ";
    std::cout << player2->getRemainingGamePieces()->size() << " remaining game pieces." << std::endl;

    std::cout << "Actual board:\n";
    actualState->getBoard()->printBoard();

    if (player1->getQuited() && player2->getQuited()) {
        auto score = player1->getScore() - player2->getScore();

        if (score != 0) {
            if (score < 0)
                std::cout << "Player 1 wins with " << -score << " points!" << std::endl;
            else
                std::cout << "Player 2 wins with " << score << "points!" << std::endl;
        }
        else {
            std::cout << "Game draw" << std::endl;
        }
    }
}

void MonteCarloTreeSearch::printMove() {
    auto actualState = gameTree->getRoot()->getState();
    auto move = Move::moveToString(actualState->getMove());
    if (move != "0000")
        std::cout << move << std::endl;
}
