#include <stdio.h>
#include <stdlib.h>


void quickSort(int items[],int l, int r);
void swap(int index1, int index2, int items[]);
void quickSortMT(int a[], int l, int r);

int main(int argc, char *argv[]) {
    // This part gets what the input is
    if(argc < 3) {
        printf("no argument, using naive pivot\n");
    }
    if(strlen[1] == 3) {
        char *abbrev = argv[1];
    } else {
        printf("invalid input, using naive pivot\n");
    }
    // gets the number of elements and initialise the array
    int size;
    int i;
    printf("Enter number of elements:");
    scanf("%d",&size);

    int * a = malloc(size * sizeof(int));   
    printf("Enter elements:\n"); 
    for(i=0;i<size;i++){
	    scanf("%d",&a[i]);
    }
    
    
    // 
    if (strcmp(abbrev,"-pm")) {
        // median of three pivot
        quickSortMT(a[], 0, size-1);
    } else if (strcmp(abbrev,"-pr")) {
        // random
        int r = rand()%(size);
        quickSort(a, 0, r);
    } else  {
        // with naive pivot 
          quickSort(a,0 , size-1 );
    } 
    
    return EXIT_SUCCESS;
}


int partition(int a[], int l, int r);

void quickSort (int a[], int l, int r){         	
   int i;  
   if  (r <= l) {
       return;
   } 
   i = partition (a, l, r);  
   quickSort (a, l, i-1);  
   quickSort (a, i+1, r);
}

int partition (int a[], int l, int r) {   
   int i = l-1;
   int j = r;   
   int pivot = a[r]; //rightmost is pivot  	
   for(;;) {   
	while ( a[++i] < pivot) ;    
	while ( pivot <  a[--j] && j != l);
	if (i >= j) { 
      		break;
    	}    
	swap(i,j,a);  
    }
    //put pivot into place  
    swap(i,r,a);  
    return i; //Index of the pivot
}


void swap(int index1, int index2, int items[]){
    int tmp;
    tmp = items[index1];
    items[index1] = items[index2];
    items[index2] = tmp;
}

// Quick sort with Medain of THREE Partitioning
void quickSortMT(int a[], int l, int r){         	
   int i;  
   if  (r <= l) {
       return;
   } 
   if(r-l > 1){
       int mid = (r+l)/2;

       swap(r-1,mid,a);
       if(a[r-1] < a[l]){
           swap(r-1,l,a);
       }
       if(a[r] < a[l]){
           swap(r,l,a);
       }
       if(a[r] < a[r-1]){
           swap(r,r-1,a);
       }
     
       i = partition(a,l+1,r-1);
   } else {
       i = partition(a,l,r);  
   }  
 
   quickSortMT (a, l, i-1);  
   quickSortMT (a, i+1, r);
}
