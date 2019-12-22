#ifndef BOARD_H
#define BOARD_H

#define BOARD_SIZE 3

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "Position.h"
#include "Player.h"
#include "DoublyLinkedList.h"

#define BOARD_IN_PROGRESS -1
#define BOARD_DRAW 0

typedef struct Board_ {
    int board[BOARD_SIZE][BOARD_SIZE];
    int moves;
} Board;

Board *newBoard();
void deleteBoard(Board *board);

void copyBoard(Board *board1, Board *board2);
Board *cloneBoard(Board *board);

DoublyLinkedList *getEmptyPositionsBoard(Board *board);
void performMoveBoard(Board *board, Player *player, Position *position);

int checkStatusBoard(Board *board);

void printBoard(Board *board);

#endif
