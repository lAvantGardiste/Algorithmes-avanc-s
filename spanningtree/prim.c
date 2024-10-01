/**
 * @file graph.c
 *
 * @brief This file implements a graph data structure using a table of lists.
 */

#include <stdlib.h>
#include <stdio.h>
#include "../graph/graph.h"
#include "../heap/heap.h"
#define INFINITY 2.00 /* we will never have distance(u,v) >= 2 because we are in
                        [0,1]x[0,1]*/
/**
 * @brief Function that computes a minimum spanning tree of graph g of the connex component of the vertex s
 *
 * @param graph The graph
 * @param s Index of the initial vertex of the Prim procedure.
 *
 * The array parents is updated so that it contains the spanning tree
 * computed by the Prim algorithm.
 * Note that the array parents must be initialized before calling the function.
 */
 void Prim(Graph g, int s){
    Heap* heap;
    heap = createHeap(g.numberVertices) ;
    for (int i = 0; i<g.numberVertices; i++){
        insertHeap(heap, i, INFINITY) ;
    }
    heap->priority[s] = 0.00 ;
    g.parents[s] = s;
    int minVertexFromHeap;
    while (heap->nbElements){
        minVertexFromHeap = removeElement(heap);
        Cell* tmp;
        tmp = g.array[minVertexFromHeap] ;
        while (tmp){
            int v;
            v = tmp->value;
            if ( ( heap->position[v] != -1 ) && ( heap->priority[v] > 
                                                distance(g.xCoordinates[minVertexFromHeap],
                                                g.yCoordinates[minVertexFromHeap],
                                                g.xCoordinates[v],
                                                g.yCoordinates[v]) )
                    
              ){
                g.parents[v] = minVertexFromHeap ;
                modifyPriorityHeap(heap, v,distance(g.xCoordinates[minVertexFromHeap],
                                                    g.yCoordinates[minVertexFromHeap],
                                                    g.xCoordinates[v],
                                                    g.yCoordinates[v])) ;


            }
        tmp = tmp->nextCell ;
        }
    }
    
    

    


    return;

 }

