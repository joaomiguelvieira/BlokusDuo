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

void insertChildTreeNode(TreeNode *parent, void *object) {
    TreeNode *node = newTreeNode(object);
    node->parent = parent;
    insertAtHeadDoublyLinkedList(parent->children, node);
}

// TODO optimize
TreeNode *getRandomChildTreeNode(TreeNode *node) {
    srand(time(NULL));
    int random = rand() % node->children->count;

    DoublyLinkedListNode *random_child;
    for (random_child = node->children->head; random != 0; random--)
        random_child = random_child->next;

    return (TreeNode *) random_child->object;
}

TreeNode *cloneTreeNode(TreeNode *node, TreeNode *parent, void * (*cloneObject)(void *object)) {
    TreeNode *new_node = newTreeNode(cloneObject(node->object));
    new_node->parent = parent;

    for (DoublyLinkedListNode *child = node->children->head; child != (DoublyLinkedListNode *) NULL; child = child->next)
        insertAtHeadDoublyLinkedList(new_node->children, cloneTreeNode((TreeNode *) child->object, new_node, cloneObject));

    return new_node;
}

TreeNode *getChildWithMaxScoreTreeNode(TreeNode *node, int (*getValue)(void *)) {
    TreeNode *max_score = (TreeNode *) node->children->head->object;

    for (DoublyLinkedListNode *child = node->children->head->next; child != (DoublyLinkedListNode *) NULL; child = child->next)
        if (getValue(((TreeNode *) child->object)->object) > getValue(max_score->object))
            max_score = (TreeNode *) child->object;

    return max_score;
}

/**
 * Tree
 */
Tree *newTree(void *object) {
    Tree *tree = (Tree *) malloc(sizeof(Tree));
    assert(tree != (Tree *) NULL);

    tree->root = newTreeNode((object));
    tree->root->parent = (TreeNode *) NULL;

    return tree;
}

void deleteTree(Tree *tree, void (*deleteObject)(void *object)) {
    deleteDownwardsTreeNode(tree->root, deleteObject);
}
