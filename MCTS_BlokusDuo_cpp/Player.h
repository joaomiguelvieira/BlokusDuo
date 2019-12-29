//
// Created by joaovieira on 12/24/19.
//

#ifndef MCTS_BLOKUSDUO_CPP_PLAYER_H
#define MCTS_BLOKUSDUO_CPP_PLAYER_H


#include <cstdint>
#include "GamePiece.h"

class Player {
private:
    static uint8_t idCount;

    uint8_t playerId;
    bool quited{false};
    std::list<std::vector<GamePiece *> *> *remainingGamePieces;
public:
    Player();
    Player(Player *player, GamePiece *removePiece);
    explicit Player(Player *player);
    explicit Player(std::list<std::vector<GamePiece *> *> *remainingGamePieces);

    ~Player();

    uint8_t getPlayerId();
    std::list<std::vector<GamePiece *> *> *getRemainingGamePieces();
    bool getQuited();
    int getScore();
    void setQuited(bool quited);
};


#endif //MCTS_BLOKUSDUO_CPP_PLAYER_H
