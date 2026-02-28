/* Amet Levent - 313CD */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

// initialization of a free queue
Queue* initQueue(void){
    Queue *q = malloc(sizeof(Queue));
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
    return q;
}

// the function that adds a node in the queue
Queue* addQueueNode(Queue* queue,char* command){
    QueueNode *p = malloc(sizeof(QueueNode));

    // if the queue is empty
    if(queue->size == 0){
        queue->front = p;
        queue->rear = p;
        queue->size = 1;
        strcpy(p->name,command);
        p->next = NULL;
        
        return queue;
    }

    //other cases
    else{
        p->next = queue->rear;
        strcpy(p->name,command);
        queue->rear = p;
        (queue->size)++;
        
        return queue;
    } 
}

// extract the command from the queue
char* extractNode(Queue* queue){
    char *copy = malloc(20*sizeof(char));

    if(queue->size == 1){
        strcpy(copy,queue->front->name);
        free(queue->front);
        queue->size = 0;
        queue->rear = NULL;
        queue->front = NULL;
       
        return copy;
    }
    
    strcpy(copy,queue->front->name);
    QueueNode *p = queue->rear;
    for(int i=0 ;i<queue->size-2; i++)
        p = p->next;
    free(p->next);
    p->next = NULL;
    queue->front = p;
    (queue->size)--;

    return copy;
}

void freeQueue(Queue* queue){
    QueueNode *copy = queue->rear;
    while(copy != NULL){
        copy = copy->next;
        free(queue->rear);
        queue->rear = copy;
    } 
    free(queue);
}