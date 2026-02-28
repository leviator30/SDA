#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "Task1_functions.h"
#include "queue.h"

void Task1(int factor,char input[30],char output[30]){
    //open and verify if the files were opened succesfully
    FILE *in = fopen(input,"rb");
    if(in == NULL){
        printf("Error opening file.\n");
        return;
    }
    FILE *out = fopen(output,"w");
    if(out == NULL){
        printf("Error opening file.\n");
        return;
    }

    //reading datas about image,conformable to ppm file
    char string[3];
    unsigned int width,height,max_value;
    fscanf(in,"%s",string);
    fscanf(in,"%u %u",&width,&height);
    fscanf(in,"%u",&max_value);

    fscanf(in,"%c",&string[0]);

    //reading image data
    TRGB **grid = malloc(height*sizeof(TRGB*));
    for(int i=0; i<width; i++)
            grid[i] = malloc(width*sizeof(TRGB)); 

    //reading RGB datas for every pixel
    for(int i=0; i<width; i++)
        for(int j=0;j<height;j++){
            fread(&grid[i][j].red,sizeof(unsigned char),1,in);
            fread(&grid[i][j].green,sizeof(unsigned char),1,in);
            fread(&grid[i][j].blue,sizeof(unsigned char),1,in);
            }
        
    //aply the functions we wrote
    TNode *root = NULL; 
    root = compression(grid,0,0,width,factor,root);
    int number_leafs = number_leaf_nodes(root);
    int max_undiv = min_leaf_level(root,width);

    //put the values in the file
    fprintf(out,"%d\n",get_heigh(root));
    fprintf(out,"%d\n",number_leafs);
    fprintf(out,"%d\n",max_undiv);

    fclose(in);
    fclose(out);
}