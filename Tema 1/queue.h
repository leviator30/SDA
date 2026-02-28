/* Amet Levent - 313CD */

#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// declaration of Queue and QueueNode types

typedef struct queuenode{
    char name[30];
    struct queuenode *next;
}QueueNode;

typedef struct queue{
    QueueNode *front;
    QueueNode *rear;
    long size;
}Queue;

Queue* initQueue(void);
Queue* addQueueNode(Queue* queue,char* command);
char* extractNode(Queue* queue);
void freeQueue(Queue* queue);

#endif