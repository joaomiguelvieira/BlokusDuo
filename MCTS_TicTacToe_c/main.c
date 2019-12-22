#include <stdio.h>
#include "Board.h"
#include "Player.h"
#include "MCTS.h"

void givenEmptyBoard_whenSimulateInterAIPlay_thenGameDraw() {
    Board *board = newBoard();

    Player *player = newPlayer();
    player->player_id = PLAYER_ID_1;

    MCTS *mcts = newMCTS();

    int total_moves = BOARD_SIZE * BOARD_SIZE;

    for (int i = 0; i < total_moves; i++) {
        printf("Player %d\n", player->player_id);
        printBoard(board);
        board = findNextMoveMCTS(mcts, board, player);

        if (checkStatusBoard(board) != BOARD_IN_PROGRESS)
            break;

        player->player_id = getOpponentPlayer(player->player_id);
    }

    assert(checkStatusBoard(board) == BOARD_DRAW);
}

int givenEmptyBoard_whenLevel1VsLevel3_thenLevel3WinsOrDraw () {
    return 0;
}

int main() {
    givenEmptyBoard_whenSimulateInterAIPlay_thenGameDraw();

    return 0;
}
