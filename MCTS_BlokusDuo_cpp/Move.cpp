//
// Created by joaovieira on 12/24/19.
//

#include "Move.h"

Move::Move(GamePiece *gamePiece, Position *center) {
    this->gamePiece = gamePiece;
    this->center = center;
}

bool Move::checkValidMove(Board *board, Player *player, GamePiece *gamePiece, Position *center) {
    for (auto & square : *gamePiece->getSquares()) {
        auto x = square->getX() + center->getX();
        auto y = square->getY() + center->getY();

        // check for board limits
        if (x < 0 || x >= board->getSize()[0] || y < 0 || y >= board->getSize()[1])
            return false;

        // check for overlap
        if (board->getBoard()[x][y])
            return false;

        // check for edge contact
        if (board->hasEdgeContact(x, y, player->getPlayerId()))
            return false;
    }

    return true;
}

std::list<Move *> *Move::getAllValidMoves(Board *board, Player *player) {
    auto validMoves = new std::list<Move *>();

    for (auto & boardAnchor : *board->getAllAnchors(player->getPlayerId())) {
        for (auto & gamePiece : *player->getRemainingGamePieces()) {
            for (auto & variant : *gamePiece) {
                for (auto & anchor : *variant->getAnchors()) {

                }
            }
        }
    }

    return validMoves;
}
