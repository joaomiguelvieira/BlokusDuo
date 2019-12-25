//
// Created by joaovieira on 12/24/19.
//

#ifndef MCTS_BLOKUSDUO_CPP_PLAYER_H
#define MCTS_BLOKUSDUO_CPP_PLAYER_H


#include "GamePiece.h"

class Player {
private:
    static int idCount;

    int playerId;
    std::list<std::vector<GamePiece *> *> *remainingGamePieces;
public:
    Player();

    ~Player();

    int getPlayerId();
    std::list<std::vector<GamePiece *> *> *getRemainingGamePieces();
};


#endif //MCTS_BLOKUSDUO_CPP_PLAYER_H
