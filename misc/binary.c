int isze(treelink t) {
    if(t==NULL) return 0;
    return 1+size(t->left) + size(t->right);
}

static int max(treeitem i1, treeitem i2) {
    if(i1>=i2)
        return i1;
    return i2;
 }
int height (treelink t) {
    if (t == NULL) return -1;
    
    return 1+ max(height(t->left),height(t->right));
}
