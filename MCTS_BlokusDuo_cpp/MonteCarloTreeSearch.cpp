//
// Created by joaovieira on 12/25/19.
//

#include <chrono>
#include "MonteCarloTreeSearch.h"
#include "UCT.h"
#include <iostream>
#include <cfloat>

MonteCarloTreeSearch::MonteCarloTreeSearch(int moveDurationMillis, bool exch_players) {
    this->moveDurationMillis = moveDurationMillis;
    this->gameTree = new Tree();
    if (exch_players) {
        this->gameTree->getRoot()->getState()->setPlayer(new Player());
        this->gameTree->getRoot()->getState()->setOpponent(new Player());
    } else {
        this->gameTree->getRoot()->getState()->setOpponent(new Player());
        this->gameTree->getRoot()->getState()->setPlayer(new Player());
    }
}

MonteCarloTreeSearch::~MonteCarloTreeSearch() {
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

        int playScore = 0;
        int playResult = simulateRandomPlay(nodeToExplore, &playScore);

        // update
        backPropagation(nodeToExplore, playResult, playScore);

        auto end = std::chrono::high_resolution_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    } while (elapsed < moveDurationMillis);

    auto winnerNode = gameTree->getRoot()->getChildWithMaxScore();
    return Move::moveToString(winnerNode->getState()->getMove());
}

Node *MonteCarloTreeSearch::selectPromisingNode(Node *rootNode) {
    Node *node = rootNode;
    while (!node->getChildArray()->empty())
        node = UCT::findBestNodeWithUCT(node);

    return node;
}

void MonteCarloTreeSearch::expandNode(Node *node) {
    if (!node->getState()->getOpponent()->getQuited()) {
        // calculate all valid moves
        std::list<std::shared_ptr<Move>> *possibleMoves = node->getState()->getPossibleMoves();

        if (!possibleMoves) {
            if (node->getState()->getMovesPlayed() < 4)
                possibleMoves = node->getState()->getBoard()->getAllValidMoves(node->getState()->getOpponent());
            else
                possibleMoves = node->getState()->getBoard()->getAllValidMoves(node->getState()->getOpponent(),
                                                                               node->getParent()->getParent()->getState()->getPossibleMoves(),
                                                                               node->getParent()->getState()->getMove(),
                                                                               node->getParent()->getParent()->getState()->getBoard());
        }

        node->getState()->setPossibleMoves(possibleMoves);

        for (const auto& possibleMove : *possibleMoves) {
            // create new state for each valid move
            auto newState = new State(node->getState()->getBoard());
            newState->setPlayer(new Player(node->getState()->getOpponent(), possibleMove->getGamePiece()));
            newState->setOpponent(new Player(node->getState()->getPlayer()));
            newState->setMove(possibleMove);
            newState->getBoard()->performMove(newState->getPlayer(), possibleMove);
            newState->setMovesPlayed(node->getState()->getMovesPlayed() + 1);

            auto newNode = new Node(newState);
            newNode->setParent(node);
            node->getChildArray()->push_back(newNode);
        }
    }

    // create quit state
    auto newState = new State(node->getState()->getBoard());
    newState->setPlayer(new Player(node->getState()->getOpponent()));
    newState->setOpponent(new Player(node->getState()->getPlayer()));
    newState->getPlayer()->setQuited(true);
    newState->setMovesPlayed(node->getState()->getMovesPlayed() + 1);

    auto newNode = new Node(newState);
    newNode->setParent(node);
    node->getChildArray()->push_back(newNode);
}

