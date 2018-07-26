// Written by Jansen Malem (z5141970)

#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "textbuffer.h"

#define SINGLE_ELEMENT 1
#define PLUS_ONE 1

typedef struct node *Node;

struct textbuffer {
    Node head;
    Node tail;
    int size; // # of all nodes
};

struct node {
    char *string;
    Node next;
};

// Prototypes
static Node newNode (char text[]);
static int numLine (char text[]);
static int lenOfTB(TB tb);
static Node connectNode(char text[]);
static int size (TB tb);
static void updateTail(TB tb);
static int needleCount(TB tb, char *ori);
static char *resultBuff(TB tb, char* str1, char* str2, int occur);

TB newTB (char text[]) {
    Node curr;
    TB new = malloc(sizeof(struct textbuffer));
    new->head = connectNode(text);
    new->size = size(new);
    curr = new->head;
    while(curr->next != NULL) {
        curr = curr->next;
    }
    new->tail = curr;
    return new;
}

void releaseTB (TB tb) {
    if(tb == NULL){
        printf("invalid pointer a\n");
        abort();
    }
    Node curr = tb->head;
    Node temp;
    while(curr!=NULL){
        temp = curr->next;
        free(curr->string);
        free(curr);
        curr = temp;
    }

    free(tb);
}

char *dumpTB (TB tb) {
    if(tb==NULL) {
        printf("Invalid pointer\n");
        abort();
    }
    if(tb->head == NULL) return "";
    int length = lenOfTB(tb);
    char *array = malloc(sizeof(char) * length);
    int i =0;
    int n =0;
    Node curr = tb->head;
    while(curr != NULL) {
        i = 0;
        while(curr->string[i] != '\0') {
            array[n] = curr->string[i];
            n++;
            i++;
        }

        array[n] = '\n';
        n++;
        curr = curr->next;
    }
    array[n] = '\0';
    return array;
}

int linesTB (TB tb) {
    return tb->size;
}


void swapTB (TB tb, int pos1, int pos2) {
    if(tb == NULL) return;
    if(pos1 == pos2) return;
    if(pos1<0 || (pos1 >= tb->size)) {
        printf("position 1 is out of range\n");
        abort();
    } else if(pos2<0 || (pos2 >= tb->size)) {
        printf("position 2 is out of range\n");
        abort();
    }
    Node temp;
    Node curr1 = tb->head;
    Node prev1 = curr1;
    Node curr2 = tb->head;
    Node prev2 = curr2;
    int n1 = 0;
    int n2 = 0;

    int var = 0;
    int swap1 = pos1;
    int swap2 = pos2;
    if (pos2 < pos1) {
        var = swap2;
        swap2 = swap1;

        swap1 = var;
    }
    while(n1 < swap1) {
        n1++;
        prev1 = curr1;
        curr1 = curr1->next;
    }

    while(n2 < swap2) {
        n2++;
        prev2 = curr2;
        curr2 = curr2->next;
    }
    if(swap1 == 0 && (swap2-swap1) != 1) {
        //then curr1 = tb->head
        temp = curr1->next;
        prev2->next = curr1;
        curr1->next = curr2->next;
        tb->head = curr2;
        curr2->next = temp;
        updateTail(tb);
        return;
    }
    // if the nodes are adjacent but none of them is in index 0
    if (swap1 != 0 && swap2!= 0 && (swap2-swap1==1)){
        temp = curr2->next;
        prev1->next = curr2;
        curr1->next = temp;
        curr2->next = curr1;
        updateTail(tb);
        return;
    }
    // if the nodes are adjacent but one of them is in index 0
    if (swap1 == 0 && (swap2-swap1 == 1)) {
        temp = curr2->next;
        curr1->next = temp;
        tb->head = curr2;
        curr2->next = curr1;
        updateTail(tb);
        return;
    }
    //normal cases
    if(swap2 > swap1) {
        temp = curr1->next;
        prev2->next = curr1;
        curr1->next = curr2->next;
        prev1->next = curr2;
        curr2->next = temp;
        updateTail(tb);
    }
}


void mergeTB (TB tb1, int pos, TB tb2) {
    if(tb1 == NULL || tb2 == NULL) {
        printf("Invalid pointer\n");
        abort();
    }
    if(tb2->head == NULL) return;

    int sizeTb1= linesTB(tb1);
    if(pos > sizeTb1) {
        printf("Out of range\n");
        abort();
    }
    // will point to the desired position for merging
    Node curr = tb1->head;
    Node prev = NULL;
    // will point to the end of tb2
    Node end2 = tb2->tail;
    // temporary pointer
    Node temp = NULL;
    // update the size
    tb1->size = tb1->size + tb2->size;
    int i =0;
    while(i<pos) {
        prev = curr;
        curr = curr->next;
        temp = curr;
        i++;
    }

    if(i == 0) {
        end2->next = tb1->head;
        tb1->head = tb2->head;

    } else if(pos == sizeTb1) {
        tb1->tail->next = tb2->head;
        tb1->tail = tb2->tail;
    }else {
        prev->next = tb2->head;
        tb2->tail->next = temp;
    }
    free(tb2);
    return;
}

