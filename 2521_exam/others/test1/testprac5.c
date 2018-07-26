#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "prac5.h"

#define THIS_IS_MADNESS 10
#define ITERATIONS 5
#define SPARTA 100
#define MIN(a,b) ((a) > (b) ? (b) : (a))
void printList(Node n) {
    if (n == NULL) {
        printf("[X]\n");
        return;
    }
    printf("[%d]->", n->data);
    printList(n->next);
}

void freeList(Node n) {
    if (n == NULL) {
        return;
    }
    freeList(n->next);
    free(n);
}

List createListFromArray(int *array, int n) {
    int i;
    List l = createList();
    Node curr = NULL;
    for (i = 0; i < n; i++) {
        Node n = createNode(array[i]);
        if (l->first == NULL) {
            l->first = n;
        } else {
            curr->next = n;
        }
        curr = n;
    }
    return l;
}

void testPartition(void) {
    int t, it, i, l;
    for (t = 0; t < THIS_IS_MADNESS; t++) {
        for (it = 0; it < ITERATIONS || it == 0; it++) {
            int *array = malloc(sizeof(int) * t);
            for (i = 0; i < t; i++) {
                array[i] = rand() % SPARTA;
            }
            for (i = -1; i <= SPARTA; i++) {
                List l1 = createListFromArray(array, t);
                int *exp_orig = malloc(sizeof(int) * t);
                int *exp_new  = malloc(sizeof(int) * t);

                int j = 0, k = 0;
                for (l = 0; l < t; l++) {
                    if (array[l] <= i) {
                        exp_new[j++] = array[l];        
                    } else {
                        exp_orig[k++] = array[l];
                    }
                }
                printf("* testing with PIVOT: %d\n", i);
                printf("* Original List: ");
                for (l = 0; l < t; l++) {
                    printf("[%d]->", array[l]);
                }
                printf("[X]\n");

                printf("** expected original: ");
                for (l = 0; l < k; l++) {
                    printf("[%d]->", exp_orig[l]);
                }
                printf("[X]\n");

                printf("** expected new: ");
                for (l = 0; l < j; l++) {
                    printf("[%d]->", exp_new[l]);
                }
                printf("[X]\n");

                printf("* running function...good luck!\n");
                fflush(stdout);
                List l2 = partition(l1, i);
                printf("* no seg fault!\n");
                fflush(stdout);
                
                printf("** your original: ");
                printList(l1->first);
                printf("** your new: ");
                printList(l2->first);
                fflush(stdout);

                printf("* now running the assertions...\n");
                printf("** seg fault below means above does not match!\n");

                // asserts
                Node curr;
                for (curr = l1->first, l = 0; l < k; l++, curr = curr->next) {
                    assert(curr->data == exp_orig[l]);
                }
                assert(curr == NULL);

                for (curr = l2->first, l = 0; l < j; l++, curr = curr->next) {
                    assert(curr->data == exp_new[l]);
                }
                assert(curr == NULL);


                printf("* test passed!\n");
                
                printf("========================================================\n");
                free(exp_orig);
                free(exp_new);
                freeList(l1->first);
                free(l1);
                freeList(l2->first);
                free(l2);
            }        
            free(array);
        }
    }
}

int main(void) {
    // hehe
    srand(1927);
    // and we partition!
    testPartition();
    printf("i am satisfied with your function. congratulations. asian father approves.\n");
    return 0;
}
