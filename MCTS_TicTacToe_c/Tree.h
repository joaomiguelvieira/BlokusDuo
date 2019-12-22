#ifndef TREE_H
#define TREE_H

#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <stdio.h>

#include "DoublyLinkedList.h"

/**
 * TreeNode
 */
typedef struct TreeNode_ {
    void *object;
    DoublyLinkedList *children;
    struct TreeNode_ *parent;
} TreeNode;

TreeNode *newTreeNode(void *object);

void deleteDownwardsTreeNode(TreeNode *node, void (*deleteObject)(void *object));
void deleteUpwardsTreeNode(TreeNode *node, void (*deleteObject)(void *object));

TreeNode *cloneTreeNode(TreeNode *node, TreeNode *parent, void * (*cloneObject)(void *object));

TreeNode *getRandomChildTreeNode(TreeNode *node);

TreeNode *getChildWithMaxScoreTreeNode(TreeNode *node, int (*getValue)(void *));

void insertChildTreeNode(TreeNode *parent, void *object);

/**
 * Tree
 */
typedef struct Tree_ {
    TreeNode *root;
} Tree;

Tree *newTree(void *object);
void deleteTree(Tree *tree, void (*deleteObject)(void *object));

#endif
