#include <iostream>
#include <cassert>
#include "GamePiece.h"
#include "MonteCarloTreeSearch.h"
#include <SerialPort.h>

#define SERIAL_PORT "/dev/ttyUSB1"
#define TEAM_ID "01"
#define SIM_MILLIS 850

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
        } else if (move == "last" || move == "l")
            std::cout << "Last move was " << last_move << std::endl;
        else if (mcts->performNextMove(move) == 0)
            last_move = move;
    }

    delete mcts;
}

void officialMatch() {
    auto serial = new LibSerial::SerialPort(SERIAL_PORT, LibSerial::BaudRate::BAUD_115200,
                                            LibSerial::CharacterSize::CHAR_SIZE_DEFAULT,
                                            LibSerial::FlowControl::FLOW_CONTROL_DEFAULT,
                                            LibSerial::Parity::PARITY_DEFAULT,
                                            LibSerial::StopBits::STOP_BITS_DEFAULT);

    // play game
    MonteCarloTreeSearch *mcts = nullptr;

    std::string bestMove, buffer;

    while (true) {
        // wait for arbiter to send message
        serial->Read(buffer, 1);

        switch (buffer[0]) {
            // init code answer with team id
            case '0':
                buffer = "1";
                buffer += TEAM_ID;
                break;
                // ask for first move of the first player
            case '2':
                serial->Read(buffer, 1);
                mcts = (buffer[0] == '5') ? new MonteCarloTreeSearch(SIM_MILLIS) : new MonteCarloTreeSearch(SIM_MILLIS, true);
                bestMove = mcts->findNextMove();
                mcts->performNextMove(bestMove);
                buffer = bestMove;
                break;
                // ask for second move of the second player
            case '3':
                serial->Read(buffer, 5);
                mcts = (buffer[0] == 'A') ? new MonteCarloTreeSearch(SIM_MILLIS) : new MonteCarloTreeSearch(SIM_MILLIS, true);
                mcts->performNextMove(buffer.substr(1));
                bestMove = mcts->findNextMove();
                mcts->performNextMove(bestMove);
                buffer = bestMove;
                break;
                // ask for move
            case '4':
                assert(mcts != nullptr);
                serial->Read(buffer, 4);
                mcts->performNextMove(buffer);
                bestMove = mcts->findNextMove();
                mcts->performNextMove(bestMove);
                buffer = bestMove;
                break;
                // finish game
            case '9':
                goto end;
        }

        serial->Write(buffer);
    }

    end:
    delete mcts;
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
