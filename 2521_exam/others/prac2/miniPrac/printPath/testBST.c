#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "BST.h"

int main(int argc, char* argv[])
{
	treelink tree_1 = NULL;
	tree_1 = insertTreeNode(tree_1, 50);
	tree_1 = insertTreeNode(tree_1, 29);
	tree_1 = insertTreeNode(tree_1, 27);
	tree_1 = insertTreeNode(tree_1, 53);
	tree_1 = insertTreeNode(tree_1, 21);
	tree_1 = insertTreeNode(tree_1, 10);
	tree_1 = insertTreeNode(tree_1, 5);
	tree_1 = insertTreeNode(tree_1, 1);
	tree_1 = insertTreeNode(tree_1, 19);
	tree_1 = insertTreeNode(tree_1, 42);
	tree_1 = insertTreeNode(tree_1, 39);
	tree_1 = insertTreeNode(tree_1, 76);
	tree_1 = insertTreeNode(tree_1, 90);
	tree_1 = insertTreeNode(tree_1, 91);
	tree_1 = insertTreeNode(tree_1, 35);
	tree_1 = insertTreeNode(tree_1, 39);
	tree_1 = insertTreeNode(tree_1, 28);
	tree_1 = insertTreeNode(tree_1, 50);
	tree_1 = insertTreeNode(tree_1, 46);
	tree_1 = insertTreeNode(tree_1, 32);
	tree_1 = insertTreeNode(tree_1, 18);
	tree_1 = insertTreeNode(tree_1, 12);
	tree_1 = insertTreeNode(tree_1, 0);

	printf("size of tree: %d\n", size(tree_1));
	printInorder(tree_1);
	printf("\n");

	printPath(tree_1);
    
    treelink tree_2 = NULL;
	tree_2 = insertTreeNode(tree_2, 5);
	tree_2 = insertTreeNode(tree_2, 4);
	tree_2 = insertTreeNode(tree_2, 7);
	tree_2 = insertTreeNode(tree_2, 2);
	tree_2 = insertTreeNode(tree_2, 1);
	tree_1 = insertTreeNode(tree_2, 3);
    
    printf("size of tree: %d\n", size(tree_2));
	printInorder(tree_2);
	printf("\n");

	printPath(tree_2);
    
    printf("passed\n");
	return EXIT_SUCCESS;
}
