/*AMET LEVENT - 313CD*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "task1.h"

//functia de adaugare a unei locatii la dictionar,si atribuirea unui index locatiei
void add_name(char name[], char name_list[100][100]) {
    int counter = 1,condition = 1;

    while(name_list[counter][0] != 0) {
        if(strcmp(name,name_list[counter]) == 0)
            condition = 0;  //verificare daca locatia a fost deja bagata
        counter++;
        }

    if(condition == 1)  //conditia de adaugare
        strcpy(name_list[counter],name);

}


void task1() {

    //prima deschidere de fisier,facem doar notarea locatiilor
    FILE *in = fopen("tema3.in","r");
    
    int numberOfNodes,numberOfRoads;
    
    fscanf(in,"%d",&numberOfNodes);
    fscanf(in,"%d",&numberOfRoads);
    
    Graph graph = createGraphAdjList(numberOfNodes);

    char string1[100], string2[100];
    int cost;
    char name_list[numberOfRoads][100];
    for(int i=0;i<=numberOfNodes;i++)
        name_list[i][0] = 0;
   
    for(int i=0;i<numberOfRoads;i++){
        fscanf(in,"%s %s %d",string1,string2,&cost);
        add_name(string1,name_list);
        add_name(string2,name_list);
        }

    fclose(in);

    //a doua deschidere de fisier,luam restul datelor cum ar fi costuri si directiile drumurilor
    FILE *in2 = fopen("tema3.in","r");

    int u,v;
    TEdge edgeArray[2*numberOfRoads+1];

    fscanf(in2,"%d",&numberOfNodes);
    fscanf(in2,"%d",&numberOfRoads);

    for(int i=0;i<numberOfRoads;i++){
        fscanf(in,"%s %s %d",string1,string2,&cost);

        for(int j=1;j<= numberOfNodes ;j++){
            if(strcmp(name_list[j], string1) == 0)
                u = j;
            if(strcmp(name_list[j], string2) == 0)
                v = j;
            }//aflam capetele drumului

        insertEdge(graph, u, v);//adaugam ambele sensuri ale drumului
        insertEdge(graph, v, u);

        edgeArray[i].cost = cost;//adaugam un sens al drumului in vectorul de laturi
        edgeArray[i].node1 = u;
        edgeArray[i].node2 = v;

        edgeArray[i+numberOfRoads].cost = cost;//adauga al doilea sens in vector
        edgeArray[i+numberOfRoads].node1 = v;
        edgeArray[i+numberOfRoads].node2 = u;
        }
   
    fclose(in2);

    sortEdgeArray(numberOfRoads,edgeArray);//sortam vectorul de laturi,conditie necesara pe kruskal


    FILE *out = fopen("tema3.out","w");

    int nrConex = nrConexComponents(graph,numberOfRoads,edgeArray);
    fprintf(out,"%d\n",nrConex);//nr de componente conexe

    int min_array_cost[100];

    for(int i=1;i<=nrConex;i++)
        min_array_cost[i-1] = Kruskal(graph, numberOfRoads, edgeArray, i);

//sortam costurile drumurilor minime din toate componentele conexe
    for(int i=0;i<nrConex-1;i++)
        for(int j = i+1;j<nrConex;j++)
            if(min_array_cost[i]>min_array_cost[j]) {
                int swap = min_array_cost[i];
                min_array_cost[i] = min_array_cost[j];
                min_array_cost[j] = swap;
            }

    for(int i=0;i<nrConex;i++)
        fprintf(out,"%d\n",min_array_cost[i]);

    fclose(out);

//eliberarea memoriei
    free(graph.visited);
    for(int i=1;i<=numberOfNodes;i++){
        TNode* currNode = (graph.adj_list)[i];
        while(currNode != NULL){
            TNode* curr = currNode;
            currNode = currNode->next;
            free(curr);
            }
        }
    free(graph.adj_list);

}