/* Amet Levent - 313CD */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doublelinkedlist.h"

// implemenation of display functions

void SHOW_CURRENT(TDoubleLinkedList *list,FILE* out){
    
    fprintf(out, "%c\n",list->finger->character);
    
}

void SHOW(TDoubleLinkedList *list, FILE* out) {
    TDoubleLinkedNode *copy = list->first->next;
    
    while(copy!=NULL){
        if(list->finger == copy)
            fprintf(out, "|%c|",copy->character);
        else fprintf(out, "%c",copy->character);
    copy = copy->next;
    }
    fprintf(out, "\n");
    
}
