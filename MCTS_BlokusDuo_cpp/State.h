//
// Created by joaovieira on 12/25/19.
//

#ifndef MCTS_BLOKUSDUO_CPP_STATE_H
#define MCTS_BLOKUSDUO_CPP_STATE_H


#include "Board.h"
#include "Player.h"

class State {
private:
    Board *board{nullptr};
    Player *player{nullptr}, *opponent{nullptr};
    Move *move{nullptr};
    int visitCount{0};
    double winScore{0};
public:
    static constexpr int IN_PROGRESS = -1;
    static constexpr int DRAW = 0;

    State();
    explicit State(State *state);
    explicit State(Board *board);

    ~State();

    void setBoard(Board *board);
    void setPlayer(Player *player);
    void setOpponent(Player *opponent);
    int getVisitCount();
    Board *getBoard();
    double getWinScore();
    Player *getPlayer();
    void setWinScore(double winScore);
    void togglePlayer();
    void randomPlay();
    void incrementVisit();
    void addScore(double score);
    std::list<State *> *getAllPossibleStates();
    Player *getOpponent();
    Move *getMove();
    int checkStatus();
    void setMove(Move *move);

    int getScore();
};


#endif //MCTS_BLOKUSDUO_CPP_STATE_H
