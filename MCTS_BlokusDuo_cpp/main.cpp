#include "GamePiece.h"
#include "MonteCarloTreeSearch.h"

void playGame() {
    auto mcts = new MonteCarloTreeSearch(1000);

    while (mcts->checkStatus() == State::IN_PROGRESS) {
        auto bestMove = mcts->findNextMove();
        mcts->performNextMove(bestMove);
    }

    mcts->printStatus();

    delete mcts;
}

int main() {
    playGame();

    return 0;
}
