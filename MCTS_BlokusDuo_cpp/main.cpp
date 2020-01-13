#include <iostream>
#include "GamePiece.h"
#include "MonteCarloTreeSearch.h"

void playGame() {
    auto mcts = new MonteCarloTreeSearch();

    while (mcts->checkStatus() == State::IN_PROGRESS) {
        auto bestMove = mcts->findNextMove();
        mcts->performNextMove(bestMove);
        mcts->printMove();
    }

    delete mcts;
}

void interactiveGame() {
    auto mcts = new MonteCarloTreeSearch();

    std::string last_move;
    while (mcts->checkStatus() == State::IN_PROGRESS) {
        mcts->printStatus();
        std::string move;
        std::cin >> move;

        if (move == "hint" || move == "h")
            mcts->printValidMoves();
        else if (move == "simulate" || move == "s")
            std::cout << "Simulated move is " << mcts->findNextMove() << std::endl;
        else if (move == "simulate and play" || move == "sp") {
            auto nextMove = mcts->findNextMove();
            std::cout << "Simulated move is " << nextMove << std::endl;
            mcts->performNextMove(nextMove);
        }
        else if (move == "last")
            std::cout << "Last move was " << last_move << std::endl;
        else
            if (mcts->performNextMove(move) == 0)
                last_move = move;
    }

    delete mcts;
}

int main(int argc, char **argv) {
    playGame();

    return 0;
}
