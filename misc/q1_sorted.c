int isSorted(int array[], int left, int right) {
    if(l==r) return 1;
    if(array[l] > array[l+1]) return 0;
    return function(array, l+1, r);
}
