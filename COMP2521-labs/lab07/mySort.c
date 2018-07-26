#include <stdio.h>
#include <stdlib.h>

//generalises to bucket sort.
//here n buckets - for size n data assuming no duplicates and keys range from
//0..n-1


//This implementation is very limited - will not work for duplicates.
//Only works for sorting n numbers with keys 0..n-1
void trickySort(int items[], int n) ;

int main(void){
    int size;
    int i;
  
    printf("Enter number of elements:");
    scanf("%d",&size);

    int * a = malloc(size * sizeof(int));   
    printf("Enter elements:\n"); 
    for(i=0;i<size;i++){
            scanf("%d",&a[i]);
    }
   
    trickySort(a,size);
    
    printf("Sorted\n");
    for(i=0;i<size;i++){
            printf("%d ",a[i]);
    }
    printf("\n");

    return 0;
}

void trickySort(int items[],int n){
    int * tmp = malloc(n * sizeof(int));
    int i;
    for(i = 0; i < n; i ++){
        if(items[i] >= n) {
           printf("I can't sort this!");
           exit(1);
        }
        tmp[items[i]] = items[i];
    }
    
    for(i = 0; i < n; i++){
        items[i] = tmp[i];
    }
}
