//
// Created by joaovieira on 12/25/19.
//

#include "MonteCarloTreeSearch.h"

MonteCarloTreeSearch::MonteCarloTreeSearch(int moveDurationMillis) {
    this->moveDurationMillis = moveDurationMillis;
    this->player1 = new Player();
    this->player2 = new Player();
    this->gameTree = new Tree();
}

MonteCarloTreeSearch::~MonteCarloTreeSearch() {
    delete player1;
    delete player2;
    delete gameTree;
}
