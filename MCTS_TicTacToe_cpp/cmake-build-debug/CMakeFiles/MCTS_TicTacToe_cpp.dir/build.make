# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/joaovieira/Desktop/BlokusDuo/MCTS_TicTacToe_cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/joaovieira/Desktop/BlokusDuo/MCTS_TicTacToe_cpp/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/MCTS_TicTacToe_cpp.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/MCTS_TicTacToe_cpp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MCTS_TicTacToe_cpp.dir/flags.make

CMakeFiles/MCTS_TicTacToe_cpp.dir/main.cpp.o: CMakeFiles/MCTS_TicTacToe_cpp.dir/flags.make
CMakeFiles/MCTS_TicTacToe_cpp.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/joaovieira/Desktop/BlokusDuo/MCTS_TicTacToe_cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MCTS_TicTacToe_cpp.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MCTS_TicTacToe_cpp.dir/main.cpp.o -c /Users/joaovieira/Desktop/BlokusDuo/MCTS_TicTacToe_cpp/main.cpp

CMakeFiles/MCTS_TicTacToe_cpp.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MCTS_TicTacToe_cpp.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/joaovieira/Desktop/BlokusDuo/MCTS_TicTacToe_cpp/main.cpp > CMakeFiles/MCTS_TicTacToe_cpp.dir/main.cpp.i

CMakeFiles/MCTS_TicTacToe_cpp.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MCTS_TicTacToe_cpp.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/joaovieira/Desktop/BlokusDuo/MCTS_TicTacToe_cpp/main.cpp -o CMakeFiles/MCTS_TicTacToe_cpp.dir/main.cpp.s

CMakeFiles/MCTS_TicTacToe_cpp.dir/MonteCarloTreeSearch.cpp.o: CMakeFiles/MCTS_TicTacToe_cpp.dir/flags.make
CMakeFiles/MCTS_TicTacToe_cpp.dir/MonteCarloTreeSearch.cpp.o: ../MonteCarloTreeSearch.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/joaovieira/Desktop/BlokusDuo/MCTS_TicTacToe_cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/MCTS_TicTacToe_cpp.dir/MonteCarloTreeSearch.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MCTS_TicTacToe_cpp.dir/MonteCarloTreeSearch.cpp.o -c /Users/joaovieira/Desktop/BlokusDuo/MCTS_TicTacToe_cpp/MonteCarloTreeSearch.cpp

CMakeFiles/MCTS_TicTacToe_cpp.dir/MonteCarloTreeSearch.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MCTS_TicTacToe_cpp.dir/MonteCarloTreeSearch.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/joaovieira/Desktop/BlokusDuo/MCTS_TicTacToe_cpp/MonteCarloTreeSearch.cpp > CMakeFiles/MCTS_TicTacToe_cpp.dir/MonteCarloTreeSearch.cpp.i

CMakeFiles/MCTS_TicTacToe_cpp.dir/MonteCarloTreeSearch.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MCTS_TicTacToe_cpp.dir/MonteCarloTreeSearch.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/joaovieira/Desktop/BlokusDuo/MCTS_TicTacToe_cpp/MonteCarloTreeSearch.cpp -o CMakeFiles/MCTS_TicTacToe_cpp.dir/MonteCarloTreeSearch.cpp.s

CMakeFiles/MCTS_TicTacToe_cpp.dir/Board.cpp.o: CMakeFiles/MCTS_TicTacToe_cpp.dir/flags.make
CMakeFiles/MCTS_TicTacToe_cpp.dir/Board.cpp.o: ../Board.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/joaovieira/Desktop/BlokusDuo/MCTS_TicTacToe_cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/MCTS_TicTacToe_cpp.dir/Board.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MCTS_TicTacToe_cpp.dir/Board.cpp.o -c /Users/joaovieira/Desktop/BlokusDuo/MCTS_TicTacToe_cpp/Board.cpp

CMakeFiles/MCTS_TicTacToe_cpp.dir/Board.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MCTS_TicTacToe_cpp.dir/Board.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/joaovieira/Desktop/BlokusDuo/MCTS_TicTacToe_cpp/Board.cpp > CMakeFiles/MCTS_TicTacToe_cpp.dir/Board.cpp.i

CMakeFiles/MCTS_TicTacToe_cpp.dir/Board.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MCTS_TicTacToe_cpp.dir/Board.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/joaovieira/Desktop/BlokusDuo/MCTS_TicTacToe_cpp/Board.cpp -o CMakeFiles/MCTS_TicTacToe_cpp.dir/Board.cpp.s

CMakeFiles/MCTS_TicTacToe_cpp.dir/Tree.cpp.o: CMakeFiles/MCTS_TicTacToe_cpp.dir/flags.make
CMakeFiles/MCTS_TicTacToe_cpp.dir/Tree.cpp.o: ../Tree.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/joaovieira/Desktop/BlokusDuo/MCTS_TicTacToe_cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/MCTS_TicTacToe_cpp.dir/Tree.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MCTS_TicTacToe_cpp.dir/Tree.cpp.o -c /Users/joaovieira/Desktop/BlokusDuo/MCTS_TicTacToe_cpp/Tree.cpp

