#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include <assert.h>
/**
 * @brief Helper function to swap two elements in the heap.
 * @param h A pointer to the Heap data structure.
 * @param i The index of the first element.
 * @param j The index of the second element.
 */
void swap(Heap *h, int i, int j) {
    int temp = h->heap[i];
    h->heap[i] = h->heap[j];
    h->heap[j] = temp;

    temp = h->position[h->heap[i]];
    h->position[h->heap[i]] = h->position[h->heap[j]];
    h->position[h->heap[j]] = temp;
}


/**
 * @brief Creates a new Heap data structure.
 * @param n The maximum number of elements that the heap can store.
 * @return A pointer to the newly created Heap data structure.
 * The elements of the arrays position and priority are initialized to -1
 */
Heap* createHeap(int n) {
    if (n<=0) return NULL;
    int i;
    Heap* newHeap;
    newHeap = malloc(sizeof(Heap));

    newHeap->n = n;
    newHeap->nbElements = 0;
    newHeap->position = malloc(sizeof(int)*n);
    newHeap->priority = malloc(sizeof(double)*n);
    newHeap->heap = malloc(sizeof(int)*n);
   
    for (i=0; i<n; i++){
        newHeap->position[i] = -1;
        newHeap->priority[i] = -1;
        newHeap->heap[i] = -1;
    }

    return newHeap;
}

/**
 * @brief Prints the elements in the Heap data structure.
 * @param h The Heap data structure to print.
 */
void printHeap(Heap h) {
    
    int i;

    printf("\nn: %d\nnbElements: %d\n",h.n,h.nbElements);
    printf("position: [");
    for (i=0; i<h.n; i++){
        printf("%d ",h.position[i]);
    }
    printf("]\n");

    printf("priority: [");
    for (i=0; i<h.n; i++){
        printf("%.2f ",h.priority[i]);
    }
    printf("]\n");
    printf("heap: ");
    if (!h.nbElements){
        printf("[]\n");
    }
    else{
        printf("[ ");
        for (i=0; i<h.nbElements; i++){
            printf("%d ",h.heap[i]);
        }
        printf("]\n");
    }
    return;
}

/**
 * @brief Gets the element with the smallest priority (smallest value in the priority array) from the Heap data structure.
 * @param h The Heap data structure to get the element from.
 * @return The element with the smallest priority.
 */
int getElement(Heap h) {
    if (!h.nbElements){
        printf("empty heap : can't get the element with the smallest priority\n");
        return -1;
    }
    
    return h.heap[0];
}

/**
 * @brief Inserts a new element into the Heap data structure with the given priority.
 * @param h A pointer to the Heap data structure to insert the element into.
 * @param element The element to insert.
 * @param priority The priority of the element to insert.
 */
void insertHeap(Heap *h, int element, double priority) {

    if(!h) return;

    assert(element < h->n && element >=0); // 0<= element < n
    assert(h->position[element] == -1); // element not already in the heap

    h->position[element] = h->nbElements;
    h->priority[element] = priority;
    h->heap[h->nbElements] = element;
    float p;
    p = h->nbElements;
    h->nbElements +=1;
    while ((p-1)/2 >= 0){

        if (h->priority[h->heap[(int)((p-1)/2)]] > h->priority[h->heap[(int)p]] ){
            swap(h,p,(int)((p-1)/2));   
 
        p = (p-1)/2.0;
        }
        else break;
    }
    
}

/**
 * @brief Modifies the priority of an element in the Heap data structur-1e.
 * @param h A pointer to the Heap data structure to modify.
 * @param element The element whose priority is to be modified.
 * @param priority The new priority of the element.
 */
void modifyPriorityHeap(Heap *h, int element, double priority) {
    double oldPriority;
    int i;
    oldPriority = h->priority[element];
    i = h->position[element];
    h->priority[element] = priority;

    /*moving up the element*/
    if (oldPriority > priority){
        float p;
        p = h->position[element];
        while((p-1)/2 >= 0){
            if (h->priority[h->heap[(int)((p-1)/2)]] > h->priority[h->heap[(int)p]]){
                swap(h,p,(int)((p-1)/2));

            }
            p = (p-1)/2.0;
        }
        return;
    }

    /*moving down the element*/
    else if (oldPriority < priority){
        while (2*i + 1 < h->nbElements || 2*i+2 < h->nbElements ){
            int l;
            int r;
            int tmp;
            l = 2*i+1;
            r = 2*i+2;
            
            if (l<h->nbElements && h->priority[h->heap[l]] <
                h->priority[h->heap[i]] && r<h->nbElements && h->priority[h->heap[r]] <
                h->priority[h->heap[i]])

            {
                tmp = i;
                i =    (h->priority[h->heap[l]] > h->priority[h->heap[r]])     ? r : l;
                swap(h,tmp,h->priority[h->heap[l]] > h->priority[h->heap[r]] ?
                r : l);
                
            }



        

            else if (l<h->nbElements && h->priority[h->heap[l]] <
                h->priority[h->heap[i]])
            {
                swap(h,i,l);
                i = l;
            }
            else if (r<h->nbElements && h->priority[h->heap[r]] <
                h->priority[h->heap[i]])
            {
                swap(h,i,r);
                i = r;
            }
            else break;

        }
    }

    else return;

}


/**
 * @brief Removes the element with the smallest priority (smallest value in the priority array) from the Heap data structure.
 * @param h A pointer to the Heap data structure to remove the element from.
 * @return The element with the smallest priority that was removed from the Heap data structure.
 */
int removeElement(Heap *h) {
    int out;
    out = getElement(*h);

    swap(h,0,h->nbElements-1);

    h->position[out] = -1;
    h->nbElements -=1;
    int root;
    root = 0;
    while (2*root +1 < h->nbElements || 2*root + 2 < h->nbElements){
        int r;
        int l;
        int tmp;
        r = 2*root +2;
        l = 2*root +1  ;

        if (l < h->nbElements && h->priority[h->heap[l]] <
            h->priority[h->heap[root]] && r < h->nbElements && h->priority[h->heap[r]] <
            h->priority[h->heap[root]] )
        {
                tmp = root;
                root =    (h->priority[h->heap[l]] > h->priority[h->heap[r]])     ? r : l;
                swap(h,tmp,h->priority[h->heap[l]] > h->priority[h->heap[r]] ?
                r : l);
                
        }
        else if (l < h->nbElements && h->priority[h->heap[l]] <
            h->priority[h->heap[root]]){
            swap(h,root,l);
            root = l;
            
        }

        else if (r < h->nbElements && h->priority[h->heap[r]] <
            h->priority[h->heap[root]] ){

            swap(h,root,r);
            root = r;

        }
        else{
            break;
        }
    }
    return out;

}
