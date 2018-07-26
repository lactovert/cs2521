////////////////////////////////////////////////////////////////////////
// COMP2521 18x1 ... the Fury of Dracula
// DracView.c: the DracView ADT implementation
//
// 2014-07-01   v1.0    Team Dracula <cs2521@cse.unsw.edu.au>
// 2017-12-01   v1.1    Team Dracula <cs2521@cse.unsw.edu.au>
// Edited by : Jansen Malem    (z5141970)
//             Elena Hadinata  (z5159267)
#include <assert.h>
#include <err.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <sysexits.h>
#include <string.h>

#include "DracView.h"
#include "Game.h"
#include "GameView.h"
#include "Globals.h"
#include "Map.h" //... //if you decide to use the Map ADT

#define EMPTY -1
#define MAX_ENCOUNTER 4
#define ZERO 0
#define MAX_TRAIL_SIZE 366

struct dracView {
    GameView gv;
    LocationID traps[TRAIL_SIZE];
    LocationID imVamp[TRAIL_SIZE];
};

// Helper function prototypes
static int prevIsUnknown (LocationID v);
static LocationID deduceLoc(LocationID trail[], int i);
static int isUnknownLoc (LocationID v);
static void updateEncounter (DracView dv, char * abbrev, char enc[]);
static void shiftTrap (LocationID traps[], char * abbrev);
static void shiftVamp (LocationID vamp[], char * abbrev);

// Creates a new DracView to summarise the current state of the game
DracView
newDracView (char *pastPlays, PlayerMessage messages[])
{
    DracView new = malloc (sizeof(struct dracView));
    if (new == NULL) err (EX_OSERR, "couldn't allocate DracView)");

    new->gv = newGameView(pastPlays, messages);
    // initialize traps and immature vampires in current game to none
    for (int i = 0; i < TRAIL_SIZE; i++) {
        new->traps[i] = NOWHERE;
        new->imVamp[i] = NOWHERE;
    }

    int playLength = strlen(pastPlays)+1;
    if(playLength > 0) {
        char *abbrev = malloc(3 * sizeof(char));
        char *enc = malloc(4 * sizeof(char));
        // playlength-1 because we count from 0;
        for(int i = 0; i < playLength-1; i+=8) { // not sure wheter to use 8 or 32, 32 makes more sense but doesnt work
            if (pastPlays[i] == 'D') {
                abbrev[0] = pastPlays[i+1];
                abbrev[1] = pastPlays[i+2];
                abbrev[2] = '\0';

                enc[0] = pastPlays[i+3];
                enc[1] = pastPlays[i+4];
                enc[2] = pastPlays[i+5];
                enc[3] = pastPlays[i+6];

                updateEncounter(new, abbrev, enc);
            }
        }
        free(abbrev);
        free(enc);
    }
    return new;
}

// Frees all memory previously allocated for the DracView toBeDeleted
void
disposeDracView (DracView toBeDeleted)
{
    disposeGameView(toBeDeleted->gv);
    free(toBeDeleted);
}

//// Functions to return simple information about the current state of the game

// Get the current round
Round
giveMeTheRound (DracView dv)
{
    return getRound(dv->gv);
}

// Get the current score
int
giveMeTheScore (DracView dv)
{
    return getScore(dv->gv);
}

// Get the current health points for a given player
int
howHealthyIs (DracView dv, PlayerID player)
{
    return getHealth(dv->gv, player);
}

// Get the current location id of a given player
LocationID
whereIs (DracView dv, PlayerID player)
{
    if (player == PLAYER_DRACULA) {
        LocationID history[TRAIL_SIZE];
        for (int i = 0; i < TRAIL_SIZE; i++) {
            history[i] = UNKNOWN_LOCATION;
        }
        giveMeTheTrail(dv, player, history);
        
        return deduceLoc(history, 0);
    }
    return getLocation(dv->gv, player);
}

// If DRACULA makes special moves
// this function will reveal the exact locations corresponding
// to each move
static LocationID deduceLoc(LocationID trail[], int i) {
    LocationID id = trail[i];
    if (isUnknownLoc(id)) {
            if (id == HIDE) {
                if(!prevIsUnknown(trail[i+1]))
                    return deduceLoc(trail, i+1);
            } else if (id == DOUBLE_BACK_1) {
                if(!prevIsUnknown(trail[i+1]))
                    return deduceLoc(trail, i+1);
            } else if (id == DOUBLE_BACK_2) {
                if(!prevIsUnknown(trail[i+2]))
                    return deduceLoc(trail, i+2);
            } else if (id == DOUBLE_BACK_3) {
                if(!prevIsUnknown(trail[i+3]))
                    return deduceLoc(trail, i+3);
            } else if (id == DOUBLE_BACK_4) {
                if(!prevIsUnknown(trail[i+4]))
                    return deduceLoc(trail, i+4);
            } else if (id == DOUBLE_BACK_5) {
                if(!prevIsUnknown(trail[i+5]))
                    return deduceLoc(trail, i+5);
            } else if (id == TELEPORT) {
                return CASTLE_DRACULA;
            }
    }
    return id;
}

