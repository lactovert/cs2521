#include <stdlib.h>
#include <stdio.h>
#include "BST.h"
#include <assert.h>

//To compile please type
//gcc -Wall -Werror -O -o testBST BST.c testBST.c
//To run please type
//./testBST

void printStuff(Treelink tree);

   
void testSumEven();
void testNumInternalNodes();
void testGetSmallest();
void testHasPathSum();
void testDoubleAndTrimTree();


int main(int argc, char * argv[]){
    testSumEven();
    testNumInternalNodes();
    testGetSmallest();
    testHasPathSum();

    testDoubleAndTrimTree();
    return 0;
}


void testSumEven(){
    printf("Testing Sum Even\n");
    Treelink t1 = createTree();
    assert(sumEven(t1) == 0);
  
    t1 = insertRec(t1,1);
    t1 = insertRec(t1,5);
    assert(sumEven(t1) == 0);
   
    t1 = insertRec(t1,10);
    assert(sumEven(t1) == 10);
    
    t1 = insertRec(t1,11);
    t1 = insertRec(t1,15);
    t1 = insertRec(t1,20);
    assert(sumEven(t1) == 30);
    

    Treelink t2 = createTree();
    t2 = insertRec(t2,10);
    assert(sumEven(t2) == 10);
   
    t2 = insertRec(t2,15);
    t2 = insertRec(t2,11);
    t2 = insertRec(t2,20);
    t2 = insertRec(t2,1);
    t2 = insertRec(t2,6);  
    assert(sumEven(t2) == 36);
   
    t2 = insertRec(t2,2);
    assert(sumEven(t2) == 38);
    printf("passed\n");
}

void testNumInternalNodes(){
    printf("Testing Num Internal Nodes\n");
    Treelink t1 = createTree();
    assert(numInternalNodes(t1) == 0);
  
    t1 = insertRec(t1,1);
    assert(numInternalNodes(t1) == 0); 
    t1 = insertRec(t1,5);   
    assert(numInternalNodes(t1) == 1);
  
    t1 = insertRec(t1,10);    
    t1 = insertRec(t1,11);
    t1 = insertRec(t1,15);
    t1 = insertRec(t1,20);
   
    assert(numInternalNodes(t1) == 5);
  
   /* 
       10
      /   \
     1    15
      \   / \
       5 11  20
      /
     2
    */
    
    Treelink t2 = createTree();
    t2 = insertRec(t2,10);
    t2 = insertRec(t2,15);
    t2 = insertRec(t2,11);
    t2 = insertRec(t2,20);
    t2 = insertRec(t2,1);
    t2 = insertRec(t2,5);  
    t2 = insertRec(t2,2);
    assert(numInternalNodes(t2) == 4);
    printf("passed\n");  
}


void testGetSmallest(){
    printf("Testing Get Smallest\n");
    Treelink t1 = createTree();
    assert(getSmallest(t1) == NULL);
  
    t1 = insertRec(t1,1);
    assert(getItem(getSmallest(t1)) == 1); 
    t1 = insertRec(t1,5);  
  
    t1 = insertRec(t1,10);    
    t1 = insertRec(t1,11);
    t1 = insertRec(t1,15);
    t1 = insertRec(t1,20);
   
    assert(getItem(getSmallest(t1)) == 1);
  
   /* 
       10
      /   \
     2    15
    /  \   / \
   1   5 11  20
     
    
    */
    
    Treelink t2 = createTree();
    t2 = insertRec(t2,10);
    t2 = insertRec(t2,15);
    t2 = insertRec(t2,11);
    t2 = insertRec(t2,20);
    t2 = insertRec(t2,2);
    t2 = insertRec(t2,1);  
    t2 = insertRec(t2,5);
    assert(getItem(getSmallest(t2)) == 1);
    printf("passed\n");  
}

void testHasPathSum(){
    printf("Testing Get Smallest\n");
    Treelink t1 = createTree();
    assert(hasPathSum(t1,0) == 1);
    assert(hasPathSum(t1,1) == 0);
     
    t1 = insertRec(t1,1);
    assert(hasPathSum(t1,1) == 1);
    assert(hasPathSum(t1,10) == 0); 

    t1 = insertRec(t1,5); 
    assert(hasPathSum(t1,1) == 1);
    assert(hasPathSum(t1,6) == 1);
  
    t1 = insertRec(t1,10);    
    t1 = insertRec(t1,11);
    t1 = insertRec(t1,15);
    t1 = insertRec(t1,20);
    assert(hasPathSum(t1,62) == 1);
    
    Treelink t2 = createTree();
    t2 = insertRec(t2,10);
    t2 = insertRec(t2,15);
    t2 = insertRec(t2,11);
    t2 = insertRec(t2,20);
    t2 = insertRec(t2,2);
    t2 = insertRec(t2,1);  
    t2 = insertRec(t2,5);
    assert(hasPathSum(t2,13) == 1);
    assert(hasPathSum(t2,17) == 1);
    assert(hasPathSum(t2,36) == 1);
    assert(hasPathSum(t2,45) == 1);
    assert(hasPathSum(t2,37) == 0);
    printf("passed\n"); 
}

//Not proper unit tests... 
void testDoubleAndTrimTree(){
    printf("Testing Trim Tree 4 15\n");
    Treelink t1 = createTree();
    
  
    t1 = insertRec(t1,1);
  
    t1 = insertRec(t1,5);  
  
    t1 = insertRec(t1,10);    
    t1 = insertRec(t1,11);
    t1 = insertRec(t1,15);
    t1 = insertRec(t1,20);
   
    t1 = trimTree(t1,4,15);

    printStuff(t1);
   /* 
       10
      /   \
     2    15
    /  \   / \
   1   5 11  20
     
    
    */
    printf("Testing Trim Tree 4 12\n");
    Treelink t2 = createTree();
    t2 = insertRec(t2,10);
    t2 = insertRec(t2,15);
    t2 = insertRec(t2,11);
    t2 = insertRec(t2,20);
    t2 = insertRec(t2,2);
    t2 = insertRec(t2,1);  
    t2 = insertRec(t2,5);
    t2 = trimTree(t2,4,12);
    printStuff(t2);

    printf("Double Tree\n");
    doubleTree(t2);
    printStuff(t2);
    printf("passed\n");  
}


void printStuff(Treelink tree){
    
    printf("\nPlease turn head on side to the left to see the tree\n");
    showBSTree(tree);
    printf("\n");
    if(size(tree) > 0)
        printf("Root of tree is %d\n",getItem(tree));
    

    printf("\nheight is %d\n",height(tree));
    
    printf("size is %d\n",size(tree));

   
    printf("Pre order traversal: ");
    preorderTraversal(tree);
    printf("\nIn order traversal: ");
    inorderTraversal(tree);
   
    printf("\nPost order traversal: ");
    postorderTraversal(tree); 
    //printf("\nLevel order traversal: ");
    //levelOrderTraversal(tree);
    printf("\npreorder iterative traversal: ");
   // preorderIterativeTraversal(tree);
    //printf("\n");
    
}
