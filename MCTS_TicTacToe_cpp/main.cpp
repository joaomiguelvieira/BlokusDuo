#include <iostream>
#include "MonteCarloTreeSearch.h"
#include "Board.h"

int main() {
    auto board = new Board();
    auto mcts = new MonteCarloTreeSearch(board, Board::P1);

    int totalMoves = Board::DEFAULT_BOARD_SIZE * Board::DEFAULT_BOARD_SIZE;
    for (int i = 0; i < totalMoves; i++) {
        board = mcts->findNextMove();
        std::cout << "Round " << i + 1 << "\n";
        board->printBoard();

        if (board->checkStatus() != -1)
            break;
    }

    auto winStatus = board->checkStatus();
    board->printStatus();

    delete mcts;

    return winStatus;
}
