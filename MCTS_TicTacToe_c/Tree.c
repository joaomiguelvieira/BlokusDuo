#include "Tree.h"

/**
 * TreeNode
 */
TreeNode *newTreeNode(void *object) {
    TreeNode *node = (TreeNode *) malloc(sizeof(TreeNode));
    assert(node != (TreeNode *) NULL);

    node->object = object;
    node->children = newDoublyLinkedList();

    return node;
}

void deleteDownwardsTreeNode(TreeNode *node, void (*deleteObject)(void *object)) {
    for (DoublyLinkedListNode *child = node->children->head; child != NULL; child = child->next) {
        deleteDownwardsTreeNode((TreeNode *) child->object, deleteObject);
    }

    deleteDoublyLinkedList(node->children, NULL);
    deleteObject(node->object);
}

void deleteUpwardsTreeNode(TreeNode *node, void (*deleteObject)(void *object)) {
    removeFromDoublyLinkedList(node->parent->children, node);

    TreeNode *root = node;
    while (root->parent)
        root = root->parent;

    deleteDownwardsTreeNode(root, deleteObject);
}

/**
 * Tree
 */
Tree *newTree() {
    Tree *tree = (Tree *) malloc(sizeof(Tree));
    assert(tree != (Tree *) NULL);

    return tree;
}

void deleteTree(Tree *tree, void (*deleteObject)(void *object)) {
    deleteDownwardsTreeNode(tree->root, deleteObject);
}
