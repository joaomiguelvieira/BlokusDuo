//
// Created by João Vieira on 22/12/2019.
//

#include "Node.h"
#include "State.h"
#include <ctime>
#include <cstdlib>
#include <algorithm>

Node::Node() {
    state = new State();
    childArray = new std::list<Node *>();
    parent = nullptr;
}

State *Node::getState() {
    return state;
}

std::list <Node *> *Node::getChildArray() {
    return childArray;
}

Node::Node(State *state) {
    this->state = state;
    childArray = new std::list<Node *>();
    parent = nullptr;
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

Node::Node(Node *node) {
    state = new State(node->getState());
    childArray = new std::list<Node *>();
    if (node->getParent() != nullptr)
        parent = node->getParent();
    for (auto & child : *node->getChildArray())
        childArray->push_back(new Node(child));
}

Node *Node::getParent() {
    return parent;
}

Node *Node::getChildWithMaxScore() {
    return *max_element(childArray->begin(), childArray->end(), [] (Node *node1, Node *node2) -> bool {
        return node1->getState()->getVisitCount() < node2->getState()->getVisitCount();
    });
}

Node::~Node() {
    delete state;
    delete childArray;
}
