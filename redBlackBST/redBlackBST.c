/**
 * \file redBlackBST.c
 * \brief Implementation of the functions related to Red-Black Binary Search Trees.
 * \author Loïck LHOTE
 * \version 0.1
 * \date janvier 2023
 *
 * Header file defining the data structure of a red-black binary search tree over integers and
 * declaring functions to manipulate them.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "redBlackBST.h"




/**
 * @brief Create an empty red-black binary search tree.
 * @return A pointer to the root of the new empty tree (NULL pointer).
 */
RedBlackBST createEmptyRedBlackBST(){
    return NULL;
}

/**
 * @brief Free the memory of a red-black binary search tree.
 * @param tree Pointer to the root of the tree.
 */
void freeRedBlackBST(RedBlackBST tree){
    if (!tree) return;

    freeRedBlackBST(tree->leftBST);
    freeRedBlackBST(tree->rightBST);
    free(tree);
    return ;
}


/**
 * @brief Perform a left rotation on the Red-Black BST.
 * @param tree Pointer to the root node of the Red-Black BST.
 * @param node Pointer to the node to rotate around.
 * @return Pointer to the root node of the rotated Red-Black BST.
 */
RedBlackBST leftRotationRedBlackBST(RedBlackBST tree, NodeRedBlackBST *node){
    NodeRedBlackBST *rightChild = node->rightBST;
    node->rightBST = rightChild->leftBST;

    if (rightChild->leftBST != NULL)
        rightChild->leftBST->father = node;

    rightChild->father = node->father;

    if (node->father == NULL)
        tree = rightChild;
    else if (node->father->leftBST == node)
        node->father->leftBST = rightChild;
    else
        node->father->rightBST = rightChild;

    rightChild->leftBST = node;
    node->father = rightChild;

    return tree;
}




/**
 * @brief Perform a right rotation on the Red-Black BST.
 * @param tree Pointer to the root node of the Red-Black BST.
 * @param node Pointer to the node to rotate around.
 * @return Pointer to the root node of the rotated Red-Black BST.
 */
RedBlackBST rightRotationRedBlackBST(RedBlackBST tree, NodeRedBlackBST *node)
{
    NodeRedBlackBST *leftChild = node->leftBST;
    node->leftBST = leftChild->rightBST;

    if (leftChild->rightBST != NULL)
        leftChild->rightBST->father = node;

    leftChild->father = node->father;

    if (node->father == NULL)
        tree = leftChild;
    else if (node->father->leftBST == node)
        node->father->leftBST = leftChild;
    else
        node->father->rightBST = leftChild;

    leftChild->rightBST = node;
    node->father = leftChild;

    return tree;
}


/**
 * @brief Balance the Red-Black BST after inserting (or crating) a red node.
 * @param tree Pointer to the root node of the Red-Black BST. Be careful, the root may change after balancing.
 * @param curr Pointer to the node that was recently inserted. Be careful, the node to deal with may change after each operation.
 *
 * There are several cases:
 *   - if *curr is the root, then change its color in black
 *   - if the father of *curr is black, then it is finished
 *   - the father and the uncle are red (see course)
 *   - the uncle node is black and the current node is a right child (left rotation, see course)
 *   - the uncle node is black and the current node is a left child (right rotation, see course)
 */