CMakeFiles/MCTS_TicTacToe_cpp.dir/Tree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MCTS_TicTacToe_cpp.dir/Tree.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/joaovieira/Desktop/BlokusDuo/MCTS_TicTacToe_cpp/Tree.cpp > CMakeFiles/MCTS_TicTacToe_cpp.dir/Tree.cpp.i

CMakeFiles/MCTS_TicTacToe_cpp.dir/Tree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MCTS_TicTacToe_cpp.dir/Tree.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/joaovieira/Desktop/BlokusDuo/MCTS_TicTacToe_cpp/Tree.cpp -o CMakeFiles/MCTS_TicTacToe_cpp.dir/Tree.cpp.s

CMakeFiles/MCTS_TicTacToe_cpp.dir/Node.cpp.o: CMakeFiles/MCTS_TicTacToe_cpp.dir/flags.make
CMakeFiles/MCTS_TicTacToe_cpp.dir/Node.cpp.o: ../Node.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/joaovieira/Desktop/BlokusDuo/MCTS_TicTacToe_cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/MCTS_TicTacToe_cpp.dir/Node.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MCTS_TicTacToe_cpp.dir/Node.cpp.o -c /Users/joaovieira/Desktop/BlokusDuo/MCTS_TicTacToe_cpp/Node.cpp

CMakeFiles/MCTS_TicTacToe_cpp.dir/Node.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MCTS_TicTacToe_cpp.dir/Node.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/joaovieira/Desktop/BlokusDuo/MCTS_TicTacToe_cpp/Node.cpp > CMakeFiles/MCTS_TicTacToe_cpp.dir/Node.cpp.i

CMakeFiles/MCTS_TicTacToe_cpp.dir/Node.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MCTS_TicTacToe_cpp.dir/Node.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/joaovieira/Desktop/BlokusDuo/MCTS_TicTacToe_cpp/Node.cpp -o CMakeFiles/MCTS_TicTacToe_cpp.dir/Node.cpp.s

CMakeFiles/MCTS_TicTacToe_cpp.dir/State.cpp.o: CMakeFiles/MCTS_TicTacToe_cpp.dir/flags.make
CMakeFiles/MCTS_TicTacToe_cpp.dir/State.cpp.o: ../State.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/joaovieira/Desktop/BlokusDuo/MCTS_TicTacToe_cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/MCTS_TicTacToe_cpp.dir/State.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MCTS_TicTacToe_cpp.dir/State.cpp.o -c /Users/joaovieira/Desktop/BlokusDuo/MCTS_TicTacToe_cpp/State.cpp

CMakeFiles/MCTS_TicTacToe_cpp.dir/State.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MCTS_TicTacToe_cpp.dir/State.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/joaovieira/Desktop/BlokusDuo/MCTS_TicTacToe_cpp/State.cpp > CMakeFiles/MCTS_TicTacToe_cpp.dir/State.cpp.i

CMakeFiles/MCTS_TicTacToe_cpp.dir/State.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MCTS_TicTacToe_cpp.dir/State.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/joaovieira/Desktop/BlokusDuo/MCTS_TicTacToe_cpp/State.cpp -o CMakeFiles/MCTS_TicTacToe_cpp.dir/State.cpp.s

CMakeFiles/MCTS_TicTacToe_cpp.dir/UCT.cpp.o: CMakeFiles/MCTS_TicTacToe_cpp.dir/flags.make
CMakeFiles/MCTS_TicTacToe_cpp.dir/UCT.cpp.o: ../UCT.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/joaovieira/Desktop/BlokusDuo/MCTS_TicTacToe_cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/MCTS_TicTacToe_cpp.dir/UCT.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MCTS_TicTacToe_cpp.dir/UCT.cpp.o -c /Users/joaovieira/Desktop/BlokusDuo/MCTS_TicTacToe_cpp/UCT.cpp

CMakeFiles/MCTS_TicTacToe_cpp.dir/UCT.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MCTS_TicTacToe_cpp.dir/UCT.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/joaovieira/Desktop/BlokusDuo/MCTS_TicTacToe_cpp/UCT.cpp > CMakeFiles/MCTS_TicTacToe_cpp.dir/UCT.cpp.i

CMakeFiles/MCTS_TicTacToe_cpp.dir/UCT.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MCTS_TicTacToe_cpp.dir/UCT.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/joaovieira/Desktop/BlokusDuo/MCTS_TicTacToe_cpp/UCT.cpp -o CMakeFiles/MCTS_TicTacToe_cpp.dir/UCT.cpp.s

