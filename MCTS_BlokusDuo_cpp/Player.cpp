//
// Created by joaovieira on 12/24/19.
//

#include "Player.h"

uint8_t Player::idCount = 0;

Player::Player() {
    playerId = ++idCount;
    remainingGamePieces = GamePiece::getInitialSetOfGamePieces();
}

uint8_t Player::getPlayerId() {
    return playerId;
}

Player::~Player() {
    for (auto & gamePiece : *remainingGamePieces) {
        for (auto & variant : *gamePiece)
            delete variant;

        delete gamePiece;
    }

    delete remainingGamePieces;
}

std::list<std::vector<GamePiece *> *> *Player::getRemainingGamePieces() {
    return remainingGamePieces;
}

Player::Player(Player *player, GamePiece *removePiece) {
    playerId = player->playerId;
    remainingGamePieces = new std::list<std::vector<GamePiece *> *>();

    for (auto & gamePiece : *player->remainingGamePieces)
        if ((*gamePiece)[0]->getCodeName() != removePiece->getCodeName())
            remainingGamePieces->push_back(gamePiece);

    quited = player->quited;
}

Player::Player(Player *player) {
    playerId = player->playerId;
    remainingGamePieces = player->remainingGamePieces;
    quited = player->quited;
}

bool Player::getQuited() {
    return quited;
}

int Player::getScore() {
    int score = 0;

    for (auto & gamePiece : *remainingGamePieces)
        score += (*gamePiece)[0]->getSquares()->size();

    return score;
}

void Player::setQuited(bool quited) {
    this->quited = quited;
}
