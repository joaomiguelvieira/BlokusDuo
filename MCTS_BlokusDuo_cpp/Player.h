//
// Created by joaovieira on 12/24/19.
//

#ifndef MCTS_BLOKUSDUO_CPP_PLAYER_H
#define MCTS_BLOKUSDUO_CPP_PLAYER_H


class Player {
private:
    static int idCount;

    int playerId;
public:
    Player();

    int getPlayerId();
};


#endif //MCTS_BLOKUSDUO_CPP_PLAYER_H
