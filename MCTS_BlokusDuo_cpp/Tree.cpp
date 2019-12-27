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

void Tree::setRoot(Node *root) {
    auto parent = root->getParent();

    if (parent)
        parent->getChildArray()->remove_if([root](Node *child)->bool{return child == root;});

    root->setParent(nullptr);
    delete this->root;
    this->root = root;
}
