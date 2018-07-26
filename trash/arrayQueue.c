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
};

//O(1)
Queue createQueue(){
    Queue q = malloc(sizeof(struct queueImp));
    q->items = malloc(DEFAULT_SIZE * sizeof(Item));
    q->size =0;
    q->maxSize = DEFAULT_SIZE;
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
    q->items[q->size++]  = i;
}

//O(n)
Item getQueue(Queue q){
    int i;
    assert(q != NULL);
    if(q->size > 0){
        Item item = q->items[0];
        q->size--;
        //shift the elements across
        for(i=0;i<q->size;i++){
            q->items[i] = q->items[i+1];
        }
        return item;
    } else {
        fprintf(stderr,"queue underflow\n");
        abort();
    }
}

void queueWhiteBoxTests(void){
    printf("White box tests not done\n");
}
