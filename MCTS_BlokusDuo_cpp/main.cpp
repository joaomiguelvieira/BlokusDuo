#include <algorithm>
#include <iostream>
#include "GamePiece.h"
#include "Player.h"
#include "MonteCarloTreeSearch.h"

int main() {
    auto mcts = new MonteCarloTreeSearch(1000);

    while (mcts->checkStatus() == MonteCarloTreeSearch::IN_PROGRESS)
        mcts->performBestMove();

    mcts->printStatus();

    delete mcts;

    return 0;
}
