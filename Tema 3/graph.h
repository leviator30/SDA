/*AMET LEVENT - 313CD*/

#ifndef GRAPH_H_
#define GRAPH_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//structura de nod in lista de adiacenta
typedef struct node{
    int finish;
    int cost;
    struct node *next;
}TNode;

//structura de graf
typedef struct graph{
    int numberOfNodes;
    TNode** adj_list;
    int *visited;
}Graph;

//structura de latura a grafului
typedef struct edge{
    int cost;
    int node1;
    int node2;
}TEdge;


Graph createGraphAdjList(int numberOfNodes);
void insertEdge(Graph graph, int u, int v);
void DFS(Graph graph, int node,int conex_count);
int nrConexComponents(Graph graph,int numberOfRoads,TEdge edgeArray[2*numberOfRoads]);

void sortEdgeArray(int numberOfRoads,TEdge edgeArray[2*numberOfRoads]);

int Kruskal(Graph graph, int numberOfRoads, TEdge edgeArray[2*numberOfRoads], int index);

#endif