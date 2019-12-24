//
// Created by joaovieira on 12/24/19.
//

#ifndef MCTS_BLOKUSDUO_CPP_POSITION_H
#define MCTS_BLOKUSDUO_CPP_POSITION_H


class Position {
private:
    int x, y;
public:
    Position(int x, int y);
    explicit Position(Position *position);

    int getX();
    int getY();
    void transformPosition(const int transformation[2][2]);
};


#endif //MCTS_BLOKUSDUO_CPP_POSITION_H
