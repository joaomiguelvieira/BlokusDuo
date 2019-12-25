//
// Created by joaovieira on 12/24/19.
//

#ifndef MCTS_BLOKUSDUO_CPP_MOVE_H
#define MCTS_BLOKUSDUO_CPP_MOVE_H


#include "Position.h"
#include "GamePiece.h"
#include "Board.h"
#include "Player.h"

class Move {
private:
    GamePiece *gamePiece;
    Position *center;
public:
    Move(GamePiece *gamePiece, Position *center);

    ~Move();

    static bool checkValidMove(Board *board, Player *player, GamePiece *gamePiece, Position *center);
    static std::list<Move *> *getAllValidMoves(Board *board, Player *player);
};


#endif //MCTS_BLOKUSDUO_CPP_MOVE_H
