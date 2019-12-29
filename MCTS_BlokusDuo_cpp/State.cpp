//
// Created by joaovieira on 12/25/19.
//

#include <climits>
#include "State.h"
#include "Move.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cfloat>

State::State() {
    board = new Board();
}

State::State(State *state) {
    board = new Board(state->board);
    player = new Player(state->player);
    opponent = new Player(state->opponent);
    visitCount = state->visitCount;
    winScore = state->winScore;
    winCount = state->winCount;
}

State::State(Board *board) {
    this->board = new Board(board);
}

State::~State() {
    delete board;
    delete player;
    delete move;
    delete opponent;
}

// TODO optimize setBoard
void State::setBoard(Board *board) {
    delete this->board;

    this->board = board;
}

void State::setPlayer(Player *player) {
    this->player = player;
}

int State::getVisitCount() {
    return visitCount;
}

Board *State::getBoard() {
    return board;
}

double State::getWinScore() {
    return winScore;
}

Player *State::getPlayer() {
    return player;
}

void State::setWinScore(double winScore) {
    this->winScore = winScore;
}

void State::incrementVisit() {
    visitCount++;
}

void State::addScore(double score) {
    if (winScore != -DBL_MAX)
        winScore += score;
}

void State::setOpponent(Player *opponent) {
    this->opponent = opponent;
}

void State::togglePlayer() {
    auto tempPlayer = player;
    player = opponent;
    opponent = tempPlayer;
}

Player *State::getOpponent() {
    return opponent;
}

std::list<State *> *State::getAllPossibleStates() {
    auto possibleStates = new std::list<State *>();

    if (!opponent->getQuited()) {
        auto possibleMoves = board->getAllValidMoves(opponent);
        for (auto & possibleMove : *possibleMoves) {
            auto newState = new State(board);
            newState->setPlayer(new Player(opponent, possibleMove->getGamePiece()));
            newState->setOpponent(new Player(player));
            newState->setMove(possibleMove);
            newState->getBoard()->performMove(newState->player, possibleMove);
            possibleStates->push_back(newState);
        }

        delete possibleMoves;
    }

    // add the quit state
    auto newState = new State(board);
    newState->setPlayer(new Player(opponent));
    newState->setOpponent(new Player(player));
    newState->getPlayer()->setQuited(true);
    possibleStates->push_back(newState);

    return possibleStates;
}

Move *State::getMove() {
    return move;
}

int State::checkStatus() {
    if (player->getQuited() && opponent->getQuited()) {
        auto scoreDiff = player->getScore() - opponent->getScore();

        if (scoreDiff < 0)
            return player->getPlayerId();
        else if (scoreDiff > 0)
            return opponent->getPlayerId();
        else
            return DRAW;
    }

    return IN_PROGRESS;
}

void State::setMove(Move *move) {
    this->move = move;
}

void State::randomPlay() {
    auto possibleMoves = board->getAllValidMoves(player);
    int totalPossibilities = (int) possibleMoves->size();

    if (totalPossibilities == 0) {
        player->setQuited(true);
        delete possibleMoves;
        return;
    }

    srand((unsigned int) time(nullptr));
    int selectRandom = rand() % totalPossibilities;

    auto it = possibleMoves->begin();
    std::advance(it, selectRandom);
    auto moveToPerform = *it;
    board->performMove(player, moveToPerform);
    auto pieceToRemove = moveToPerform->getGamePiece();
    player->getRemainingGamePieces()->remove_if([pieceToRemove](std::vector<GamePiece *> *gamePiece)->bool{return (*gamePiece)[0]->getCodeName() == pieceToRemove->getCodeName();});

    for (auto & possibleMove : *possibleMoves)
        delete possibleMove;
    delete possibleMoves;
}

int State::getScore() {
    return abs(player->getScore() - opponent->getScore());
}

double State::getStateViability() {
    // if quit then node is not viable
    if (Move::moveToString(move) == "0000")
        return -DBL_MAX;

    // proximity to diagonal
    double distanceDiag = 0.7 * abs(move->getCenter()->getX() + move->getCenter()->getY() - 13);
    double proximityDiag = 9.1 - distanceDiag;
    double proximityDiagContribution = 0;
    if (proximityDiag > 0)
        proximityDiagContribution = proximityDiag / 9.9;

    // number of visits
    double visitsContribution = 0;
    if (visitCount > 10)
        visitsContribution = exp2(-1.0 / visitCount);

    // number of squares
    double squaresContribution = move->getGamePiece()->getSquares()->size();
    squaresContribution /= 5;

    double viability =
            8 * visitsContribution +
            2 * squaresContribution +
            proximityDiagContribution;

    return viability;
}

void State::incrementWinCount() {
    winCount++;
}

double State::getWinCount() {
    return winCount;
}
