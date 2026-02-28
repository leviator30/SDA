/* Amet Levent - 313CD */

#ifndef UPDATE_H_
#define UPDATE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doublelinkedlist.h"

void MOVE_LEFT(TDoubleLinkedList *list);
void MOVE_RIGHT(TDoubleLinkedList *list);
void MOVE_LEFT_CHAR(TDoubleLinkedList *list,char character,FILE *out);
void MOVE_RIGHT_CHAR(TDoubleLinkedList *list,char character);
void WRITE(TDoubleLinkedList *list, char character);
void INSERT_LEFT(TDoubleLinkedList *list, char character, FILE *out);
void INSERT_RIGHT(TDoubleLinkedList *list, char character);

#endif