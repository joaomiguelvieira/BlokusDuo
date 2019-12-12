import math
import sys


def uct_value(total_visit, node_win_score, node_visit):
    if node_visit == 0:
        return sys.maxint

    return float(node_win_score) / node_visit + 1.41 * math.sqrt(math.log(total_visit) / float(node_visit))


def find_best_node_with_uct(node):
    parent_visit = node.state.visits
    return max(node.children, lambda child: uct_value(parent_visit, child.state.score, child.state.visits))[0]
