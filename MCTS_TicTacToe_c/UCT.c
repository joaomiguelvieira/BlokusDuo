#include "UCT.h"

double valueUCT(TreeNode *node) {
    if (!((State *) node->object)->visits)
        return DBL_MAX;

    double node_win_score = ((State *) node->object)->score;
    int node_visit = ((State *) node->object)->visits;
    int total_visit = ((State *) node->parent->object)->visits;

    return (node_win_score / (double) node_visit) + 1.41 * sqrt(log(total_visit) / (double) node_visit);
}

TreeNode *findBestNodeWithUCT(TreeNode *node) {
    TreeNode *best_node = (TreeNode *) node->children->head->object;

    for (DoublyLinkedListNode *child = node->children->head->next; child != (DoublyLinkedListNode *) NULL; child = child->next)
        if (valueUCT((TreeNode *) child->object) > valueUCT(best_node))
            best_node = (TreeNode *) child->object;

    return best_node;
}
