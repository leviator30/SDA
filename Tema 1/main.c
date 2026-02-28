/* Amet Levent - 313CD */

//  including the headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "stack.h"
#include "doublelinkedlist.h"
#include "update.h"
#include "query.h"

int main() {
// the "tema1.in" file is open
    TDoubleLinkedList *list = InitDoubleLinkedList();

    FILE *in = fopen("tema1.in","r");

// check if the file was opened succesfully
    if(in ==NULL){
        printf("eroare");
        return 1;
    }
    
// declaration of variabiles
    int n;
    char line[100];
    char **string;
    char character;

// initialization for the structures we need(queue of commands,UNDO and REDO stacks)
    Queue* queue = initQueue();
    Stack* stackUNDO = initStack();
    Stack* stackREDO = initStack();

// reading from the file(we considered an array of strings)
    fscanf(in,"%d ",&n);
    string = malloc(n*(sizeof(char*)));
    for(int i=0;i<n;i++){
        fgets(line,100,in); 
        string[i] = strdup(line);   
        if(string[i] == NULL){
            fprintf(stderr,"error");
            exit(1);
            }
        int lenght = strlen(string[i]);
        string[i][lenght-1] = '\0';
    }

    fclose(in);
    
// the tema1.out file is opened 
    FILE *out = fopen("tema1.out","w");

// taking every string to see what command is
    for(int i=0;i<n;i++) {
    // adding the commands in the queue

        if( strcmp("MOVE_LEFT",string[i]) == 0 )
           queue = addQueueNode(queue,"MOVE_LEFT");

        if( strcmp("MOVE_RIGHT",string[i]) == 0 )
           queue = addQueueNode(queue,"MOVE_RIGHT");
        
        if(strncmp("MOVE_LEFT_CHAR",string[i],14) == 0 )
            queue = addQueueNode(queue,string[i]);        
        
        if(strncmp("MOVE_RIGHT_CHAR",string[i],15) == 0 )
            queue = addQueueNode(queue,string[i]);     
        
        if(strncmp("WRITE",string[i],5) == 0 )
            queue = addQueueNode(queue,string[i]);     
        
        if(strncmp("INSERT_LEFT",string[i],11) == 0 )
            queue = addQueueNode(queue,string[i]);     
        
        if(strncmp("INSERT_RIGHT",string[i],12) == 0 )
            queue = addQueueNode(queue,string[i]);

        // we don't put commands "SHOW" or "CURRENT_SHOW" in the queue of commands,we execute them immediatly
        if(strcmp(string[i],"SHOW") == 0 )
            SHOW(list,out);
        
        if(strcmp(string[i],"SHOW_CURRENT") == 0 )
            SHOW_CURRENT(list,out);

        // we don't put commands "UNDO" or "REDO" in the queue of commands,we directlly put or take what we need from them
        // we take from the "stackUNDO" the last element and put it in the "stackREDO"  
        if(strcmp(string[i],"UNDO") == 0 ){
            stackREDO = addStackNode(stackREDO,list->finger);
            // finger take the position from the "stackUNDO"  
            list->finger = stackUNDO->head->address;
            stackUNDO = extractStackNode(stackUNDO);
            }

        // we take from the "stackREDO" the last element and put it in the "stackUNDO"    
        if(strcmp(string[i],"REDO") == 0 ){
            stackUNDO = addStackNode(stackUNDO,list->finger);
            // finger take the position from the "stackREDO"
            list->finger = stackREDO->head->address;
            stackREDO = extractStackNode(stackREDO);
            }

        // we execute the first command from the queue
        if(strcmp("EXECUTE",string[i]) == 0){
            char *comanda = extractNode(queue);
            
            if( strcmp("MOVE_LEFT",comanda) == 0 ){
                // we put the current address of the finger in the "stackUNDO"
                if(list->finger->prev != list->first)
                    stackUNDO = addStackNode(stackUNDO,list->finger);
                // we execute the command
                MOVE_LEFT(list);
                }
            
            // same here
            if( strcmp("MOVE_RIGHT",comanda) == 0 ){
                stackUNDO = addStackNode(stackUNDO,list->finger);
                MOVE_RIGHT(list);
                }
            
            //same here
            if(strncmp("MOVE_LEFT_CHAR",comanda,14) == 0 ){
                // we separate the character we need for the function
                character = comanda[15];
                stackUNDO = addStackNode(stackUNDO,list->finger);
                MOVE_LEFT_CHAR(list,character,out);
                }

            //same here
            if(strncmp("MOVE_RIGHT_CHAR",comanda,15) == 0 ){
                // we separate the character we need for the function
                character = comanda[16];
                stackUNDO = addStackNode(stackUNDO,list->finger);
                MOVE_RIGHT_CHAR(list,character);
                }

            //we execute the command
            if(strncmp("WRITE",comanda,5) == 0 ){
                // we separate the character we need
                character = comanda[6];
                WRITE(list,character);
                // free the stack
                freeStack(stackUNDO);
                freeStack(stackREDO);
                // reinitializate the stacks
                stackUNDO = initStack();
                stackREDO = initStack();
                }

            // execute the function
            if(strncmp("INSERT_LEFT",comanda,11) == 0 ){
                // separate the character
                character = comanda[12];
                INSERT_LEFT(list,character,out);
                }

            // execute the function
            if(strncmp("INSERT_RIGHT",comanda,12) == 0 ){
                // separate the character
                character = comanda[13];
                INSERT_RIGHT(list,character);
                }
            
            // free comanda(allocate dinamically in the function "extractNode")
            free(comanda);
            }
        }

    fclose(out);

    // free the queue,stacks and double linked list we used
    freeStack(stackUNDO);
    freeStack(stackREDO);
    freeDoubleLinkedList(list);
    freeQueue(queue);

    // free the array of strings
    for(int i=0;i<n;i++)
        free(string[i]);
    free(string);

    return 0;   
}