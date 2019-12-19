cmake_minimum_required(VERSION 3.15)
project(MCTS_TicTacToe_c C)

set(CMAKE_C_STANDARD 99)

add_executable(MCTS_TicTacToe_c main.c DoublyLinkedList.c DoublyLinkedList.h Tree.c Tree.h Board.c Board.h Position.c Position.h Player.c Player.h)