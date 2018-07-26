FLAGS=-std=c99
testList: testLists.o lists.o
	gcc -Wall -Werror -gdwarf-2 -o testList testLists.o lists.o

lists.o: lists.c lists.h
	gcc $(FLAGS) -c lists.c

testLists.o: testLists.c lists.h
	gcc $(FLAGS) -c testLists.c

clean:
	rm testList *.o
