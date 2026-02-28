/* Amet Levent - 313CD */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doublelinkedlist.h"

// initialization of a double linked list which have the first element a santinel,and the second element '#'
TDoubleLinkedList* InitDoubleLinkedList() {
    TDoubleLinkedList *list = malloc(sizeof(TDoubleLinkedList));
    TDoubleLinkedNode *p_santinela = malloc(sizeof(TDoubleLinkedNode));
    TDoubleLinkedNode *p = malloc(sizeof(TDoubleLinkedNode));
    
    p_santinela->prev = NULL;
    p_santinela->next = p;
    p_santinela->character = ' ';
    p->character = '#';
    p->prev = p_santinela;
    p->next = NULL;
    
    list->first = p_santinela;
    list->last = p;
    list->finger = p;
    return list;
}

// the function which free a double linked list and its elements
void freeDoubleLinkedList(TDoubleLinkedList* list){
    TDoubleLinkedNode *copy =list->first;
    while(list->first != NULL){
        list->first = list->first->next;
        free(copy);
        copy = list->first;
        }
    free(list);
}