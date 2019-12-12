#include <stdlib.h>
#include <assert.h>

#include "DoublyLinkedList.h"

/**
 * DoublyLinkedListNode
 */
typedef struct DoublyLinkedListNode_ {
    struct DoublyLinkedListNode_ *previous, *next;
    void *object;
} DoublyLinkedListNode;

DoublyLinkedListNode *newDoublyLinkedListNode(void *object) {
    DoublyLinkedListNode *node = (DoublyLinkedListNode *) malloc(sizeof(DoublyLinkedListNode));
    assert(node != (DoublyLinkedListNode *) NULL);

    node->object = object;

    return node;
}

void deleteDoublyLinkedListNode(DoublyLinkedListNode *node, void (*deleteObject)(void *object)) {
    deleteObject(node->object);
    free(node);
}

/**
 * DoublyLinkedList
 */
typedef struct DoublyLinkedList_ {
    DoublyLinkedListNode *head, *tail;
    void (*deleteObject)(void *object);
    int count;
} DoublyLinkedList;

DoublyLinkedList *newDoublyLinkedList(void (*deleteObject)(void *object)) {
    DoublyLinkedList *list = (DoublyLinkedList *) malloc(sizeof(DoublyLinkedList));
    assert(list != (DoublyLinkedList *) NULL);

    list->head = (DoublyLinkedListNode *) NULL;
    list->tail = (DoublyLinkedListNode *) NULL;
    list->deleteObject = deleteObject;
    list->count = 0;

    return list;
}

void deleteDoublyLinkedList(DoublyLinkedList *list) {
    DoublyLinkedListNode *node = list->head;

    while(node) {
        DoublyLinkedListNode *next_node = node->next;
        deleteDoublyLinkedListNode(node, list->deleteObject);
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
}

void insertAtTailDoublyLinkedList(DoublyLinkedList *list, void *object) {
    DoublyLinkedListNode *node = newDoublyLinkedListNode(object);

    node->next = (DoublyLinkedListNode *) NULL;
    node->previous = list->tail;

    if (list->tail != (DoublyLinkedListNode *) NULL)
        list->tail->next = node;

    list->tail = node;
}

/**
 * DoublyLinkedListIterator
 */
typedef struct DoublyLinkedListIterator_ {
    DoublyLinkedList *list;
    DoublyLinkedListNode *node;
} DoublyLinkedListIterator;

DoublyLinkedListIterator *newDoublyLinkedListIterator(DoublyLinkedList *list) {
    DoublyLinkedListIterator *iterator = (DoublyLinkedListIterator *) malloc(sizeof(DoublyLinkedListIterator));
    assert(iterator != (DoublyLinkedListIterator *) NULL);

    iterator->list = list;

    return iterator;
}

void deleteDoublyLinkedListIterator(DoublyLinkedListIterator *iterator) {
    free(iterator);
}

void *getNextDoublyLinkedListIterator(DoublyLinkedListIterator *iterator) {
    if (iterator->node != (DoublyLinkedListNode *) NULL)
        iterator->node = iterator->node->next;

    return iterator->node->object;
}

void *resetDoublyLinkedListIterator