void pasteTB (TB tb1, int pos, TB tb2){
    char *str = dumpTB(tb2);
    char *del = str;
    TB dup = newTB(str);
    mergeTB(tb1, pos, dup);
    free(del);
}

TB cutTB (TB tb, int from, int to) {
    if(tb == NULL) abort();
    if(tb->head == NULL) {
        printf("Empty text buffer\n");
        abort();
    }
    TB new;
    Node begin = tb->head;
    Node prevBegin;
    Node end = tb->head;
    Node temp = end->next;
    int i = 0;
    int j = 0;
    int size = tb->size;
    int newSize = tb->size - (to - from +1);
    if(from < 0 || (from > size-1)) {
        printf("Out of range\n");
        abort();
    } else if(to < 0 || (to > size-1)) {
        printf("Out of range\n");
        abort();
    }
    // if from > to then return NULL
    if(from > to) return NULL;

    // use the begin and end to locate the node
    while(i < from) {
        i++;
        prevBegin = begin;
        begin = begin->next;
    }
    while ( j < to) {
        j++;
        end = end->next;
        temp = end->next;
    }

    if (i == 0) {
        tb->head = temp;

        new = malloc(sizeof(struct textbuffer));
        new->head = begin;
        new->tail = end;
        new->tail->next = NULL;
        new->size = to - from + PLUS_ONE;

        // Update the old text buffer size
        tb->size = newSize;

        return new;
    }
    prevBegin->next = end->next;

    new = malloc(sizeof(struct textbuffer));
    new->head = begin;
    new->tail = end;
    new->tail->next = NULL;
    new->size = to - from + PLUS_ONE;

    // Update the old text buffer size
    tb->size = newSize;

    return new;
}

TB copyTB (TB tb, int from, int to) {
    if(tb == NULL) abort();
    if(tb->head == NULL) {
        printf("Empty text buffer\n");
        abort();
    }
    TB new = malloc(sizeof(struct textbuffer));
    int i = 0;
    int j = 0;
    Node begin = tb->head;
    Node end = tb->head;
    Node curr;
    Node copy;
    // check if out of range
    int size = tb->size;
    if(from < 0 || from >size-1) {
        printf("Out of range\n");
        abort();
    } else if(to < 0 || to > size-1) {
        printf("Out of range\n");
        abort();
    }
    // if from > to then return NULL
    if(from > to) return NULL;

    while (i<from) {
        i++;
        begin = begin->next;
    }
    while (j<to) {
        j++;
        end = end->next;
    }
    if(from == 0 && to == 0) {
        new->head = newNode(begin->string);
        new->tail = new->head;
        new->tail->next = NULL;
        new->size = SINGLE_ELEMENT;
        return new;
    }

    curr = begin;
    copy = newNode(curr->string);
    new->head = copy;
    curr = curr->next;
    while(curr != end) {
        copy->next = newNode(curr->string);
        copy = copy->next;
        curr = curr->next;
    }
    copy->next = newNode(curr->string);

    new->size = to - from + PLUS_ONE;

    return new;

}


void deleteTB (TB tb, int from, int to) {
    if (tb == NULL) abort();
    if (tb->head == NULL) return;
    if (from > to) return;
    if (from < 0 || (from > tb->size-1)) return;
    if (to < 0 || (to > tb->size-1)) return;
    
    TB delete = cutTB (tb, from , to);
    releaseTB(delete);
}

