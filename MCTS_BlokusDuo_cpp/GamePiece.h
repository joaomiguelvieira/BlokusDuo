//
// Created by joaovieira on 12/24/19.
//

#ifndef MCTS_BLOKUSDUO_CPP_GAMEPIECE_H
#define MCTS_BLOKUSDUO_CPP_GAMEPIECE_H


#include <list>
#include <vector>
#include "Position.h"

class GamePiece {
private:
    static constexpr int DEFAULT_MAX_SQUARES = 5;
    static const int transformations[8][2][2];

    char codeName;
    int transformation;
    std::vector<Position *> *squares;
    std::vector<Position *> *anchors;
public:
    static constexpr int N_TRANSFORMATIONS = 8;

    GamePiece(char codeName, int nSquares, int squares[][2], int nAnchors, int anchors[][2]);
    explicit GamePiece(GamePiece *gamePiece);

    ~GamePiece();

    void printGamePiece();
    static std::list<GamePiece *> *getInitialSetOfGamePieces();
    char getCodeName();
    void transformPiece(int transformation);
};


#endif //MCTS_BLOKUSDUO_CPP_GAMEPIECE_H
