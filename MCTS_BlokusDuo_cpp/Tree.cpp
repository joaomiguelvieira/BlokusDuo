//
// Created by joaovieira on 12/25/19.
//

#include "Tree.h"

Tree::Tree() {
    root = new Node();
}

Tree::~Tree() {
    delete root;
}

Node *Tree::getRoot() {
    return root;
}

// TODO delete unnecessary nodes
void Tree::setRoot(Node *root) {
    this->root = root;
}
