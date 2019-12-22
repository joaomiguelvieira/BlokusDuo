#include "Board.h"

Board *newBoard() {
    Board *board = (Board *) malloc(sizeof(Board));
    assert(board != (Board *) NULL);

    return board;
}

void deleteBoard(Board *board) {
    free(board);
}

Board *cloneBoard(Board *board) {
    Board *new_board = (Board *) malloc(sizeof(Board));
    assert(new_board != (Board *) NULL);

    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            new_board->board[i][j] = board->board[i][j];

    new_board->moves = board->moves;

    return new_board;
}

void copyBoard(Board *board1, Board *board2) {
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            board2->board[i][j] = board1->board[i][j];

    board2->moves = board1->moves;
}

void performMoveBoard(Board *board, Player *player, Position *position) {
    board->moves++;
    board->board[position->x][position->y] = player->player_id;
}

int checkForWinBoard(int *row) {
    int winner = row[0];

    for (int i = 1; i < BOARD_SIZE; i++)
        if (row[i] != winner)
            return 0;

    return winner;
}

DoublyLinkedList *getEmptyPositionsBoard(Board *board) {
    DoublyLinkedList *empty_positions = newDoublyLinkedList();

    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            if (board->board[i][j] == 0)
                insertAtHeadDoublyLinkedList(empty_positions, (void *) newPosition(i, j));

    return empty_positions;
}

int checkStatusBoard(Board *board) {
    int transposed_board[BOARD_SIZE][BOARD_SIZE];
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            transposed_board[i][j] = board->board[j][i];

    int diag1[BOARD_SIZE], diag2[BOARD_SIZE];
    for (int i = 0; i < BOARD_SIZE; i++) {
        diag1[i] = board->board[i][i];
        diag2[i] = board->board[BOARD_SIZE - i - 1][i];
    }

    int winner = 0;

    for (int i = 0; i < BOARD_SIZE; i++) {
        if ((winner = checkForWinBoard(board->board[i])))
            return winner;

        if ((winner = checkForWinBoard(transposed_board[i])))
            return winner;
    }

    if ((winner = checkForWinBoard(diag1)))
        return winner;

    if ((winner = checkForWinBoard(diag2)))
        return winner;

    return getEmptyPositionsBoard(board)->count ? BOARD_IN_PROGRESS : BOARD_DRAW;
}

void printBoard(Board *board) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            printf("%d ", board->board[i][j]);
        }

        printf("\n");
    }
}
