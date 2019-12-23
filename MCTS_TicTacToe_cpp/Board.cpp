//
// Created by João Vieira on 22/12/2019.
//

#include <iostream>
#include "Board.h"
#include "Position.h"

Board::Board() {
    boardValues = new int*[DEFAULT_BOARD_SIZE];
    for (int i = 0; i < DEFAULT_BOARD_SIZE; ++i) {
        boardValues[i] = new int[DEFAULT_BOARD_SIZE];

        for (int j = 0; j < DEFAULT_BOARD_SIZE; ++j) {
            boardValues[i][j] = 0;
        }
    }

    totalMoves = 0;
}

int Board::checkStatus() {
    int maxIndex = DEFAULT_BOARD_SIZE - 1;
    int diag1[DEFAULT_BOARD_SIZE], diag2[DEFAULT_BOARD_SIZE];

    for (int i = 0; i < DEFAULT_BOARD_SIZE; i++) {
        int *row = boardValues[i];
        int col[DEFAULT_BOARD_SIZE];
        for (int j = 0; j < DEFAULT_BOARD_SIZE; j++) {
            col[j] = boardValues[j][i];
        }

        int checkRowForWin = checkForWin(row);
        if(checkRowForWin!=0)
            return checkRowForWin;

        int checkColForWin = checkForWin(col);
        if(checkColForWin!=0)
            return checkColForWin;

        diag1[i] = boardValues[i][i];
        diag2[i] = boardValues[maxIndex - i][i];
    }

    int checkDia1gForWin = checkForWin(diag1);
    if(checkDia1gForWin!=0)
        return checkDia1gForWin;

    int checkDiag2ForWin = checkForWin(diag2);
    if(checkDiag2ForWin!=0)
        return checkDiag2ForWin;

    if (!getEmptyPositions()->empty())
        return IN_PROGRESS;
    else
        return DRAW;
}

Board::Board(Board *board) {
    boardValues = new int*[DEFAULT_BOARD_SIZE];
    for (int i = 0; i < DEFAULT_BOARD_SIZE; ++i) {
        boardValues[i] = new int[DEFAULT_BOARD_SIZE];

        for (int j = 0; j < DEFAULT_BOARD_SIZE; ++j) {
            boardValues[i][j] = 0;
        }
    }

    for (int i = 0; i < DEFAULT_BOARD_SIZE; ++i) {
        for (int j = 0; j < DEFAULT_BOARD_SIZE; ++j) {
            boardValues[i][j] = board->getBoardValues()[i][j];
        }
    }

    totalMoves = board->getTotalMoves();
}

int **Board::getBoardValues() {
    return boardValues;
}

int Board::checkForWin(const int *row) {
    bool isEqual = true;
    int previous = row[0];
    for (int i = 0; i < DEFAULT_BOARD_SIZE; i++) {
        if (previous != row[i]) {
            isEqual = false;
            break;
        }
        previous = row[i];
    }
    if(isEqual)
        return previous;
    else
        return 0;
}

std::list<Position *> *Board::getEmptyPositions() {
    auto emptyPositions = new std::list<Position *>();

    for (int i = 0; i < DEFAULT_BOARD_SIZE; ++i) {
        for (int j = 0; j < DEFAULT_BOARD_SIZE; ++j) {
            if (!boardValues[i][j])
                emptyPositions->push_back(new Position(i, j));
        }
    }

    return emptyPositions;
}

void Board::performMove(int player, Position *p) {
    totalMoves++;
    boardValues[p->getX()][p->getY()] = player;
}

int Board::getTotalMoves() {
    return totalMoves;
}

void Board::printBoard() {
    for (int i = 0; i < DEFAULT_BOARD_SIZE; ++i) {
        for (int j = 0; j < DEFAULT_BOARD_SIZE; ++j) {
            std::cout << boardValues[i][j] << " ";
        }

        std::cout << "\n";
    }
}

void Board::printStatus() {
    switch (checkStatus()) {
        case P1:
            std::cout << "Player 1 wins\n";
            break;
        case P2:
            std::cout << "Player 2 wins\n";
            break;
        case DRAW:
            std::cout << "Game Draw\n";
            break;
        default:
            std::cout << "Game In Progress\n";
            break;
    }
}
