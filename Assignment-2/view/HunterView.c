////////////////////////////////////////////////////////////////////////
// COMP2521 18x1 ... the Fury of Dracula
// HunterView.c: the HunterView ADT implementation
//
// 2014-07-01   v1.0    Team Dracula <cs2521@cse.unsw.edu.au>
// 2017-12-01   v1.1    Team Dracula <cs2521@cse.unsw.edu.au>
// Edited by : Jansen Malem    (z5141970)
//             Elena Hadinata  (z5159267)

#include <stdio.h>
#include <assert.h>
#include <err.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sysexits.h>

#include "Game.h"
#include "GameView.h"
#include "Globals.h"
#include "HunterView.h"
// #include "Map.h" ... if you decide to use the Map ADT

#define TRUE 1
#define FALSE !TRUE
#define MAX_TRAIL_SIZE 366

struct hunterView {
    GameView gv;
};

// Helper functions
static int prevIsUnknown (LocationID v);
static void initializeTrail (LocationID trail[], int size);
static LocationID deduceLoc(LocationID trail[], int i);
static int isUnknownLoc (LocationID v);
static int alreadyInTrail (LocationID curr, LocationID trail[]);

// Creates a new HunterView to summarise the current state of the game
HunterView
newHunterView (char *pastPlays, PlayerMessage messages[])
{

    HunterView new = malloc (sizeof(struct hunterView));
    if (new == NULL) err (EX_OSERR, "couldn't allocate HunterView");

    new->gv = newGameView(pastPlays, messages);

    return new;
}

// Frees all memory previously allocated for the HunterView toBeDeleted
void
disposeHunterView (HunterView toBeDeleted)
{
    disposeGameView(toBeDeleted->gv);
    free(toBeDeleted);
}

//// Functions to return simple information about the current state of the game

// Get the current round
Round
giveMeTheRound (HunterView hv)
{
    return getRound(hv->gv);
}

// Get the id of current player
PlayerID
whoAmI (HunterView hv)
{
    return getCurrentPlayer(hv->gv);
}

// Get the current score
int
giveMeTheScore (HunterView hv)
{
    return getScore(hv->gv);
}

// Get the current health points for a given player
int
howHealthyIs (HunterView hv, PlayerID player)
{
    return getHealth(hv->gv, player);
}

// Get the current location id of a given player
LocationID
whereIs (HunterView hv, PlayerID player)
{
    // if one of the hunters was at a location in DRACULA's trail
    // hunters may know where dracula's action correspond to
    if (player == PLAYER_DRACULA) {
        int deduce = FALSE;
        LocationID dracTrail[MAX_TRAIL_SIZE];
        initializeTrail(dracTrail, MAX_TRAIL_SIZE);
        giveMeTheTrail(hv, PLAYER_DRACULA, dracTrail);
        for (PlayerID i = PLAYER_LORD_GODALMING; i < NUM_PLAYERS-1; i++) {
            LocationID trail[TRAIL_SIZE];
            initializeTrail(trail, TRAIL_SIZE);
            giveMeTheTrail(hv, i, trail);
            for (int j = 0; j < TRAIL_SIZE; j++) {
                if (alreadyInTrail(trail[j], dracTrail)) {
                    deduce = TRUE;
                }
            }
        }
        if (deduce == TRUE) {
            return deduceLoc(dracTrail, 0);
        }
    }
    
    return getLocation(hv->gv, player);
}

// Everytime a trail is initialized it should be empty,
// set everything to UNKNOWN_LOCATION
static void initializeTrail (LocationID trail[], int size) {
    for (int i = 0; i < size; i++) {
        trail[i] = UNKNOWN_LOCATION;
    }
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

// Determines whether a location is already in the trail
static int alreadyInTrail (LocationID curr, LocationID trail[]) {
    for (int i = 0; i < TRAIL_SIZE; i++) {
        if (curr == trail[i]) return TRUE;
    }
    return FALSE;
}


//// Functions that return information about the history of the game

// Fills the trail array with the location ids of the last 6 turns
void
giveMeTheTrail (HunterView hv, PlayerID player,
    LocationID trail[TRAIL_SIZE])
{
    getHistory(hv->gv, player, trail);
}

//// Functions that query the map to find information about connectivity

// What are my possible next moves (locations)
LocationID *
whereCanIgo (HunterView hv, int *numLocations,
    bool road, bool rail, bool sea)
{   
    PlayerID currPlayer = whoAmI(hv);
    LocationID currLoc = whereIs(hv, currPlayer);
    Round currRound = getRound(hv->gv);
    
    return connectedLocations(hv->gv, numLocations,
        currLoc, currPlayer, currRound, road, rail, sea);
}

// What are the specified player's next possible moves
LocationID *
whereCanTheyGo (HunterView hv, int *numLocations, PlayerID player,
    bool road, bool rail, bool sea)
{
    LocationID currLoc = whereIs(hv, player);
    Round currRound = getRound(hv->gv);
    return connectedLocations(hv->gv, numLocations,
        currLoc, player, currRound,
        road, rail, sea);
}
