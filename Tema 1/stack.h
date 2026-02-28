/* Amet Levent - 313CD */

#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doublelinkedlist.h"

// declaration of Stack and StackNode types

typedef struct StackNode{
    TDoubleLinkedNode* address;
    struct StackNode *next;
}StackNode;

typedef struct Stack{
    StackNode *head;
    long size;
}Stack;

Stack* initStack(void);
Stack* addStackNode(Stack* stack, TDoubleLinkedNode* address);
Stack* extractStackNode(Stack* stack);
void freeStack(Stack* Stack);

#endif