CC=gcc
CFLAGS=-Wall -Werror -std=gnu99

all: words words2 mkwords

words: words.o Tree.o Item.o
	$(CC) $(CFLAGS) -o words words.o Tree.o Item.o

words2: words2.o HashTable.o List.o Item.o
	$(CC) $(CFLAGS) -pg -o words2 words2.o HashTable.o List.o Item.o

mkwords: mkwords.c
	$(CC) -Wall -Werror -o mkwords mkwords.c

words.o: words.c Tree.h Item.h

tree.o: Tree.c Tree.h Item.h

words2.o: words2.c HashTable.h Item.h
	$(CC) $(CFLAGS)  -pg -c words2.c

HashTable.o: HashTable.c HashTable.h Item.h List.h
	$(CC) $(CFLAGS)  -pg -c HashTable.c

List.o: List.c Item.h List.h
	$(CC) $(CFLAGS)  -pg -c List.c

Item.o: Item.c Item.h
	$(CC) $(CFLAGS)  -pg -c Item.c


clobber: clean
	rm -f words words2 mkwords
clean:
	rm -f core *.o
