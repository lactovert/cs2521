#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Item.h"
#include "Queue.h"

void queueWhiteBoxTests(void);
int main (int argc, char *argv[]){
    //Run white box tests
    queueWhiteBoxTests();
    //Run black box tests
    printf("Black Box tests:\n");
    printf("Test 1 : Empty queue\n");
    Queue new1 = createQueue();
    assert(queueSize(new1)==0);
    destroyQueue(new1);
    
    printf("Test 2 : 1 element queue\n");
    Queue new2 = createQueue();
    assert(queueSize(new2)==0);
    Item a = 17;
    putQueue(new2, a);
    assert(queueSize(new2)==1);
    assert(getQueue(new2)==17);
    destroyQueue(new2);
    
    printf("Test 3 : multiple element queue\n");
    Queue new3 = createQueue();
    //Item n = 17;
    int i =0;
    while (i < 10) {
        putQueue(new3, i);
        i++;
    }
    assert(queueSize(new3)==10);
    assert(getQueue(new3)==0);
    destroyQueue(new3);

    printf("All blackbox test passed!\n");
    return 0;
}       
