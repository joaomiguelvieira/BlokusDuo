#include "MonteCarloTreeSearch.h"
#include "Board.h"
#include <cassert>

int main() {
    auto *mcts = new MonteCarloTreeSearch();
    auto *board = new Board();

    int player = Board::P1;
    int totalMoves = Board::DEFAULT_BOARD_SIZE * Board::DEFAULT_BOARD_SIZE;
    for (int i = 0; i < totalMoves; i++) {
        board = mcts->findNextMove(board, player);

        if (board->checkStatus() != -1)
            break;

        player = 3 - player;
    }

    int winStatus = board->checkStatus();

    assert(winStatus == Board::DRAW);

    delete board;
    delete mcts;

    return 0;
}
