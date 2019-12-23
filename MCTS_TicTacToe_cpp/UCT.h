//
// Created by João Vieira on 22/12/2019.
//

#ifndef MCTS_TICTACTOE_CPP_UCT_H
#define MCTS_TICTACTOE_CPP_UCT_H


#include "Node.h"

class UCT {
private:

public:
    static Node *findBestNodeWithUCT(Node *node);
    static double uctValue(int totalVisit, double nodeWinScore, int nodeVisit);
};


#endif //MCTS_TICTACTOE_CPP_UCT_H
