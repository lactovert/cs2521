// Doubly and singly linked lists 

typedef int Item;

typedef struct node *link;

struct node {
    Item item;
    link next;
};


typedef struct dnode *dlink;

struct dnode {
    Item item;
    dlink prev;
    dlink next;
};

void printDList(dlink list);

// traverses the list and prints the list
void printList (link list);

// Create a new node, initialised with the item provided. Return
// pointer to node (link)
link newNode(Item item);

// Insert a new node into a given non-empty list
// The node is inserted directly after the head of the list ls
void insertNext (link ls, link node);

// return the sum of all items in list
int sumListItems (link lists);

//frees all memory used in the list
void freeList(link list);

// create a circular list with the number of nodes specified with 
// each link storing data from 1 to the number of nodes specified
link createCircularList(int numNodes);

// print the data in a circular fashion starting from any node
void printCircularList(link);

// create a double-linked list which has contains the same elements,
// in the same order as 'list'
dlink doublify (link list);

// frees all the memory used in the double-linked list
void freeDList(dlink list);
