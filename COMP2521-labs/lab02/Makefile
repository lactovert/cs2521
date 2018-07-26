# COMP2521 lab02

CC	= gcc
CFLAGS	= -Wall -Werror -std=c99 -O
LDFLAGS	= -g

all: testStack testArrayQueue testListQueue
testStack: testStack.o arrayStack.o
	$(CC) $(LDFLAGS) -o $@ $+
testArrayQueue: testQueue.o arrayQueue.o
	$(CC) $(LDFLAGS) -o $@ $+
testListQueue: testQueue.o listQueue.o
	$(CC) $(LDFLAGS) -o $@ $+

testStack.o: testStack.c Stack.h Item.h
arrayStack.o: arrayStack.c Stack.h Item.h
arrayQueue.o: arrayQueue.c Queue.h Item.h
listQueue.o: listQueue.c Queue.h Item.h
testQueue.o: testQueue.c Queue.h Item.h

.PHONY: clean
clean:
	-rm -f *.o
	-rm -f testStack testListQueue testArrayQueue
