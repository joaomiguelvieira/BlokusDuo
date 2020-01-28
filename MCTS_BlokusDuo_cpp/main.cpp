#include <iostream>
#include <cassert>
#include "GamePiece.h"
#include "MonteCarloTreeSearch.h"

#define TEAM_ID "01"

void playGame(bool evalPerformance = false) {
    auto mcts = new MonteCarloTreeSearch();

    while (mcts->checkStatus() == State::IN_PROGRESS) {
        auto bestMove = mcts->findNextMove();
        mcts->performNextMove(bestMove);
        if (!evalPerformance)
            mcts->printMove();
        else {
            auto round = mcts->getGameTree()->getRoot()->getState()->getMovesPlayed();
            auto simulations = mcts->getGameTree()->getRoot()->getState()->getVisitCount();
            std::cout << "Round " << round << " -> " << simulations << " simulations" << std::endl;
        }
    }

    delete mcts;
}

void interactiveGame() {
    auto mcts = new MonteCarloTreeSearch();

    std::string last_move;
    while (mcts->checkStatus() == State::IN_PROGRESS) {
        mcts->printStatus();
        std::string move;
        std::cin >> move;

        if (move == "hint" || move == "h")
            mcts->printValidMoves();
        else if (move == "simulate" || move == "s")
            std::cout << "Simulated move is " << mcts->findNextMove() << std::endl;
        else if (move == "simulate and play" || move == "sp") {
            auto nextMove = mcts->findNextMove();
            std::cout << "Simulated move is " << nextMove << std::endl;
            mcts->performNextMove(nextMove);
        }
        else if (move == "last" || move == "l")
            std::cout << "Last move was " << last_move << std::endl;
        else
            if (mcts->performNextMove(move) == 0)
                last_move = move;
    }

    delete mcts;
}

#define MSG_TERMINATOR '\0'

void sendSerial(const std::string& buffer) {
    for (int i = 0; buffer[i] != '\0'; i++)
        putchar(buffer[i]);

    putchar(MSG_TERMINATOR);
}

void recvSerial(std::string *buffer) {
    int i = 0;

    do {
        (*buffer)[i] = getchar();
        i++;
    }
    while ((*buffer)[i - 1] != MSG_TERMINATOR);
}

void officialMatch() {
    // TODO open serial

    // play game
    auto mcts = new MonteCarloTreeSearch(900);

    std::string bestMove, buffer;

    while (mcts->checkStatus() == State::IN_PROGRESS) {
        // wait for arbiter to send message
        recvSerial(&buffer);

        switch (buffer[0]) {
            // init code answer with team id
            case '0':
                buffer = "1";
                buffer += TEAM_ID;
                break;
            // ask for first move of the first player
            case '2':
                assert(buffer[1] == '5');
                bestMove = mcts->findNextMove();
                mcts->performNextMove(bestMove);
                buffer = bestMove;
                break;
            // ask for second move of the second player
            case '3':
                assert(buffer[1] == 'A');
                mcts->performNextMove(buffer.substr(2));
                bestMove = mcts->findNextMove();
                mcts->performNextMove(bestMove);
                buffer = bestMove;
                break;
            // ask for move
            case '4':
                mcts->performNextMove(buffer.substr(1));
                bestMove = mcts->findNextMove();
                mcts->performNextMove(bestMove);
                buffer = bestMove;
                break;
            // finish game
            case '9':
                goto end;
        }

        sendSerial(buffer);
    }

    end: delete mcts;
}

int main(int argc, char **argv) {
    std::string mode = "autoplay";

    if (argc > 1)
        mode = argv[1];

    if (mode == "autoplay")
        playGame();
    else if (mode == "performance")
        playGame(true);
    else if (mode == "interactive")
        interactiveGame();
    else if (mode == "match")
        officialMatch();

    return 0;
}
