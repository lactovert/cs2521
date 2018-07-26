#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static void bubbleSort(int array[], int size);
static void swap(int array[], int a, int b);
static void printArray(int array[], int size);

int main(int argc, char *argv[]) {
    int array[10] = {10, 9 ,8, 7, 6 ,5, 4, 3, 2, 1};
    printArray(array, 10);
    bubbleSort(array, 10);
    printArray(array, 10);
    
    return EXIT_SUCCESS;
}
// ascedning order bubble sort
static void bubbleSort(int array[], int size) {
    for(int i = 0; i < size; i++) {
        for(int j = size-1; j >=1; j--){
            if(array[j] < array[j-1])
                swap(array,j,j-1);
        }
    }   
    
}

static void swap(int array[], int a, int b) {
    int temp = array[a];
    array[a] = array[b];
    array[b] = temp;
    return;
}

static void printArray(int array[], int size) {
    for(int i =0; i<size; i++) {
        printf("%d ",array[i]);
    }
    printf("\n");
}

