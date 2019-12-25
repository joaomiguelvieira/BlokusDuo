//
// Created by joaovieira on 12/24/19.
//

#include "Board.h"

Board::Board() {
    board = new int*[DEFAULT_BOARD_SIZE];
    for (int i = 0; i < DEFAULT_BOARD_SIZE; ++i) {
        board[i] = new int[DEFAULT_BOARD_SIZE];
    }
}

Board::~Board() {
    for (int i = 0; i < DEFAULT_BOARD_SIZE; ++i) {
        delete [] board[i];
    }
    delete [] board;
}

int **Board::getBoard() {
    return board;
}

int *Board::getSize() {
    return size;
}
