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

std::list<Position *> *Board::getAllAnchors(int playerId) {
    auto anchors = new std::list<Position *>();

    // first or second moves
    if (!board[4][4])
        anchors->push_back(new Position(4, 4));

    if (!board[9][9])
        anchors->push_back(new Position(9, 9));

    if (!anchors->empty())
        return anchors;

    // any other moves
    for (int i = 0; i < size[0]; ++i) {
        for (int j = 0; j < size[1]; ++j) {
            if (!board[i][j] && hasCornerContact(i, j, playerId) && !hasEdgeContact(i, j, playerId))
                anchors->push_back(new Position(i, j));
        }
    }

    return anchors;
}

bool Board::hasCornerContact(int x, int y, int playerId) {
    return (x - 1 >= 0 && y - 1 >= 0 && board[x - 1][y - 1] == playerId) ||
           (x - 1 >= 0 && y + 1 < size[1] && board[x - 1][y + 1] == playerId) ||
           (x + 1 < size[0] && y - 1 >= 0 && board[x + 1][y - 1] == playerId) ||
           (x + 1 < size[0] && y + 1 < size[1] && board[x + 1][y + 1] == playerId);

}

bool Board::hasEdgeContact(int x, int y, int playerId) {
    return (x - 1 >= 0 && board[x - 1][y] == playerId) || (x + 1 < size[0] && board[x + 1][y] == playerId) ||
           (y - 1 >= 0 && board[x][y - 1] == playerId) || (y + 1 < size[1] && board[x][y + 1] == playerId);

}
