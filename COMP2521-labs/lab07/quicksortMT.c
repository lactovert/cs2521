#include <stdio.h>
#include <stdlib.h>

void quickSortMT(int items[],int l, int r);
void swap(int index1, int index2, int items[]);

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
   
    quickSortMT(a,0,size-1);
    
    printf("Sorted\n");
    for(i=0;i<size;i++){
            printf("%d ",a[i]);
    }
    printf("\n");

    return 0;
}

int partition(int a[], int l, int r);

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

