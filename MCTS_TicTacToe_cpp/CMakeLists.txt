cmake_minimum_required(VERSION 3.15)
project(MCTS_TicTacToe_cpp)

set(CMAKE_CXX_STANDARD 14)

add_executable(MCTS_TicTacToe_cpp main.cpp MonteCarloTreeSearch.cpp MonteCarloTreeSearch.h Board.cpp Board.h Tree.cpp Tree.h Node.cpp Node.h State.cpp State.h UCT.cpp UCT.h Position.cpp Position.h)