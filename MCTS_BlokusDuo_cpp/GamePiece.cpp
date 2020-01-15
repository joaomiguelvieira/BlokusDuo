//
// Created by joaovieira on 12/24/19.
//

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
GamePiece::GamePiece(char codeName, std::vector<std::vector<int>> squares, std::vector<std::vector<int>> anchors) {
    this->codeName = codeName;
    this->transformation = 0;

    this->squares = new std::vector<Position *>();
    for (auto & square : squares)
        this->squares->push_back(new Position(square[0], square[1]));

    this->anchors = new std::vector<Position *>();
    for (auto & anchor : anchors)
        this->anchors->push_back(new Position(anchor[0], anchor[1]));
}

GamePiece::~GamePiece() {
    for (auto & anchor : *anchors)
        delete anchor;
    delete anchors;

    for (auto & square : *squares)
        delete square;
    delete squares;
}

std::list<std::vector<GamePiece *> *> *GamePiece::getInitialSetOfGamePieces() {
    auto initialSetOfGamePieces = new std::list<std::vector<GamePiece *> *>();

    struct DefaultGamePiece {char codeName; std::vector<std::vector<int>> squares, anchors; std::vector<int> variants;};
    std::vector<struct DefaultGamePiece> defaultGamePieces = {
            {.codeName = 'a', .squares = {{ 0,  0}},                                         .anchors = {{ 0,  0}},                                         .variants = {0}},
            {.codeName = 'b', .squares = {{ 0,  0}, { 0,  1}},                               .anchors = {{ 0,  0}, { 0,  1}},                               .variants = {0, 2}},
            {.codeName = 'c', .squares = {{ 0,  0}, { 0,  1}, { 0, -1}},                     .anchors = {{ 0,  1}, { 0, -1}},                               .variants = {0, 2}},
            {.codeName = 'd', .squares = {{ 0,  0}, { 0, -1}, { 1,  0}},                     .anchors = {{ 0,  0}, { 0, -1}, { 1,  0}},                     .variants = {0, 1, 2, 3}},
            {.codeName = 'e', .squares = {{ 0,  0}, { 0,  1}, { 0,  2}, { 0, -1}},           .anchors = {{ 0,  2}, { 0, -1}},                               .variants = {0, 2}},
            {.codeName = 'f', .squares = {{ 0,  0}, { 0,  1}, {-1,  1}, { 0, -1}},           .anchors = {{ 0,  1}, {-1,  1}, { 0, -1}},                     .variants = {0, 1, 2, 3, 4, 5, 6, 7}},
            {.codeName = 'g', .squares = {{ 0,  0}, { 0,  1}, { 0, -1}, { 1,  0}},           .anchors = {{ 0,  1}, { 1,  0}, { 0, -1}},                     .variants = {0, 1, 2, 6}},
            {.codeName = 'h', .squares = {{ 0,  0}, { 1,  0}, { 0,  1}, { 1,  1}},           .anchors = {{ 0,  0}, { 1,  0}, { 0,  1}, { 1,  1}},           .variants = {0}},
            {.codeName = 'i', .squares = {{ 0,  0}, {-1,  0}, { 0,  1}, { 1,  1}},           .anchors = {{ 0,  0}, {-1,  0}, { 0,  1}, { 1,  1}},           .variants = {0, 1, 2, 3}},
            {.codeName = 'j', .squares = {{ 0,  0}, { 0, -1}, { 0, -2}, { 0,  1}, { 0,  2}}, .anchors = {{ 0, -2}, { 0,  2}},                               .variants = {0, 2}},
            {.codeName = 'k', .squares = {{ 0,  0}, { 0, -1}, { 0, -2}, { 0,  1}, {-1,  1}}, .anchors = {{ 0, -2}, { 0,  1}, {-1,  1}},                     .variants = {0, 1, 2, 3, 4, 5, 6, 7}},
            {.codeName = 'l', .squares = {{ 0,  0}, { 0, -1}, { 0, -2}, {-1,  0}, {-1,  1}}, .anchors = {{ 0, -2}, {-1,  0}, {-1,  1}},                     .variants = {0, 1, 2, 3, 4, 5, 6, 7}},
            {.codeName = 'm', .squares = {{ 0,  0}, { 0, -1}, { 0,  1}, {-1,  0}, {-1,  1}}, .anchors = {{ 0, -1}, {-1,  0}, {-1,  1}, { 0,  1}},           .variants = {0, 1, 2, 3, 4, 5, 6, 7}},
            {.codeName = 'n', .squares = {{ 0,  0}, { 0, -1}, { 0,  1}, {-1, -1}, {-1,  1}}, .anchors = {{-1, -1}, { 0, -1}, {-1,  1}, { 0,  1}},           .variants = {0, 1, 2, 6}},
            {.codeName = 'o', .squares = {{ 0,  0}, { 0, -1}, { 1,  0}, { 0,  1}, { 0,  2}}, .anchors = {{ 0,  2}, { 1,  0}, { 0, -1}},                     .variants = {0, 1, 2, 3, 4, 5, 6, 7}},
            {.codeName = 'p', .squares = {{ 0,  0}, { 0, -1}, { 0,  1}, {-1,  1}, { 1,  1}}, .anchors = {{ 0, -1}, {-1,  1}, { 1,  1}},                     .variants = {0, 2, 3, 4}},
            {.codeName = 'q', .squares = {{ 0,  0}, { 0, -1}, { 0, -2}, { 1,  0}, { 2,  0}}, .anchors = {{ 0,  0}, { 0, -2}, { 2,  0}},                     .variants = {0, 1, 2, 3}},
            {.codeName = 'r', .squares = {{ 0,  0}, { 0, -1}, {-1, -1}, { 1,  0}, { 1,  1}}, .anchors = {{ 0,  0}, { 0, -1}, {-1, -1}, { 1,  0}, { 1,  1}}, .variants = {0, 1, 2, 3}},
            {.codeName = 's', .squares = {{ 0,  0}, { 1,  0}, { 1,  1}, {-1,  0}, {-1, -1}}, .anchors = {{ 1,  0}, { 1,  1}, {-1,  0}, {-1, -1}},           .variants = {0, 1, 2, 3}},
            {.codeName = 't', .squares = {{ 0,  0}, { 1,  0}, { 0,  1}, {-1,  0}, {-1, -1}}, .anchors = {{ 1,  0}, { 0,  1}, {-1,  0}, {-1, -1}},           .variants = {0, 1, 2, 3, 4, 5, 6, 7}},
            {.codeName = 'u', .squares = {{ 0,  0}, { 1,  0}, { 0,  1}, {-1,  0}, { 0, -1}}, .anchors = {{ 1,  0}, { 0,  1}, {-1,  0}, { 0, -1}},           .variants = {0}}
    };

    for (const auto& defaultGamePiece : defaultGamePieces) {
        auto gamePiece = new std::vector<GamePiece *>();

        for (const auto& transformation : defaultGamePiece.variants) {
            auto variant = new GamePiece(defaultGamePiece.codeName, defaultGamePiece.squares, defaultGamePiece.anchors);
            variant->transformPiece(transformation);
            gamePiece->push_back(variant);
        }

        initialSetOfGamePieces->push_back(gamePiece);
    }

    return initialSetOfGamePieces;
}

char GamePiece::getCodeName() {
    return codeName;
}

void GamePiece::transformPiece(int transformation) {
    this->transformation = transformation;

    for (auto & square : *squares)
        square->transform(transformations[transformation]);

    for (auto & anchor : *anchors)
        anchor->transform(transformations[transformation]);
}

std::vector<Position *> *GamePiece::getSquares() {
    return squares;
}

std::vector<Position *> *GamePiece::getAnchors() {
    return anchors;
}

int GamePiece::getTransformation() {
    return transformation;
}

bool GamePiece::equals(GamePiece *gamePiece) {
    if (this == gamePiece) return true;
    if (gamePiece == nullptr) return false;
    return codeName == gamePiece->codeName && transformation == gamePiece->transformation;
}
