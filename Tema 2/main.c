#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Task1_functions.h"
#include "Task2_functions.h"

int main(int argc,char *argv[]){
    if(strcmp(argv[1],"-c1") == 0){
        char* buffer = argv[2];
        int factor = atoi(buffer);
        Task1(factor,argv[3],argv[4]);
    }

    if(strcmp(argv[1],"-c2") == 0){
        char* buffer = argv[2];
        int factor = atoi(buffer);
        Task2(factor,argv[3],argv[4]);
    }

    return 0;
}