void balanceRedBlackBST(RedBlackBST *tree, NodeRedBlackBST *curr){
    if (!tree || !(*tree) || !curr) return;
    if (!curr) return;

/* if the current node is the root of the whole tree */
    if (!curr->father){
      //  printf("on est a la racine donc on change juste la couleur en noir\n");
        curr->color = BLACK;
        return;
    }
    /* if the father of curr is black then we are good*/
    if (curr->father->color == BLACK) return;
    
    /* if the father of the curr is the root of the tree then we just change the
     * father to black*/
    if (curr->father->father == NULL){
        curr->father->color = BLACK;
        return;

    }
    /*from here, the father and the grandfather arent NULL */

    
    /*finding the uncle*/
    NodeRedBlackBST* uncle;
    int sideFather; /* 1 left | 2 right */
    int sideCurr; /* 4 left | 6 right */
    int side; /* 5 LL, 7 LR, 6 RL, 8 RR */
    int LL, RR, LR, RL;
    LL = 5;
    RR = 8;
    LR = 7;
    RL = 6;
    if (curr->father == curr->father->father->leftBST){
        uncle = curr->father->father->rightBST;
        sideFather = 1;
    }
    else{
        uncle = curr->father->father->leftBST;
        sideFather = 2;
    }    
    
    if (curr == curr->father->leftBST)
        sideCurr = 4;
    else
        sideCurr = 6;
    
    side = sideFather + sideCurr;
    
    if (!uncle){
        if (side == RL){
            *tree = rightRotationRedBlackBST(*tree,curr->father);
            balanceRedBlackBST(tree,curr->rightBST);
            return;

        }
        else if (side == LR){
            *tree = leftRotationRedBlackBST(*tree,curr->father);
            balanceRedBlackBST(tree,curr->leftBST);
        }
        else if (side == LL){
            curr->father->color = BLACK;
            curr->father->father->color = RED;
            *tree = rightRotationRedBlackBST(*tree,curr->father->father);
            return;
        }
        else if (side == RR){
            curr->father->color = BLACK;
            curr->father->father->color = RED;
            *tree = leftRotationRedBlackBST(*tree,curr->father->father);
            return;

        }

    }
    else{
        if (uncle->color == RED){
            uncle->color = BLACK;
            curr->father->color = BLACK;
            uncle->father->color = RED;
            balanceRedBlackBST(tree,uncle->father);
            return;
        }
        else{
            
            if (side == RL){
                *tree = rightRotationRedBlackBST(*tree,curr->father);
                balanceRedBlackBST(tree,curr->rightBST);
                return;

            }
            else if (side == LR){
                *tree = leftRotationRedBlackBST(*tree,curr->father);
                balanceRedBlackBST(tree,curr->leftBST);
                return;
            }
            else if (side == LL){
                curr->father->color = BLACK;
                curr->father->father->color = RED;
                *tree = rightRotationRedBlackBST(*tree,curr->father->father);
                return;
            }
            else if (side == RR){
                curr->father->color = BLACK;
                curr->father->father->color = RED;
                *tree = leftRotationRedBlackBST(*tree,curr->father->father);
                return;

            }

        }

    }


    return;
}


/**
 * @brief Insert a node in the Red-Black BST.
 * @param tree Pointer to the root node of the Red-Black BST.
 * @param value Value to be inserted in the Red-Black BST.
 *
 * The root of the tree can be modified so that we have a pointer on a RedBlackBST.
 */


/*
void insertNodeRedBlackBST(RedBlackBST *tree, int value){
    if (!tree) return;
    if (!*tree){
        NodeRedBlackBST* node;
        node = malloc(sizeof(NodeRedBlackBST));
        node->value = value;
        node->color = RED;
        node->father = NULL;
        node->leftBST = NULL;
        node->rightBST = NULL;
        *tree = node;
        return;
    }
    RedBlackBST* tmp;
    tmp = tree;
    RedBlackBST* father;
    father = tree;

    while (*tmp != NULL){
        if ((*tmp)->value < value){
            father = tmp;
            tmp = &((*tmp)->rightBST);
            

        }
        else{
            father = tmp;

            tmp = &((*tmp)->leftBST);

        }
    
    }
    NodeRedBlackBST* node;
    node = malloc(sizeof(NodeRedBlackBST));
    node->value = value;
    node->color = RED;
    node->father = *father;
    node->leftBST = NULL;
    node->rightBST = NULL;
    *tmp = node;
    balanceRedBlackBST(tree,node);
    return;

    



}
*/
void insertNodeRedBlackBST(RedBlackBST *tree, int value)
{   
    if (!tree) return;
    static int add = -1;
    static int firstCall = 0;
    static NodeRedBlackBST* father = NULL;
    static NodeRedBlackBST* curr = NULL;
    add++;
    firstCall++;
    if(!*tree){
        NodeRedBlackBST* node;
        node = malloc(sizeof(NodeRedBlackBST));
        node->value = value;
        node->color = RED;
        node->leftBST = NULL;
        node->rightBST = NULL;
        node->father = father;
        *tree = node;
        curr = node;
        if (firstCall == 1){
            //balanceRedBlackBST(tree,curr);
            add = -1;
            firstCall = 0;
            father = NULL;
            curr = NULL;
        }
        return;
    }
    if (value > (*tree)->value){

        father = *tree;
        insertNodeRedBlackBST(&((*tree)->rightBST),value);
        add--;
    }
    else{
        father = *tree;
        insertNodeRedBlackBST(&((*tree)->leftBST),value);
        add--;
    }
    if (add == 0 ){
 //       printf("on a remonté les appels\n\n");
        add = -1;
        firstCall = 0;
        father = NULL;
        balanceRedBlackBST(tree,curr);
        curr = NULL;
    }
    return;
}


