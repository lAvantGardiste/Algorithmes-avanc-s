/**
 * \file rbst.c
 * \brief Implementation of the functions related to Randomized Binary Search Trees (RBST).
 * \author Loïck LHOTE
 * \version 0.1
 * \date janvier 2023
 *
 * Header file defining the data structure of a randomized binary search tree over integers and
 * declaring functions to manipulate them.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "rbst.h"
#define MAX(x,y) (x >= y ? x : y)

/**
 * @brief Create an empty binary search tree.
 * @return A pointer to the root of the new empty tree (NULL pointer).
 */
RBinarySearchTree createEmptyRBST(){
    return NULL;
}

/**
 * @brief Free the memory of a binary search tree.
 * @param tree Pointer to the root of the tree.
 */
void freeRBST(RBinarySearchTree tree){
    if (!tree) return;
    freeRBST(tree->leftRBST);
    freeRBST(tree->rightRBST);
    free(tree);
    return;
}

/**
 * @brief Compute the size of a randomized binary search tree.
 * @param tree Pointer to the root of the tree.
 * @return The number of nodes in the tree.
 */
int sizeOfRBST(RBinarySearchTree tree) {
    if (!tree) return 0;

    return 1 + sizeOfRBST(tree->leftRBST) + sizeOfRBST(tree->rightRBST);
}

/**
 * @brief Split a randomized binary search tree into two parts according to a value.
 * @param tree The RBST to split.
 * @param value The value to split the tree on.
 * @param inf Pointer to a randomized BST that will store the final tree containing the elements strictly smaller than value.
 * @param sup Pointer to a randomized BST that will store the final tree containing the elements greater or equal to value.
 *
 * Split a randomized binary search tree into two parts according to a value.
 *
 * Be carful: the RBST tree is modified during the process but the inf and sub parts contain together
 * all the nodes of tree.
 */
void splitRBST(RBinarySearchTree tree, int value, RBinarySearchTree* inf, RBinarySearchTree* sup) {
    if (!tree){
        *inf = NULL;
        *sup = NULL;
        return;
    }


    if (value == tree->value){
        *inf = tree->leftRBST;
        //tree->leftBST = NULL;
        *sup = tree;
        return;
    }

    if (value > tree->value){
        RBinarySearchTree* alpha;
        RBinarySearchTree* beta;
        alpha = malloc(sizeof(RBinarySearchTree));
        beta = malloc(sizeof(RBinarySearchTree));
        splitRBST(tree->rightRBST,value,alpha,beta);
        *inf = tree;
        (*inf)->rightRBST = *alpha;
        *sup = *beta;
        free(alpha);
        free(beta);
    }
    if(value < tree->value){
        // printf("gauche\n");
        RBinarySearchTree* alpha;
        RBinarySearchTree* beta;
        alpha = malloc(sizeof(RBinarySearchTree));
        beta = malloc(sizeof(RBinarySearchTree));
        splitRBST(tree->leftRBST,value,alpha,beta);
        //  printf("on passe le split\n");
        *sup = tree;
        (*sup)->leftRBST = *beta;
        *inf = *alpha;
        free(alpha);
        free(beta);

    }
    /*pas pensé à la possibilité que inf ou sup soit NULL ==> segmentation
     * fault*/
    if (*inf != NULL){
        (*inf)->size = sizeOfRBST(*inf);
    }         
    if (*sup != NULL){
        (*sup)->size = sizeOfRBST(*sup);
    }
    return;
}

/**
 * @brief Insert a value at the root of a randomized binary search tree.
 * @param tree Pointer to the root of the tree.
 * @param value The value to insert.
 * @return A pointer to the root of the modified tree.
 */
RBinarySearchTree insertAtRoot(RBinarySearchTree tree, int value) {
    RBinarySearchTree* inf;
    RBinarySearchTree* sup;
    inf = malloc(sizeof(RBinarySearchTree));
    sup = malloc(sizeof(RBinarySearchTree));
    splitRBST(tree,value,inf,sup);
    RBinarySearchTree node;
    node = malloc(sizeof(NodeRBST));
    node->value = value;
    node->size = sizeOfRBST(*inf) + sizeOfRBST(*sup) + 1;
    node->leftRBST = *inf;
    node ->rightRBST = *sup;
    //free(inf);
    //free(sup);
    return node;



}


/**
 * @brief Add a value to a binary search tree.
 * @param tree Pointer to the root of the tree.
 * @param value The value to add.
 * @return A pointer to the root of the modified tree.
 */
RBinarySearchTree addToRBST(RBinarySearchTree tree, int value){
    static int add = 0;
    if (!tree){
        RBinarySearchTree node;
        node = malloc(sizeof(NodeRBST));
        node->value = value;
        node->size = 1;
        node->leftRBST = NULL;
        node->rightRBST = NULL;
        add = 1;
        return node;

    }
    //srand(time(NULL));
    int p;
    p = rand()%101;
    if ((1.0/(tree->size+1)) < p/100.0){
        if (value > tree->value){
            tree->rightRBST = addToRBST(tree->rightRBST, value);
        }
        if (value < tree->value){
            tree->leftRBST = addToRBST(tree->leftRBST,value);
        }
        //update the size to do
        if (add==1) tree->size++;
        return tree;
    }
    //insertion at the root
    else{
        add = 1;
        return insertAtRoot(tree,value);
    }


}


/**
 * @brief Compute the height of a binary search tree.
 * @param tree Pointer to the root of the tree.
 * @return The height of the tree.
 */
int heightRBST(RBinarySearchTree tree) {
    if (!tree) return -1;
    if (!tree->leftRBST && !tree->rightRBST) return 0;
    int left_height;
    int right_height;
    left_height = heightRBST(tree->leftRBST);
    right_height = heightRBST(tree->rightRBST);

    return 1 + MAX(left_height,right_height);
}

/**
 * @brief Search for a value in a binary search tree.
 * @param tree Pointer to the root of the tree.
 * @param value The value to search for.
 * @return A pointer to the node containing the value, or NULL if the value is not in the tree.
 */
RBinarySearchTree searchRBST(RBinarySearchTree tree, int value){
    if (!tree) return NULL;

    if (value == tree->value) return tree;
    if (value > tree->value) searchRBST(tree->rightRBST,value);

    else searchRBST(tree->leftRBST,value);
}


/**
 * @brief Build a randomized binary search tree from a given permutation.
 * @param permutation Array of integers representing the permutation
 * @param n size of the array
 * @return A random binary such tree built by successively inserting the elements of permutation.
 */
RBinarySearchTree buildRBSTFromPermutation(int *permutation,size_t n) {
    if (!permutation) return NULL;
    RBinarySearchTree tree;
    tree = createEmptyRBST();

    for(size_t i = 0; i<n; i++){
        tree = addToRBST(tree,permutation[i]);
    }
    return tree;
}


/**
 * @brief Print the elements of a binary search tree in a pretty format.
 * @param tree Pointer to the root of the tree.
 * @param space Space to be printed before the current element.
 */
void prettyPrintRBST(RBinarySearchTree tree, int space) {
    if (tree == NULL) {
        return;
    }
    space += 10;

    prettyPrintRBST(tree->rightRBST, space);

    printf("\n");
    for (int i = 10; i < space; i++) {
        printf(" ");
    }
    printf("[%d,%d]\n", tree->value, tree->size);

    prettyPrintRBST(tree->leftRBST, space);
    return ;
}
