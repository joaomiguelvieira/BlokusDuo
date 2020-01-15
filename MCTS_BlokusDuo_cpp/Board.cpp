//
// Created by joaovieira on 12/24/19.
//

#include <iostream>
#include "Board.h"

Board::Board() {
    for (auto & i : board)
        for (unsigned char & j : i)
            j = 0;
}

Board::Board(Board *board) {
    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            this->board[i][j] = board->board[i][j];
}

std::list<Position *> *Board::getAllAnchors(int playerId) {
    auto anchors = new std::list<Position *>();

    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            if (isAnchor(i, j, playerId))
                anchors->push_back(new Position(i, j));

    return anchors;
}

bool Board::hasCornerContact(int x, int y, int playerId) {
    return (x - 1 >= 0 && y - 1 >= 0 && board[x - 1][y - 1] == playerId) ||
           (x - 1 >= 0 && y + 1 < BOARD_SIZE && board[x - 1][y + 1] == playerId) ||
           (x + 1 < BOARD_SIZE && y - 1 >= 0 && board[x + 1][y - 1] == playerId) ||
           (x + 1 < BOARD_SIZE && y + 1 < BOARD_SIZE && board[x + 1][y + 1] == playerId);

}

bool Board::hasEdgeContact(int x, int y, int playerId) {
    return (x - 1 >= 0 && board[x - 1][y] == playerId) || (x + 1 < BOARD_SIZE && board[x + 1][y] == playerId) ||
           (y - 1 >= 0 && board[x][y - 1] == playerId) || (y + 1 < BOARD_SIZE && board[x][y + 1] == playerId);

}

void Board::performMove(Player *player, Move *move) {
    for (auto & square : *move->getGamePiece()->getSquares())
        board[square->getX() + move->getCenter()->getX()][square->getY() + move->getCenter()->getY()] = player->getPlayerId();
}

bool Board::checkValidMove(Player *player, GamePiece *gamePiece, Position *center) {
    for (auto & square : *gamePiece->getSquares()) {
        auto x = square->getX() + center->getX();
        auto y = square->getY() + center->getY();

        if (!respectsBoundaries(x, y) || isOccupied(x, y) || hasEdgeContact(x, y, player->getPlayerId()))
            return false;
    }

    return true;
}

std::list<Move *> *Board::getAllValidMoves(Player *player) {
    // all valid moves cover 5, 5
    if (!isOccupied(4, 4))
        return getMovesCoveringPosition(player, 4, 4);
    // all valid moves cover a, a
    if (!isOccupied(9, 9))
        return getMovesCoveringPosition(player, 9, 9);
    // valid moves are attached to anchors
    else
        return getMovesFromAnchors(player, getAllAnchors(player->getPlayerId()));
}

bool Board::isOccupied(int x, int y) {
    return board[x][y] != 0;
}

bool Board::respectsBoundaries(int x, int y) {
    return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
}

bool Board::isAnchor(int x, int y, int playerId) {
    return respectsBoundaries(x, y) && !isOccupied(x, y) && hasCornerContact(x, y, playerId) && !hasEdgeContact(x, y, playerId);
}

