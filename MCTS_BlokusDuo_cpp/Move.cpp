//
// Created by joaovieira on 12/24/19.
//

#include "Move.h"

Move::Move(GamePiece *gamePiece, Position *center, int transformation) {
    this->gamePiece = gamePiece;
    this->center = center;
    this->transformation = transformation;
}

// check for board limits, overlap and edge contact
bool Move::verifyValidMove(Board *board, Player *player, GamePiece *gamePiece, Position *center, int transformation) {
    auto tempGamePiece = gamePiece;
    if (transformation) {
        tempGamePiece = new GamePiece(gamePiece);
        tempGamePiece->transformPiece(transformation);
    }

    auto validMode = true;
    for (auto & square : *tempGamePiece->getSquares()) {
        auto x = square->getX() + center->getX();
        auto y = square->getY() + center->getY();

        // check for board limits
        if (x < 0 || x >= board->getSize()[0] || y < 0 || y >= board->getSize()[1]) {
            validMode = false;
            break;
        }

        // check for overlap
        if (board->getBoard()[x][y] != 0) {
            validMode = false;
            break;
        }

        // check for edge contact
        if ((x - 1 >= 0 && x - 1 < board->getSize()[0] && board->getBoard()[x - 1][y] == player->getPlayerId()) ||
                (x + 1 >= 0 && x + 1 < board->getSize()[0] && board->getBoard()[x + 1][y] == player->getPlayerId()) ||
                (y - 1 >= 0 && y - 1 < board->getSize()[1] && board->getBoard()[x][y - 1] == player->getPlayerId()) ||
                (y + 1 >= 0 && y + 1 < board->getSize()[1] && board->getBoard()[x][y + 1] == player->getPlayerId())) {
            validMode = false;
            break;
        }
    }

    if (transformation)
        delete tempGamePiece;

    return validMode;
}
