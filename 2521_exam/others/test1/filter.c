#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
    int value;
    struct _node*next;
}*Node;

/*
    New node helper
*/
Node newNode(int value){
    Node n = malloc(sizeof(struct _node));
    n->value = value;
    n->next = NULL;
    return n;
}

/*
    Take in a list and a predicate function, and create a new list containing elements
    from the given list that pass the predicate.
*/
Node filter(Node l, int (*predicate)(int)){
    if(!l) return NULL;
    if(predicate(l->value)){
        Node nl = newNode(l->value);
        nl->next = filter(l->next, predicate);
        return nl;
    }
    return filter(l->next, predicate);
}

/*
    Given a list l, and a function that takes in two integers and returns an int
    and an int, fold (or reduce) the list.
    An example is:
    l = [1,2..100]
    int plus(int a, int b){return a+b;}
    fold(l, plus, 0) == 5050
    m = [1,2..10]
    int mult(int a, int b){return a*b};
    fold(m, mult, 1) == 3628800
    Folding an empty list yeilds the starting value.
*/
int fold (Node l, int (*fn) (int, int), int start){
    if(!l) return start;
    // calls the function again in the fn to get the next value
    return fn(l->value, fold(l->next, fn, start));
}

/*
    Given a list l, and a function fn, return a new list of elements that consist
    of fn applied to l's elements
    An example is:
    l=[1,2,..10]
    int square(int a) {return a*a};
    map(l,square) == [1,4,9..100]
*/
Node map(Node l, int(*fn)(int)){
    if(!l) return l;
    Node nl = newNode(fn(l->value));
    nl->next = map(l->next, fn);
    return nl;
}

int isEven(int a){ return !(a%2);}
int mult(int a, int b){ return a*b;}
int add(int a, int b){ return a+b;}
int square(int a){ return a*a;}

void printList(Node n){
    if(!n){
        printf("\n");
        return;
    }
    printf("[%d]->",n->value);
    printList(n->next);
}

Node prepend(Node l, int s){
    Node new = newNode(s);
    new->next = l;
    return new;
}

// creates in reverse lol
Node createListFromString(char *s){
    Node n = NULL;
    for(int i=0; s[i]!=0; i++){
        n = prepend(n, (int)s[i]-'0');
    }
    return n;
}

int main(){
    Node n = createListFromString("12345678");
    printList(n);

    printList(map(n, square));
    printList(filter(n, isEven));
    printf("%d\n", fold(n, add, 0));

    printf("i got lazy and didnt free everything. it is an exercise for the reader\n");
    return 0;
}
