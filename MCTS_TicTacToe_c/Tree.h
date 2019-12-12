#ifndef TREE_H
#define TREE_H

#include "DoublyLinkedList.h"

/**
 * TreeNode
 */
typedef struct TreeNode_ {
    void *object;
    DoublyLinkedList *children;
    struct TreeNode_ *parent;
} TreeNode;

/**
 * Tree
 */
typedef struct Tree_ {
    TreeNode *root;
} Tree;

#endif