//replace every occurence of str1 with str2
void replaceText (TB tb, char* str1, char* str2) {

    if (strcmp(str1, str2) == 0) return;
    if (tb == NULL) {
        printf("invalid pointer, replace failed\n");
        abort();
    }
    if (tb->head == NULL) {
        printf("empty text buffer, replace failed\n");
        abort();
    }

    int size = tb->size;
    char *ori = dumpTB(tb);
    char *temp = ori;

    //length of the text
    int repLen = strlen(str1);
    int occur = needleCount(tb, str1);

    if(occur == 0) return;

    char *result = resultBuff(tb, str1, str2, occur);
    int n = 0;
    int j = 0;
    while (temp[n] != '\0') {
        if (strstr(temp, str1) == temp) {
            // copy the str2 to result
            for(int k = 0; str2[k] != '\0'; k++) {
                result[j] = str2[k];
                j++;
            }
            //increment index n by the length of str1 after spotting
            temp += repLen;

        } else {
            result[j] = *temp;
            j++;
            temp++;
        }
    }

    TB new = newTB(result);
    deleteTB(tb, 0, size-1);
    mergeTB(tb, 0, new);

    free(ori);
    free(result);

}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Helper functions
static Node connectNode(char text[]){
    char *string = strdup(text);
    char *org = string;
    char *temp;
    Node curr;
    Node start;
    int line = numLine(text);
    int n = 0;
    temp = strsep(&string, " ");
    n++;

    start = newNode(temp);
    assert(start != NULL);


    curr = start;
    while(n < line) {
        temp = strsep(&string, " ");
        curr->next = newNode(temp);
        curr = curr->next;
        n++;
    }
    free(org);
    return start;
}
static Node newNode (char text[]) {
    assert(text != NULL);

    Node new = malloc(sizeof(struct node));
    assert(new != NULL);

    new->string = strdup(text);

    new->next = NULL;
    return new;
}

static int numLine (char text[]){
    if(text == NULL) abort();
    int i = 0;
    int retval = 0;
    while (text[i] != '\0') {
        if (text[i] == '\n') retval++;
        i++;
    }
    return retval;
}


static int lenOfTB(TB tb){
    if(tb == NULL) {
        abort();
    }
    if (tb->head == NULL) return 0;

    Node curr = tb->head;
    int chars = 0;
    int i = 0;
    // loop through each node
    // and their string
    while(curr != NULL) {
        i = 0;
        while(curr->string[i] != '\0') {
            chars++;
            i++;
        }
        // the '\n'
        chars++;
        curr = curr->next;
    }
    // the '\0'
    chars++;
    return chars;
}


static int size (TB tb) {
    Node curr = tb->head;
    int res = 0;
    while (curr!=NULL) {
        res++;
        curr = curr->next;
    }
    return res;
}

static void updateTail(TB tb) {
    Node curr;
    curr = tb->head;
    while(curr->next != NULL) {
        curr = curr->next;
    }
    tb->tail = curr;
    curr->next = NULL;
}

static int needleCount(TB tb, char *str1) {
    char *temp = dumpTB(tb);
    char *del = temp;
    char *curr = NULL;
    int occur = 0;
    int repLen = strlen(str1);
    while((curr = strstr(temp, str1)) != NULL){
        temp += curr - temp;
        temp += repLen;
        occur++;
    }
    free(del);
    return occur;
}

static char *resultBuff(TB tb, char* str1, char* str2, int occur) {
    char *ori = dumpTB(tb);
    char *result;
    //length of the text
    int oriLen = strlen(ori) + PLUS_ONE;
    int repLen = strlen(str1);
    int newLen = strlen(str2);
    int diffLen = newLen - repLen;
    int resLen = occur * diffLen + oriLen;
    result = calloc(resLen, sizeof(char));
    free(ori);
    return result;
}

