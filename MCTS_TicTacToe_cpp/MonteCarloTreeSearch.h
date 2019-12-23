//
// Created by João Vieira on 22/12/2019.
//

#ifndef MCTS_TICTACTOE_CPP_MONTECARLOTREESEARCH_H
#define MCTS_TICTACTOE_CPP_MONTECARLOTREESEARCH_H

#include <ctime>
#include "Board.h"
#include "Node.h"

class MonteCarloTreeSearch {
private:
    static constexpr int WIN_SCORE = 10;

    int level;
    int opponent;

    int getMillisForCurrentLevel();
public:
    MonteCarloTreeSearch();

    Board *findNextMove(Board *board, int playerNo);
    static Node *selectPromisingNode(Node *rootNode);
    static void expandNode(Node *pNode);
    int simulateRandomPlayout(Node *node);
    static void backPropagation(Node *nodeToExplore, int playerNo);

    void setLevel(int i);
};


#endif //MCTS_TICTACTOE_CPP_MONTECARLOTREESEARCH_H
