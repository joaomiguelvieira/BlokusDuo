#include "MCTS.h"
#include <stdio.h>

MCTS *newMCTS() {
    MCTS *mcts = (MCTS *) malloc(sizeof(MCTS));
    assert(mcts != (MCTS *) NULL);

    mcts->level = 3;

    return mcts;
}

void deleteMCTS(MCTS *mcts) {
    free(mcts);
}

int getMillisForCurrentLevelMCTS(MCTS *mcts) {
    return 2 * (mcts->level - 1) + 1;
}

TreeNode *selectPromisingNodeMCTS(TreeNode *node) {
    TreeNode *promising_node = node;

    while (promising_node->children->count)
        promising_node = findBestNodeWithUCT(promising_node);

    return promising_node;
}

void expandNodeMCTS(TreeNode *node) {
    DoublyLinkedList *possible_states = getAllPossibleStates((State *) node->object);
    for (DoublyLinkedListNode *state = possible_states->head; state != (DoublyLinkedListNode *) NULL; state = state->next) {
        ((State *) state->object)->player->player_id = getOpponentPlayer(((State *) node->object)->player->player_id);
        insertChildTreeNode(node, state->object);
    }

    deleteDoublyLinkedList(possible_states, NULL);
}

int simulateRandomPlayoutMCTS(MCTS *mcts, TreeNode *node) {
    TreeNode *temp_node = cloneTreeNode(node, node->parent, (void *(*)(void *)) cloneState);
    State *temp_state = (State *) temp_node->object;
    int board_status = checkStatusBoard(temp_state->board);

    if (board_status == mcts->opponent) {
        ((State *) temp_node->parent->object)->score = DBL_MIN;
        return board_status;
    }

    while (board_status == BOARD_IN_PROGRESS) {
        togglePlayerState(temp_state);
        randomPlayState(temp_state);
        board_status = checkStatusBoard(temp_state->board);
    }

    return board_status;
}

void backPropagationMCTS(TreeNode *node_to_explore, int player_id) {
    TreeNode *temp_node = node_to_explore;
    while (temp_node != (TreeNode *) NULL) {
        ((State *) temp_node->object)->visits++;
        if (((State *) temp_node->object)->player->player_id == player_id)
            addScoreState((State *) temp_node->object, WIN_SCORE);

        temp_node = temp_node->parent;
    }
}

Board *findNextMoveMCTS(MCTS *mcts, Board *board, Player *player) {
    TimeInterval *time_interval = newTimeInterval();
    setStartTimeInterval(time_interval);
    double time_limit = 60 * getMillisForCurrentLevelMCTS(mcts);

    mcts->opponent = getOpponentPlayer(player->player_id);

    State *state = newState();
    Tree *tree = newTree(state);
    copyBoard(board, ((State *) tree->root->object)->board);
    ((State *) tree->root->object)->player->player_id = mcts->opponent;

    do {
        // selection
        TreeNode *promising_node = selectPromisingNodeMCTS(tree->root);

        // expansion
        if (checkStatusBoard(((State *) promising_node->object)->board) == BOARD_IN_PROGRESS)
            expandNodeMCTS(promising_node);

        // simulation
        TreeNode *node_to_explore = promising_node;
        if (promising_node->children->count > 0)
            node_to_explore = getRandomChildTreeNode(promising_node);
        int playout_result = simulateRandomPlayoutMCTS(mcts, node_to_explore);

        // update
        backPropagationMCTS(node_to_explore, playout_result);

        setEndTimeInterval(time_interval);
    } while (getElapsedMillisTimeInterval(time_interval) < time_limit);

    TreeNode *winner_node = getChildWithMaxScoreTreeNode(tree->root, (int (*)(void *)) getValueState);
    return ((State *) winner_node->object)->board;
}
