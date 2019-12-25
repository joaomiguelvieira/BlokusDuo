//
// Created by joaovieira on 12/24/19.
//

#include <iostream>
#include "GamePiece.h"

const int GamePiece::transformations[8][2][2] = {
    {{ 1,  0}, { 0,  1}},
    {{-1,  0}, { 0,  1}},
    {{ 0, -1}, { 1,  0}},
    {{ 0,  1}, { 1,  0}},
    {{-1,  0}, { 0, -1}},
    {{ 1,  0}, { 0, -1}},
    {{ 0,  1}, {-1,  0}},
    {{ 0, -1}, {-1,  0}}
};

// TODO optimize array allocation
GamePiece::GamePiece(char codeName, int nSquares, int squares[][2], int nAnchors, int anchors[][2]) {
    this->codeName = codeName;

    this->transformation = 0;

    this->squares = new std::vector<Position *>();
    for (int i = 0; i < nSquares; ++i)
        this->squares->push_back(new Position(squares[i][0], squares[i][1]));

    this->anchors = new std::vector<Position *>();
    for (int j = 0; j < nAnchors; ++j)
        this->anchors->push_back(new Position(anchors[j][0], anchors[j][1]));
}

// TODO optimize array allocation
GamePiece::GamePiece(GamePiece *gamePiece) {
    codeName = gamePiece->codeName;

    transformation = gamePiece->transformation;

    squares = new std::vector<Position *>();
    for (auto & square : *gamePiece->squares)
        squares->push_back(new Position(square));

    anchors = new std::vector<Position *>();
    for (auto & anchor : *gamePiece->anchors)
        anchors->push_back(new Position(anchor));
}

GamePiece::~GamePiece() {
    for (auto & anchor : *anchors)
        delete anchor;
    delete anchors;

    for (auto & square : *squares)
        delete square;
    delete squares;
}

void GamePiece::printGamePiece() {
    auto offset = DEFAULT_MAX_SQUARES / 2;

    char printArea[DEFAULT_MAX_SQUARES][DEFAULT_MAX_SQUARES];
    for (int i = 0; i < DEFAULT_MAX_SQUARES; ++i) {
        for (int j = 0; j < DEFAULT_MAX_SQUARES; ++j) {
            printArea[i][j] = ' ';
        }
    }

    for (auto & square : *squares)
        printArea[square->getX() + offset][square->getY() + offset] = '#';

    for (auto & anchor : *anchors)
        printArea[anchor->getX() + offset][anchor->getY() + offset] = 'X';

    printArea[offset][offset] = printArea[offset][offset] == 'X' ? '+' : 'O';

    std::cout << "Game Piece: " << codeName << transformation << "\n";

    for (int i = 0; i < DEFAULT_MAX_SQUARES; ++i) {
        for (int j = 0; j < DEFAULT_MAX_SQUARES; ++j) {
            std::cout << printArea[j][i];
        }
        std::cout << "\n";
    }
}

