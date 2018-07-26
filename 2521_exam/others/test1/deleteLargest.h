// 
// Implement the following function (you can implement as many helper
// functions as you need, but declare them to be static
// 
typedef int bool;
typedef int Item;

#define TRUE (1 == 1)
#define FALSE (1 == 0)

typedef struct _treeNode *treeLink;
typedef struct _treeNode {
  Item item;
  treeLink left, right;
} treeNode;

treeLink deleteLargest (treeLink tree);
