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
        double score1, score2;

        // baseline is number of visits
        score1 = (double) node1->getState()->getVisitCount();
        score2 = (double) node2->getState()->getVisitCount();

        // for small number of visits use win score
        if (node1->getState()->getWinScore() > 0)
            score1 += exp2(-1.0 / node1->getState()->getWinScore());
        if (node2->getState()->getWinScore() > 0)
            score2 += exp2(-1.0 / node2->getState()->getWinScore());

        // for small number of visits use proximity to diagonal
        double maximumDistanceToDiag = 14.0 / sqrt(2);
        if (node1->getState()->getMove() != nullptr) {
            auto distanceToDiag = 1.0 / sqrtf(2.0) * abs(node1->getState()->getMove()->getCenter()->getX() -
                    node1->getState()->getMove()->getCenter()->getY());
            score1 += exp2(-1.0 / (maximumDistanceToDiag - distanceToDiag));
        }
        if (node2->getState()->getMove() != nullptr) {
            auto distanceToDiag = 1.0 / sqrtf(2.0) * abs(node2->getState()->getMove()->getCenter()->getX() -
                                                                 node2->getState()->getMove()->getCenter()->getY());
            score2 += exp2(-1.0 / (maximumDistanceToDiag - distanceToDiag));
        }

        return score1 < score2;
    });
}

void Node::resetChildArray() {
    delete childArray;
    childArray = new std::list<Node *>();
}
