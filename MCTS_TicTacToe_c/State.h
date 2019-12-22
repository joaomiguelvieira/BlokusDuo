#ifndef STATE_H
#define STATE_H

#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <float.h>

#include "Board.h"
#include "Player.h"
#include "DoublyLinkedList.h"

typedef struct State_ {
    Board *board;
    Player *player;
    int visits;
    double score;
} State;

State *newState();
void deleteState(State *state);

State *cloneState(State *state);

DoublyLinkedList *getAllPossibleStates(State *state);

void togglePlayerState(State *state);

void randomPlayState(State *state);

void addScoreState(State *state, double score);

double getValueState(State *state);

#endif