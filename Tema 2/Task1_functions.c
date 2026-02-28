#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Task1_functions.h"
#include "queue.h"

//function to find average red color value
unsigned int red_color(TRGB **grid,unsigned int x,unsigned int y,unsigned int size){
    unsigned long long red = 0;
    for (int i = x; i < x + size; i++)
        for (int j = y; j < y + size; j++)
            red = red + grid[i][j].red;
    red = red/(size*size);
    return red;
}

//function to find average green color value
unsigned int green_color(TRGB **grid,unsigned int x,unsigned int y,unsigned int size){
    unsigned long long green = 0;
    for (int i = x; i < x + size; i++)
        for (int j = y; j < y + size; j++)
            green = green + grid[i][j].green;
    green = green/(size*size);
    return green;
}

//function to find average blue color value
unsigned int blue_color(TRGB **grid,unsigned int x,unsigned int y,unsigned int size){
    unsigned long long blue = 0;
    for (int i = x; i < x + size; i++)
        for (int j = y; j < y + size; j++)
            blue = blue + grid[i][j].blue;
    blue = blue/(size*size);
    return blue;
}

//function to verify if the compression is posible
unsigned long long verify_compression(TRGB **grid, int x, int y, int size){
    //assignng the average values for every color
    unsigned int red = red_color(grid,x,y,size);
    unsigned int green = green_color(grid,x,y,size);
    unsigned int blue = blue_color(grid,x,y,size);

    unsigned long long mean=0;

    //using the given formulas to calculate the average value for an area
    for (int i = x; i < x + size; i++)
        for (int j = y; j < y + size; j++)
            mean = mean + (red-grid[i][j].red)*(red-grid[i][j].red) + (green - grid[i][j].green)*(green - grid[i][j].green) + (blue - grid[i][j].blue)*(blue - grid[i][j].blue);;
        
    mean = mean/(3*size*size);

    return mean;
}

//function to compress a given area
TNode* compression(TRGB **grid,unsigned int x,unsigned int y,int size,unsigned long long to_compare,TNode* root){
    
        if(root == NULL){
            root = malloc(sizeof(TNode));
            root->part1 = root->part2 = root->part3 = root->part4 = NULL;
        }

        //comparing the average value for the area with the compression factor

        //if the average value it's bigger,we need to divide the area in 4,compress each one,and consider that node of type 0 
        if(verify_compression(grid,x,y,size) > to_compare){
            root->type = 0;
            root->part1 = compression(grid, x, y, size/2, to_compare,root->part1);
            root->part2 = compression(grid, x, y+size/2, size/2, to_compare,root->part2);
            root->part3 = compression(grid, x+size/2, y+size/2, size/2, to_compare,root->part3);
            root->part4 = compression(grid, x+size/2, y, size/2, to_compare,root->part4);
            }
        //if the average value it's smaller,we put the values in the tree,and we consider that node of type 1
        else {
            root->type = 1;
            root->colors.red = red_color(grid,x,y,size);
            root->colors.green = green_color(grid,x,y,size);
            root->colors.blue = blue_color(grid,x,y,size);
            root->part1 = root->part2 = root->part3 = root->part4 = NULL;
        }
        return root;
    }

//function to find the heigh of a tree
int get_heigh(TNode *root){
    if(root == NULL)
        return 0;
    int maxChildHeight = 0;
        
    if(maxChildHeight < get_heigh(root->part1))
        maxChildHeight = get_heigh(root->part1);
    
    if(maxChildHeight < get_heigh(root->part2))
        maxChildHeight = get_heigh(root->part2);
    
    if(maxChildHeight < get_heigh(root->part3))
        maxChildHeight = get_heigh(root->part3);
    
    if(maxChildHeight < get_heigh(root->part4))
        maxChildHeight = get_heigh(root->part4);
    
    return 1+maxChildHeight;
}

//function to find the number of leaf nodes
int number_leaf_nodes(TNode *root){
    if(root == NULL)
        return 0;
    if(root->type == 0)
        return number_leaf_nodes(root->part1)+number_leaf_nodes(root->part2)+number_leaf_nodes(root->part3)+number_leaf_nodes(root->part4);
    if(root->type == 1)
        return 1;

    return 0;
}
