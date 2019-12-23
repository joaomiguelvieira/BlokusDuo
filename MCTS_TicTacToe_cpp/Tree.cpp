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
    this->root = root;
}

Tree::~Tree() {

}