CMakeFiles/MCTS_TicTacToe_cpp.dir/Position.cpp.o: CMakeFiles/MCTS_TicTacToe_cpp.dir/flags.make
CMakeFiles/MCTS_TicTacToe_cpp.dir/Position.cpp.o: ../Position.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/joaovieira/Desktop/BlokusDuo/MCTS_TicTacToe_cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/MCTS_TicTacToe_cpp.dir/Position.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MCTS_TicTacToe_cpp.dir/Position.cpp.o -c /Users/joaovieira/Desktop/BlokusDuo/MCTS_TicTacToe_cpp/Position.cpp

CMakeFiles/MCTS_TicTacToe_cpp.dir/Position.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MCTS_TicTacToe_cpp.dir/Position.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/joaovieira/Desktop/BlokusDuo/MCTS_TicTacToe_cpp/Position.cpp > CMakeFiles/MCTS_TicTacToe_cpp.dir/Position.cpp.i

CMakeFiles/MCTS_TicTacToe_cpp.dir/Position.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MCTS_TicTacToe_cpp.dir/Position.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/joaovieira/Desktop/BlokusDuo/MCTS_TicTacToe_cpp/Position.cpp -o CMakeFiles/MCTS_TicTacToe_cpp.dir/Position.cpp.s

# Object files for target MCTS_TicTacToe_cpp
MCTS_TicTacToe_cpp_OBJECTS = \
"CMakeFiles/MCTS_TicTacToe_cpp.dir/main.cpp.o" \
"CMakeFiles/MCTS_TicTacToe_cpp.dir/MonteCarloTreeSearch.cpp.o" \
"CMakeFiles/MCTS_TicTacToe_cpp.dir/Board.cpp.o" \
"CMakeFiles/MCTS_TicTacToe_cpp.dir/Tree.cpp.o" \
"CMakeFiles/MCTS_TicTacToe_cpp.dir/Node.cpp.o" \
"CMakeFiles/MCTS_TicTacToe_cpp.dir/State.cpp.o" \
"CMakeFiles/MCTS_TicTacToe_cpp.dir/UCT.cpp.o" \
"CMakeFiles/MCTS_TicTacToe_cpp.dir/Position.cpp.o"

# External object files for target MCTS_TicTacToe_cpp
MCTS_TicTacToe_cpp_EXTERNAL_OBJECTS =

MCTS_TicTacToe_cpp: CMakeFiles/MCTS_TicTacToe_cpp.dir/main.cpp.o
MCTS_TicTacToe_cpp: CMakeFiles/MCTS_TicTacToe_cpp.dir/MonteCarloTreeSearch.cpp.o
MCTS_TicTacToe_cpp: CMakeFiles/MCTS_TicTacToe_cpp.dir/Board.cpp.o
MCTS_TicTacToe_cpp: CMakeFiles/MCTS_TicTacToe_cpp.dir/Tree.cpp.o
MCTS_TicTacToe_cpp: CMakeFiles/MCTS_TicTacToe_cpp.dir/Node.cpp.o
MCTS_TicTacToe_cpp: CMakeFiles/MCTS_TicTacToe_cpp.dir/State.cpp.o
MCTS_TicTacToe_cpp: CMakeFiles/MCTS_TicTacToe_cpp.dir/UCT.cpp.o
MCTS_TicTacToe_cpp: CMakeFiles/MCTS_TicTacToe_cpp.dir/Position.cpp.o
MCTS_TicTacToe_cpp: CMakeFiles/MCTS_TicTacToe_cpp.dir/build.make
MCTS_TicTacToe_cpp: CMakeFiles/MCTS_TicTacToe_cpp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/joaovieira/Desktop/BlokusDuo/MCTS_TicTacToe_cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable MCTS_TicTacToe_cpp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MCTS_TicTacToe_cpp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MCTS_TicTacToe_cpp.dir/build: MCTS_TicTacToe_cpp

.PHONY : CMakeFiles/MCTS_TicTacToe_cpp.dir/build

CMakeFiles/MCTS_TicTacToe_cpp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MCTS_TicTacToe_cpp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MCTS_TicTacToe_cpp.dir/clean

CMakeFiles/MCTS_TicTacToe_cpp.dir/depend:
	cd /Users/joaovieira/Desktop/BlokusDuo/MCTS_TicTacToe_cpp/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/joaovieira/Desktop/BlokusDuo/MCTS_TicTacToe_cpp /Users/joaovieira/Desktop/BlokusDuo/MCTS_TicTacToe_cpp /Users/joaovieira/Desktop/BlokusDuo/MCTS_TicTacToe_cpp/cmake-build-debug /Users/joaovieira/Desktop/BlokusDuo/MCTS_TicTacToe_cpp/cmake-build-debug /Users/joaovieira/Desktop/BlokusDuo/MCTS_TicTacToe_cpp/cmake-build-debug/CMakeFiles/MCTS_TicTacToe_cpp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MCTS_TicTacToe_cpp.dir/depend
