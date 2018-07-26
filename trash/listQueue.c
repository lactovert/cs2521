//A linked list implementation of a queue

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Item.h"
#include "Queue.h"

typedef struct queueNode * link;

struct queueNode { 
    Item item; 
    link next; 
};

struct queueImp { 
    link head; 
    link tail;
    int size; 
};

static link createNode(Item item){ 
    link n = malloc (sizeof(*n));
    assert(n != NULL);
    n->item = item; 
    n->next = NULL;     
    return n;                         
}

// Creates an empty Queue
Queue createQueue (void){ 
    Queue q = malloc (sizeof (*q));
    assert(q != NULL); 
    q->head = NULL; 
    q->tail = NULL;
    q->size = 0; 
    return q;
}

void destroyQueue(Queue queue){
    link curr;
    link next;
    assert(queue != NULL);
    curr = queue->head;
    while(curr!=NULL){
        next = curr->next;
        free(curr);
        curr = next;
    }
    free(queue);

}

int queueSize (Queue q){ 
    assert(q != NULL);
    return q->size; 
}


void putQueue (Queue q, Item item){ 
    assert(q != NULL); 
    link n = createNode(item);
    if(q->head != NULL){
       q->head->next = n;
    } else {
       q->tail = n; 
    }
    q->head = n;

}

Item getQueue (Queue q){ 
    assert(q != NULL);
    Item item = q->head->item;
    link delNode = q->head;
    q->head = q->head->next;      
    free(delNode);
    return item;



}

void queueWhiteBoxTests(void){
    printf("White box tests: not done\n");
}
