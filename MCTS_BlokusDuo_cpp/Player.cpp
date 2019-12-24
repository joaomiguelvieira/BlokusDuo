//
// Created by joaovieira on 12/24/19.
//

#include "Player.h"

int Player::idCount = 0;

Player::Player() {
    playerId = ++idCount;
}

int Player::getPlayerId() {
    return playerId;
}
