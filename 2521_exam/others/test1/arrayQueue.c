#include <stdlib.h>
#include <stdio.h>
#include "Item.h"
#include "Queue.h"
#include <assert.h>

#define DEFAULT_SIZE 10

struct queueImp{
    Item *items;
    int size;
    int maxSize;
    int start;
    int end;
};

//O(1)
Queue createQueue(){
    Queue q = malloc(sizeof(struct queueImp));
    q->items = malloc(DEFAULT_SIZE * sizeof(Item));
    q->size = 0;
    q->maxSize = DEFAULT_SIZE;
    q->start = -1;
    q->end = -1;
    return q;
}

void destroyQueue(Queue q){
    assert(q != NULL);
    free(q->items);
    free(q);
}

//O(1)
int queueSize(Queue q){
    assert(q != NULL);
    return (q->size);
}

//O(1);
void putQueue(Queue q, Item i){
    assert(q != NULL);
    assert(q->size < q->maxSize);
    if (q->size == 0){
        q->start++;
    }
    q->items[q->size++] = i;
    q->end++;
}

//O(n)
Item getQueue(Queue q){
    Item result;
    if (q==NULL) abort();
    if (queueSize(q) > 0) {
        result = q->items[q->start];
        q->start++;
        q->size--;
    } else {
        fprintf(stderr,"queue underflow\n");
        abort();
    }
    return result;
}
/*
void queueWhiteBoxTests(void){
    printf("White box tests for array queue :\n");
    printf("Test 1: createQueue\n");
    Queue new1 = createQueue();
    assert(new1!=NULL);
    assert(new1->maxSize==DEFAULT_SIZE);
    assert(new1->size==0);
    assert(new1->start==-1);
    assert(new1->end==-1);
    destroyQueue(new1);
    
    printf("Test 2: putQueue\n");
    Queue new2 = createQueue();
    assert(new2!=NULL);
    assert(new2->size==0);
    for(int i = 0; i<10; i++) {
        putQueue(new2, i);
    }
    assert(new2->size==10);
    assert(new2->start==0);
    assert(new2->end==9);
    destroyQueue(new2);
    
    printf("All white box tests passed!\n\n");
}*/
