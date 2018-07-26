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
    link n = malloc (sizeof(struct queueNode));
    assert(n != NULL);
    n->item = item;
    n->next = NULL;
    return n;                         
}

// Creates an empty Queue
Queue createQueue (void){ 
    Queue q = malloc (sizeof(struct queueImp));
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
    link temp;
    /*
    if(q->head != NULL){
       q->head->next = n;
    } else {
       q->tail = n; 
    }
    q->head = n;
    */
    if (q->head == NULL) {
        q->head = n;
        q->tail = n;
        q->size++;
    } else if (q->head !=NULL) {
        q->size++;
        temp = q->tail;
        temp->next = n;
        q->tail = n;
    }
}

Item getQueue (Queue q){ 
    assert(q != NULL);
    Item item = q->head->item;
    link delNode = q->head;
    q->head = q->head->next;      
    free(delNode);
    q->size--;
    return item;
}

void queueWhiteBoxTests(void){
    printf("White box tests:\n");
    printf("Test 1: createQueue and putQueue\n");
    Queue new1 = createQueue();
    assert(new1->head == NULL); 
    assert(new1->tail == NULL);
    assert(new1->size == 0);
    
    putQueue(new1, 17);
    assert(new1->head->item == 17);
    assert(new1->tail->item == 17);
    assert(new1->size == 1);
    putQueue(new1, 18);
    assert(new1->head->item == 17);
    assert(new1->tail->item == 18);
    assert(new1->size == 2);
    
    
    printf("Test 2: getQueue\n");
    Queue new2 = createQueue();
    assert(new2->head == NULL); 
    assert(new2->tail == NULL);
    assert(new2->size == 0);
    
    putQueue(new2, 17);
    assert(new2->head->item == 17);
    assert(new2->tail->item == 17);
    assert(new2->size == 1);
    putQueue(new2, 18);
    assert(new2->head->item == 17);
    assert(new2->tail->item == 18);
    assert(new2->size == 2);
    
    assert(getQueue(new2) == 17);
    assert(new2->size == 1);
    assert(getQueue(new2) == 18);
    assert(new2->size == 0);
    
    destroyQueue(new1);
    destroyQueue(new2);
    printf("All whitebox tests passed!\n\n");
    
}
