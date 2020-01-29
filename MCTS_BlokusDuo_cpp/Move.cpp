//
// Created by joaovieira on 12/24/19.
//

#include <sstream>
#include "Move.h"

Move::Move(std::shared_ptr<GamePiece> gamePiece, Position *center) {
    this->gamePiece = gamePiece;
    this->center = center;
}

Move::~Move() {
    delete center;
}

std::shared_ptr<GamePiece> Move::getGamePiece() {
    return gamePiece;
}

Position *Move::getCenter() {
    return center;
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

bool Move::equals(Move *move) {
    if (this == move) return true;
    if (move == nullptr) return false;
    return move->center->equals(center) && move->gamePiece->equals(gamePiece.get());
}

Move::Move(Move *move) {
    gamePiece = move->gamePiece;
    center = new Position(move->center);
}
