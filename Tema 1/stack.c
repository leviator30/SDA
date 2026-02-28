/* Amet Levent - 313CD */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "doublelinkedlist.h"

// initialization of a stack with 0 elements
Stack* initStack(void){
    Stack *stack = malloc(sizeof(Stack));
    
    stack->head = NULL;
    stack->size = 0;
    
    return stack;
}

// the function to add a node in stack
Stack* addStackNode(Stack* stack, TDoubleLinkedNode* address){
    StackNode *p = malloc(sizeof(StackNode));
    
    // the case when the stack is empty
    if(stack->head == NULL){
        p->next = NULL;
        p->address = address;
        stack->head = p;
        stack->size = 1;

        return stack;
        }

    // the other cases    
    p->next = stack->head;
    p->address = address;
    stack->size++;
    stack->head = p;

    return stack;
}

// the function to take the last element from the stack
Stack* extractStackNode(Stack* stack){
    StackNode* copy = stack->head;
    
    stack->head = stack->head->next;
    stack->size--;
    // free the copy
    free(copy);
    
    return stack;
}

// the function that free the stack and every element from it
void freeStack(Stack* Stack){
    while(Stack->head != NULL){
        StackNode *copy = Stack->head;
        Stack->head = Stack->head->next;
        free(copy);
    }
    free(Stack);
}
