#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Task1_functions.h"
#include "queue.h"
#include "Task2_functions.h"

void Task2(int factor, char input[30], char output[30]){
    //open and verify if the files were opened succesfully
    FILE *in = fopen(input, "rb");
    if(in == NULL){
        printf("Error opening file.\n");
        return;
    }
    FILE *out = fopen(output, "wb");
    if(out == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // reading datas about image,conformable to ppm file
    char string[3];
    unsigned int width, height, max_value;
    fscanf(in, "%s", string);
    fscanf(in, "%u %u", &width, &height);
    fscanf(in, "%u", &max_value);

    fscanf(in, "%c", &string[0]);

    // reading image data
    TRGB **grid = malloc(height * sizeof(TRGB *));
    for (int i = 0; i < width; i++)
        grid[i] = malloc(width * sizeof(TRGB));

    //reading RGB datas for every pixel
    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++) {
            fread(&grid[i][j].red, sizeof(unsigned char), 1, in);
            fread(&grid[i][j].green, sizeof(unsigned char), 1, in);
            fread(&grid[i][j].blue, sizeof(unsigned char), 1, in);
        }

    //compress the given file
    TNode *root = NULL;
    root = compression(grid, 0, 0, width, factor, root);

    fwrite(&width,sizeof(int),1,out);
    Queue *q = init_queue();
    enqueue(q,root);
    int level = 0;
    
    //we go through the levels and display the values
    while(q->front != NULL){
        int level_size = q->size;
        
        for(int i=0;i<level_size;i++){
            TNode *p = dequeue(q);
            if(p->type == 0)
                fwrite(&(p->type),sizeof(char),1,out);
            if(p->type == 1){
                fwrite(&(p->type),sizeof(char),1,out);
                fwrite(&(p->colors.red),sizeof(char),1,out);
                fwrite(&(p->colors.green),sizeof(char),1,out);
                fwrite(&(p->colors.blue),sizeof(char),1,out);
                }
            
            if(p->part1 != NULL)
                enqueue(q,p->part1);
            if(p->part2 != NULL)
                enqueue(q,p->part2);
            if(p->part3 != NULL)
                enqueue(q,p->part3);
            if(p->part4 != NULL)
                enqueue(q,p->part4);    
                }
        level++;
        }

    fclose(in);
    fclose(out);
}