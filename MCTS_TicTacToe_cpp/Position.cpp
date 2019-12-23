//
// Created by João Vieira on 23/12/2019.
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

void Position::setX(int x) {
    this->x = x;
}

void Position::setY(int y) {
    this->y = y;
}

Position::Position(Position *position) {
    x = position->getX();
    y = position->getY();
}
