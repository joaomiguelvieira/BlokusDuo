//
// Created by joaovieira on 12/24/19.
//

#ifndef MCTS_BLOKUSDUO_CPP_BOARD_H
#define MCTS_BLOKUSDUO_CPP_BOARD_H


#include <cstdint>
#include <list>
#include "Position.h"
#include "Player.h"
#include "Move.h"

class Board {
private:
    static constexpr int DEFAULT_BOARD_SIZE = 14;

    uint8_t **board;
    int size[2]{DEFAULT_BOARD_SIZE, DEFAULT_BOARD_SIZE};
public:
    Board();
    explicit Board(Board *board);

    ~Board();

    uint8_t **getBoard();
    int *getSize();
    std::list<Position *> *getAllAnchors(int playerId);
    bool hasCornerContact(int x, int y, int playerId);
    bool hasEdgeContact(int x, int y, int playerId);
    void printBoard();
    void performMove(Player *player, Move *move);
    bool checkValidMove(Player *player, GamePiece *gamePiece, Position *center);
    std::list<Move *> *getAllValidMoves(Player *player);
};


#endif //MCTS_BLOKUSDUO_CPP_BOARD_H
