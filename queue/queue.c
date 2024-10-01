#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "../list/list.h"

/**
 * @brief Creates a new, empty queue.
 *
 * @return A pointer to the newly created queue.
 */
 Queue* createQueue() {
    Queue* queue;
    queue = malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}


/**
 * @brief Checks whether the queue is empty.
 *
 * @param q The queue to check.
 * @return 1 if the queue is empty, 0 otherwise.
 */
int isQueueEmpty(Queue q) {
    if ((!q.front) && (!q.rear)) return 1;
    return 0;
}


/**
 * @brief Prints all the elements in the queue, from front to rear.
 *
 * @param q The queue to print.
 */
void queuePrint(Queue q) {

    if (isQueueEmpty(q) == 1){
        printf("[]");
        return;
    }
    printf("[");
    Cell* tmp;
    tmp = q.front;
    do{
        printf("%d",tmp->value);
        tmp = tmp->nextCell;
        if(tmp != NULL) printf(",");

    }while (tmp != NULL);
    printf("]");
    return;
}


/**
 * @brief Adds an element to the rear of the queue.
 *
 * @param q A pointer to the queue to add the element to.
 * @param data The data to be added to the queue.
 */
void enqueue(Queue* q, int data) {
    if (!q) return;
    Cell* cell;
    cell = malloc(sizeof(Cell));
    cell->value = data;
    cell->key = NULL;
    cell ->nextCell = NULL;
    if (isQueueEmpty(*q) == 1){
        q->front = cell;
        q->rear = cell;


    }
    else{
        q->rear->nextCell = cell;
        q->rear = cell;
    }
    return;
}

/**
 * @brief Removes and returns the front element of the queue.
 *
 * @param q A pointer to the queue to remove the front element from.
 * @return The value stored in the front element of the queue.
 */
int dequeue(Queue* q) {
    if (!q) return EXIT_FAILURE;

    if (isQueueEmpty(*q) == 1){
        printf("list is empty, can't dequeue, return -1\n");
        return -1;
    }
    int data;
    if (q->rear == q->front){
        data = q->front->value;
        //modif 
        free(q->rear);
        q->rear = NULL;
        q->front = NULL;
    }
    else{
        data = q->front->value;
        Cell* tmp;
        tmp = q->front->nextCell;
        free(q->front);
        q->front = tmp;
    }
    return data;
}


/**
 * @brief Returns the value of the front node but doesn't modify the queue
 *
 * @param q The queue to get the front value.
 * @return The value of the front node.
 */
int queueGetFrontValue(Queue q) {

    if (isQueueEmpty(q) == 1){
        printf("list is empty, can't dequeue, return -1\n");
        return EXIT_FAILURE;
    }
    //int data;
    /*
    if (q.rear == q.front){
        data = q.front->value;
    }
    else{
        data = q.front->value;
    }
    */
    
    return q.front->value;
}
