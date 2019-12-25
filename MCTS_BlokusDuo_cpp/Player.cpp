//
// Created by joaovieira on 12/24/19.
//

#include "Player.h"

int Player::idCount = 0;

Player::Player() {
    playerId = ++idCount;
    remainingGamePieces = GamePiece::getInitialSetOfGamePieces();
}

int Player::getPlayerId() {
    return playerId;
}

Player::~Player() {
    for (auto & gamePiece : *remainingGamePieces)
        delete gamePiece;
    delete remainingGamePieces;
}

std::list<GamePiece *> *Player::getRemainingGamePieces() {
    return remainingGamePieces;
}
