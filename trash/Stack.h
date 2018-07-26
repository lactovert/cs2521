//Stack.h
//A simple Stack Interface

typedef struct stackImp *Stack;

//Function Prototypes

Stack createStack( void );
void destroyStack( Stack stack );
Item pop( Stack stack);
void push( Stack stack, Item data);
int stackSize( Stack stack);

