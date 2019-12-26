//
// Created by joaovieira on 12/25/19.
//

#include <cfloat>
#include "State.h"
#include "Move.h"

State::State() {
    board = new Board();
    player = nullptr;
    opponent = nullptr;
    visitCount = 0;
    winScore = 0;
}

State::State(State *state) {
    board = new Board(state->getBoard());
    player = state->getPlayer();
    opponent = state->getOpponent();
    visitCount = state->getVisitCount();
    winScore = state->getVisitCount();
}

State::State(Board *board) {
    this->board = new Board(board);
}

State::~State() {
    delete board;
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
    if (winScore != INT_MIN)
        score += score;
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
    auto possibleMoves = Move::getAllValidMoves(board, player);
    for (auto & possibleMove : *possibleMoves) {
        auto newState = new State(board);
        newState->setPlayer(new Player(opponent));
        newState->setOpponent(new Player(player, possibleMove->getGamePiece()))
        newState->getBoard()->performMove(newState->player, possibleMove);
        possibleStates->push_back(newState);
    }

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
