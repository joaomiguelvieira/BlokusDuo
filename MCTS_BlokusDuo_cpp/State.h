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
    std::list<Move *> *possibleMoves{nullptr};
    int visitCount{0};
    double winScore{0};
    int winCount{0};
    int movesPlayed{0};
public:
    static constexpr int IN_PROGRESS = -1;
    static constexpr int DRAW = 0;

    State();

    explicit State(Board *board);

    ~State();

    int getVisitCount();

    Board *getBoard();


    Player *getPlayer();

    void setWinScore(double winScore);

    void incrementVisit();

    void addScore(double score);

    void setOpponent(Player *opponent);

    Player *getOpponent();

    Move *getMove();

    void setMove(Move *move);

    void setPlayer(Player *player);

    int checkStatus();

    double getStateViability(State *previousState);

    void incrementWinCount();

    double getWinCount();

    int getScore();

    int getMovesPlayed();

    void setMovesPlayed(int movesPlayed);

    void setPossibleMoves(std::list<Move *> *possibleMoves);

    std::list<Move *> *getPossibleMoves();
};


#endif //MCTS_BLOKUSDUO_CPP_STATE_H
