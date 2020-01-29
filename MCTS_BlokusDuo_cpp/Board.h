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

    void performMove(Player *player, const std::shared_ptr<Move>& move);

    bool checkValidMove(Player *player, const std::shared_ptr<GamePiece>& gamePiece, Position *center);

    std::list<std::shared_ptr<Move>> *getMovesFromAnchors(Player *player, std::list<Position *> *boardAnchors);

    static std::list<std::shared_ptr<Move>> *getMovesCoveringPosition(Player *player, int x, int y);

    std::list<std::shared_ptr<Move>> *getAllValidMoves(Player *player);

    std::list<std::shared_ptr<Move>> *getAllValidMoves(Player *player, std::list<std::shared_ptr<Move>> *previouslyValidMoves,
                                        const std::shared_ptr<Move>& previouslyPlayedMove, Board *previousBoard);
};


#endif //MCTS_BLOKUSDUO_CPP_BOARD_H
