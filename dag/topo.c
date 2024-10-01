/**
 * @file topo.c
 *
 * @brief This file implements based on the topological ordering.
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../graph/graph.h"
#include "../stack/stack.h"
#define MAX(x,y) (x >= y ? x : y)
#define MIN(x,y) (x <= y ? x : y)

/**
 * @brief Function to perform a topological sort of a graph. Update the field topological_ordering of the graph.
 *
 * @param graph The graph to be sorted.
 */
void topologicalSort(Graph graph){
    int numberOfVertexVisited = 0;
    //Stack* stackTopo;
    //stackTopo = createStack();
    for (int i = 0; i<graph.numberVertices; i++){
        if (graph.parents[i] == -1){
            graph.parents[i] = -2;
            Stack* stackDFS = createStack();
            push(stackDFS,i);
            while (*stackDFS != NULL){
                int topStack;
                topStack = peek(*stackDFS);
                Cell* tmp;
                tmp = graph.array[topStack];
                int p;
                p = 1 ;

                while ( tmp ){
                    if (graph.parents[tmp->value] == -1){
                        graph.parents[tmp->value] = 2;
                        push(stackDFS,tmp->value);
                        p = 0;
                        break;
                    }
                    tmp = tmp->nextCell;
                }

                if (p == 1){
                    if (!(*stackDFS)->nextCell){
                        graph.parents[topStack] = topStack;
                    }


                    /*i is the beginning of a connexe component */
                    else {
                        graph.parents[topStack] = (*stackDFS)->nextCell->value;

                    }

                    graph.topological_ordering[graph.numberVertices-1 -
                        numberOfVertexVisited ] = pop(stackDFS);
                    numberOfVertexVisited++;


                }

            }
            /*
               while (*stackTopo){    
               graph.topological_ordering[m] = pop(stackTopo);
               printf("%d\n",m);
               m++;

               }
             */
        }
    }

    /* find the beginning of every connexe components */

    return;
}


/**
 * @brief Function to compute the earliest start date of each vertex in a graph.
 *
 * @param graph The graph for which to compute the earliest start dates.
 * Updates the array containing the earliest start date of each vertex in the graph structure.
 */

/*
   char str[10];
   int isSource;
   isSource = 1 ;
   Stack* stack;
   double max;
   for (int j = 0; j<graph.numberVertices; j++){
   sprintf(str,"%d",j);

   for (int i = 0; i<graph.numberVertices; i++){

   if (findKeyInList(graph.array[i],str) != NULL){
   isSource = 0;
   break;
   }
   }

   if (isSource == 1){
   graph.earliest_start[j] = 0.00;

   }
   else{

   }
   isSource = 1;
   }
 */
void computeEarliestStartDates(Graph graph) {
    graph.earliest_start[graph.topological_ordering[0]] = 0.00;
    char key[10];

    for (int j = 1; j<graph.numberVertices; j++){
        double dtot;
        dtot = 0.00;

        for (int i = 0; i<graph.numberVertices; i++){
            sprintf(key,"%d",graph.topological_ordering[j]);
            if (findKeyInList(graph.array[i],key) != NULL){
                dtot = MAX(dtot, graph.earliest_start[i] + distance(graph.xCoordinates[i],
                            graph.yCoordinates[i],
                            graph.xCoordinates[graph.topological_ordering[j]],
                            graph.yCoordinates[graph.topological_ordering[j]])
                        );

            }
        }

        graph.earliest_start[graph.topological_ordering[j]] = dtot;
    }

    return;
}


/**
 * @brief Function to compute the latest start date of each vertex in a graph.
 *
 * @param graph The graph for which to compute the latest start dates.
 * Updates the array containing the latest start date of each vertex in the graph structure.
 */
void computeLatestStartDates(Graph graph) {
    double maxEarliestAmongWellVertex;
    maxEarliestAmongWellVertex = 0.00;
    for (int i = 0; i<graph.numberVertices; i++){
        if (!graph.array[i]){
            maxEarliestAmongWellVertex = MAX(maxEarliestAmongWellVertex, graph.earliest_start[i]);
        }
    }

    graph.latest_start[graph.topological_ordering[graph.numberVertices - 1]] = maxEarliestAmongWellVertex;

    for (int i = graph.numberVertices - 2; i>=0 ; i-- ){
        double dtard;
        dtard = maxEarliestAmongWellVertex;
 //     printf("max earliest : %lf\n\n",maxEarliestAmongWellVertex);
        if (graph.array[graph.topological_ordering[i]]){
            Cell* tmp;
            tmp = graph.array[graph.topological_ordering[i]];
            int sucessor;
            while (tmp){
                sucessor = tmp->value;
                dtard = MIN(dtard, graph.latest_start[sucessor] - distance(graph.xCoordinates[sucessor],
                            graph.yCoordinates[sucessor],
                            graph.xCoordinates[graph.topological_ordering[i]],
                            graph.yCoordinates[graph.topological_ordering[i]]) 
                        );
                tmp = tmp->nextCell;
            }
        }
        graph.latest_start[graph.topological_ordering[i]] = dtard;
    }
    return;


}

