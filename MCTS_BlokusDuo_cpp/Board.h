//
// Created by joaovieira on 12/24/19.
//

#ifndef MCTS_BLOKUSDUO_CPP_BOARD_H
#define MCTS_BLOKUSDUO_CPP_BOARD_H


#include <list>
#include "Position.h"

class Board {
private:
    static constexpr int DEFAULT_BOARD_SIZE = 14;

    int **board;
    int size[2]{DEFAULT_BOARD_SIZE, DEFAULT_BOARD_SIZE};
public:
    Board();

    ~Board();

    int **getBoard();
    int *getSize();
    std::list<Position *> *getAllAnchors(int playerId);

    bool hasCornerContact(int x, int y, int playerId);

    bool hasEdgeContact(int x, int y, int playerId);
};


#endif //MCTS_BLOKUSDUO_CPP_BOARD_H
