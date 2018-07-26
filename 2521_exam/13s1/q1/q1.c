// q1.c ... Question 1 in COMP1927 13s1 Final Exam
// Find maximum value in an array via recursive divide-and-conquer

#include <stdlib.h>
#include <stdio.h>

#define MAXARRAY 5

int max(int a[], int lo, int hi);

int main(int argc, char **argv)
{
	int array[MAXARRAY]={11,2,3,4,5};  // array storage
	int n;  // count of elements in array
	//int val;  // next value read from stdin
	int ArrayMax(int *, int);

	// read array contents from stdin
	n = 1;
	/*while (fscanf(stdin,"%d",&val) == 1)
		array[n++] = val;*/
     
    
	// display maximum value
	if (n > 0)
		printf("Max = %d\n", ArrayMax(array,5));
	else
		printf("Array is empty\n");

	return 0;
}

// find maximum value in a[0..n-1]
int ArrayMax(int a[], int n)
{   
    if(n==0) abort();
    if(a==NULL) abort();
	int left = max(a, 0, (n-1)/2);
    int right = max(a, ((n-1)/2)+1, n-1);
	return left>right ? left : right;
}

// recursive function to find maximum in a[lo..hi]
int max(int a[], int lo, int hi)
{   
    if(hi==lo) return a[hi];
    if(hi-lo==1) {
        return a[lo]>a[hi] ? a[lo] : a[hi];    
    }
	int left = max(a, lo, lo+(hi/2));
    int right = max(a, lo+(hi/2)+1, hi);
    
	return left>right ? left : right;
}
