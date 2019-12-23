//
// Created by João Vieira on 22/12/2019.
//

#ifndef MCTS_TICTACTOE_CPP_TREE_H
#define MCTS_TICTACTOE_CPP_TREE_H


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


#endif //MCTS_TICTACTOE_CPP_TREE_H
