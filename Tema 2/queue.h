#ifndef queue_h_
#define queue_h_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Task1_functions.h"

typedef struct queuenode{
    TNode *value;
    struct queuenode *next;
}QueueNode;

typedef struct queue{
    QueueNode *front;
    QueueNode *rear;
    long size;
}Queue;

Queue* init_queue();
QueueNode* create_queue(TNode* value);
int is_queue_empty(Queue *q);
void enqueue(Queue *q,TNode* node);
TNode* dequeue(Queue *q);
int min_leaf_level(TNode *root,int size);

#endif