#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Task1_functions.h"
#include "queue.h"

//function for initializing a queue
Queue* init_queue(){
    Queue *q = malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    q->size = 0;
    return q;
}

//function to create a queue with only one value
QueueNode* create_queue(TNode* value){
    QueueNode *node = malloc(sizeof(QueueNode));
    node->value = value;
    node->next = NULL;
    return node;
}

//function to verify if a queue is empty
int is_queue_empty(Queue *q){
    return q->front == NULL;
}

//function to add a node in the queue
void enqueue(Queue *q,TNode* node){
    if(q->front == NULL)
        q->front = q->rear = create_queue(node);
    else{
        QueueNode *p = create_queue(node);
        q->rear->next = p;
        q->rear = p;
    }
    q->size++;
}

//function to take out a node from the queue
TNode* dequeue(Queue *q){
    if(q->front == NULL)
        return NULL;
    
    TNode* result = q->front->value;
    QueueNode *tmp = q->front;
    
    q->front = q->front->next;
    
    if(tmp->next == NULL)
        q->rear = NULL;
    
    free(tmp);
    q->size--;
    
    return result;
}

//function to find the side size of the larges area in the immage that remained undivided
int min_leaf_level(TNode *root,int size){

    int min_leaf_height;
    int ok = 0,level = 0;
    Queue *q = init_queue();
    enqueue(q,root);
    
    while(q->front != NULL){
        int level_size = q->size;
        
            for(int i=0;i<level_size;i++){
                TNode *p = dequeue(q);
                //enqueue the nodes from the tree that are'n leaf nodes
                if(p->part1 != NULL)
                    enqueue(q,p->part1);
                if(p->part2 != NULL)
                    enqueue(q,p->part2);
                if(p->part3 != NULL)
                    enqueue(q,p->part3);
                if(p->part4 != NULL)
                    enqueue(q,p->part4);    
                
                //we return the value for the first leaf node that we finf=d,because we use a level traversal
                if(p->part1 == NULL && p->part2 == NULL && p->part3 == NULL && p->part4 == NULL && ok == 0){
                    ok = 1;
                    if(level==0)
                        return size;

                    min_leaf_height = size/(2<<(level-1));
                    return min_leaf_height;    
                    }
                }
            level++;
        }
    return 0;
}

