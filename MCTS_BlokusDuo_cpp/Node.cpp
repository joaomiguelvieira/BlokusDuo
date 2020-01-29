//
// Created by joaovieira on 12/25/19.
//

#include "Node.h"
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <cmath>

Node::Node() {
    state = new State();
    childArray = new std::list<Node *>();
}

Node::Node(State *state) {
    this->state = state;
    childArray = new std::list<Node *>();
}

Node::~Node() {
    for (auto &child : *childArray)
        delete child;

    delete state;
    delete childArray;
}

State *Node::getState() {
    return state;
}

std::list<Node *> *Node::getChildArray() {
    return childArray;
}

void Node::setParent(Node *node) {
    parent = node;
}

Node *Node::getRandomChildNode() {
    srand((unsigned int) time(nullptr));
    auto it = childArray->begin();
    std::advance(it, rand() % childArray->size());
    return *it;
}

Node *Node::getParent() {
    return parent;
}

Node *Node::getChildWithMaxScore() {
    return *max_element(childArray->begin(), childArray->end(), [](Node *node1, Node *node2) -> bool {
        return node1->getState()->getStateViability(
                node1->getParent() == nullptr ? nullptr : node1->getParent()->getState()) <
               node2->getState()->getStateViability(
                       node2->getParent() == nullptr ? nullptr : node2->getParent()->getState());
    });
}
