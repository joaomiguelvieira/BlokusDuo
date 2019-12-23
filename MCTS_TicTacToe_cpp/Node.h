//
// Created by João Vieira on 22/12/2019.
//

#ifndef MCTS_TICTACTOE_CPP_NODE_H
#define MCTS_TICTACTOE_CPP_NODE_H


#include "State.h"
#include <list>

class Node {
private:
    State *state;
    std::list <Node *> *childArray;
    Node *parent;
public:
    Node();
    explicit Node(State *state);
    explicit Node(Node *node);

    State *getState();
    std::list <Node *> *getChildArray();
    void setParent(Node *node);

    Node *getRandomChildNode();

    Node *getParent();

    Node *getChildWithMaxScore();
};


#endif //MCTS_TICTACTOE_CPP_NODE_H
