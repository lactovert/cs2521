#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "BST.h"

int main (int argc, char *argv[]) {
    Treelink new = createTree();
    assert(new!=NULL);
    printf("        50.........\n");
    printf("        /\\.........\n");
    printf("      40 60        \n");
    printf("      /\\   \\.......\n");
    printf("    21 45   70     \n");
    printf("   /               \n");
    printf("  10               \n");
    int sum = sumEven(new);
    int smal = getSmallest(new);
    int numInternal = numInternalNodes(new);
    int path = hasPathSum(new, 180);
    printf("sumEven : %d\n", sum);
    printf("getSmallest :%d\n", smal);    
    printf("InternalNodes : %d\n", numInternal);
    printf("has path (180)(answer is 1): %d\n", path);
    doubleTree(new);
    preorderTraversal(new);
    printf("\nsumEven : %d\n", sumEven(new));
    Treelink mod = trimTree(new, 45, 60);
    assert(!search(mod, 10));
    assert(!search(mod, 21));
    assert(!search(mod, 70));
    assert(search(mod, 60));
    assert(search(mod, 45));
    printf("All test passed!\n");
    return EXIT_SUCCESS;
}
