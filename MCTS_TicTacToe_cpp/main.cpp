#include "MonteCarloTreeSearch.h"
#include "Board.h"

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

    auto winStatus = board->checkStatus();

    delete board;
    delete mcts;

    return winStatus;
}
