//
// Created by joaovieira on 12/25/19.
//

#ifndef MCTS_BLOKUSDUO_CPP_TREE_H
#define MCTS_BLOKUSDUO_CPP_TREE_H


#include "Node.h"

class Tree {
private:
    Node *root;
public:
    Tree();

    ~Tree();

    Node *getRoot();
    void setRoot(Node *root);
};


#endif //MCTS_BLOKUSDUO_CPP_TREE_H
