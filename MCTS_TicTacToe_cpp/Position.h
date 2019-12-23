//
// Created by João Vieira on 23/12/2019.
//

#ifndef MCTS_TICTACTOE_CPP_POSITION_H
#define MCTS_TICTACTOE_CPP_POSITION_H


class Position {
protected:
    int x, y;
public:
    Position(int x, int y);
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
};


#endif //MCTS_TICTACTOE_CPP_POSITION_H
