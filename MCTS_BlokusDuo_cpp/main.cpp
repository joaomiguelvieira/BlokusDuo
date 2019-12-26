#include <algorithm>
#include <iostream>
#include "GamePiece.h"
#include "Player.h"
#include "MonteCarloTreeSearch.h"

int main() {
    auto mcts = new MonteCarloTreeSearch(1000);

    while (mcts->checkStatus() == State::IN_PROGRESS) {
        auto bestMove = mcts->findNextMove();
        mcts->performBestMove(bestMove)
    }

    mcts->printStatus();

    delete mcts;

    return 0;
}
