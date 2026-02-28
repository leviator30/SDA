/*AMET LEVENT - 313CD*/

#ifndef TASK2_H_
#define TASK2_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"

void task2();

int DFS_2(Graph graph, int node);

void Dijkstra(FILE *out, Graph graph, int numberOfNodes,int adj_mat[1000][1000],int source, char name_list[][1000],int depth[1000], int weight); 
void add_name_2(char name[], char name_list[][1000]);
void sortEdgeArray_2(int numberOfRoads,TEdge edgeArray[numberOfRoads]);

#endif