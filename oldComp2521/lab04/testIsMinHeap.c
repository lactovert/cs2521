#include <assert.h>
#include <stdio.h>

#include "isMinHeap.h"

void testValidMinHeaps(void);
void testInvalidMinHeaps(void);

int main(int argc, char * argv[]){
    //Stops output being buffered, so we get all printf output
    //before program crashes/aborts etc
    setbuf(stdout, NULL);
    testValidMinHeaps();
    testInvalidMinHeaps();
    return 0;
}


void testValidMinHeaps(void){
    int heap1[] = {0,2,10};

    printf("Test 1: Some valid heaps from 2,10\n");
    assert(isMinHeap(heap1,2));
    printf("passed\n");

    //ADD MORE TESTS HERE
}

void testInvalidMinHeaps(void){
     int heap1[] = {0,10,7,6};

     printf("Test Invalid heap 1: 10,7,6\n");
     assert(!isMinHeap(heap1,3));
     printf("passed\n");

     //ADD MORE TESTS HERE
}
