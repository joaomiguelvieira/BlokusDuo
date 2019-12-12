from Board import Board
from MonteCarloTreeSearch import MonteCarloTreeSearch

board = Board()

mcts1 = MonteCarloTreeSearch()
mcts3 = MonteCarloTreeSearch()

player = Board.P1

total_moves = Board.DEFAULT_BOARD_SIZE * Board.DEFAULT_BOARD_SIZE
for i in range(0, total_moves):
    if player == Board.P1:
        board = mcts3.find_next_move(board, player)
        print("Player 1")
    else:
        board = mcts1.find_next_move(board, player)
        print("Player 2")

    if board.check_status() != -1:
        break

    player = Board.P2 if player == Board.P1 else Board.P1

win_status = board.check_status()
print("Win status: " + str(win_status))
print(board)
