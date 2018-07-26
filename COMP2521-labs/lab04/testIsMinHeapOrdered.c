#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "isMinHeapOrdered.h"

void testIsMinHeapOrderedTrue(void);
void testIsMinHeapOrderedFalse(void);
void blackBoxTests(void);

int main (int argc, const char * argv[]) {
    //Stops output being buffered, so we get all printf output
    //before program crashes/aborts etc
   setbuf(stdout, NULL);
   testIsMinHeapOrderedTrue();
   testIsMinHeapOrderedFalse();
   blackBoxTests();
   printf ("All tests passed!\n");
  
   return EXIT_SUCCESS;
}


void testIsMinHeapOrderedTrue (void) {
   
   
   Link newTree = NULL;
   printf("Tests for trees that are heap ordered\n");
   printf("Test 1 : Empty tree\n");
   assert(isMinHeapOrdered(newTree));
   printf("Passed\n");

   newTree = malloc(sizeof(struct node));
   newTree->item = 9;
   newTree->left = NULL;
   newTree->right = NULL;
 
   printf("Test 2 : Tree size 1\n");
   assert(isMinHeapOrdered(newTree)); 
   printf("Passed\n");

   Link newNode;
   newNode = malloc(sizeof(struct node));
   newNode->item = 15;
   newNode->left = NULL;
   newNode->right = NULL;
   newTree->left = newNode;
     
   printf("Test 3 : Tree size 2\n");
   assert(isMinHeapOrdered(newTree) );
   printf("Passed\n");

   //ADD MORE TESTS

   free(newNode);
   free(newTree);

}

void testIsMinHeapOrderedFalse (void) {

 
   Link newTree = NULL;
   printf("Tests for trees that are not heap ordered\n");
  

   newTree = malloc(sizeof(struct node));
   newTree->item = 9;
   newTree->left = NULL;
   newTree->right = NULL;
 
   

   Link newNode;
   newNode = malloc(sizeof(struct node));
   newNode->item = 8;
   newNode->left = NULL;
   newNode->right = NULL;
   
   newTree->left = newNode;     


   printf("Test 1 : Tree size 2\n");
   assert(!isMinHeapOrdered(newTree) );
   printf("Passed\n");

   //ADD MORE TESTS

   free(newNode);
   free(newTree);
   
  
}

void blackBoxTests (void) {
    printf("Black Box Tests\n");
    printf("Normal Tree(NOT Min Heap)\n");
    Link newTree = NULL;
    newTree = malloc(sizeof(struct node));
    newTree->item = 50;
    newTree->left = NULL;
    newTree->right = NULL;
    
    Link newNode;
    newNode = malloc(sizeof(struct node));
    newNode->item = 75;
    newNode->left = NULL;
    newNode->right = NULL;
    
    Link newNode1;
    newNode1 = malloc(sizeof(struct node));
    newNode1->item = 35;
    newNode1->left = NULL;
    newNode1->right = NULL;
    
    Link newNode2;
    newNode2 = malloc(sizeof(struct node));
    newNode2->item = 45;
    newNode2->left = NULL;
    newNode2->right = NULL;
    
    Link newNode3;
    newNode3 = malloc(sizeof(struct node));
    newNode3->item = 85;
    newNode3->left = NULL;
    newNode3->right = NULL;

    Link newNode4;
    newNode4 = malloc(sizeof(struct node));
    newNode4->item = 25;
    newNode4->left = NULL;
    newNode4->right = NULL;
    
    Link newNode5;
    newNode5 = malloc(sizeof(struct node));
    newNode5->item = 60;
    newNode5->left = NULL;
    newNode5->right = NULL;
    
    newTree->left = newNode1;
    newTree->right = newNode;
    
    newNode1->left = newNode4;
    newNode1->right = newNode2;
    
    newNode->left = newNode5;
    newNode->right = newNode3;
    assert(!isMinHeapOrdered(newTree));
    
    printf("Unbalanced Tree(is a Min Heap\n");
    Link newTree1;
    newTree1 = malloc(sizeof(struct node));
    newTree1->item = 50;
    newTree1->left = NULL;
    newTree1->right = NULL;
    
    Link newNode10;
    newNode10 = malloc(sizeof(struct node));
    newNode10->item = 100;
    newNode10->left = NULL;
    newNode10->right = NULL;
    
    Link newNode11;
    newNode11 = malloc(sizeof(struct node));
    newNode11->item = 120;
    newNode11->left = NULL;
    newNode11->right = NULL;
    
    Link newNode12;
    newNode12 = malloc(sizeof(struct node));
    newNode12->item = 140;
    newNode12->left = NULL;
    newNode12->right = NULL;  
    
    Link newNode13;
    newNode13 = malloc(sizeof(struct node));
    newNode13->item = 150;
    newNode13->left = NULL;
    newNode13->right = NULL; 
    
    Link newNode14;
    newNode14 = malloc(sizeof(struct node));
    newNode14->item = 170;
    newNode14->left = NULL;
    newNode14->right = NULL;
    
    newTree1->left = newNode11;
    newTree1->right = newNode10;
    
    newNode11->left = newNode12;
    newNode11->right = newNode13;
    
    newNode13->right = newNode14;
    
    assert(isMinHeapOrdered(newTree1));
    
    printf("Tree with duplicate element\n");
    
    Link newTree2;
    newTree2 = malloc(sizeof(struct node));
    newTree2->item = 10;
    newTree2->left = NULL;
    newTree2->right = NULL;
    
    Link newNode15;
    newNode15 = malloc(sizeof(struct node));
    newNode15->item = 10;
    newNode15->left = NULL;
    newNode15->right = NULL;
    
    Link newNode16;
    newNode16 = malloc(sizeof(struct node));
    newNode16->item = 14;
    newNode16->left = NULL;
    newNode16->right = NULL;
    
    newTree2->left = newNode15;
    newTree2->right = newNode16;
    
    assert(!isMinHeapOrdered(newTree2));
    
    free(newTree);
    free(newNode);
    free(newNode1);
    free(newNode2);
    free(newNode3);
    free(newNode4);
    free(newNode5);
    
    free(newTree1);
    free(newNode10);
    free(newNode11);
    free(newNode12);
    free(newNode13);
    free(newNode14);
    
    free(newTree2);
    free(newNode15);
    free(newNode16);
    
    printf("Black Box Test Passed\n");
}
