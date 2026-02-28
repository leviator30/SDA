/*AMET LEVENT - 313CD*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task1.h"
#include "task2.h"


int main(int argc,char *argv[]){
    if(strcmp(argv[1],"1") == 0)
        task1();//apelare task1
    
    if(strcmp(argv[1],"2") == 0)
        task2();//apelare task2
    
    return 0;
}