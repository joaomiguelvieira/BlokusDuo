//
// Created by joaovieira on 12/24/19.
//

#include <iostream>
#include "Board.h"

Board::Board() {
    board = new int*[DEFAULT_BOARD_SIZE];
    for (int i = 0; i < DEFAULT_BOARD_SIZE; ++i) {
        board[i] = new int[DEFAULT_BOARD_SIZE];

        for (int j = 0; j < DEFAULT_BOARD_SIZE; ++j) {
            board[i][j] = 0;
        }
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

void Board::printBoard() {
    for (int i = 0; i < size[0]; ++i) {
        for (int j = 0; j < size[1]; ++j) {
            std::cout << (board[j][i] == 0 ? ' ' : board[j][i]);
        }

        std::cout << "\n";
    }
}

Board::Board(Board *board) {
    this->board = new int*[board->size[0]];
    for (int i = 0; i < board->size[0]; ++i) {
        this->board[i] = new int[board->size[1]];

        for (int j = 0; j < board->size[1]; ++j) {
            this->board[i][j] = board->board[i][j];
        }
    }

    this->size[0] = board->size[0];
    this->size[1] = board->size[1];
}

void Board::performMove(Player *player, Move *move) {
    for (auto & square : *move->getGamePiece()->getSquares())
        board[square->getX() + move->getCenter()->getX()][square->getY() + move->getCenter()->getY()] = player->getPlayerId();
}
