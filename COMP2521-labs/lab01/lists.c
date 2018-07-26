#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "lists.h"

static dlink newDnode (int item);


void printList (link list) {
    link curr = list;
    while (curr != NULL) {
        printf ("[%d]->", curr->item);
        curr = curr->next;
    }
    printf ("[X]\n");
}

// Create a new node, initialised with the item provided. Return
// pointer to node (link)
link newNode(Item item){
    link new = malloc(sizeof(struct node));
    new->item = item;
    new->next = NULL;
    return new;
}

// Insert a new node into a given non-empty list
// The node is inserted directly after the head of the list ls
void insertNext(link ls, link node){
    if(ls==NULL){
        ls = node;
        return;
    }
    link tmp = ls->next;
    ls->next = node;
    node->next = tmp;
}

// return the sum of all items in list
int sumListItems (link ls) {
    link curr = ls;
    int sum = 0;
    while (curr != NULL) {
        sum = sum + curr -> item;
        curr = curr->next;
    }
    return sum;
}

//frees all memory used in the list
void freeList(link list){
    if (!list) return;
    link curr = list;
    if (curr->next == NULL){
        free(curr);
    } else {
        link tmp = curr->next;
        free(curr);
        curr = tmp;
        
        while (curr!=NULL && curr!=list) {
            tmp = curr->next;
            free(curr);
            curr = tmp;
        }
    }
}

// create a circular list with the number of nodes specified with
// each link storing data from 1 to the number of nodes specified
link createCircularList (int numNodes){
    if (numNodes == 0) return NULL;
    link list = newNode(1);
    link end = list;
    int i = 2;
    while (i <= numNodes) {
        end->next = newNode(i);
        end = end->next;
        i++;
    }
    end->next = list;
    return list;
}

// print the data in a circular fashion starting from any node
void printCircularList(link list){
    if(list == NULL) return;
    link curr = list;
    printf("%d ",curr->item);
    curr = curr->next;
    while(curr != list){
        printf("%d ",curr->item);
        curr = curr->next;
    }
    printf("\n");
}

// create a double-linked list which has contains the same elements,
// in the same order as 'list'
dlink doublify (link list) {
    if (!list) return NULL;
    
    int num = 0;
    
    link curr = list;
    //initialise the first element in the newlist
    num = curr->item;
    dlink newList = newDnode(num);
    curr = curr->next;
    
    // 2 pointers to help with appending
    dlink newCurr = newList;
    dlink tmp = NULL;
    
    while (curr!=NULL && curr != list) {
        num = curr->item;
        // get pointer to the current element in new list
        // since i need it for new->prev
        tmp = newCurr;
        newCurr->next = newDnode(num);
        newCurr->prev = tmp;
        newCurr = newCurr->next;
        
        curr = curr->next;
    }
    
    return newList;
}

// frees all the memory used in the double-linked list
void freeDList(dlink list){
    dlink curr = list;
    dlink head = list;
    dlink tmp;
    
    tmp = curr->next;
    free(curr);
    curr = tmp;
    
    while (curr!=NULL && curr!=head) {
        tmp = curr->next;
        free(curr);
        curr = tmp;
    }
}



// Helper function
static dlink newDnode (int item) {
    dlink new = malloc(sizeof(struct dnode));
    new->item = item;
    new->next= NULL;
    new->prev = NULL;
    return new;
}

/*
void printDList(dlink list) {
    dlink curr = list;
    while(curr!=NULL){
        printf("%d",curr->item);
        curr = curr->next;
    }
}
*/
