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
    static constexpr int BOARD_SIZE = 14;

    uint8_t board[BOARD_SIZE][BOARD_SIZE];
public:
    Board();
    explicit Board(Board *board);

    bool isOccupied(int x, int y);
    static bool respectsBoundaries(int x, int y);
    bool hasCornerContact(int x, int y, int playerId);
    bool hasEdgeContact(int x, int y, int playerId);
    bool isAnchor(int x, int y, int playerId);
    std::list<Position *> *getAllAnchors(int playerId);
    std::string toString();
    void performMove(Player *player, Move *move);
    bool checkValidMove(Player *player, GamePiece *gamePiece, Position *center);
    std::list<Move *> *getMovesFromAnchors(Player *player, std::list<Position *> *boardAnchors);
    static std::list<Move *> *getMovesCoveringPosition(Player *player, int x, int y);
    std::list<Move *> *getAllValidMoves(Player *player);
    std::list<Move *> *getAllValidMoves(Player *player, std::list<Move *> *previouslyValidMoves,
            Move *previouslyPlayedMove, Board *previousBoard);
};


#endif //MCTS_BLOKUSDUO_CPP_BOARD_H
