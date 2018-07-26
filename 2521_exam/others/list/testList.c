#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "list.h"

// compile with gcc -Wall -Werror -o question testList.c list.c

// insert proper tests here
int main (int argc, const char * argv[]) {
  printf("Write your tests here!\n");
  printf("Remember to consider boundary/edge cases as well as typical use cases!\n");
  printf("And dont forget to free!\n");

  link i = fromTo(1,10);
  // do some tests
  printf("List i: ");
  printList(i);
  printf("%dth node from the back is ", 0);
  printLink(nodeFromEnd(i,0));
  printf("%dth node from the back is ", 10);
  printLink(nodeFromEnd(i,10));
  link j = createListFromStr("1014101");
  printList(j);
  printf("should be a palindrome: %d\n", isPalindrome(j));
  
  link k = createListFromStr("101745101");
  printList(k);
  printf("should not be a palindrome: %d\n", isPalindrome(k));
  
  link l = createListFromStr("1");
  printList(l);
  printf("should be a palindrome: %d\n", isPalindrome(l));
  
  freeList(i);
  freeList(j);
  freeList(k);
  freeList(l);
  return EXIT_SUCCESS;;
}
