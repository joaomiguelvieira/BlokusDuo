#include "DoublyLinkedList.h"

/**
 * DoublyLinkedListNode
 */
DoublyLinkedListNode *newDoublyLinkedListNode(void *object) {
    DoublyLinkedListNode *node = (DoublyLinkedListNode *) malloc(sizeof(DoublyLinkedListNode));
    assert(node != (DoublyLinkedListNode *) NULL);

    node->object = object;

    return node;
}

void deleteDoublyLinkedListNode(DoublyLinkedListNode *node, void (*deleteObject)(void *object)) {
    if (deleteObject != NULL)
        deleteObject(node->object);

    free(node);
}

/**
 * DoublyLinkedList
 */
DoublyLinkedList *newDoublyLinkedList() {
    DoublyLinkedList *list = (DoublyLinkedList *) malloc(sizeof(DoublyLinkedList));
    assert(list != (DoublyLinkedList *) NULL);

    list->head = (DoublyLinkedListNode *) NULL;
    list->tail = (DoublyLinkedListNode *) NULL;
    list->count = 0;

    return list;
}

void deleteDoublyLinkedList(DoublyLinkedList *list, void (*deleteObject)(void *object)) {
    DoublyLinkedListNode *node = list->head;

    while(node) {
        DoublyLinkedListNode *next_node = node->next;
        deleteDoublyLinkedListNode(node, deleteObject);
        node = next_node;
    }
}

void insertAtHeadDoublyLinkedList(DoublyLinkedList *list, void *object) {
    DoublyLinkedListNode *node = newDoublyLinkedListNode(object);

    node->previous = (DoublyLinkedListNode *) NULL;
    node->next = list->head;

    if (list->head != (DoublyLinkedListNode *) NULL)
        list->head->previous = node;

    list->head = node;
    list->count++;
}

void insertAtTailDoublyLinkedList(DoublyLinkedList *list, void *object) {
    DoublyLinkedListNode *node = newDoublyLinkedListNode(object);

    node->next = (DoublyLinkedListNode *) NULL;
    node->previous = list->tail;

    if (list->tail != (DoublyLinkedListNode *) NULL)
        list->tail->next = node;

    list->tail = node;
    list->count++;
}

void removeFromDoublyLinkedList(DoublyLinkedList *list, void *object) {
    for (DoublyLinkedListNode *node = list->head; node != (DoublyLinkedListNode *) NULL; node = node->next) {
        if (node->object == object) {
            if (node->previous != (DoublyLinkedListNode *) NULL)
                node->previous->next = node->next;

            if (node->next != (DoublyLinkedListNode *) NULL)
                node->next->previous = node->previous;

            deleteDoublyLinkedListNode(node, NULL);
        }
    }
}
