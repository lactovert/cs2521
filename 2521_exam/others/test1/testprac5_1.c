#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "prac5.h"

void printList(Node n) {
    if (n == NULL) {
        printf("[X]\n");
        return;
    }
    printf("[%d]->", n->data);
    printList(n->next);
}

void freeList(Node n) {
    if (n == NULL) {
        return;
    }
    freeList(n->next);
    free(n);
}

List createListFromArray(int *array, int n) {
    int i;
    List l = createList();
    Node curr = NULL;
    for (i = 0; i < n; i++) {
        Node n = createNode(array[i]);
        if (l->first == NULL) {
            l->first = n;
        } else {
            curr->next = n;
        }
        curr = n;
    }
    return l;
}

int main(void) {
    List l = createList();
    partition(l, 50);
    return 0;
}
