/*AMET LEVENT - 313CD*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task2.h"
#include "graph.h"
#include "task1.h"

#define INF 12345 //declaram infinit

//sortarea vectorului de laturi
void sortEdgeArray_2(int numberOfRoads,TEdge edgeArray[numberOfRoads]) {
    for(int i=0;i<numberOfRoads-1;i++)
        for(int j=i+1;j<numberOfRoads;j++)
            if(edgeArray[i].cost > edgeArray[j].cost){
                int k = edgeArray[i].cost;
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

//functie de adaugare la dictionar
void add_name_2(char name[], char name_list[][1000]) {
    int counter = 1,condition = 1;

    while(name_list[counter][0] != 0) {
        if(strcmp(name,name_list[counter]) == 0)
            condition = 0;
        counter++;
        }

    if(condition == 1)
        strcpy(name_list[counter],name);

}

//parcurgere DFS speciala care implica conditia de a ajunge la insula
int DFS_2(Graph graph, int node) {
    (graph.visited)[node] = 1; 
    TNode* adjNode = (graph.adj_list)[node];
    while (adjNode != NULL) {
        
        int adjFinish = adjNode->finish;
        
        if (!(graph.visited)[adjFinish]) 
            DFS_2(graph, adjFinish);

        adjNode = adjNode->next;
    }

    if((graph.visited)[1] == 0)
        return 0;
    
    return 1;
}

//algoritmul dijkstra
void Dijkstra(FILE *out, Graph graph, int numberOfNodes,int adj_mat[1000][1000],int source, char name_list[][1000],int depth[1000],int weight) {
    int cost[numberOfNodes][numberOfNodes],distances[numberOfNodes],pred[numberOfNodes];
    int visited[numberOfNodes],count,mindistance,nextnode;

    for(int i=1;i<=numberOfNodes;i++)
        for(int j=1;j<=numberOfNodes;j++)
            if(adj_mat[i][j] == 0)
                cost[i][j] = INF;
            else cost[i][j] = adj_mat[i][j];

    for(int i=1;i<=numberOfNodes;i++){
        distances[i] = cost[source][i];
        pred[i] = source;
        visited[i] = 0;
    }

    distances[source] = 0;
    visited[source] = 1;
    count = 1;

    while(count < numberOfNodes) {
        mindistance = INF;
    
    for(int i=1;i<=numberOfNodes;i++)
        if(distances[i] < mindistance && !visited[i]) {
        mindistance = distances[i];
        nextnode = i;
    }
    
    
    visited[nextnode] = 1;
    for(int i=1;i<=numberOfNodes;i++)
        if(!visited[i])
            if(mindistance + cost[nextnode][i] < distances[i]) {
                distances[i] = mindistance + cost[nextnode][i];
                pred[i] = nextnode;
            }
        
    count++;
    }

    //conditia de a ajunge la corabie
    if(visited[numberOfNodes] == 0){
        fprintf(out,"Echipajul nu poate transporta comoara inapoi la corabie");
        return;
        }
   
    //pt ca am folosit vector de tati,drumul nostru este invers si trebuie pus in ordine
    char name_list_inversed[1000][1000];
    int counter = 0,min = INF;

    int path = pred[numberOfNodes];
    strcpy(name_list_inversed[counter],name_list[numberOfNodes]);
    counter++;

    while(path != source){
        if(depth[path] < min)
            min = depth[path];
        strcpy(name_list_inversed[counter],name_list[path]);
        if(path)
        path = pred[path];
        counter++;
    }
    strcpy(name_list_inversed[counter],name_list[1]);


    
    for(int i=counter;i>=0;i--)
        fprintf(out,"%s ",name_list_inversed[i]);

    fprintf(out,"\n");

    fprintf(out,"%d\n",distances[numberOfNodes]);

    fprintf(out,"%d\n", min);

    int score = weight/min;

    fprintf(out,"%d\n", score);
}




void task2() {

    //prima deschidere de fisier,facem doar notarea locatiilor
    FILE *in = fopen("tema3.in","r");
    
    int numberOfNodes,numberOfRoads,weight;
    int adj_mat[1000][1000];
    
    for(int i=1;i<=numberOfNodes;i++)
        for(int j=1;j<=numberOfNodes;j++)
            adj_mat[i][j] = INF;
    
    
    fscanf(in,"%d",&numberOfNodes);
    fscanf(in,"%d",&numberOfRoads);
    
    Graph graph = createGraphAdjList(numberOfNodes);

    char string1[1000], string2[1000],string[1000];
    int cost,depth[1000];
    char name_list[numberOfRoads][1000];
    for(int i=0;i<=numberOfNodes;i++)
        name_list[i][0] = 0;
   
    for(int i=0;i<numberOfRoads;i++)
        fscanf(in,"%s %s %d",string1,string2,&cost);
        

    fscanf(in,"%s %d",string,&cost);
    strcpy(name_list[1],string);
    depth[1] = cost;

    fscanf(in,"%s %d",string,&cost);
    strcpy(name_list[numberOfNodes],string);
    depth[numberOfNodes] = cost;

    for(int i=1;i<=numberOfNodes-2;i++){
        fscanf(in,"%s %d",string,&cost);
        add_name_2(string,name_list);
        depth[i+1] = cost;
        }

    fscanf(in,"%d",&weight);

    fclose(in);

    //a doua deschidere de fisier,luam restul datelor cum ar fi costuri si directiile drumurilor
    FILE *in2 = fopen("tema3.in","r");

    int u,v;
    TEdge edgeArray[numberOfRoads+1];

    fscanf(in2,"%d",&numberOfNodes);
    fscanf(in2,"%d",&numberOfRoads);

    for(int i=0;i<numberOfRoads;i++){
        fscanf(in,"%s %s %d",string1,string2,&cost);

        for(int j=1;j<= numberOfNodes ;j++){
            if(strcmp(name_list[j], string1) == 0)
                u = j;
            if(strcmp(name_list[j], string2) == 0)
                v = j;
            }

        insertEdge(graph, u, v);

        edgeArray[i].cost = cost;//adaugare laturilor in vectorul de laturi
        edgeArray[i].node1 = u;
        edgeArray[i].node2 = v;

        adj_mat[u][v] = cost;

        }
   
    for(int i=1;i<=numberOfNodes;i++)
        fscanf(in,"%s %d",string,&cost);

    fscanf(in2,"%d",&weight);
    fclose(in2);

    sortEdgeArray_2(numberOfRoads,edgeArray);

    FILE *out = fopen("tema3.out","w");
    
    if(DFS_2(graph,numberOfNodes) == 0)
        fprintf(out, "Echipajul nu poate ajunge la insula");
    else 
        Dijkstra(out,graph,numberOfNodes,adj_mat,1,name_list,depth,weight);

    fclose(out);
}