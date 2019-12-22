#ifndef MCTS_H
#define MCTS_H

#include <stdlib.h>
#include <assert.h>

#include "Board.h"
#include "TimeInterval.h"
#include "Tree.h"
#include "State.h"
#include "UCT.h"

#define WIN_SCORE 10

typedef struct MCTS_ {
    int level;
    int opponent;
} MCTS;

MCTS *newMCTS();
void deleteMCTS(MCTS *mcts);

Board *findNextMoveMCTS(MCTS *mcts, Board *board, Player *player);

#endif
