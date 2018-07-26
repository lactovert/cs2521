#include <stdio.h>
#include <stdlib.h>
#include "deleteLargest.h"
#include <assert.h>
int main (int argc, char *argv[]) {
    treeLink one = malloc(sizeof(struct _treeNode));
    one->item = 100;
    one->left = NULL;
    one ->right = NULL;
    
    treeLink two = malloc(sizeof(struct _treeNode));
    two->item = 1;
    two->left = NULL;
    two ->right = NULL;
    
    one->left = two;
    deleteLargest(one);
    printf("%d\n", one->item);
    
    //assert(!one);
    assert(two!=NULL);
    free(two);
    return EXIT_SUCCESS;
}