// Helps deduceLoc, if previous location corresponding an action
// is unknown, just return the action as the location
static int prevIsUnknown (LocationID v) {
    return (!(v != SEA_UNKNOWN && v != CITY_UNKNOWN && v != NOWHERE));
}
// checks whether a location is known to players or not
// stops idToType from breaking
static int isUnknownLoc (LocationID v) {
    return (!(v >= ADRIATIC_SEA && v <= ZURICH));
}

// Get the most recent move of a given player
void
lastMove (DracView dv, PlayerID player,
    LocationID *start, LocationID *end)
{
    LocationID history[TRAIL_SIZE];
    for (int i = 0; i < TRAIL_SIZE; i++) {
        history[i] = UNKNOWN_LOCATION;
    }
    getHistory(dv->gv, player, history);
    
    *start = history[1];
    *end = history[0];
}

// Find out what minions are placed at the specified location
void
whatsThere (DracView dv, LocationID where,
    int *numTraps, int *numVamps)
{
    *numTraps = 0;
    *numVamps = 0;
    if (where == UNKNOWN_LOCATION || idToType(where)==SEA) {
        return;
    }
    for (int i = 0; i < TRAIL_SIZE; i++) {
        if (dv->traps[i] == where) (*numTraps)++;
        if (dv->imVamp[i] == where) (*numVamps)++;
    }
    /*
    for (int i = 0; i < TRAIL_SIZE; i++) {
        printf("!!!traps: %d\n", dv->traps[i]);
    }
    for (int i = 0; i < TRAIL_SIZE; i++) {
        printf("!!!vamps: %d\n", dv->imVamp[i]);
    }*/
}

//// Functions that return information about the history of the game

// Fills the trail array with the location ids of the last 6 turns
void
giveMeTheTrail (DracView dv, PlayerID player,
    LocationID trail[TRAIL_SIZE])
{
    getHistory(dv->gv, player, trail);
    for (int i = 0; i < TRAIL_SIZE; i++) {
        trail[i] = deduceLoc(trail, i);
    }
}

//// Functions that query the map to find information about connectivity

// What are my (Dracula's) possible next moves (locations)
LocationID *
whereCanIgo (DracView dv, int *numLocations, bool road, bool sea)
{
    LocationID currLoc = whereIs(dv, PLAYER_DRACULA);
    printf("$$$$$$%s\n", idToAbbrev(currLoc));
    Round currRound = getRound(dv->gv);
    return connectedLocations(dv->gv, numLocations,
        currLoc, PLAYER_DRACULA, currRound,
        road, false, sea);
}

// What are the specified player's next possible moves
LocationID *
whereCanTheyGo (DracView dv, int *numLocations, PlayerID player,
    bool road, bool rail, bool sea)
{
    LocationID currLoc = getLocation(dv->gv, player);
    Round currRound = getRound(dv->gv);
    return connectedLocations(dv->gv, numLocations,
        currLoc, player, currRound,
        road, rail, sea);
}

// Helper functions
static void updateEncounter (DracView dv, char * abbrev, char enc[]) {
    for (int i = 0; i < MAX_ENCOUNTER; i++) {
        switch (enc[i]) {
            case 'T' :
                shiftTrap(dv->traps, abbrev);
                break;
            case 'V' :
                shiftVamp(dv->imVamp, abbrev);
                break;
        }
    }

}

static void shiftTrap (LocationID traps[], char * abbrev) {
    for (int n = TRAIL_SIZE-2; n >= 0; n--) {
            traps[n+1] = traps[n];
    }

    LocationID new = abbrevToID(abbrev);
    traps[ZERO] = new;
}

static void shiftVamp (LocationID vamp[], char * abbrev) {
    for (int n = TRAIL_SIZE-2; n >= 0; n--) {
            vamp[n+1] = vamp[n];
    }

    LocationID new = abbrevToID(abbrev);
    vamp[ZERO] = new;
}
