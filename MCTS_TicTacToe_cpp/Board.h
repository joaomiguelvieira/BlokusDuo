//
// Created by João Vieira on 22/12/2019.
//

#ifndef MCTS_TICTACTOE_CPP_BOARD_H
#define MCTS_TICTACTOE_CPP_BOARD_H


#include <list>
#include "Position.h"

class Board {
private:

protected:
    int **boardValues;
    int totalMoves;
public:
    static constexpr int DEFAULT_BOARD_SIZE = 3;
    static constexpr int IN_PROGRESS = -1;
    static constexpr int DRAW = 0;
    static constexpr int P1 = 1;
    static constexpr int P2 = 2;

    Board();
    explicit Board(Board *board);

    ~Board();

    int checkStatus();
    int **getBoardValues();
    static int checkForWin(const int *row);
    std::list<Position *> *getEmptyPositions();

    void performMove(int player, Position *p);

    int getTotalMoves();

    void printBoard();

    void printStatus();
};


#endif //MCTS_TICTACTOE_CPP_BOARD_H
