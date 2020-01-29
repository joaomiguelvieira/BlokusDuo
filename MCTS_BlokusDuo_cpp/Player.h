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
    std::list<std::shared_ptr<std::vector<std::shared_ptr<GamePiece>>>> *remainingGamePieces;
public:
    Player();

    Player(Player *player, std::shared_ptr<GamePiece> removePiece);

    explicit Player(Player *player);

    ~Player();

    uint8_t getPlayerId();

    std::list<std::shared_ptr<std::vector<std::shared_ptr<GamePiece>>>> *getRemainingGamePieces();

    bool getQuited();

    int getScore();

    void setQuited(bool quited);

    std::string toString();
};


#endif //MCTS_BLOKUSDUO_CPP_PLAYER_H