/*
// Test
void whiteBoxTest(void) {

    printf("Test 1 : Create a newTB\n");
    //Test 1 create newTB
    TB new1 = newTB("Hello \nWorld \nthis \nis \na \ntest \n");
    assert(new1 != NULL);
    assert(new1->size == 6);
    assert(linesTB(new1) == 6);

    assert(new1->head != NULL);
    assert(new1->tail->next == NULL);
    releaseTB(new1);
    printf("Test 1 passed\n");

    //Test 2 : swapTB
    printf("Test 2 : swapTB\n");
    TB new2 = newTB("Test \nwith \ndifferent \ninput \n! \n");
    assert(new2 != NULL);
    swapTB(new2, 0, 1);
    assert(new2->head != NULL);
    assert(new2->tail->next == NULL);
    assert(linesTB(new2) == 5);
    swapTB(new2, 0, 4);
    assert(new2->head !=NULL);
    assert(new2->head->next != NULL);
    assert(new2->tail->next == NULL);
    assert(linesTB(new2) == 5);
    swapTB(new2, 4, 0);
    assert(new2->head !=NULL);
    assert(new2->head->next != NULL);
    assert(new2->tail->next == NULL);
    assert(linesTB(new2) == 5);
    swapTB(new2, 2, 1);
    char *text = dumpTB(new2);
    assert(new2->head !=NULL);
    assert(new2->head->next != NULL);
    assert(new2->tail->next == NULL);
    assert(linesTB(new2) == 5);
    printf("the swapped result: \n%s\n", text);
    free(text);

    releaseTB(new2);
    printf("Test 2 passed\n");

    // Test 3 : mergeTB //tested
    printf("Test 3 : mergeTB\n");
    TB new3 = newTB("1.1 abc\n1.2 def\nxxxxx\n");
    TB new3_1 = newTB("new stuff\nblah blah blah\nqwer\n");
    TB new3_2 = newTB("second\nmerge\ntest\n");
    char* str3 = dumpTB(new3) ;
    printf("Original Tb:\n%s\n", str3) ;
    mergeTB(new3, 0, new3_1);
    char *str3_1 = dumpTB(new3);
    printf("Merged...\n%s\n", str3_1);
    mergeTB(new3, 0, new3_2);
    char *str3_2 = dumpTB(new3);
    printf("Merged again...\n%s\n", str3_2);

    free(str3) ;
    free(str3_1);
    free(str3_2);
    releaseTB (new3);
    printf("Test 3 passed\n");

    // Test 4 : pasteTB
    printf("Test 4 : pasteTB\n");
    TB new4 = newTB("qwert\nyuiop\n12345\n6789\n");
    TB new4_1 = newTB("okay\n");
    TB new4_2 = newTB("hey\nC\n");
    char *str4 = dumpTB(new4);
    printf("original text : \n%s\n",str4);

    pasteTB(new4, 0, new4_1);
    char *str4_1 = dumpTB(new4);
    printf("%s\n", str4_1);

    pasteTB(new4, 4, new4_2);
    char *str4_2 = dumpTB(new4);
    printf("%s\n", str4_2);

    free(str4);
    free(str4_1);
    free(str4_2);
    releaseTB(new4);
    releaseTB(new4_1);
    releaseTB(new4_2);

    // Test 5 : cutTB
    printf("Test 5 : cutTB\n");
    TB new5 = newTB("cut this\n");
    assert(new5->size == 1);
    TB new5_1 = cutTB(new5, 0, 0);
    assert(new5->size == 0);
    assert(new5_1->size == 1);
    TB new5_2 = newTB("This\nis\na\ncut\ntest\n");
    assert(new5_2->size == 5);
    TB new5_3 = cutTB(new5_2, 0, 4);
    assert(new5_2->size == 0);
    assert(new5_3->size == 5);
    TB new5_4 = cutTB(new5_3, 0, 2);
    assert(new5_4->size == 3);
    TB new5_5 = newTB("Test\none\ntwo\nthree\n");
    TB new5_6 = cutTB(new5_5, 0, 1);
    assert(new5_5->size == 2);
    assert(new5_6->size == 2);

    releaseTB(new5);
    releaseTB(new5_1);
    releaseTB(new5_2);
    releaseTB(new5_3);
    releaseTB(new5_4);
    releaseTB(new5_5);
    releaseTB(new5_6);
    printf("Test 5 passed\n");

    // Test 6 : copyTB
    printf("Test 6 : copyTB\n");
    TB new6 = newTB("Hey\ncode\ncopy\nthis\n");
    TB new6_1 = copyTB(new6, 0, 2);
    TB new6_2 = copyTB(new6, 0, 0);
    char *str6 = dumpTB(new6);
    printf("%s\n", str6);
    char *str6_1 = dumpTB(new6_1);
    printf("%s\n", str6_1);
    char *str6_2 = dumpTB(new6_2);
    printf("%s\n", str6_2);
    free(str6);
    free(str6_1);
    free(str6_2);
    releaseTB(new6);
    releaseTB(new6_1);
    releaseTB(new6_2);
    printf("Test 6 passed\n");

    // Test 7 : deleteTB
    printf("Test 7 :deleteTB\n");
    TB new7 = newTB("This\ntext\nis\ngoing\nto\nbe\ndeleted\n");
    printf("Calling deleteTB(tb, 0 ,1)\n");
    deleteTB(new7, 0, 1);
    assert(linesTB(new7) == 5);
    char *str7 = dumpTB(new7);
    printf("%s\n", str7);
    printf("Deleting the rest\n");

    deleteTB(new7, 0, 3);
    assert(linesTB(new7) == 1);
    char *str7_1= dumpTB(new7);
    printf("%s\n",str7_1);
    printf("Deleted up to the second last element\n");

    deleteTB(new7, 0, 0);
    assert(linesTB(new7) == 0);
    printf("Deleted the last element\n");

    free(str7);
    free(str7_1);

    releaseTB(new7);
    printf("Test 7 passed\n");


    // Test 8 : replaceText
    printf("Test 8 : replaceText\n");
    // This test covers various cases
    // when the needle is in the beginning
    // consecutive needles
    TB new8 = newTB("oltalololol_batol_tolest\n");
    replaceText(new8, "ol", "AK");
    char *str8 = dumpTB(new8);
    printf("After replacement :\n%s\n", str8);
    free(str8);
    releaseTB(new8);
    printf("Test 8 passed\n");
    printf("All White Box tests passed!\n");
    return;
}*/
