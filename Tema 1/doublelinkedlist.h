/* Amet Levent - 313CD */

#ifndef DOUBLE_LINKED_LIST_C_
#define DOUBLE_LINKED_LIST_C_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// declaration of TDoubleLinkedList and TDoubleLinkedNode types

typedef struct DoubleLinkedNode{
    char character;
    struct DoubleLinkedNode *prev;
    struct DoubleLinkedNode *next;
}TDoubleLinkedNode;

typedef struct DoubleLinkedList{
    TDoubleLinkedNode *first;
    TDoubleLinkedNode *finger;
    TDoubleLinkedNode *last;
}TDoubleLinkedList;

TDoubleLinkedList* InitDoubleLinkedList();
void freeDoubleLinkedList(TDoubleLinkedList* list);

#endif