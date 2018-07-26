#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "lists.h"
void test1(void);
void test2(void);
void test3(void);
// insert proper tests here
int main (int argc, const char * argv[]) {
 	test1();
 	test2();
 	test3();
  	printf("You have passed all the tests! The gods of computer science deem you worthy\n");
  	return 0;
}

void test1(void){
	printf("Starting test1\n");
	dlink l1= genDList(10);
	printf("Initial list is\n");
	printDList(l1);
	printf("Slicing at position 4\n");
	dlink l2 = appendCut(4, l1);
	printDList(l2);
	printf("PASSED!\n");
	printf("##########################\n");
}

void test2(void){
	printf("Starting test2\n");
	dlink l1= genDList(10);
	printf("Initial list is\n");
	printDList(l1);
	printf("Slicing at position 0\n");
	dlink l2 = appendCut(0, l1);
	printDList(l2);
	printf("PASSED!\n");
	printf("##########################\n");
}

void test3(void){
	printf("Starting test3\n");
	dlink l1= genDList(10);
	printf("Initial list is\n");
	printDList(l1);
	printf("Slicing at position 1245\n");
	dlink l2 = appendCut(1245, l1);
	printDList(l2);
	printf("PASSED!\n");
	printf("##########################\n");
}
