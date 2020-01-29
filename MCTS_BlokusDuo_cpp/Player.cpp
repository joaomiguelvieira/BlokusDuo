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
    delete remainingGamePieces;
}

std::list<std::shared_ptr<std::vector<std::shared_ptr<GamePiece>>>> *Player::getRemainingGamePieces() {
    return remainingGamePieces;
}

Player::Player(Player *player, std::shared_ptr<GamePiece> removePiece) {
    playerId = player->playerId;

    remainingGamePieces = new std::list<std::shared_ptr<std::vector<std::shared_ptr<GamePiece>>>>();
    for (auto &gamePiece : *player->remainingGamePieces)
        if ((*gamePiece)[0]->getCodeName() != removePiece->getCodeName())
            remainingGamePieces->push_back(gamePiece);

    quited = player->quited;
}

Player::Player(Player *player) {
    playerId = player->playerId;

    //remainingGamePieces = player->remainingGamePieces;
    remainingGamePieces = new std::list<std::shared_ptr<std::vector<std::shared_ptr<GamePiece>>>>();
    for (auto &gamePiece : *player->remainingGamePieces)
        remainingGamePieces->push_back(gamePiece);

    quited = player->quited;
}

bool Player::getQuited() {
    return quited;
}

int Player::getScore() {
    int score = 0;

    for (auto &gamePiece : *remainingGamePieces)
        score += (*gamePiece)[0]->getSquares()->size();

    return score;
}

void Player::setQuited(bool quited) {
    this->quited = quited;
}

std::string Player::toString() {
    std::string text;

    text += "Player " + std::to_string(playerId) + ": { ";
    text += "quited: ";
    if (quited) text += "true; "; else text += "false; ";
    text += "score: " + std::to_string(getScore()) + "; ";
    text += "remaining pieces: ";
    for (auto gamePiece : *remainingGamePieces) {
        text += (*gamePiece)[0]->getCodeName();
        text += " ";
    }

    text += "}";

    return text;
}
