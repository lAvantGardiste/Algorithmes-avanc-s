/**
 * \file bst.c
 * \brief Implementation of classical functions for BST
 * \author Loïck LHOTE
 * \version 0.1
 * \date janvier 2023
*
 * Source code of the functions declared in bst.h.
 * Thes functions are to manipulate binary search trees.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "bst.h"
#define MAX(x,y) (x>=y ? x : y)

/**
 * @brief Create an empty binary search tree.
 * @return A pointer to the root of the new empty tree (NULL pointer).
 */
BinarySearchTree createEmptyBST() {
    return NULL;
}

/**
 * @brief Free the memory of a binary search tree.
 * @param tree Pointer to the root of the tree.
 */
void freeBST(BinarySearchTree tree) {
    if (!tree){
        return;
    }


    freeBST(tree->leftBST);
    freeBST(tree->rightBST);
    free(tree);
    return;
}


/**
 * @brief Add a value to a binary search tree.
 * @param tree Pointer to the root of the tree.
 * @param value The value to add.
 * @return A pointer to the root of the modified tree.
 */
BinarySearchTree addToBST(BinarySearchTree tree, int value) {
    if (!tree){
        NodeBST* node;
        node = malloc(sizeof(NodeBST));
        node->value = value;
        node->leftBST = NULL;
        node->rightBST = NULL;
        return node;
    }
    if (tree->value < value){
        tree->rightBST = addToBST(tree->rightBST, value);

    }
    if (tree->value > value){
        tree->leftBST = addToBST(tree->leftBST,value);
    }
    
    return tree;

}


/**
 * @brief Compute the height of a binary search tree.
 * @param tree Pointer to the root of the tree.
 * @return The height of the tree.
 */
int heightBST(BinarySearchTree tree) {
    if (!tree) return -1;
  
  /*if (!tree->leftBST && !tree->rightBST){
        return 0;
    }*/
    int left_height;
    int right_height;
    left_height = heightBST(tree->leftBST);
    right_height = heightBST(tree->rightBST);
     
    return 1 + MAX(left_height,right_height);
    

}


/**
 * @brief Search for a value in a binary search tree.
 * @param tree Pointer to the root of the tree.
 * @param value The value to search for.
 * @return A pointer to the node containing the value, or NULL if the value is not in the tree.
 */
BinarySearchTree searchBST(BinarySearchTree tree, int value) {
    if (!tree) return NULL;
    if (tree->value == value) return tree;
    
    if(value > tree->value){
        searchBST(tree->rightBST,value);
    }
    else{
        searchBST(tree->leftBST,value);
    }
}


/**
 * @brief Delete the root of a binary search tree.
 * @param tree Pointer to the root of the tree.
 * @return A pointer to the root of the modified tree.
 */
BinarySearchTree deleteRootBST(BinarySearchTree tree) {
    if (!tree) return NULL;
    

    if (!tree->leftBST && !tree->rightBST) return NULL;
    
    
    
    if (!tree->leftBST) return tree->rightBST;
    
    if (!tree->rightBST) return tree->leftBST;
    
/**
 * the root has 2 subtrees*/
    BinarySearchTree tmp;
    tmp = tree->leftBST;
/**
 * if the left subtree does not have a right subtree*/
    if (!tmp->rightBST){
        tree->value = tmp->value;
        tree->leftBST = tmp->leftBST;
        free(tmp);
        //tmp->rightBST = tree->rightBST;
        //free(tree);
        return tree;
    }
/**
 * if the left subtree does have a right subtree
 * we are looking for the rightes node of the leftsubtree while updating it and its
 father*/    
    else{
        BinarySearchTree father;
        while(1){
            if(!tmp->rightBST){
                break;
            }
            father = tmp;
            tmp = tmp->rightBST;
        }
        /**
         * updating the value of the new root with the value of the rightest
         * node*/
        tree->value = tmp->value;
        /**
         * deleting the rightest node and connecting its left subtree to his
         * father*/
        father->rightBST = tmp->leftBST;
        free(tmp);
        return tree;

    }
}


/**
 * @brief Delete a value from a binary search tree.
 * @param tree Pointer to the root of the tree.
 * @param value The value to delete.
 * @return A pointer to the root of the modified tree.
 */
BinarySearchTree deleteFromBST(BinarySearchTree tree, int value) {
    if (!tree) return NULL;
    if (tree->value == value){
        BinarySearchTree tmp;
        tmp = deleteRootBST(tree);
        free(tree);//attention j'avais oublié ça
        return tmp;
    }
    if (value > tree->value){
        tree->rightBST = deleteFromBST(tree->rightBST,value);
    }
    if (value < tree->value){
        tree->leftBST = deleteFromBST(tree->leftBST,value);
    }
    return tree;
       
    
}

/**
 * @brief Build a binary search tree from a given permutation.
 * @param permutation Array of integers representing the permutation
 * @param n size of the array
 * @return A binary such tree built by successively inserting the elements of permutation.
 */
BinarySearchTree buildBSTFromPermutation(int *permutation,size_t n) {
    BinarySearchTree tree;
    tree = createEmptyBST();
    for(size_t i=0; i<n; i++){
           tree = addToBST(tree,permutation[i]);
        }
    return tree;
}


/**
 * @brief Print the elements of a binary search tree in a pretty format.
 * @param tree Pointer to the root of the tree.
 * @param space Space to be printed before the current element.
 */
void prettyPrintBST(BinarySearchTree tree, int space) {
    if (tree == NULL) {
        return;
    }
    space += 10;

    prettyPrintBST(tree->rightBST, space);

    printf("\n");
    for (int i = 10; i < space; i++) {
        printf(" ");
    }
    printf("%d\n", tree->value);

    prettyPrintBST(tree->leftBST, space);
}

/**

Quelles conclusions pouvez-vous tirer des résultats d’expériences que vous obtenez ?

... Répondre ici.


*/
