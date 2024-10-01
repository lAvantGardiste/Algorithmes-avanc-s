#include <stdio.h>
#include "heap.h"

int main() {
    Heap *heap = createHeap(10);
    
    /*
    printf("Current heap: ");
    printHeap(*heap);
    

    insertHeap(heap, 1, 5.0);
    printf("Current heap: ");
    printHeap(*heap);

    insertHeap(heap, 2, 2.0);
    printf("Current heap: ");
    printHeap(*heap);

    insertHeap(heap, 3, 4.0);
    printf("Current heap: ");
    printHeap(*heap);

    insertHeap(heap, 4, 1.0);
    printf("Current heap: ");
    printHeap(*heap);

    insertHeap(heap, 0, 3.0);
    printf("Current heap: ");
    printHeap(*heap);
    

    printf("Element with lowest priority: %d\n", getElement(*heap));
    modifyPriorityHeap(heap, 4, 3.5);
    printf("Heap after modifying priority of element 4: ");
    printHeap(*heap);
    int removedElement = removeElement(heap);
    printf("Heap after removing element with lowest priority: ");
    printHeap(*heap);
    printf("Removed element: %d\n", removedElement);
    */
    printf("Current heap: ");
    printHeap(*heap);
    

    insertHeap(heap, 0, 0.0);
    insertHeap(heap, 1, 1.0);
    printf("Current heap: ");
    printHeap(*heap);

    insertHeap(heap, 2, 2.0);
    printf("Current heap: ");
    printHeap(*heap);

    insertHeap(heap, 3, 3.0);
    printf("Current heap: ");
    printHeap(*heap);

    insertHeap(heap, 4, 4.0);
    printf("Current heap: ");
    printHeap(*heap);

    insertHeap(heap, 5, 5.0);
    printf("Current heap: ");
    printHeap(*heap);
    insertHeap(heap, 6, 6.0);
    insertHeap(heap, 7, 7.0);
    insertHeap(heap, 8, 8.0);
    insertHeap(heap, 9, 9.0);
    heap->position[0] = 0 ;
    heap->heap[0] = 0;
    heap->position[1] = 2 ;
    heap->position[2] = 1 ;
    heap->position[3] = 6 ;
    heap->position[4] = 4 ;
    heap->position[5] = 5 ;
    heap->position[6] = 3 ;
    heap->position[7] = 9 ;
    heap->position[8] = 8 ;
    heap->position[9] = 7;
    heap->heap[1] =2 ;
    heap->heap[2] =1 ;
    heap->heap[3] =6 ;
    heap->heap[4] =4 ;
    heap->heap[5] =5 ;
    heap->heap[6] =3 ;
    heap->heap[7] = 9;
    heap->heap[8] = 8;
    heap->heap[9] = 7;
    printf("Current heap: ");
    printHeap(*heap);
    int removedElement = removeElement(heap);
    printf("Heap after removing element with lowest priority: ");
    printHeap(*heap);
    printf("Removed element: %d\n", removedElement);
    return 0;
}
