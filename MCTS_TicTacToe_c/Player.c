#include "Player.h"

Player *newPlayer() {
    Player *player = (Player *) malloc(sizeof(Player));
    assert(player != (Player *) NULL);

    return player;
}

void deletePlayer(Player *player) {
    free(player);
}
