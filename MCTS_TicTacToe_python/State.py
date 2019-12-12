import sys
from random import randint
from Board import Board
from copy import deepcopy


class State:
    def __init__(self):
        self.score = 0
        self.player = None
        self.visits = 0
        self.board = Board()

    def get_all_possible_states(self):
        possible_states = []
        available_positions = self.board.get_empty_positions()
        for position in available_positions:
            new_state = State()
            new_state.board = deepcopy(self.board)
            new_state.player = self.get_opponent()
            new_state.board.perform_move(new_state.player, position)
            possible_states.append(new_state)
        return possible_states

    def random_play(self):
        available_positions = self.board.get_empty_positions()
        total_possibilities = len(available_positions)
        select_random = randint(0, total_possibilities - 1)
        self.board.perform_move(self.player, available_positions[select_random])

    def add_score(self, score):
        if 'minint' not in dir(sys):
            sys.minint = -sys.maxint - 1

        if self.score != sys.minint:
            self.score += score

    def get_opponent(self):
        return Board.P1 if self.player == Board.P2 else Board.P2

    def toggle_player(self):
        self.player = self.get_opponent()
