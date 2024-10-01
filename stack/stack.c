/**
 * @file stack.c
 * @brief Implementation file for the Stack data structure.
 */

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "../list/list.h"

/**
 * @brief Creates a new stack with no elements.
 *
 * @return A pointer to the new stack.
 */
Stack* createStack() {
    Stack* ptrStack = malloc(sizeof(Stack));
    *ptrStack = newList();

    
    return ptrStack;
}

/**
 * @brief Pushes an element onto the top of the stack.
 *
 * @param stack The stack to push onto.
 * @param data The data to push onto the stack.
 */
void push(Stack* stack, int data) {
    if (!stack) return;
    char key[10];
    sprintf(key,"%d",data);
    *stack = addKeyValueInList(*stack,key,data);
}

/**
 * @brief Pops an element from the top of the stack.
 *
 * @param stack The stack to pop from.
 *
 * @return The data from the top element of the stack.
 */
int pop(Stack* stack) {
    if (!stack){
        printf("ptrStack given is null : error for pop function\n");
        return EXIT_FAILURE;
    }
    if(!*stack){
        printf("can't pop from pointer pointing to an empty stack\n");
        return EXIT_FAILURE;
    }

    int data;
    data = (*stack)->value;
    Cell* tmp;
    tmp = *stack;
    *stack = (*stack)->nextCell;
    free(tmp->key);
    free(tmp);
    return data;
}

/**
 * @brief Peeks at the top element of the stack without removing it.
 *
 * @param stack The stack to peek at.
 *
 * @return The data from the top element of the stack.
 */
int peek(Stack stack) {
    if(!stack){
        printf("can't peek from an empty stack\n");
        return EXIT_FAILURE;
    }
    return stack->value;
}

/**
 * @brief Checks whether the stack is empty.
 *
 * @param stack The stack to check.
 *
 * @return 1 if the stack is empty, 0 otherwise.
 */
int isStackEmpty(Stack stack) {
    if (!stack) return 1;
    return 0;
}

/**
 * @brief Prints the contents of the stack to stdout.
 *
 * @param stack The stack to print.
 */
void stackPrint(Stack stack) {
    printList(stack,0);
    return;
}
