//
// Created by joaovieira on 12/24/19.
//

#ifndef MCTS_BLOKUSDUO_CPP_MOVE_H
#define MCTS_BLOKUSDUO_CPP_MOVE_H


#include <string>
#include "Position.h"
#include "GamePiece.h"
#include "Player.h"

class Move {
private:
    GamePiece *gamePiece;
    Position *center;
public:
    Move(GamePiece *gamePiece, Position *center);

    ~Move();

    GamePiece *getGamePiece();
    Position *getCenter();
    static std::string moveToString(Move *move);
    bool equals(Move *move);
};


#endif //MCTS_BLOKUSDUO_CPP_MOVE_H
