//
// Created by joaovieira on 12/25/19.
//

#include "State.h"
#include "Move.h"
#include <cstdlib>
#include <cmath>
#include <cfloat>

State::State() {
    board = new Board();
}

State::State(Board *board) {
    this->board = new Board(board);
}

State::~State() {
    delete board;
    delete player;
    delete opponent;
    delete possibleMoves;
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

Player *State::getOpponent() {
    return opponent;
}

std::shared_ptr<Move> State::getMove() {
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

void State::setMove(std::shared_ptr<Move> move) {
    this->move = move;
}

int State::getScore() {
    return abs(player->getScore() - opponent->getScore());
}

double State::getStateViability(State *previousState) {
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

    // number of anchors
    double anchorsContribution = move->getGamePiece()->getAnchors()->size();
    anchorsContribution /= 5;

    // proximity to opponent's move
    double distanceOpponent = 338;
    if (previousState != nullptr && previousState->getMove() != nullptr) {
        distanceOpponent = pow(previousState->getMove()->getCenter()->getX() - move->getCenter()->getX(), 2) +
                           pow(previousState->getMove()->getCenter()->getY() - move->getCenter()->getY(), 2);
    }
    double proximityOpponent = 338 - distanceOpponent;
    double proximityOpponentContribution = 0;
    if (proximityOpponent > 0)
        proximityOpponentContribution = proximityOpponent / 338;

    return 16 * visitsContribution +
           4 * squaresContribution +
           4 * anchorsContribution +
           2 * proximityOpponentContribution +
           proximityDiagContribution;
}

void State::incrementWinCount() {
    winCount++;
}

double State::getWinCount() {
    return winCount;
}

int State::getMovesPlayed() {
    return movesPlayed;
}

void State::setMovesPlayed(int movesPlayed) {
    this->movesPlayed = movesPlayed;
}

void State::setPossibleMoves(std::list<std::shared_ptr<Move>> *possibleMoves) {
    this->possibleMoves = possibleMoves;
}

std::list<std::shared_ptr<Move>> *State::getPossibleMoves() {
    return possibleMoves;
}
