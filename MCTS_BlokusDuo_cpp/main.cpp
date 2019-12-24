#include <algorithm>
#include "GamePiece.h"

int main() {
    auto initialSetOfGamePieces = GamePiece::getInitialSetOfGamePieces();

    auto testPiece = *std::find_if(initialSetOfGamePieces->begin(), initialSetOfGamePieces->end(), [](GamePiece *gamePiece){return gamePiece->getCodeName() == 't';});

    for (int i = 0; i < GamePiece::N_TRANSFORMATIONS; ++i) {
        auto transformedPiece = new GamePiece(testPiece);
        transformedPiece->transformPiece(i);
        transformedPiece->printGamePiece();
        delete transformedPiece;
    }

    for (auto & gamePiece : *initialSetOfGamePieces) {
        delete gamePiece;
    }
    delete initialSetOfGamePieces;

    return 0;
}
