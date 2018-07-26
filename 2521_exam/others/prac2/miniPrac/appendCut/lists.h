// Doubly and singly linked lists
//

typedef struct _node *link;

typedef struct _dnode *dlink;

typedef int Item;

typedef struct _node {
    Item item;
    link next;
} node;

typedef struct _dnode {
    Item item;
    dlink prev;
    dlink next;
} dnode;
// pretty prints a list
void printList (link list);

// return the sum of all items in list
int sumListItems (link lists);

// return a list with items start (start+1) ... end
// empty list if start > end
link fromTo (int start, int end);

//frees all memory used in the list
void freeList(link list);

// create a double-linked list which has contains the same elements,
// in the same order as 'list'
dlink doublify (link list);

// frees all the memory used in the double-linked list
void freeDList(dlink list);

//generate a list of numItems random items
link genList(int numItems);

void printDList (dlink list);
dlink genDList(int numItems);
dlink appendCut(int k, dlink d);
