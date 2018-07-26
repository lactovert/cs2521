#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define TRUE 1
#define FALSE 0

int binaryCheck(int a[], int l, int r);

int main(int argc, char *argv[])
{

	int a_1[] = {1,2,3,3,4,5,6,7,8,9};
	int a_2[] = {1,20,300,35,7,999};
	int a_3[] = {0};
	int a_4[] = {9,9,9,9,9,9,9,9,9,9};
	int a_5[] = {101,101,101,101,102,102,102,102,103,103};

	assert( binaryCheck(a_1, 0, 9) == TRUE  );
	assert( binaryCheck(a_2, 0, 5) == FALSE );
	assert( binaryCheck(a_3, 0, 0) == TRUE  );
	assert( binaryCheck(a_4, 0, 9) == TRUE  );
	assert( binaryCheck(a_5, 0, 9) == TRUE  );

    printf("All test passed!\n");
	return EXIT_SUCCESS;
}


// search through the array a recursively using a binary partioning method.
// check to see if the array is in order or not. 
// **DO NOT USE ITERATION (while/for loops)**
int binaryCheck(int a[], int l, int r)
{

	if(a==NULL) return 1;
	if(l==r) return 1;
	if(a[l+1]<a[l]) return 0;

	return binaryCheck(a,l+1,r);
}
