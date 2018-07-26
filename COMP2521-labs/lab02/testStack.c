#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Item.h"
#include "Stack.h"

//This function should contain
//tests that have access to the internal structure 
//of the stack. It should be implemented in arrayStack.c
void whiteBoxTests(void);


int main (int argc, char *argv[]){
    
    //Item a = 17;
    //Item array[25]={0};
    //Run white box tests
    whiteBoxTests();

    //Run black box tests
    //Black box tests should test the ADT through the interface only
    
    printf("Black Box tests:\n");
    printf("This is just a small example for you to get started\n");

    printf("Test 1: empty stack\n");
    Stack s1;
    s1 = createStack();
    assert(s1 != NULL);
    assert(stackSize(s1) == 0);
    printf("Passed Test 1\n");
    destroyStack(s1);
    
    printf("Test 2: single element\n");
    Stack s2;
    s2 = createStack();
    assert(s2 != NULL);
    push(s2, 17);
    assert(stackSize(s2) == 1);
    pop(s2);
    assert(stackSize(s2) == 0);
    printf("Passed Test 2\n");
    destroyStack(s2);
    
    printf("Test 3: overflowing element\n");
    Stack s3;
    s3 = createStack();
    assert(s3 != NULL);
    printf("Fills 10 elements to the array\n");
    int i = 0;
    for(i = 0; i<10;i++) push(s3, i);
    assert(stackSize(s3) == 10);
    printf("Overflowing started\n");
    push(s3,i);
    assert(stackSize(s3) == 11);
    printf("Stack successfully expanded\n");
    printf("Passed Test 3\n");
    destroyStack(s3);
    
    printf("Test 4: underflowing element\n");
    Stack s4;
    s4 = createStack();
    assert(s4 != NULL);
    printf("Fills 40 elements to the array\n");
    int l = 0;
    for(l = 0; l<40;l++) push(s4, 1);
    assert(stackSize(s4) == 40);
    printf("Pops 31 elements from the array\n");
    for(int j = 0; j<31; j++) pop(s4);
    assert(stackSize(s4) == 9);
    printf("Stack successfully shrunk\n");
    printf("Passed Test 4\n");
    destroyStack(s4);
    
    return 0;
}       
