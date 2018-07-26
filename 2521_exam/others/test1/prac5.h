#define TRUE 1
#define FALSE 0

typedef struct _node *Node;
typedef struct _list *List;

typedef struct _list {
    Node first;
} list;

typedef struct _node {
    int data;
    Node next;
} node;

List createList(void);
Node createNode(int i);

List partition(List l, int val); 
void printList(Node n);
