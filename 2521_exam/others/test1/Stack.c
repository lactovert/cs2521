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

