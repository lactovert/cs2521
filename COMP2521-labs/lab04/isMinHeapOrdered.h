typedef struct node * Link;

struct node {
   int   item;
   Link  left;
   Link  right;
} ;


// This function should return 1 if the tree
// is in min heap order and false otherwise
int isMinHeapOrdered ( Link tree);

