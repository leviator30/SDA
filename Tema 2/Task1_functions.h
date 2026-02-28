#ifndef Task1_functions_h_
#define Task1_functions_h_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct RGB{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
}TRGB;

typedef struct node{
    TRGB colors;
    unsigned char type;
    struct node *part1;
    struct node *part2;
    struct node *part3;
    struct node *part4;
}TNode;

unsigned int red_color(TRGB **grid,unsigned int x,unsigned int y,unsigned int size);
unsigned int green_color(TRGB **grid,unsigned int x,unsigned int y,unsigned int size);
unsigned int blue_color(TRGB **grid,unsigned int x,unsigned int y,unsigned int size);
unsigned long long verify_compression(TRGB **grid, int x, int y, int size);
TNode* compression(TRGB **grid,unsigned int x,unsigned int y,int size,unsigned long long to_compare,TNode* root);
void Task1(int factor,char input[30],char output[30]);
int get_heigh(TNode *root);
int number_leaf_nodes(TNode *root);
int max_undivided(unsigned int size,TNode *root);

#endif