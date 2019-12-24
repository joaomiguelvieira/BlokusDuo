//
// Created by João Vieira on 22/12/2019.
//

#include "Tree.h"
#include "Node.h"

Tree::Tree() {
    root = new Node();
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

Tree::~Tree() {
    delete root;
}
