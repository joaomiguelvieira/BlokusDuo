//
// Created by joaovieira on 12/24/19.
//

#include <iostream>
#include "Board.h"

Board::Board() {
    board = new uint8_t*[DEFAULT_BOARD_SIZE];
    for (int i = 0; i < DEFAULT_BOARD_SIZE; ++i) {
        board[i] = new uint8_t[DEFAULT_BOARD_SIZE];

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

uint8_t **Board::getBoard() {
    return board;
}

int *Board::getSize() {
    return size;
}

std::list<Position *> *Board::getAllAnchors(int playerId) {
    auto anchors = new std::list<Position *>();

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
    std::vector<char> axis = {'1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e'};
    std::cout << "  0 ";
    for (auto & tick : axis)
        std::cout << tick << " ";
    std::cout << "f" << std::endl;
    std::cout << "0 + + + + + + + + + + + + + + + +" << std::endl;
    for (int i = 0; i < size[0]; ++i) {
        std::cout << axis[i] << " + ";
        for (int j = 0; j < size[1]; ++j) {
            if (board[j][i] == 0)
                std::cout << "  ";
            else
                std::cout << unsigned(board[j][i]) << " ";
        }

        std::cout << "+" << std::endl;
    }
    std::cout << "f + + + + + + + + + + + + + + + +" << std::endl;
}

Board::Board(Board *board) {
    this->board = new uint8_t*[board->size[0]];
    for (int i = 0; i < board->size[0]; ++i) {
        this->board[i] = new uint8_t[board->size[1]];

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

bool Board::checkValidMove(Player *player, GamePiece *gamePiece, Position *center) {
    for (auto & square : *gamePiece->getSquares()) {
        auto x = square->getX() + center->getX();
        auto y = square->getY() + center->getY();

        // check for board limits
        if (x < 0 || x >= size[0] || y < 0 || y >= size[1])
            return false;

        // check for overlap
        if (board[x][y])
            return false;

        // check for edge contact
        if (hasEdgeContact(x, y, player->getPlayerId()))
            return false;
    }

    return true;
}

std::list<Move *> *Board::getAllValidMoves(Player *player) {
    auto validMoves = new std::list<Move *>();

    // all valid moves cover 5, 5
    if (!board[4][4]) {
        for (auto & gamePiece : *player->getRemainingGamePieces()) {
            for (auto & variant : *gamePiece) {
                for (auto & square : *variant->getSquares()) {
                    auto center = Position(4, 4);
                    center.subtract(square);

                    validMoves->push_back(new Move(variant, &center));
                }
            }
        }

        return validMoves;
    }

    // all valid moves cover a, a
    if (!board[9][9]) {
        for (auto & gamePiece : *player->getRemainingGamePieces()) {
            for (auto & variant : *gamePiece) {
                for (auto & square : *variant->getSquares()) {
                    auto center = Position(9, 9);
                    center.subtract(square);

                    validMoves->push_back(new Move(variant, &center));
                }
            }
        }

        return validMoves;
    }

    auto boardAnchors = getAllAnchors(player->getPlayerId());
    for (auto & boardAnchor : *boardAnchors) {
        for (auto & gamePiece : *player->getRemainingGamePieces()) {
            for (auto & variant : *gamePiece) {
                for (auto & anchor : *variant->getAnchors()) {
                    auto center = Position(boardAnchor);
                    center.subtract(anchor);

                    if (checkValidMove(player, variant, &center))
                        validMoves->push_back(new Move(variant, &center));
                }
            }
        }

        delete boardAnchor;
    }

    delete boardAnchors;

    return validMoves;
}
