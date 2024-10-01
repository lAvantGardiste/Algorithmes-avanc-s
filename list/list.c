/**
 * @file list.c
 * @brief Implementation file for a linked list
 *
 * This file contains the implementation of the linked list data structure
 * and its associated functions.
 *
 * @author Loïck Lhote
 * @date February 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

/**
 * @brief Creates a new linked list
 *
 * @return A pointer to the newly created linked list
 */
List newList() {
    return NULL;
}

/**
 * @brief Frees the memory used by a linked list
 *
 * @param L Pointer to the linked list to be freed
 */
void freeList(List L){
/* if the list is a NULL pointer*/    
    if (!L){
        return;
    }
    if (!L->nextCell){
        free(L->key);
        free(L);


    }
    else{
       freeList(L->nextCell);
       free(L->key);
       free(L);
    }
    return;
}

/**
 * @brief Prints the contents of a linked list
 *
 * @param L Pointer to the linked list to be printed
 * @param type If type==0, prints only the values, otherwise print the couples (key,vlaue)
 *
 * Prints the linked list in the following way if k!=0:
 * [(key 1, value 1),(key 2, value 2), … ,(key k, value k)]
 * Prints the linked list in the following way if k==0:
 * [value 1,value 2,…,value k]
 */

void printList(List L, int type) {
    
    if (!L){
        /*
        printf("The linked list passed in paramater is empty");
        */
        printf("[]");
        return;
    }
    static int p = 0;
    if (p==0){

        printf("[");
        p = -1;
    }
    if (!type){
        if (L->nextCell == NULL){
            printf("%d]",L->value);
            p = 0;
            return;

        }
        else{
            printf("%d,",L->value);
            printList(L->nextCell, type);
        }
    }
    else{
        if (L->nextCell == NULL){
            if (!L->key){
                printf("(NULL,%d)]",L->value);
            }
            else{
                printf("(%s,%d)]",L->key,L->value);
            }
            p=0;
            return;
        }
        else{
            if (!L->key){
                printf("(NULL,%d),",L->value);
            }
            else{
                printf("(%s,%d),",L->key,L->value);
            }
            printList(L->nextCell, type);
        }
    }
    
    return;
}

/**
 * @brief Finds a key in a linked list
 *
 * @param L Pointer to the linked list to search in
 * @param key Key to search for
 *
 * @return A pointer to the first cell containing the key, or NULL if the key is not found
 */
Cell* findKeyInList(List L, string key) {

    if (!L){
        return NULL;
    }
    

    if (key == NULL){
        if (L->key == NULL){
            return L;
        }
        else{
            findKeyInList(L->nextCell,key);
        }
    }
    else{
        if (L->key != NULL){
            if (strcmp(key,L->key) == 0){
                return L;

            }
            else {
                findKeyInList(L->nextCell,key);
            }
        }
        else{
            findKeyInList(L->nextCell,key);

        }
    }
}

/**
 * @brief Deletes a key from a linked list
 *
 * @param L Pointer to the linked list to search in
 * @param key Key to delete
 *
 * @return A pointer to the modified linked list
 * Only the first occurrence of the key is deleted.
 */
List delKeyInList(List L, string key) {
    /*List empty*/
    if (!L){    
        return NULL;

    }
    Cell* target;
    target = findKeyInList(L, key);
    /*if the key does not exist in the linked list*/
    if (!target){
        return L;

    }
    /*target exists in the linked list */
    

    /*List contains only one cell*/
    if(L->nextCell == NULL){
        free(L->key);
        free(L);
        return NULL;
    }
    
    if (L==target){
        Cell* tmp;
        tmp = L->nextCell;
        free(L->key);
        free(L);
        return tmp;
    }
    Cell* tmp2;
    tmp2 = L;
    while(1){
        if(tmp2->nextCell == target){
            break;
        }
        tmp2 = tmp2->nextCell;
    }
    tmp2->nextCell = target->nextCell;
    free(target->key);
    free(target);
    
    return L;

}

/**
 * @brief Adds a key-value pair to a linked list
 *
 * @param L Pointer to the linked list to add to
 * @param key Key to add
 * @param value Value to add
 *
 * @return A pointer to the modified linked list
 *
 * The key-value pair is added at the beginning of the list
 */

 List addKeyValueInList(List L, string key, int value) {
    Cell* newCell;
    newCell = malloc(sizeof(Cell));
    newCell->value = value;
    newCell->key = NULL;
    newCell->nextCell = NULL;
    if (key != NULL){
        newCell->key = malloc(strlen(key)+1);
        strcpy(newCell->key, key);

    }
    if(L==NULL){
       return newCell;
    }
    else{

        newCell->nextCell = L;
        /*???? L=NULL;*/

        

    }
    return newCell;
}