/**
 * @brief Compute the height of a red-black binary search tree.
 * @param tree Pointer to the root of the tree.
 * @return The height of the tree.
 */
int heightRedBlackBST(RedBlackBST tree){
    if (tree == NULL) {
        return -1; // height of an empty tree is -1
    }
    int leftHeight = heightRedBlackBST(tree->leftBST);
    int rightHeight = heightRedBlackBST(tree->rightBST);
    if (leftHeight > rightHeight)
        return leftHeight + 1;
    else
        return rightHeight + 1;
}


/**
 * @brief Search for a value in a red-black binary search tree.
 * @param tree Pointer to the root of the tree.
 * @param value The value to search for.
 * @return A pointer to the node containing the value, or NULL if the value is not in the tree.
 */
RedBlackBST searchRedBlackBST(RedBlackBST tree, int value){
    if (tree == NULL)
        return NULL; // value not in the tree
    else if (value < tree->value)
        return searchRedBlackBST(tree->leftBST, value);
    else if (value > tree->value)
        return searchRedBlackBST(tree->rightBST, value);
    else
        return tree; // value found in the tree
}


/**
* @brief Computes the black height of a red-black tree (counts also the root if it is black).
* @param node Pointer to the root node of the tree.
* @return The black height of the tree.
*
* It returns 1 plus the black height of the tree if the root is black or the black heiht with a red root.
* It returns -1 if the black height of the left and right subtrees of the root are different
* or equal to -1.
*
*/

int blackHeightRedBlackBST(RedBlackBST tree) {
  if (!tree) {
    return 1; // If the tree is empty, then the black height is 1.
  }
  int leftHeight = blackHeightRedBlackBST(tree->leftBST); // Recursively compute the black height of the left subtree.
  int rightHeight = blackHeightRedBlackBST(tree->rightBST); // Recursively compute the black height of the right subtree.

  if(leftHeight!=rightHeight) // the black height of the left and right subtrees must be equal
    return -1;
  if(leftHeight==-1)
    return -1;

  // If the left and right subtrees have the same black height and the root node is black, then the black height of the tree is increased by 1.
  if (tree->color == BLACK) {
    return leftHeight + 1;
  }
  return leftHeight;
}



/**
 * @brief Test if a Red-Black BST is a valid Red-Black BST.
 * @param tree Pointer to the root node of the Red-Black BST.
 * @return 1 if the Red-Black BST is a valid Red-Black BST, 0 otherwise.
 */
int isRedBlackBST(RedBlackBST tree)
{   if (blackHeightRedBlackBST(tree) == -1) return 0;

    return 1;
}


/**
 * @brief Build a red-black binary search tree from a given permutation.
 * @param permutation Array of integers representing the permutation
 * @param n size of the array
 * @return A red-black binary search tree built by successively inserting the elements of permutation.
 */
RedBlackBST buildRedBlackBSTFromPermutation(int *permutation,size_t n){
    //printf("ON BUILD PERMUTATION\n");
    if (!permutation)
        return NULL;
    if (n == 0) return NULL;

    RedBlackBST tree = createEmptyRedBlackBST();
    
    for(size_t i = 0; i<n; i++){
        insertNodeRedBlackBST(&tree, permutation[i]);
    }
    //printf("ON FINIT PERMUTATION\n");
    return tree;
}


/**
 * @brief Print the elements of a binary search tree in a pretty format.
 * @param tree Pointer to the root of the tree.
 * @param space Space to be printed before the current element.
 */
void prettyPrintRedBlackBST(RedBlackBST tree, int space) {
    if (tree == NULL) {
        return;
    }
    space += 10;

    prettyPrintRedBlackBST(tree->rightBST, space);

    printf("\n");
    for (int i = 10; i < space; i++) {
        printf(" ");
    }
    printf("[%d,%d]\n", tree->value, tree->color);

    prettyPrintRedBlackBST(tree->leftBST, space);
    return ;
}
