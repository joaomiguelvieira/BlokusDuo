#include <iostream>
#include "MonteCarloTreeSearch.h"
#include "Board.h"

void givenEmptyBoard_whenSimulateInterAIPlay_thenGameDraw() {
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
};

void givenEmptyBoard_whenLevel1VsLevel3_thenLevel3WinsOrDraw() {
    auto board = new Board();
    auto mcts1 = new MonteCarloTreeSearch();
    mcts1->setLevel(1);

    auto mcts3 = new MonteCarloTreeSearch();
    mcts3->setLevel(3);

    int player = Board::P1;
    int totalMoves = Board::DEFAULT_BOARD_SIZE * Board::DEFAULT_BOARD_SIZE;
    for (int i = 0; i < totalMoves; i++) {
        if (player == Board::P1)
            board = mcts3->findNextMove(board, player);
        else
            board = mcts1->findNextMove(board, player);

        if (board->checkStatus() != -1) {
            break;
        }
        player = 3 - player;
    }
    int winStatus = board->checkStatus();
    assert(winStatus == Board::DRAW || winStatus == Board::P1);
}

int main() {
    givenEmptyBoard_whenSimulateInterAIPlay_thenGameDraw();

    return 0;
}
