import numpy as np
from Position import Position


def check_for_win(row):
    is_equal = True
    size = len(row)
    previous = row[0]
    for i in range(1, size):
        if previous != row[i]:
            is_equal = False
            break
        previous = row[i]

    if is_equal:
        return previous
    else:
        return 0


class Board:
    DEFAULT_BOARD_SIZE = 3
    IN_PROGRESS = -1
    DRAW = 0
    P1 = 1
    P2 = 2

    def __init__(self):
        self.totalMoves = 0
        self.boardValues = np.zeros((3, 3))

    def __str__(self):
        board = ""
        size = len(self.boardValues)
        for i in range(0, size):
            for j in range(0, size):
                board += str(int(self.boardValues[i, j])) + " "
            board += "\n"

        return board

    def perform_move(self, player, position):
        self.totalMoves += 1
        self.boardValues[position.x, position.y] = player

    def check_status(self):
        board_size = len(self.boardValues)
        max_index = board_size - 1
        diag1 = np.empty(board_size)
        diag2 = np.empty(board_size)

        for i in range(0, board_size):
            row = self.boardValues[i, :]
            col = np.empty(board_size)
            for j in range(0, board_size):
                col[j] = self.boardValues[i, j]

            check_row_for_win = check_for_win(row)
            if check_row_for_win != 0:
                return check_row_for_win

            check_col_for_win = check_for_win(col)
            if check_col_for_win != 0:
                return check_col_for_win

            diag1[i] = self.boardValues[i, i]
            diag2[i] = self.boardValues[max_index - i, i]

        check_diag1_for_win = check_for_win(diag1)
        if check_diag1_for_win != 0:
            return check_diag1_for_win

        check_diag2_for_win = check_for_win(diag2)
        if check_diag2_for_win != 0:
            return check_diag2_for_win

        if len(self.get_empty_positions()) > 0:
            return Board.IN_PROGRESS
        else:
            return Board.DRAW

    def get_empty_positions(self):
        size = len(self.boardValues)
        empty_positions = []
        for i in range(0, size):
            for j in range(0, size):
                if self.boardValues[i, j] == 0:
                    new_position = Position(i, j)
                    empty_positions.append(new_position)
        return empty_positions
