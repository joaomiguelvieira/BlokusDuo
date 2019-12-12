#include "Board.h"

Board *newBoard() {
    Board *board = (Board *) malloc(sizeof(Board));
    assert(board != (Board *) NULL);

    return board;
}

void deleteBoard(Board *board) {
    free(board);
}

Board *copyBoard(Board *board) {
    Board *new_board = (Board *) malloc(sizeof(Board));
    assert(new_board != (Board *) NULL);

    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            new_board->board[i][j] = board->board[i][j];

    new_board->moves = board->moves;

    return new_board;
}

void performMove(Player player, Position position) {

}
