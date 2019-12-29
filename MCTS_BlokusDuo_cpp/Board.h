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

    uint8_t board[DEFAULT_BOARD_SIZE][DEFAULT_BOARD_SIZE];
    int size[2]{DEFAULT_BOARD_SIZE, DEFAULT_BOARD_SIZE};

    // buffer
    static std::vector<Board> *buffer;
    static int bufferPtr;
public:
    Board();
    explicit Board(Board *board);

    uint8_t **getBoard();
    int *getSize();
    std::list<Position *> *getAllAnchors(int playerId);
    bool hasCornerContact(int x, int y, int playerId);
    bool hasEdgeContact(int x, int y, int playerId);
    void printBoard();
    void performMove(Player *player, Move *move);
    bool checkValidMove(Player *player, GamePiece *gamePiece, Position *center);
    std::list<Move *> *getAllValidMoves(Player *player);

    // buffer
    static void reserveBuffer(int bufferSize);
    static void deleteBuffer();
    static Board *captureBoard();
    static Board *captureBoard(Board *board);
    static void releaseBoard();
};


#endif //MCTS_BLOKUSDUO_CPP_BOARD_H
