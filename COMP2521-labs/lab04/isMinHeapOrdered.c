
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "isMinHeapOrdered.h"

int isMinHeap(Link n, int parents);

//To compile, run and test
//gcc -Wall -Werror -O -std=c99 -o testIsMinHeapOrdered testIsMinHeapOrdered.c isMinHeapOrdered.c
//./testIsMinHeapOrdered

//returns 1 if the tree-based heap is in min-heap order.
//You may assume an empty tree is in min-heap order and so 
//is a single node.
int isMinHeapOrdered(Link n){
    if (n==NULL) return 1;
    int check1 = 1, check2 = 1; 
    if(n->left!= NULL) check1 = (n->left->item > n->item);
    if(n->right!= NULL) check2 = (n->right->item > n->item);
    if (!check1 || !check2) return 0;
    
    return isMinHeapOrdered(n->left) && isMinHeapOrdered(n->right);
}  