std::string Board::toString() {
    std::string text = "    ";
    char axis[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e'};
    for (auto tick : axis) {
        text += tick;
        text += " ";
    }
    text += "\n";
    text += "  + + + + + + + + + + + + + + + +\n";
    for (int i = 0; i < BOARD_SIZE; i++) {
        text += axis[i];
        text += " + ";
        for (auto & j : board) {
            if (j[i] == 0)
                text += "  ";
            else
                text += std::to_string(j[i]) + " ";
        }
        text += "+\n";
    }
    text += "  + + + + + + + + + + + + + + + +";

    return text;
}

std::list<Move *> *Board::getMovesFromAnchors(Player *player, std::list<Position *> *boardAnchors) {
    auto validMoves = new std::list<Move *>();

    for (auto boardAnchor : *boardAnchors) {
        for (auto gamePiece : *player->getRemainingGamePieces()) {
            for (auto variant : *gamePiece) {
                for (auto anchor : *variant->getAnchors()) {
                    auto center = new Position(boardAnchor);
                    center->subtract(anchor);

                    if (checkValidMove(player, variant, center))
                        validMoves->push_back(new Move(variant, center));
                }
            }
        }
    }

    return validMoves;
}

std::list<Move *> *Board::getMovesCoveringPosition(Player *player, int x, int y) {
    auto validMoves = new std::list<Move *>();

    for (auto gamePiece : *player->getRemainingGamePieces()) {
        for (auto variant : *gamePiece) {
            for (auto square : *variant->getSquares()) {
                auto center = new Position(x, y);
                center->subtract(square);

                validMoves->push_back(new Move(variant, center));
            }
        }
    }

    return validMoves;
}

std::list<Move *> *
Board::getAllValidMoves(Player *player, std::list<Move *> *previouslyValidMoves, Move *previouslyPlayedMove,
                        Board *previousBoard) {
    auto validMoves = new std::list<Move *>();

    // in case the player has quited return empty list
    if (player->getQuited())
        return validMoves;

    // delete obsolete moves
    for (auto previouslyValidMove : *previouslyValidMoves) {
        if (previouslyValidMove->getGamePiece()->getCodeName() != previouslyPlayedMove->getGamePiece()->getCodeName() &&
            checkValidMove(player, previouslyValidMove->getGamePiece(), previouslyValidMove->getCenter()))
            validMoves->push_back(previouslyValidMove);
    }

    // calculate new anchors
    auto newAnchors = new std::list<Position *>();
    for (auto possibleAnchorSource : *previouslyPlayedMove->getGamePiece()->getAnchors()) {
        int x = possibleAnchorSource->getX() + previouslyPlayedMove->getCenter()->getX();
        int y = possibleAnchorSource->getY() + previouslyPlayedMove->getCenter()->getY();

        if (isAnchor(x - 1, y - 1, player->getPlayerId()) &&
            !previousBoard->isAnchor(x - 1, y - 1, player->getPlayerId()))
            newAnchors->push_back(new Position(x - 1, y - 1));

        if (isAnchor(x + 1, y - 1, player->getPlayerId()) &&
            !previousBoard->isAnchor(x + 1, y - 1, player->getPlayerId()))
            newAnchors->push_back(new Position(x + 1, y - 1));

        if (isAnchor(x - 1, y + 1, player->getPlayerId()) &&
            !previousBoard->isAnchor(x - 1, y + 1, player->getPlayerId()))
            newAnchors->push_back(new Position(x - 1, y + 1));

        if (isAnchor(x + 1, y + 1, player->getPlayerId()) &&
            !previousBoard->isAnchor(x + 1, y + 1, player->getPlayerId()))
            newAnchors->push_back(new Position(x + 1, y + 1));
    }

    // get valid moves from new anchors only
    auto newPossibleMoves = getMovesFromAnchors(player, newAnchors);

    /*================================================================================================================*/
    std::cout << "========== FINDING POSSIBLE MOVES DIFFERENTIALLY ==========" << std::endl;

    auto deterministicMoves = getAllValidMoves(player);

    for (auto deterministicMove : *deterministicMoves) {
        auto oldMove = false;

        for (auto move : *previouslyValidMoves) {
            if (deterministicMove->equals(move)) {
                oldMove = true;
                break;
            }
        }

        if (oldMove) {
            auto detected = false;
            for (auto heuristicMove : *validMoves) {
                if (deterministicMove->equals(heuristicMove)) {
                    detected = true;
                    break;
                }
            }

            if (!detected)
                std::cout << "Failed to predict old move " << Move::moveToString(deterministicMove) << std::endl;
        }
        else {
            auto detected = false;
            for (auto heuristicMove : *newPossibleMoves) {
                if (deterministicMove->equals(heuristicMove)) {
                    detected = true;
                    break;
                }
            }

            if (!detected)
                std::cout << "Failed to predict new move " << Move::moveToString(deterministicMove) << std::endl;
        }
    }
    /*================================================================================================================*/

    // TODO optimize list merge
    for (auto validMove : *newPossibleMoves)
        validMoves->push_back(validMove);

    return validMoves;
}
