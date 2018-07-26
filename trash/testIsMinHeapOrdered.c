#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "isMinHeapOrdered.h"

void testIsMinHeapOrderedTrue(void);
void testIsMinHeapOrderedFalse(void);

int main (int argc, const char * argv[]) {
    //Stops output being buffered, so we get all printf output
    //before program crashes/aborts etc
   setbuf(stdout, NULL);
   testIsMinHeapOrderedTrue();
   testIsMinHeapOrderedFalse();

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