int MonteCarloTreeSearch::simulateRandomPlay(Node *node, int *score) {
    auto actualNode = node;
    int status = actualNode->getState()->checkStatus();

    if (status == gameTree->getRoot()->getState()->getPlayer()->getPlayerId()) {
        actualNode->getParent()->getState()->setWinScore(-DBL_MAX);
        *score = actualNode->getState()->getScore();
        return status;
    }

    while (status == State::IN_PROGRESS) {
        auto newNode = new Node(new State(actualNode->getState()->getBoard()));
        newNode->getState()->setMovesPlayed(actualNode->getState()->getMovesPlayed() + 1);
        newNode->getState()->setOpponent(new Player(actualNode->getState()->getPlayer()));
        newNode->setParent(actualNode);

        std::list<std::shared_ptr<Move>> *possibleMoves;
        if (actualNode->getState()->getMovesPlayed() < 4)
            possibleMoves = actualNode->getState()->getBoard()->getAllValidMoves(actualNode->getState()->getOpponent());
        else
            possibleMoves = actualNode->getState()->getBoard()->getAllValidMoves(actualNode->getState()->getOpponent(),
                                                                                 actualNode->getParent()->getParent()->getState()->getPossibleMoves(),
                                                                                 actualNode->getParent()->getState()->getMove(),
                                                                                 actualNode->getParent()->getParent()->getState()->getBoard());

        actualNode->getState()->setPossibleMoves(possibleMoves);

        if (possibleMoves->empty()) {
            newNode->getState()->setPlayer(new Player(actualNode->getState()->getOpponent()));
            newNode->getState()->getPlayer()->setQuited(true);
        } else {
            srand((unsigned int) time(nullptr));
            auto it = possibleMoves->begin();
            std::advance(it, rand() % possibleMoves->size());
            auto moveToPerform = *it;
            newNode->getState()->setPlayer(
                    new Player(actualNode->getState()->getOpponent(), moveToPerform->getGamePiece()));
            newNode->getState()->getBoard()->performMove(newNode->getState()->getPlayer(), moveToPerform);
            newNode->getState()->setMove(moveToPerform);
        }

        status = newNode->getState()->checkStatus();
        //actualNode->getParent()->getChildArray()->push_back(newNode);
        actualNode = newNode;
    }

    *score = actualNode->getState()->getScore();

    while (actualNode != node) {
        auto parent = actualNode->getParent();
        delete actualNode;
        actualNode = parent;
    }

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
int MonteCarloTreeSearch::performNextMove(const std::string &move) {
    if (gameTree->getRoot()->getChildArray()->empty())
        expandNode(gameTree->getRoot());

    for (auto &child : *gameTree->getRoot()->getChildArray()) {
        if (Move::moveToString(child->getState()->getMove()) == move) {
            gameTree->setRoot(child);

            return 0;
        }
    }

    std::cout << "ERROR! Move could not be predicted! Doing nothing!" << std::endl;

    return -1;
}

void MonteCarloTreeSearch::printValidMoves() {
    auto node = gameTree->getRoot();

    std::list<std::shared_ptr<Move>> *possibleMoves;

    if (node->getState()->getMovesPlayed() < 4)
        possibleMoves = node->getState()->getBoard()->getAllValidMoves(node->getState()->getOpponent());
    else
        possibleMoves = node->getState()->getBoard()->getAllValidMoves(node->getState()->getOpponent(),
                                                                       node->getParent()->getParent()->getState()->getPossibleMoves(),
                                                                       node->getParent()->getState()->getMove(),
                                                                       node->getParent()->getParent()->getState()->getBoard());

    std::cout << "Here's all valid moves: ";
    for (const auto& validMove : *possibleMoves)
        std::cout << Move::moveToString(validMove) << " ";
    std::cout << std::endl;
}

void MonteCarloTreeSearch::printStatus() {
    auto actualState = gameTree->getRoot()->getState();
    auto player1 = actualState->getPlayer()->getPlayerId() == 1 ? actualState->getPlayer() : actualState->getOpponent();
    auto player2 = actualState->getPlayer()->getPlayerId() == 2 ? actualState->getPlayer() : actualState->getOpponent();

    std::cout << "----------------- Available Tiles -----------------" << std::endl;
    std::cout << player1->toString() << std::endl;
    std::cout << player2->toString() << std::endl;

    std::cout << "---------------------- Board ----------------------" << std::endl;
    std::cout << actualState->getBoard()->toString() << std::endl;

    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "Round " << actualState->getMovesPlayed() << std::endl;
    std::cout << "Player " << std::to_string(actualState->getOpponent()->getPlayerId()) << ": ";
}

void MonteCarloTreeSearch::printMove(bool printQuit) {
    auto actualState = gameTree->getRoot()->getState();
    auto move = Move::moveToString(actualState->getMove());
    if (move != "0000" || printQuit)
        std::cout << move << std::endl;
}

Tree *MonteCarloTreeSearch::getGameTree() {
    return gameTree;
}
