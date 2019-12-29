//
// Created by joaovieira on 12/25/19.
//

#ifndef MCTS_BLOKUSDUO_CPP_MONTECARLOTREESEARCH_H
#define MCTS_BLOKUSDUO_CPP_MONTECARLOTREESEARCH_H


#include "Tree.h"
#include "Player.h"

class MonteCarloTreeSearch {
private:
    static constexpr int WIN_SCORE = 10;
    static constexpr int DEFAULT_DURATION_MILLIS = 1000;

    int moveDurationMillis{DEFAULT_DURATION_MILLIS};
    Tree *gameTree;
    std::list<std::vector<GamePiece *> *> *gamePieceSet1, *gamePieceSet2;
public:
    explicit MonteCarloTreeSearch(int moveDurationMillis = DEFAULT_DURATION_MILLIS);

    ~MonteCarloTreeSearch();

    int checkStatus();
    std::string findNextMove();
    static Node *selectPromisingNode(Node *rootNode);
    static void expandNode(Node *node);
    int simulateRandomPlayout(Node *node, int *score);
    static void backPropagation(Node *nodeToExplore, int playerId, int winScore);
    int performNextMove(const std::string& move);
    void printStatus();
    void printMove();

    void printValidMoves();
};

#endif //MCTS_BLOKUSDUO_CPP_MONTECARLOTREESEARCH_H
