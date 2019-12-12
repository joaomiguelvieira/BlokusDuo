#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

/**
 * DoublyLinkedListNode
 */
typedef struct DoublyLinkedListNode_ {
    struct DoublyLinkedListNode_ *previous, *next;
    void *object;
} DoublyLinkedListNode;

/**
 * DoublyLinkedList
 */
typedef struct DoublyLinkedList_ {
    DoublyLinkedListNode *head, *tail;
    int count;
} DoublyLinkedList;

DoublyLinkedList *newDoublyLinkedList();
void deleteDoublyLinkedList(DoublyLinkedList *list, void (*deleteObject)(void *object));
void removeFromDoublyLinkedList(DoublyLinkedList *list, void *object);

#endif
