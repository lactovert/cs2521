#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "lists.h"

// insert proper tests here
int main (int argc, const char * argv[]) {
    
    //creates an  empty list  and then prints it
    link emptyList = NULL;
    printList(emptyList);
    
    //creates a 4 element list
    link list = newNode(1);
    list->next = newNode(2);
    list->next->next = newNode(3);
    list->next->next->next = newNode(4);
    printList(list);
    
    //creates a 1 element list
    link edge = newNode(99);
    printList(edge);
    
    int i = 0;
    i = sumListItems(list);
    printf("The sum is %d\n",i);
    
    i = sumListItems(edge);
    printf("The sum is %d\n",i);
    
    i = sumListItems(emptyList);
    printf("The sum is %d\n",i);
    
    // testing phase
    // insert 17 to list
    insertNext (list, newNode(17));
    printList(list);
    
    // insert 17 to edge
    insertNext (edge, newNode(17));
    printList(edge);
    
    //freeing every list made
    freeList(emptyList);
    freeList(edge);
    
    
    
    link circle = createCircularList(5);
    printCircularList(circle);
    
    
    link circle1 = createCircularList(1);
    printCircularList(circle1);
    freeList(circle1);
    
    link circle0 = createCircularList(0);
    printCircularList(circle0);
    freeList(circle0);
    
    dlink duplicate = doublify(list);
    dlink circleduplicate = doublify(circle);
    //printDList(circleduplicate);
    freeList(list);
    freeDList(duplicate);
    freeDList(circleduplicate);
    freeList(circle);
    return EXIT_SUCCESS;
}
