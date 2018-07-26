//An implementation of a binary search tree

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "BST.h"
#include "Queue.h"

static treelink createNode(TreeItem item);

struct treeNode {
    TreeItem item;
    treelink left;
    treelink right;
};

static treelink createNode(TreeItem item){
     treelink t = (treelink) malloc (sizeof (*t));
     t->item = item;
     t->left = NULL;
     t->right = NULL;
     return t;
}

TreeItem getItem(treelink t){
     assert(t != NULL);
     return t->item;
}

void printTreeNode (treelink t) {
     if(t != NULL)
     printf("%d ",t->item);
}

void preorderTraversal (treelink tree, void (*visit) (treelink)) {
    if (tree == NULL) {
       return;
    }
    (*visit)(tree);
    preorderTraversal (tree->left,visit);
    preorderTraversal (tree->right,visit);
}

//This function inserts duplcates on the left
treelink insertTreeNode (treelink tree, TreeItem item) {
  if (tree == NULL) {
      tree = createNode(item);
      tree->item = item;
      tree->left = NULL;
      tree->right = NULL;

  } else if (tree->item < item) {
      tree->right = insertTreeNode (tree->right, item);
  } else {
      tree->left = insertTreeNode (tree->left, item);
  }
  return tree;
}

int size(treelink t){
    if(t == NULL){
        return 0;
    } else {
        return 1 + size(t->left) + size(t->right);
    }
}

//returns the node of the element with item i
treelink search(treelink t, TreeItem i){
    treelink result = NULL;
    if (t == NULL) {
        result = NULL;
    } else if( i < t->item ){
        result = search(t->left,i);
    } else if( i > t->item ){
        result = search(t->right,i);
    } else {
        result = t;
    }
    return result;
}

int countLeaves (treelink tree) {
    if (tree == NULL) return 0;
    if(tree->left == NULL && tree->right == NULL) return 1;
    return countLeaves(tree->left) + countLeaves(tree->right);
}






TreeItem * levelOrderTraversal(treelink tree) {
    treelink curr = tree;
    int numNodes = size(tree);
    int i = 0;
    if (numNodes == 0) return NULL;
    TreeItem *array = calloc(numNodes, sizeof(struct treeNode));
    Queue q = newQueue();
    QueueJoin(q, curr);
    while (!QueueIsEmpty(q)) {
        curr = QueueLeave(q);
        array[i] = curr->item;
        i++;
        if (curr->left!=NULL) {
            QueueJoin(q, curr->left);
        }
        if (curr->right != NULL) {
            QueueJoin(q, curr->right);
        }
    }
    dropQueue(q);
    return array;
}


int countIf (treelink tree, int (*pred)(TreeItem)) {

    if(tree==NULL) return 0;
    TreeItem *array= levelOrderTraversal(tree);
    int i = 0;
    int result = 0;
    int numNodes = size(tree);
    while (i < numNodes) {
        if((*pred)(array[i])==1){
            result++;
        }
        i++;
    }

    free(array);
    return result;
}

int isEven (TreeItem n) {
    if (isNegative(n) == 1) {
        n = -n;
    }
    if (n%2 == 0) return 1;
    return 0;
}

int isOdd (TreeItem n) {
    if (isNegative(n) == 1) {
        n = -n;
    }
    if (n%2 == 1) return 1;
    return 0;
}

int isNegative (TreeItem n) {
    if (n < 0) return 1;
    return 0;
}



//helper function

void destroyTree(treelink tree){
    if (tree == NULL) return;
    if (tree!=NULL){
        destroyTree(tree->left);
        destroyTree(tree->right);
    }
    free(tree);
}


void whiteBoxTests (void) {
    printf("======White Box Tests======\n");
    printf("Test 1: Count Leaves, array with duplicates\n");
    TreeItem array1[7]={5,3,6,2,4,9,9};
    assert(array1!=NULL);
    treelink new1 = NULL;
    assert(new1==NULL);
    printf("create the tree\n");
    for(int i = 0; i < 7; i++) {
       new1 = insertTreeNode(new1, array1[i]);
    }
    assert(new1!=NULL);
    assert(size(new1)==7);
    assert(countLeaves(new1) == 3);
    assert(new1->item==5);
    assert(new1->left->item==3);
    assert(new1->right->item==6);
    assert(new1->left->left->item==2);
    assert(new1->left->right->item==4);
    assert(new1->right->right->item==9);
    assert(new1->right->right->left->item==9);
    printf("Duplicates placed left, success\n");

    printf("Test 2: Count leaves (1 element tree)\n");
    TreeItem array2[1]={0};
    assert(array2!=NULL);
    treelink new2 = NULL;
    assert(new2==NULL);
    new2 = insertTreeNode(new2, array2[0]);
    assert(new2!=NULL);
    assert(size(new2)==1);
    assert(countLeaves(new2) == 1);

    destroyTree(new1);
    destroyTree(new2);

    printf("Test 3: isEven, isOdd, isNegative\n");
    assert(isEven(0)==1);
    assert(isEven(2)==1);
    assert(isEven(1000)==1);
    assert(isEven(-2)==1);
    assert(isEven(-1000)==1);
    assert(isEven(1)==0);
    assert(isEven(3)==0);
    assert(isEven(1001)==0);
    assert(isEven(-1)==0);
    assert(isEven(-1001)==0);

    assert(isOdd(0)==0);
    assert(isOdd(2)==0);
    assert(isOdd(1000)==0);
    assert(isOdd(-2)==0);
    assert(isOdd(-1000)==0);
    assert(isOdd(1)==1);
    assert(isOdd(3)==1);
    assert(isOdd(1001)==1);
    assert(isOdd(-1)==1);
    assert(isOdd(-1001)==1);

    assert(isNegative(0)==0);
    assert(isNegative(2)==0);
    assert(isNegative(1000)==0);
    assert(isNegative(-2)==1);
    assert(isNegative(-1000)==1);
    assert(isNegative(1)==0);
    assert(isNegative(3)==0);
    assert(isNegative(1001)==0);
    assert(isNegative(-1)==1);
    assert(isNegative(-1001)==1);

    printf("Test 4: levelOrderTraversal\n");
    TreeItem array4[7] = {10,6,14,3,7,12,16};
    treelink new4 = NULL;
    for(int i = 0; i < 7; i++) {
       new4 = insertTreeNode(new4, array4[i]);
    }
    assert(new4!=NULL);
    assert(size(new4)==7);
    assert(countLeaves(new4) == 4);
    TreeItem * arrayLevelOrder = levelOrderTraversal(new4);
    assert(arrayLevelOrder[0]==10);
    assert(arrayLevelOrder[1]==6);
    assert(arrayLevelOrder[2]==14);
    assert(arrayLevelOrder[3]==3);
    assert(arrayLevelOrder[4]==7);
    assert(arrayLevelOrder[5]==12);
    assert(arrayLevelOrder[6]==16);
    free(arrayLevelOrder);
    destroyTree(new4);
    printf("White Box tests passed!\n\n");
    return;
}
