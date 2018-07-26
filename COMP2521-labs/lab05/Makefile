CC=gcc
CFLAGS=-Wall -Werror -std=gnu99 -O
OBJS1=travel.o Graph.o Queue.o
OBJS2=url_file.o html.o set.o queue.o directedGraph.o stack.o
TESTS=ts tq tk tg

all: travel crawl

travel : $(OBJS1)
	$(CC) -o travel $(OBJS1)

crawl : crawl.o $(OBJS2)
	gcc -g -o crawl crawl.o $(OBJS2) -lcurl

travel.o : travel.c Graph.h
Graph.o : Graph.c Graph.h
Queue.o : Queue.c Queue.h Item.h

tests : $(TESTS)

url_file.o : url_file.c url_file.h
html.o : html.c html.h
set.o : set.c set.h
queue.o : queue.c queue.h
stack.o : stack.c stack.h
directedGraph.o : directedGraph.c directedGraph.h

ts : ts.o set.o
	gcc -o ts ts.o set.o
ts.o : ts.c set.h

tq : tq.o queue.o
	gcc -o tq tq.o queue.o
tq.o : tq.c queue.h

tk : tk.o stack.o
	gcc -o tk tk.o stack.o
tk.o : tk.c stack.h

tg : tg.o directedGraph.o
	gcc -o tg tg.o directedGraph.o
tg.o : tg.c graph.h

clean :
	rm -f travel crawl *.o core *.dSYM  $(TESTS)
