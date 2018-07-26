typedef int TreeItem;
typedef struct treeNode * treelink;

//Functions that are provided
treelink insertTreeNode (treelink tree, TreeItem item);
void printInorder (treelink tree);
void printTreeNode (treelink t);
int size(treelink t);
treelink search(treelink t, TreeItem i);
TreeItem getItem(treelink t);

//Functions you need to write
int countLeaves(treelink tree);
treelink searchInsert(treelink t, TreeItem i); 
int countIf (treelink tree, int (*pred)(TreeItem));
int isEven (TreeItem n);
int isOdd (TreeItem n);
int isNegative (TreeItem n);
void printPath(treelink tree);

