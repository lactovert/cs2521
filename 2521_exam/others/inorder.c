#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <inorder.h>

typedef treeNode *Treelink;

typedef treeNode {
    int item;
    Treelink left;
    Treelink right;  
};

Treelink inorderSucc (Treelink root, int num) {
    Treelink curr, parent = NULL;
    curr = root;
    
    while(curr!=NULL || curr->value != num) {
        if(curr->value > num) {
            // go left
            parent = curr;
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    
    return parent == NULL ?minValue(curr->right) : parent;
}

Treelink minValue (Treelink root) {
    if(!root) return NULL;
    Treelink curr = root;
    while(curr->left!=NULL) curr = curr->left;
    return curr;
}
