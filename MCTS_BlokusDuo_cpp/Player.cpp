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
}

Player::Player(Player *player) {
    playerId = player->playerId;
    remainingGamePieces = player->remainingGamePieces;
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
