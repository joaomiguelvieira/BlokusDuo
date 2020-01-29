//
// Created by joaovieira on 12/24/19.
//

#ifndef MCTS_BLOKUSDUO_CPP_GAMEPIECE_H
#define MCTS_BLOKUSDUO_CPP_GAMEPIECE_H


#include <list>
#include <vector>
#include <memory>
#include "Position.h"

class GamePiece {
private:
    static const int transformations[8][2][2];

    char codeName;
    int transformation;
    std::vector<Position *> *squares;
    std::vector<Position *> *anchors;
public:

    GamePiece(char codeName, std::vector<std::vector<int>> squares, std::vector<std::vector<int>> anchors);

    ~GamePiece();

    static std::list<std::shared_ptr<std::vector<std::shared_ptr<GamePiece>>>> *getInitialSetOfGamePieces();

    char getCodeName();

    std::vector<Position *> *getSquares();

    std::vector<Position *> *getAnchors();

    void transformPiece(int transformation);

    int getTransformation();

    bool equals(const std::shared_ptr<GamePiece> &gamePiece);
};


#endif //MCTS_BLOKUSDUO_CPP_GAMEPIECE_H
