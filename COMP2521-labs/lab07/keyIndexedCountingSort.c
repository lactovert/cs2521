#include <stdio.h>
#include <stdlib.h>


void keyIndexed(int items[], int n, int max) ;

int main(void){
    int size;
    int i;
    int max;

    printf("Enter max key:");
    scanf("%d",&max);
    printf("Enter number of elements:");
    scanf("%d",&size);

    int * a = malloc(size * sizeof(int));   
    printf("Enter elements:\n"); 
    for(i=0;i<size;i++){
            scanf("%d",&a[i]);
    }
   
    keyIndexed(a,size,max);
    
    printf("Sorted\n");
    for(i=0;i<size;i++){
            printf("%d ",a[i]);
    }
    printf("\n");

    return 0;
}



//Sort array of size n with keys between 0 and m-1 
void keyIndexed(int items[], int n, int m) { 
	int i, index;
	int *count = malloc((m+1)* sizeof(int)); 
	int *tmp =  malloc((n) *sizeof(int)); 

        //initialise array O(m)
	for (i = 0; i <= m; i++){
    		count[i] = 0; 
	}
 
	//Count how many of each key we have O(n)
   	for (i = 0; i < n; i++){
       		count[items[i] +  1]++;
   	}

        //O(m)
	for (i = 1; i <= m; i++){
      		count[i] += count[i - 1]; //cumulative total
   	}

   	//use cumulative totals to put items in order
        //O(n)
   	for (i = 0; i < n; i++){
      		index = count[items[i]]++; 
      		tmp[index] = items[i]; 
   	}
  

        //O(n)
   	for (i = 0; i < n; i++){
       		items[i] = tmp[i]; //copy back   
   	}
   	free(tmp); 
   	free(count); 
} 
