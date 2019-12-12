from random import randint
from State import State


class Node:
    def __init__(self):
        self.parent = None
        self.state = State()
        self.children = []

    def get_random_child_node(self):
        no_of_possible_moves = len(self.children)
        select_random = randint(0, no_of_possible_moves - 1)
        return self.children[select_random]

    def get_child_with_max_score(self):
        return max(self.children, key=lambda child: child.state.visits)
