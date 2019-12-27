//
// Created by joaovieira on 12/25/19.
//

#ifndef MCTS_BLOKUSDUO_CPP_MONTECARLOTREESEARCH_H
#define MCTS_BLOKUSDUO_CPP_MONTECARLOTREESEARCH_H


#include "Tree.h"
#include "Player.h"

class MonteCarloTreeSearch {
private:
    static constexpr int DEFAULT_DURATION_MILLIS = 1000;

    int moveDurationMillis{DEFAULT_DURATION_MILLIS};
    Tree *gameTree;
public:
    explicit MonteCarloTreeSearch(int moveDurationMillis);

    ~MonteCarloTreeSearch();

    int checkStatus();

    //Move *findNextMove();
};

#endif //MCTS_BLOKUSDUO_CPP_MONTECARLOTREESEARCH_H
