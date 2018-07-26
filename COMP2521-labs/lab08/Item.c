// Item.c ... implementation of Items
// Written by John Shepherd, May 2013

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"


// display an Item
void showItem(Item it)
{
        printf("%s",it);
}

// free memory for an Item
void dropItem(Item it)
{
        free(it);
}

// compare two Items
int cmp(Key k1, Key k2)
{
        return strcmp(k1,k2);
}

