//
// Created by joaovieira on 12/25/19.
//

#ifndef MCTS_BLOKUSDUO_CPP_NODE_H
#define MCTS_BLOKUSDUO_CPP_NODE_H


#include <list>
#include "State.h"

class Node {
private:
    State *state;
    std::list<Node *> *childArray;
    Node *parent;
public:
    Node();
    explicit Node(State *state);
    explicit Node(Node *node);

    ~Node();

    State *getState();
    std::list<Node *> *getChildArray();
    void setParent(Node *node);
    Node *getRandomChildNode();
    Node *getParent();
    Node *getChildWithMaxScore();
};


#endif //MCTS_BLOKUSDUO_CPP_NODE_H
