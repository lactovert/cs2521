// Implement the deleteLargest function below
//
// Compile and test the function using
// gcc -Wall -Werror -O -o deleteLargest deleteLargest.c deleteLargestTest.o
// ./deleteLargest


#include <stdio.h>
#include <stdlib.h>
#include "deleteLargest.h"
/*
typedef struct _treeNode {
  Item item;
  treeLink left, right;
} treeNode;
*/

//Delete the largest item in the tree and return the resulting tree
//You must free the memory of the node that is deleted
//If the tree is empty simply return the empty tree
//For example
/*
//       5                 5
/      / \               /  \
//     2   7        ---> 2   7
//        / \                /
//       6   8              6
//
*/
//You may assume there are no duplicates in the tree
treeLink deleteLargest (treeLink tree) {
     /* treeLink curr = tree;
      treeLink prev = NULL;
      if (tree == NULL) return NULL;
      
      while(curr->right != NULL){
            prev = curr;
            curr = curr->right;
      }
      // for curr->right == NULL;
      if(prev == NULL) {
        if(curr->left==NULL){
            free(curr);
            return NULL;
        } else if (curr->left!=NULL) {
            treeLink temp = curr->left;
            free(curr);
            curr = NULL;
            return temp;
        }
      }
      
      if(curr->left!=NULL){

            prev->right = curr->left;
            free(curr);
            return tree;
      }
      free(curr);
      return tree;
      */
//===================================================
      treeLink curr = tree;
      treeLink prev = NULL;
      if(tree == NULL) return NULL;
      while(curr->right != NULL){
        prev = curr;
        curr = curr->right;
      }
      if(prev == NULL){
        tree = curr->left;
      }else{
        prev->right = curr->left;
      }
      free(curr);
     return tree;
}

