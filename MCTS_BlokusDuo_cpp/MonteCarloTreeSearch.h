//
// Created by joaovieira on 12/25/19.
//

#ifndef MCTS_BLOKUSDUO_CPP_MONTECARLOTREESEARCH_H
#define MCTS_BLOKUSDUO_CPP_MONTECARLOTREESEARCH_H


#include "Tree.h"
#include "Player.h"

class MonteCarloTreeSearch {
private:
    static constexpr int DEFAULT_DURATION_MILLIS = 1000;

    int moveDurationMillis{DEFAULT_DURATION_MILLIS};
    Tree *gameTree;
public:
    explicit MonteCarloTreeSearch(int moveDurationMillis = DEFAULT_DURATION_MILLIS, bool exch_players = false);

    ~MonteCarloTreeSearch();

    int checkStatus();

    std::string findNextMove();

    static Node *selectPromisingNode(Node *rootNode);

    static void expandNode(Node *node);

    int simulateRandomPlay(Node *node, int *score);

    static void backPropagation(Node *nodeToExplore, int playerId, int winScore);

    int performNextMove(const std::string &move);

    void printValidMoves();

    void printStatus();

    void printMove(bool printQuit = false);

    Tree *getGameTree();
};

#endif //MCTS_BLOKUSDUO_CPP_MONTECARLOTREESEARCH_H
