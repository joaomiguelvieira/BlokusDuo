//
// Created by joaovieira on 12/25/19.
//

#ifndef MCTS_BLOKUSDUO_CPP_MONTECARLOTREESEARCH_H
#define MCTS_BLOKUSDUO_CPP_MONTECARLOTREESEARCH_H


#include "Tree.h"
#include "Player.h"

class MonteCarloTreeSearch {
private:
    int moveDurationMillis;
    Tree *gameTree;
    Player *player1, *player2;
public:
    static constexpr int IN_PROGRESS = -1;
    static constexpr int DRAW = 0;

    explicit MonteCarloTreeSearch(int moveDurationMillis);

    ~MonteCarloTreeSearch();
};

#endif //MCTS_BLOKUSDUO_CPP_MONTECARLOTREESEARCH_H
