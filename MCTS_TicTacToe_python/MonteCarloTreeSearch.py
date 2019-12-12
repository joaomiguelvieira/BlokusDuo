from copy import deepcopy
import sys

from Board import Board
from Node import Node
from Tree import Tree
from UCT import find_best_node_with_uct


def select_promising_node(root_node):
    node = root_node

    while len(node.children) != 0:
        node = find_best_node_with_uct(node)

    return node


def expand_node(node):
    possible_states = node.state.get_all_possible_states()
    for state in possible_states:
        new_node = Node()
        new_node.state = state
        new_node.parent = node
        new_node.state.player = node.state.get_opponent()
        node.children.append(new_node)


class MonteCarloTreeSearch:
    WIN_SCORE = 10

    def __init__(self):
        self.opponent = None

    def find_next_move(self, board, player):
        self.opponent = Board.P2 if player == Board.P1 else Board.P1
        tree = Tree()
        tree.root.state.board = board
        tree.root.state.player = self.opponent

        iterations = 100

        while iterations > 0:
            # Phase 1 - Selection
            promising_node = select_promising_node(tree.root)

            # Phase 2 - Expansion
            if promising_node.state.board.check_status() == Board.IN_PROGRESS:
                expand_node(promising_node)

            # Phase 3 - Simulation
            node_to_explore = promising_node
            if len(promising_node.children) > 0:
                node_to_explore = promising_node.get_random_child_node()

            playout_result = self.simulate_random_playout(node_to_explore)

            # Phase 4 - Update
            self.back_propagation(node_to_explore, playout_result)

            iterations -= 1

        winner_node = tree.root.get_child_with_max_score()

        return winner_node.state.board

    def back_propagation(self, node_to_explore, player):
        temp_node = node_to_explore
        while temp_node is not None:
            temp_node.state.visits += 1
            if temp_node.state.player == player:
                temp_node.state.add_score(self.WIN_SCORE)
            temp_node = temp_node.parent

    def simulate_random_playout(self, node):
        temp_node = deepcopy(node)
        temp_state = temp_node.state
        board_status = temp_state.board.check_status()

        if board_status == self.opponent:
            temp_node.parent.state.score = sys.minint
            return board_status

        while board_status == Board.IN_PROGRESS:
            temp_state.toggle_player()
            temp_state.random_play()
            board_status = temp_state.board.check_status()

        return board_status
