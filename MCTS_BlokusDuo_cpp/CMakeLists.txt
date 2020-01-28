cmake_minimum_required(VERSION 3.15)
project(MCTS_BlokusDuo_cpp)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(MCTS_BlokusDuo_cpp main.cpp Board.cpp Board.h Player.cpp Player.h GamePiece.cpp GamePiece.h Position.cpp Position.h Move.cpp Move.h MonteCarloTreeSearch.cpp MonteCarloTreeSearch.h UCT.cpp UCT.h State.cpp State.h Node.cpp Node.h Tree.cpp Tree.h)

include_directories("/usr/local/include/libserial")
target_link_libraries(MCTS_BlokusDuo_cpp "/usr/local/lib64/libserial.so.1")
