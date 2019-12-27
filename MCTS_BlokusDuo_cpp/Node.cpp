//
// Created by joaovieira on 12/25/19.
//

#include "Node.h"
#include <ctime>
#include <cstdlib>
#include <algorithm>

Node::Node() {
    state = new State();
    childArray = new std::list<Node *>();
}

Node::Node(State *state) {
    this->state = state;
    childArray = new std::list<Node *>();
}

Node::Node(Node *node) {
    state = new State(node->state);
    childArray = new std::list<Node *>();
    if (node->parent != nullptr)
        parent = node->parent;
    for (auto & child : *node->childArray)
        childArray->push_back(new Node(child));
}

Node::~Node() {
    for (auto & child : *childArray)
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
    int noOfPossibleMoves = (int) childArray->size();
    srand((unsigned int) time(nullptr));
    int selectRandom = rand() % noOfPossibleMoves;

    auto it = childArray->begin();
    std::advance(it, selectRandom);
    return *it;
}

Node *Node::getParent() {
    return parent;
}

Node *Node::getChildWithMaxScore() {
    return *max_element(childArray->begin(), childArray->end(), [] (Node *node1, Node *node2) -> bool {
        return node1->getState()->getVisitCount() < node2->getState()->getVisitCount();
    });
}

void Node::resetChildArray() {
    delete childArray;
    childArray = new std::list<Node *>();
}
