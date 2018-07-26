########################################################################
# COMP2521 18x1 // The Fury of Dracula // the View
#
# view/Makefile: build tests for {Game,Hunter,Drac}View

CC	= gcc

CFLAGS	= -Wall -Werror -std=c99 -g

BINS	= testGameView testHunterView testDracView

all: ${BINS}

testGameView: testGameView.o GameView.o Map.o Places.o Queue.o
testGameView.o: testGameView.c Globals.h Game.h 

testHunterView: testHunterView.o HunterView.o GameView.o Map.o Places.o Queue.o
testHunterView.o: testHunterView.c Map.c Places.h

testDracView: testDracView.o DracView.o GameView.o Map.o Places.o Queue.o
testDracView.o: testDracView.c Map.c Places.h

Places.o: Places.c Places.h
Map.o: Map.c Map.h Places.h Queue.h
GameView.o: GameView.c GameView.h Map.h
HunterView.o: HunterView.c HunterView.h
DracView.o: DracView.c DracView.h
Queue.o: Queue.c Queue.h Item.h

.PHONY: clean
clean:
	-rm -f ${BINS} *.o core

