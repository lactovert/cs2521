////////////////////////////////////////////////////////////////////////
// Runs a player's game turn ...
//
// Can produce either a Hunter player or a Dracula player
// depending on the setting of the I_AM_DRACULA #define
//
// This is a dummy version of the real player.c used when you submit
// your AIs. It is provided so that you can test whether your code is
// likely to compile ...
//
// Note that it used to drive both Hunter and Dracula AIs.  It first
// creates an appropriate view, and then invokes the relevant
// decide-my-move function, which should use the registerBestPlay()
// function to send the move back.
//
// The real player.c applies a timeout, so that it will halt the AI
// after a fixed amount of time, if it doesn't finish first.  The last
// move registered will be the one used by the game engine.  This
// version of player.c won't stop your decide-my-move function if it
// goes into an infinite loop.  Sort that out before you submit.
//
// Based on the program by David Collien, written in 2012
//
// 2017-12-04   v1.1    Team Dracula <cs2521@cse.unsw.edu.au>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Game.h"
#ifdef I_AM_DRACULA
# include "DracView.h"
# include "dracula.h"
#else
# include "HunterView.h"
# include "hunter.h"
#endif

// moves given by registerBestPlay are this long (including terminator)
#define MOVE_SIZE 3

// The minimum static globals I can get away with
static char latestPlay[MOVE_SIZE] = "";
static char latestMessage[MESSAGE_SIZE] = "";

// A pseudo-generic interface, which defines
// - a type `view_t',
// - functions `newView', `decideMove', `disposeView',
// - a trail `xtrail', and a message buffer `xmsgs'.
#ifdef I_AM_DRACULA
typedef DracView view_t;
# define newView newDracView
# define decideMove decideDraculaMove
# define disposeView disposeDracView
# define xtrail "GZA.... SED.... HZU.... MZU...."
# define xmsgs { "", "", "", "" }
#else
typedef HunterView view_t;
# define newView newHunterView
# define decideMove decideHunterMove
# define disposeView disposeHunterView
# define xtrail "GZA.... SED.... HZU...."
# define xmsgs { "", "", "" }
#endif

int
main (void)
{
    char *trail = xtrail;
    PlayerMessage msgs[] = xmsgs;
    view_t state = newView (trail, msgs);
    decideMove (state);
    disposeView (state);

    printf ("Move: %s, Message: %s\n", latestPlay, latestMessage);
    return EXIT_SUCCESS;
}

// Saves characters from play (and appends a terminator)
// and saves characters from message (and appends a terminator)
void
registerBestPlay (char *play, PlayerMessage message)
{
    strncpy (latestPlay, play, MOVE_SIZE - 1);
    latestPlay[MOVE_SIZE - 1] = '\0';

    strncpy (latestMessage, message, MESSAGE_SIZE);
    latestMessage[MESSAGE_SIZE - 1] = '\0';
}
