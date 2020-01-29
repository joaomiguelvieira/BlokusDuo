//
// Created by joaovieira on 12/25/19.
//

#ifndef MCTS_BLOKUSDUO_CPP_STATE_H
#define MCTS_BLOKUSDUO_CPP_STATE_H


#include "Board.h"
#include "Player.h"

class State {
private:
    std::unique_ptr<Board> board{nullptr};
    std::unique_ptr<Player> player{nullptr}, opponent{nullptr};
    std::shared_ptr<Move> move{nullptr};
    std::list<std::shared_ptr<Move>> *possibleMoves{nullptr};
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

    std::shared_ptr<Move> getMove();

    void setMove(std::shared_ptr<Move> move);

    void setPlayer(Player *player);

    int checkStatus();

    double getStateViability(State *previousState);

    void incrementWinCount();

    double getWinCount();

    int getScore();

    int getMovesPlayed();

    void setMovesPlayed(int movesPlayed);

    void setPossibleMoves(std::list<std::shared_ptr<Move>> *possibleMoves);

    std::list<std::shared_ptr<Move>> *getPossibleMoves();
};


#endif //MCTS_BLOKUSDUO_CPP_STATE_H
