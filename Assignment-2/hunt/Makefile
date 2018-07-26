########################################################################
# COMP2521 18x1 // The Fury of Dracula // the Hunt
#
# hunt/Makefile: build your Dracula and Hunter AIs

CC	= gcc
CFLAGS	= -Wall -Werror -std=c99 -g
# do not change the following line
BINS	= dracula hunter
# add any other *.o files that your system requires
# (and add their dependencies below after DracView.o)
# if you're not using Map.o or Places.o, you can remove them
OBJS	= GameView.o Map.o Places.o
# add whatever system libraries you need here (e.g. -lm)
LIBS	=

all: ${BINS}

dracula: dracPlayer.o dracula.o DracView.o ${OBJS} ${LIBS}
hunter: player.o hunter.o HunterView.o ${OBJS} ${LIBS}

dracPlayer.o: player.c Game.h DracView.h dracula.h
	${CC} ${CFLAGS} -DI_AM_DRACULA -c player.c -o dracPlayer.o

player.o: player.c Game.h HunterView.h hunter.h

dracula.o: dracula.c Game.h DracView.h
hunter.o: hunter.c Game.h HunterView.h
Places.o: Places.c Places.h
Map.o: Map.c Map.h Places.h
GameView.o: GameView.c Globals.h GameView.h
HunterView.o: HunterView.c Globals.h HunterView.h
DracView.o: DracView.c Globals.h DracView.h
# if you use other ADTs, add dependencies for them here

.PHONY: clean
clean:
	-rm -f ${BINS} *.o core

