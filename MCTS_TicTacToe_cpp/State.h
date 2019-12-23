//
// Created by João Vieira on 22/12/2019.
//

#ifndef MCTS_TICTACTOE_CPP_STATE_H
#define MCTS_TICTACTOE_CPP_STATE_H


#include "Board.h"

class State {
private:
    Board *board;
    int playerNo;
    int visitCount;
    double winScore;
public:
    State();
    explicit State(State *state);
    explicit State(Board *board);

    void setBoard(Board *pBoard);
    void setPlayerNo(int i);
    int getVisitCount();

    Board *getBoard();

    double getWinScore();

    int getPlayerNo();

    void setWinScore(int i);

    void togglePlayer();

    void randomPlay();

    void incrementVisit();

    void addScore(double i);

    std::list<State *> *getAllPossibleStates();

    int getOpponent();
};


#endif //MCTS_TICTACTOE_CPP_STATE_H
