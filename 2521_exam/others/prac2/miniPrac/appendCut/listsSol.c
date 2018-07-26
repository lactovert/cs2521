#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "lists.h"


void printList (link list) {
  link curr = list;
  while (curr != NULL) {
    printf ("[%d]->", curr->item);
    curr = curr->next;
  }
  printf ("[X]\n");
}

void printDList (dlink list) {
  if(list == NULL){
      printf ("[X]\n");
      return;
  }
  dlink curr = list;
  dlink last;
  while (curr != NULL) {
    if(curr->next == NULL){
      last = curr;
    }
    printf ("[%d]->", curr->item);
    curr = curr->next;
  }
  printf ("[X]\n");
  printf("Now in reverse\n");
    curr = last;
  // and now in reverse
  while (curr != NULL) {
    if(curr->prev == NULL){
      last = curr;
    }
    printf ("[%d]->", curr->item);
    curr = curr->prev;
  }
  printf ("[X]\n");
}

//new node creator
static link newNode(int value){
  link new = malloc(sizeof(node));
  new->item = value; //assign the value 
  new->next = NULL; // point next to null
  return new;
}
//new node creator
static dlink newDNode(int value){
  dlink new = malloc(sizeof(dnode));
  new->item = value; //assign the value 
  new->next = NULL; // point next to null
  new->prev = NULL;
  return new;
}

static void freeNode(link curr){
  
  if(curr!= NULL){
    free(curr);
  }

}

static void freeDNode(dlink curr){
  
  if(curr!= NULL){
    free(curr);
  }

}

link genList(int numItems){
  srand(time(NULL));

  // create head
  link head = newNode(rand());
  link curr = head;
  numItems--;

  for(int i = numItems; i > 0; i--){
    link new = newNode(rand());
    curr-> next = new; // link the new node to the end of the list
    curr = new; // mov current pointer to point to the end of the list
  }

  return head;
}

dlink genDList(int numItems){
  srand(time(NULL));

  // create head
  dlink head = newDNode(numItems);
  dlink curr = head;
  numItems--;

  for(int i = numItems; i > 0; i--){
    dlink new = newDNode(i);
    curr-> next = new; // link the new node to the end of the list
    new-> prev = curr;
    curr = new; // mov current pointer to point to the end of the list 
  }
  
  return head;
}



dlink appendCut(int index, dlink head){
  if(head == NULL){
    return NULL;
  }
  dlink curr = head ;
  dlink newHead;
  int i = 0;
  while(curr!= NULL && i != index){
    if(i == index){
      break;
    }
    i++;
    curr = curr->next; 
  }
  // so either we got to the required item or it doesn't exist
  if(curr == NULL){
    return NULL; // the index is invalid
  }else if (curr->next == NULL){

    return head;

  }else{
    
    newHead = curr->next; // saving new head node
    newHead->prev = NULL; // splitting list into two
    curr->next = NULL;

    dlink temp = newHead; // traverse till the end of the second half
    while(temp->next != NULL){
      temp = temp->next;
    }

    temp->next = head;
    head->prev = temp;

  }
  return newHead;
}