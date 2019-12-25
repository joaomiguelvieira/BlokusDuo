//
// Created by joaovieira on 12/24/19.
//

#include "Position.h"

Position::Position(int x, int y) {
    this->x = x;
    this->y = y;
}

int Position::getX() {
    return x;
}

int Position::getY() {
    return y;
}

Position::Position(Position *position) {
    x = position->x;
    y = position->y;
}

void Position::transformPosition(const int (*transformation)[2]) {
    auto newX = x * transformation[0][0] + y * transformation[0][1];
    auto newY = x * transformation[1][0] + y * transformation[1][1];

    x = newX;
    y = newY;
}

void Position::subtract(Position *position) {
    x -= position->x;
    y -= position->y;
}
