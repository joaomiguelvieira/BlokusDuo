#include <algorithm>
#include <iostream>
#include "GamePiece.h"
#include "Player.h"

int main() {
    auto player1 = new Player();

    std::cout << "Player " << player1->getPlayerId() << " has " << player1->getRemainingGamePieces()->size() << " remaining game pieces:\n";
    for (auto & gamePiece : *player1->getRemainingGamePieces())
        std::cout << (*gamePiece)[0]->getCodeName() << " has " << gamePiece->size() << " variant(s)" << "\n";

    delete player1;

    return 0;
}
