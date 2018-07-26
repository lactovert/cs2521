//An array based implementation of a stack

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "Item.h"
#include "Stack.h"
#include "assert.h"

#define DEFAULT_SIZE 10

struct stackImp{
    Item * items;
    int top;
    int maxSize;
};

//A stack is created with a default initial size of 10
Stack createStack (void){
    Stack s = malloc(sizeof(struct stackImp)); 
    assert(s != NULL);
    s->items = malloc(DEFAULT_SIZE * sizeof(Item));
    assert(s->items != NULL);
    s->top = 0; 
    s->maxSize = DEFAULT_SIZE;
    return s;
}

void destroyStack(Stack stack){
    assert(stack != NULL);
    free(stack->items);
    free(stack);
}

//You need to modify this
void push (Stack stack, Item item){ 
    if(stack == NULL) abort();
    if(stack->top >= stack->maxSize) {
        int oldSize = stack->maxSize;
        stack->items = realloc(stack->items, 2 * sizeof(Item)*oldSize);
        stack->maxSize *= 2;
        assert(stack->maxSize == 2*oldSize);
    }   
    stack->items[stack->top] = item;
    stack->top++;
}

//You need to modify this
Item pop (Stack stack){ 
    if (stack == NULL) {
        printf("Stack Underflow\n");
        abort();
    }
    int max = stack->maxSize;
    int curr = stack->top-1;
    if(curr > 1){
        if (max/curr > 4 && max >= 20){
            // resize the the array to half
            stack->items = realloc(stack->items, sizeof(Item)*stack->maxSize/2);
            stack->maxSize /=2;
        }
    }

    stack->top--;
    return stack->items[stack->top];
}

int stackSize(Stack stack){
    assert(stack != NULL);
    return stack->top;
}

//You need to write these
void whiteBoxTests(void){

    printf("White box tests:\n");
    printf("Test 1 : createStack\n");
    Stack new1 = createStack();
    assert(new1!=NULL);
    assert(new1->top == 0);
    
    assert(new1->items != NULL);
    assert(new1->maxSize==DEFAULT_SIZE);
    destroyStack(new1);
    
    printf("Test 2 : push\n");
    Stack new2 = createStack();
    Item input = 17;
    push(new2, input);
    assert(new2->top == 1);
    assert(stackSize(new2) == 1);
    assert(new2->maxSize == DEFAULT_SIZE);
    assert(new2->items[0] == 17);
    destroyStack(new2);
    
    printf("Test 3 : push overflow\n");
    Stack new3 = createStack();
    for (int i = 0; i<39; i++) {
        push(new3, input);
    }
    assert(new3->top == 39);
    assert(stackSize(new3)==39);
    assert(new3->items[38]==17);
    assert(new3->maxSize==40);
    destroyStack(new3);
    
    printf("Test 4 : pop\n");
    Stack new4 = createStack();
    for (int j = 0; j<25; j++) {
        push(new4, input);
    }
    assert(new4->top == 25);
    assert(stackSize(new4) == 25);
    assert(new4->items[24] == 17);
    assert(new4->maxSize == 40);
    for (int l = 0; l<21; l++) {
        pop(new4);
    }
    assert(new4->top == 4);
    assert(stackSize(new4) == 4);
    printf("max size %d\n",new4->maxSize);
    assert(new4->maxSize == 10);
    destroyStack(new4);
    printf("All white box test passed!\n\n");
}
