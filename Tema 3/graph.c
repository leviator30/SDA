/*AMET LEVENT - 313CD*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"

//functie de creare a grafului
Graph createGraphAdjList(int numberOfNodes) {
	Graph graph;
    graph.numberOfNodes = numberOfNodes;

    graph.adj_list = malloc((numberOfNodes+1) * sizeof(TNode*));
    for(int i=0;i<numberOfNodes;i++)
        graph.adj_list[i] = NULL;

    graph.visited = calloc(numberOfNodes+1, sizeof(int));

	return graph;
}

//functie de inserare a unei laturi in lista de adiacenta
void insertEdge(Graph graph, int u, int v){

    TNode* newNode = malloc(sizeof(TNode));
    newNode->finish = v;
    newNode->next = NULL;

    if((graph.adj_list)[u] == NULL)
        (graph.adj_list[u]) = newNode;
    else {
        TNode* currNode = (graph.adj_list)[u];
        while(currNode->next != NULL)
            currNode = currNode->next;
        currNode->next = newNode;
    }

}

//parcurgere DFS
void DFS(Graph graph, int node,int conex_count) {
    (graph.visited)[node] = conex_count; //notam fiecare nod cu indexul componentei de care apartine
    TNode* adjNode = (graph.adj_list)[node];
    while (adjNode != NULL) {
        int adjFinish = adjNode->finish;
        
        if (!(graph.visited)[adjFinish]) 
            DFS(graph, adjFinish,conex_count);
        
        adjNode = adjNode->next;
    }
}

//algoritm de aflare a numarului de componente conexe
int nrConexComponents(Graph graph,int numberOfRoads,TEdge edgeArray[2*numberOfRoads]) {
    int count = 0;
    
    for (int i = 1; i <= graph.numberOfNodes; i++) {
        if (!(graph.visited)[i]) {
            DFS(graph, i, count+1);
            count++;    //contorul cu care notam componentele conexe si nodurile
        }
    }

    return count;
}

//sortarea laturilor in functie de cost
void sortEdgeArray(int numberOfRoads,TEdge edgeArray[2*numberOfRoads]) {
    for(int i=0;i<2*numberOfRoads-1;i++)
        for(int j=i+1;j<2*numberOfRoads;j++)
            if(edgeArray[i].cost > edgeArray[j].cost){
                int k = edgeArray[i].cost;  //interschimbari clasice
                edgeArray[i].cost = edgeArray[j].cost;
                edgeArray[j].cost = k;

                k = edgeArray[i].node1;
                edgeArray[i].node1 = edgeArray[j].node1;
                edgeArray[j].node1 = k;

                k = edgeArray[i].node2;
                edgeArray[i].node2 = edgeArray[j].node2;
                edgeArray[j].node2 = k;
            }

}

//algoritmul kruskal
int Kruskal(Graph graph, int numberOfRoads, TEdge edgeArray[2*numberOfRoads], int index) {
    int S = 0,t[2*numberOfRoads+1];
    
    for(int i =1 ; i <= graph.numberOfNodes ; ++i)
        t[i] = i;

    for(int i=0;i < 2*numberOfRoads ;i++ ){
        if((t[edgeArray[i].node1] != t[edgeArray[i].node2] )&&((graph.visited)[edgeArray[i].node1] == index)) {            
                                                                //verificam daca latura apartine de componenta conexa respectiva
            S = S + edgeArray[i].cost;

            int ai = t[edgeArray[i].node1], aj = t[edgeArray[i].node2];
            for(int j = 0;j < 2*numberOfRoads; j++)
                if( t[j] == aj )
                    t[j] = ai;
            }
        }
    return S;

}
