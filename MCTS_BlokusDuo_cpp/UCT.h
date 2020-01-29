//
// Created by joaovieira on 12/25/19.
//

#ifndef MCTS_BLOKUSDUO_CPP_UCT_H
#define MCTS_BLOKUSDUO_CPP_UCT_H


#include "Node.h"

class UCT {
public:
    static Node *findBestNodeWithUCT(Node *node);

    static double uctValue(int totalVisit, double nodeWinScore, int nodeVisit);
};


#endif //MCTS_BLOKUSDUO_CPP_UCT_H
