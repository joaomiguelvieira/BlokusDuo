//
// Created by joaovieira on 12/24/19.
//

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

bool Move::isEqual(Move *move) {
    return this->center->getX() == move->center->getX() &&
           this->center->getY() == move->center->getY() &&
           this->gamePiece->getCodeName() == move->gamePiece->getCodeName() &&
           this->gamePiece->getTransformation() == move->gamePiece->getTransformation();
}
