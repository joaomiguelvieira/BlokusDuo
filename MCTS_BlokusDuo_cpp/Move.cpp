//
// Created by joaovieira on 12/24/19.
//

#include <sstream>
#include "Move.h"

Move::Move(GamePiece *gamePiece, Position *center) {
    this->gamePiece = gamePiece;
    this->center = new Position(center);
}

Move::~Move() {
    delete center;
}

GamePiece *Move::getGamePiece() {
    return gamePiece;
}

Position *Move::getCenter() {
    return center;
}

bool Move::isEqual(Move *move1, Move *move2) {
    return move1 == move2 ||
           (move1->center->getX() == move2->center->getX() &&
           move1->center->getY() == move2->center->getY() &&
           move1->gamePiece->getCodeName() == move2->gamePiece->getCodeName() &&
           move1->gamePiece->getTransformation() == move2->gamePiece->getTransformation());
}

std::string Move::moveToString(Move *move) {
    std::stringstream text;

    if (move == nullptr) {
        text << "0000";
        return text.str();
    }

    text << std::hex << move->center->getX() + 1;
    text << std::hex << move->center->getY() + 1;
    text << move->gamePiece->getCodeName();
    text << move->gamePiece->getTransformation();

    return text.str();
}
