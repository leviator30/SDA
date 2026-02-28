/* Amet Levent - 313CD */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doublelinkedlist.h"

// implementation we need

void MOVE_LEFT(TDoubleLinkedList *list) {
    if((list->finger->prev != list->first)&&(list->finger->prev != NULL))
        list->finger = list->finger->prev;
} 

void MOVE_RIGHT(TDoubleLinkedList *list) {
    if(list->finger->next != NULL)
        list->finger = list->finger->next;
    else {
        TDoubleLinkedNode *p = malloc(sizeof(TDoubleLinkedNode));
        p->next = NULL;
        p->prev = list->last;
        p->character = '#';
        list->last->next = p;
        list->last = p;
        list->finger = p;
    }
} 

void MOVE_LEFT_CHAR(TDoubleLinkedList *list,char character,FILE *out) {
    TDoubleLinkedNode *copy = list->finger;
    while(copy != list->first) {
    if(copy->character == character){
        list->finger = copy;
        return;
        }
    copy = copy->prev;
    }
    
    fprintf(out,"ERROR\n");

}

void MOVE_RIGHT_CHAR(TDoubleLinkedList *list,char character) {
    TDoubleLinkedNode *copy = list->finger,*copy2;
    while(copy != NULL) {
        if(copy->character == character){
            list->finger = copy;
        return;
        }
    if(copy->next == NULL)
        copy2 = copy;
    copy = copy->next;
    }

    TDoubleLinkedNode *p = malloc(sizeof(TDoubleLinkedNode));
    p->prev = copy2;
    p->next = NULL;
    copy2->next = p;
    list->last = p;
    list->finger = p;
    p->character = '#';
}

void WRITE(TDoubleLinkedList *list, char character) {
    list->finger->character = character;
}

void INSERT_LEFT(TDoubleLinkedList *list, char character, FILE *out){
    if(list->finger->prev == list->first){
        
        fprintf(out,"ERROR\n");

        return;
    }
    TDoubleLinkedNode *node = malloc(sizeof(TDoubleLinkedNode));
    node->next = list->finger;
    node->prev = list->finger->prev;
    list->finger->prev->next = node;
    list->finger->prev = node;
    node->character = character;
    list->finger = node;
}

void INSERT_RIGHT(TDoubleLinkedList *list, char character){
    TDoubleLinkedNode *node = malloc(sizeof(TDoubleLinkedNode));
    
    if(list->finger->next == NULL){
        node->prev = list->last;
        node->next = NULL;
        list->last->next = node;
        node->character = character;
        list->last = node;
        list->finger = node;
        return;
    }
    
    node->next = list->finger->next;
    node->prev = list->finger;
    list->finger->next->prev = node;
    list->finger->next = node;
    node->character = character;
    list->finger = node;
}
