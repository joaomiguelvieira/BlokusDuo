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

    GamePiece(char codeName, std::vector<std::vector<int>> squares, std::vector<std::vector<int>> anchors);
    explicit GamePiece(GamePiece *gamePiece);

    ~GamePiece();

    void printGamePiece();
    static std::list<std::vector<GamePiece *> *> *getInitialSetOfGamePieces();
    char getCodeName();
    std::vector<Position *> *getSquares();
    std::vector<Position *> *getAnchors();
    void transformPiece(int transformation);
};


#endif //MCTS_BLOKUSDUO_CPP_GAMEPIECE_H
