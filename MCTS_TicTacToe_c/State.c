#include "State.h"

State *newState() {
    State *state = (State *)malloc(sizeof(State));
    assert(state != (State *) NULL);

    state->player = newPlayer();
    state->board = newBoard();
    state->score = 0;
    state->visits = 0;

    return state;
}

void deleteState(State *state) {
    deletePlayer(state->player);
    deleteBoard(state->board);
    free(state);
}

DoublyLinkedList *getAllPossibleStates(State *state) {
    DoublyLinkedList *possible_states = newDoublyLinkedList();
    DoublyLinkedList *available_positions = getEmptyPositionsBoard(state->board);
    for (DoublyLinkedListNode *node = available_positions->head; node != (DoublyLinkedListNode *) NULL; node = node->next) {
        State *new_state = newState();
        new_state->board = cloneBoard(state->board);
        new_state->player->player_id = getOpponentPlayer(state->player->player_id);
        performMoveBoard(new_state->board, new_state->player, (Position *) node->object);
        insertAtHeadDoublyLinkedList(possible_states, (void *) new_state);
    }

    return possible_states;
}

void togglePlayerState(State *state) {
    state->player->player_id = getOpponentPlayer(state->player->player_id);
}

// TODO optimize
void randomPlayState(State *state) {
    DoublyLinkedList *available_positions = getEmptyPositionsBoard(state->board);

    srand(time(NULL));
    int random = rand() % available_positions->count;

    DoublyLinkedListNode *random_node;
    for (random_node = available_positions->head; random > 0; random--)
        random_node = random_node->next;

    performMoveBoard(state->board, state->player, (Position *) random_node->object);
}

State *cloneState(State *state) {
    State *new_state = newState();
    new_state->player->player_id = state->player->player_id;
    copyBoard(state->board, new_state->board);
    new_state->score = state->score;
    new_state->visits = state->visits;

    return new_state;
}

void addScoreState(State *state, double score) {
    if (state->score != DBL_MIN)
        state->score += score;
}

double getValueState(State *state) {
    return state->score;
}