std::list<GamePiece *> *GamePiece::getInitialSetOfGamePieces() {
    auto initialSetOfGamePieces = new std::list<GamePiece *>();

    struct OneSquareGamePiece {char codeName; int nAnchors; int squares[1][2], anchors[1][2];};
    struct OneSquareGamePiece oneSquareGamePieces[] = {
            {.codeName = 'a', .nAnchors = 1, .squares = {{ 0,  0}}, .anchors = {{ 0,  0}}}
    };

    struct TwoSquareGamePiece {char codeName; int nAnchors; int squares[2][2], anchors[2][2];};
    struct TwoSquareGamePiece twoSquareGamePieces[] = {
            {.codeName = 'b', .nAnchors = 2, .squares = {{ 0,  0}, { 0,  1}}, .anchors = {{ 0,  0}, { 0,  1}}}
    };

    struct ThreeSquareGamePiece {char codeName; int nAnchors; int squares[3][2], anchors[3][2];};
    struct ThreeSquareGamePiece threeSquareGamePieces[] = {
            {.codeName = 'c', .nAnchors = 2, .squares = {{ 0,  0}, { 0,  1}, { 0, -1}}, .anchors = {{ 0,  1}, { 0, -1}, { 0,  0}}},
            {.codeName = 'd', .nAnchors = 3, .squares = {{ 0,  0}, { 0, -1}, { 1,  0}}, .anchors = {{ 0,  0}, { 0, -1}, { 1,  0}}}
    };

    struct FourSquareGamePiece {char codeName; int nAnchors; int squares[4][2], anchors[4][2];};
    struct FourSquareGamePiece fourSquareGamePieces[] = {
            {.codeName = 'e', .nAnchors = 2, .squares = {{ 0,  0}, { 0,  1}, { 0,  2}, { 0, -1}}, .anchors = {{ 0,  2}, { 0, -1}, { 0,  0}, { 0,  0}}},
            {.codeName = 'f', .nAnchors = 3, .squares = {{ 0,  0}, { 0,  1}, {-1,  1}, { 0, -1}}, .anchors = {{ 0,  1}, {-1,  1}, { 0, -1}, { 0,  0}}},
            {.codeName = 'g', .nAnchors = 3, .squares = {{ 0,  0}, { 0,  1}, { 0, -1}, { 1,  0}}, .anchors = {{ 0,  1}, { 1,  0}, { 0, -1}, { 0,  0}}},
            {.codeName = 'h', .nAnchors = 4, .squares = {{ 0,  0}, { 1,  0}, { 0,  1}, { 1,  1}}, .anchors = {{ 0,  0}, { 1,  0}, { 0,  1}, { 1,  1}}},
            {.codeName = 'i', .nAnchors = 4, .squares = {{ 0,  0}, {-1,  0}, { 0,  1}, { 1,  1}}, .anchors = {{ 0,  0}, {-1,  0}, { 0,  1}, { 1,  1}}}
    };

    struct FiveSquareGamePiece {char codeName; int nAnchors; int squares[5][2], anchors[5][2];};
    struct FiveSquareGamePiece fiveSquareGamePieces[] = {
            {.codeName = 'j', .nAnchors = 2, .squares = {{ 0,  0}, { 0, -1}, { 0, -2}, { 0,  1}, { 0,  2}}, .anchors = {{ 0, -2}, { 0,  2}, { 0,  0}, { 0,  0}, { 0,  0}}},
            {.codeName = 'k', .nAnchors = 3, .squares = {{ 0,  0}, { 0, -1}, { 0, -2}, { 0,  1}, {-1,  1}}, .anchors = {{ 0, -2}, { 0,  1}, {-1,  1}, { 0,  0}, { 0,  0}}},
            {.codeName = 'l', .nAnchors = 4, .squares = {{ 0,  0}, { 0, -1}, { 0, -2}, {-1,  0}, {-1,  1}}, .anchors = {{ 0, -2}, {-1,  0}, {-1,  1}, { 0,  0}, { 0,  0}}},
            {.codeName = 'm', .nAnchors = 4, .squares = {{ 0,  0}, { 0, -1}, { 0,  1}, {-1,  0}, {-1,  1}}, .anchors = {{ 0, -1}, {-1,  0}, {-1,  1}, { 0,  1}, { 0,  0}}},
            {.codeName = 'n', .nAnchors = 4, .squares = {{ 0,  0}, { 0, -1}, { 0,  1}, {-1, -1}, {-1,  1}}, .anchors = {{-1, -1}, { 0, -1}, {-1,  1}, { 0,  1}, { 0,  0}}},
            {.codeName = 'o', .nAnchors = 3, .squares = {{ 0,  0}, { 0, -1}, { 1,  0}, { 0,  1}, { 0,  2}}, .anchors = {{ 0,  2}, { 1,  0}, { 0, -1}, { 0,  0}, { 0,  0}}},
            {.codeName = 'p', .nAnchors = 3, .squares = {{ 0,  0}, { 0, -1}, { 0,  1}, {-1,  1}, { 1,  1}}, .anchors = {{ 0, -1}, {-1,  1}, { 1,  1}, { 0,  0}, { 0,  0}}},
            {.codeName = 'q', .nAnchors = 3, .squares = {{ 0,  0}, { 0, -1}, { 0, -2}, { 1,  0}, { 2,  0}}, .anchors = {{ 0,  0}, { 0, -2}, { 2,  0}, { 0,  0}, { 0,  0}}},
            {.codeName = 'r', .nAnchors = 5, .squares = {{ 0,  0}, { 0, -1}, {-1, -1}, { 1,  0}, { 1,  1}}, .anchors = {{ 0,  0}, { 0, -1}, {-1, -1}, { 1,  0}, { 1,  1}}},
            {.codeName = 's', .nAnchors = 4, .squares = {{ 0,  0}, { 1,  0}, { 1,  1}, {-1,  0}, {-1, -1}}, .anchors = {{ 1,  0}, { 1,  1}, {-1,  0}, {-1, -1}, { 0,  0}}},
            {.codeName = 't', .nAnchors = 4, .squares = {{ 0,  0}, { 1,  0}, { 0,  1}, {-1,  0}, {-1, -1}}, .anchors = {{ 1,  0}, { 0,  1}, {-1,  0}, {-1, -1}, { 0,  0}}},
            {.codeName = 'u', .nAnchors = 4, .squares = {{ 0,  0}, { 1,  0}, { 0,  1}, {-1,  0}, { 0, -1}}, .anchors = {{ 1,  0}, { 0,  1}, {-1,  0}, { 0, -1}, { 0,  0}}}
    };

    for (auto gamePiece : oneSquareGamePieces)
        initialSetOfGamePieces->push_back(new GamePiece(gamePiece.codeName, 1, gamePiece.squares, gamePiece.nAnchors, gamePiece.anchors));

    for (auto gamePiece : twoSquareGamePieces)
        initialSetOfGamePieces->push_back(new GamePiece(gamePiece.codeName, 2, gamePiece.squares, gamePiece.nAnchors, gamePiece.anchors));

    for (auto gamePiece : threeSquareGamePieces)
        initialSetOfGamePieces->push_back(new GamePiece(gamePiece.codeName, 3, gamePiece.squares, gamePiece.nAnchors, gamePiece.anchors));

    for (auto gamePiece : fourSquareGamePieces)
        initialSetOfGamePieces->push_back(new GamePiece(gamePiece.codeName, 4, gamePiece.squares, gamePiece.nAnchors, gamePiece.anchors));

    for (auto gamePiece : fiveSquareGamePieces)
        initialSetOfGamePieces->push_back(new GamePiece(gamePiece.codeName, 5, gamePiece.squares, gamePiece.nAnchors, gamePiece.anchors));

    return initialSetOfGamePieces;
}

char GamePiece::getCodeName() {
    return codeName;
}

void GamePiece::transformPiece(int transformation) {
    this->transformation = transformation;

    for (auto & square : *squares)
        square->transformPosition(transformations[transformation]);

    for (auto & anchor : *anchors)
        anchor->transformPosition(transformations[transformation]);
}

std::vector<Position *> *GamePiece::getSquares() {
    return squares;
}
