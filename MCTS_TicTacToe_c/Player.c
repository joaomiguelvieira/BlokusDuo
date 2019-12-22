#include "Player.h"

Player *newPlayer() {
    Player *player = (Player *) malloc(sizeof(Player));
    assert(player != (Player *) NULL);

    return player;
}

void deletePlayer(Player *player) {
    free(player);
}

int getOpponentPlayer(int player) {
    return player == PLAYER_ID_1 ? PLAYER_ID_2 : PLAYER_ID_1;
}