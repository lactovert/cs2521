#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "BST.h"

void destroyTree(treelink tree);
void whiteBoxTests(void);

int main (int argc, char *argv[]) {
    whiteBoxTests();

    printf("======Black box tests======\n");

    printf("Test 0 : empty tree\n");
    treelink new = NULL;
    printTreeNode(new);
    printTreeNode(NULL);
    assert(size(new)==0);
    assert(size(NULL)==0);
    printf("...Size of an empty tree vs NULL input, same\n");
    treelink res0 = search(new, 2);
    treelink res00 = search(NULL, 2);
    assert(res0==NULL);
    assert(res00==NULL);
    destroyTree(res0);
    destroyTree(res00);
    printf("Searching on an empty tree\n");
    assert(countLeaves(NULL)==0);
    assert(countLeaves(new)==0);
    printf("...Counting leaves of an empty tree vs NULL input, same\n");
    TreeItem *aNew = levelOrderTraversal(new);
    TreeItem *aNULL = levelOrderTraversal(NULL);
    assert(aNew==NULL);
    assert(aNULL==NULL);
    printf("...levelOrderTraversal arrays are both NULL\n");
    assert(isEven(0)==1);
    assert(isEven(1)==0);
    assert(isEven(-1)==0);
    assert(isEven(2)==1);
    printf("...isEven passed\n");
    assert(isOdd(0)==0);
    assert(isOdd(1)==1);
    assert(isOdd(-1)==1);
    assert(isOdd(2)==0);
    printf("...isOdd passed\n");
    assert(isNegative(0)==0);
    assert(isNegative(1)==0);
    assert(isNegative(-1)==1);
    assert(isNegative(-20)==1);
    printf("...isNegative passed\n");
    assert(countIf(new,isEven)==0);
    assert(countIf(NULL,isEven)==0);
    printf("...countIf Even same\n");
    assert(countIf(new,isOdd)==0);
    assert(countIf(NULL,isOdd)==0);
    printf("...countIf Odd same\n");
    assert(countIf(new,isNegative)==0);
    assert(countIf(NULL,isNegative)==0);
    printf("...countIf Negative same\n");
    printf("\n");


    printf("Test 1 : multiple element non-duplicating positives 5 2 8 1 4\n");
    int array1[5]={5, 2, 8, 1, 4};
    treelink new1 = NULL;
    int i = 0;
    while(i < 5) {
        new1 = insertTreeNode(new1, array1[i]);
        i++;
        assert(size(new1)==i);
    }
    assert(countIf(new1, isEven)==3);
    printf("...This tree has 3 evens\n");
    assert(countIf(new1, isOdd)==2);
    printf("...This tree has 2 odds\n");
    assert(countIf(new1, isNegative)==0);;
    printf("...No negatives\n");

    printf("...Printing preorder traversal : ");
    preorderTraversal(new1,printTreeNode);
    assert(countLeaves(new1)==3);
    assert(getItem(new1)==5);
    printf("\n...Tree successfully created\n");
    printf("...Searching for Tree Items...\n");
    treelink res1 = search(new1, 5);
    assert(getItem(res1)==5);
    printf("5 found\n");
    treelink res11 = search(new1, 1);
    assert(getItem(res11)==1);
    assert(res11!=NULL);
    printf("1 found\n");
    treelink res111 = search(new1, 0);
    assert(res111==NULL);
    printf("0 not found\n");
    
    
    printf("Test 2 : 3 element duplicating positives 1 1 0\n");
    int array2[3]={1, 1, 0};
    treelink new2 = NULL;
    int j = 0;
    while(j < 3) {
        new2 = insertTreeNode(new2, array2[j]);
        j++;
        assert(size(new2)==j);
    }
    assert(countLeaves(new2)==1);
    assert(getItem(new2)==1);
    printf("...Tree successfully created\n");

    assert(countIf(new2, isEven)==1);
    printf("...This tree has 1 even\n");
    assert(countIf(new2, isOdd)==2);
    printf("...This tree has 2 odds\n");
    assert(countIf(new2, isNegative)==0);;
    printf("...No negatives\n");

    printf("Searching for Tree Items...\n");
    treelink res2 = search(new2, 1);
    assert(getItem(res2)==1);
    printf("1 found\n");
    treelink res22 = search(new2, 1);
    assert(getItem(res22)==1);
    printf("1 found again\n");
    treelink res222 = search(new2, 0);
    assert(getItem(res222)==0);
    printf("0 found\n");
    treelink res2222 = search(new2, -1);
    assert(res2222==NULL);
    printf("-1 not found\n");



    printf("Test 3 : 1 element negative -1\n");
    treelink new3 = NULL;
    new3 = insertTreeNode(new3,-1);
    assert(getItem(new3)==-1);
    printf("...Tree successfully created\n");
    
    assert(countIf(new3, isEven)==0);
    printf("This tree has no evens\n");
    assert(countIf(new3, isOdd)==1);
    printf("This tree has 1 odd\n");
    assert(countIf(new3, isNegative)==1);;
    printf("1 negative\n");
    
    printf("Searching for Tree Items...\n");
    treelink res3 = search(new3, -1);
    assert(getItem(res3)==-1);
    printf("-1 found\n");
    treelink res33 = search(new3, 0);
    assert(res33==NULL);
    printf("0 not found\n");
    treelink res333 = search(new3, 1);
    assert(res333==NULL);
    printf("1 not found\n");



    printf("Test 4 : 2 element combo -1 1\n");
    int array4[2]={-1, 1};
    treelink new4 = NULL;
    int k = 0;
    while(k < 2) {
        new4 = insertTreeNode(new4, array4[k]);
        k++;
        assert(size(new4)==k);
    }
    assert(getItem(new4)==-1);
    printf("Tree successfully created\n");

    assert(countIf(new4, isEven)==0);
    printf("...This tree has no evens\n");
    assert(countIf(new4, isOdd)==2);
    printf("...This tree has 2 odds\n");
    assert(countIf(new4, isNegative)==1);;
    printf("...1 negative\n");
    
    printf("Searching for Tree Items...\n");
    treelink res4 = search(new4, -1);
    assert(getItem(res4)==-1);
    printf("-1 found\n");
    treelink res44 = search(new4, 0);
    assert(res44==NULL);
    printf("0 not found\n");
    treelink res444 = search(new4, 1);
    assert(getItem(res444)==1);
    printf("1 found\n");
    
    
    printf("Test 5 : level order\n");
    printf("...NULL tree\n");
    treelink new5 = NULL;
    TreeItem * array5 = levelOrderTraversal(new5);
    assert(array5==NULL);

    printf("...Balanced tree\n");
    int a5Bal[7]={4, 2, 1, 3, 6, 5, 7};
    treelink new5Bal = NULL;
    int l = 0;
    while (l < 7) {
        new5Bal = insertTreeNode(new5Bal, a5Bal[l]);
        l++;
        assert(size(new5Bal)==l);
    }
    TreeItem * array5Bal = levelOrderTraversal(new5Bal);
    assert(array5Bal[0]==4);
    assert(array5Bal[1]==2);
    assert(array5Bal[2]==6);
    assert(array5Bal[3]==1);
    assert(array5Bal[4]==3);
    assert(array5Bal[5]==5);
    assert(array5Bal[6]==7);
    free(array5Bal);

    printf("...Imbalanced tree\n");
    int a5Imbal[7]={6, 5, 2, 1, 3, 4, 7};
    treelink new5Imbal = NULL;
    l = 0;
    while (l < 7) {
        new5Imbal = insertTreeNode(new5Imbal, a5Imbal[l]);
        l++;
        assert(size(new5Imbal)==l);
    }
    TreeItem * array5Imbal = levelOrderTraversal(new5Imbal);
    assert(array5Imbal[0]==6);
    assert(array5Imbal[1]==5);
    assert(array5Imbal[2]==7);
    assert(array5Imbal[3]==2);
    assert(array5Imbal[4]==1);
    assert(array5Imbal[5]==3);
    assert(array5Imbal[6]==4);
    free(array5Imbal);

    printf("...Degenerate tree\n");
    treelink new5D = NULL;
    l = 0;
    while (l < 7) {
        new5D = insertTreeNode(new5D, l);
        l++;
        assert(size(new5D)==l);
    }
    TreeItem * array5D = levelOrderTraversal(new5D);
    assert(array5D[0]==0);
    assert(array5D[1]==1);
    assert(array5D[2]==2);
    assert(array5D[3]==3);
    assert(array5D[4]==4);
    assert(array5D[5]==5);
    assert(array5D[6]==6);
    free(array5D);

    destroyTree(new);
    destroyTree(new1);
    destroyTree(new2);
    destroyTree(new3);
    destroyTree(new4);
    destroyTree(new5Bal);
    destroyTree(new5Imbal);
    destroyTree(new5D);

    
    
    printf("All test passed!\n");
    return EXIT_SUCCESS;
}
