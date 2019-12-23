//
// Created by João Vieira on 22/12/2019.
//

#include "State.h"
#include "Board.h"
#include <climits>

State::State() {
    board = new Board();
}

void State::setBoard(Board *pBoard) {
    board = pBoard;
}

void State::setPlayerNo(int i) {
    playerNo = i;
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

State::State(State *state) {
    board = new Board(state->getBoard());
    playerNo = state->getPlayerNo();
    visitCount = state->getVisitCount();
    winScore = state->getVisitCount();
}

int State::getPlayerNo() {
    return playerNo;
}

void State::setWinScore(int i) {
    winScore = i;
}

void State::togglePlayer() {
    playerNo = 3 - playerNo;
}

void State::randomPlay() {
    auto availablePositions = board->getEmptyPositions();
    int totalPossibilities = availablePositions->size();

    srand(time(nullptr));
    int selectRandom = rand() % totalPossibilities;

    auto it = availablePositions->begin();
    std::advance(it, selectRandom);
    board->performMove(playerNo, *it);
}

void State::incrementVisit() {
    visitCount++;
}

void State::addScore(double i) {
    if (winScore != INT_MIN)
        winScore += i;
}

std::list<State *> *State::getAllPossibleStates() {
    auto possibleStates = new std::list<State *>();
    auto availablePositions = board->getEmptyPositions();
    for (auto & availablePosition : *availablePositions) {
        auto newState = new State(board);
        newState->setPlayerNo(3 - playerNo);
        newState->getBoard()->performMove(newState->getPlayerNo(), availablePosition);
        possibleStates->push_back(newState);
    }

    return possibleStates;
}

State::State(Board *board) {
    this->board = new Board(board);
}

int State::getOpponent() {
    return 3 - playerNo;
}
