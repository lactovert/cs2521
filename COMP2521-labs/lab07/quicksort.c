#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void quickSort(int items[],int l, int r);
void swap(int index1, int index2, int items[]);
void quickSortMT(int a[], int l, int r);
static void printArray(int array[], int size);
void insertionSort(int a[], int l, int r);
int parseThreshold(char *abbrev);
int power(int n);


int main(int argc, char *argv[]) {
    // This part gets what the input is
    if(argc < 2) {
        printf("invalid input, enter correct sort\n");
    } else {
    
         char *abbrev = argv[1];
         /*if(strlen(abbrev)<3) {
            //printf("invalid input, using naive pivot\n");
            abbrev = "-pn";
        }*/
        // gets the number of elements and initialise the array
        int size;
        int i;
        printf("Enter number of elements:");
        scanf("%d",&size);

        int *a = malloc(size * sizeof(int));   
        printf("Enter elements:\n"); 
        for(i=0;i<size;i++){
	        scanf("%d",&a[i]);
        }
        
        
        // 
        if (strcmp(abbrev,"-pm")==0) {
            // median of three pivot
            quickSortMT(a, 0, size-1);
            printf("Sorted with median of three pivot\n");
        } else if (strcmp(abbrev,"-pr")==0) {
            // random
            int r = rand()%(size);
            swap(r, size-1, a);
            quickSort(a, 0, size-1);
            printf("Sorted with random pivot\n");
        } else if(abbrev[2]-'a'==0) {
                int tres = parseThreshold(abbrev);
                if (size < tres) {
                    insertionSort(a, 0, size-1);
                } else {
                    quickSort(a, 0, size-1);
                }
        } else if(abbrev[2]=='b') {
            int tres = parseThreshold(abbrev);
            quickSort(a, tres, size-1);
            insertionSort(a, 0, size-1);
        }
        else  {
            // with naive pivot 
            quickSort(a,0 , size-1 );
            printf("Sorted with naive pivot\n");
        }
        
        if(argv[2]!=NULL) {
            if(strcmp(argv[2],"-q")!=0){
                printArray(a,size);
            }
        } else if(argv[2]==NULL) {
            printArray(a,size);
        }
        
        
        
    }
    return EXIT_SUCCESS;
}

static void printArray(int array[], int size) {
    for (int i =0; i < size;i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
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

void insertionSort(int a[], int l, int r) {
    int i, j, key; 
    for (i= l; i<= r; i++) { 
        key = a[i];
        for (j = i; j >= 1 && key < a[j-1]; j--){
            a[j] = a[j -1];
        }
        a[j] = key; 
    } 
}

int parseThreshold(char *abbrev) {
    int i = 3;
    int result = 0;
    int array[7]={0};
    while(abbrev[i]!='\0') {
        i++;
    }
    int n = 0;
    int l = 3;
    while(l<i) {
        array[n] = abbrev[l]-'0';
        
        l++;
        n++;
    }
    int a = 0;
    int b = n-1;
    while(b>=0) {
       result = result + (array[a]*power(b));

       a++;
       b--;
    }
    
    return result;
}

int power(int n) {
    int result = 1;
    for(int i=0; i < n; i++) {
        result = result * 10;
    }
    
    return result;
}
