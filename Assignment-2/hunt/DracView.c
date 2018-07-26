// DracView.c ... DracView ADT implementation
// COMP1927 16s2 ... ... basic DracView (supplied code)
// Code by TheGroup from COMP1927 14s2 (modified by gac & jas & angf)

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Globals.h"
#include "Game.h"
#include "GameView.h"
#include "DracView.h"

#define TRUE 1
#define FALSE 0

// Representation of Dracula's view of the game


struct dracView {
    GameView game;
    LocationID myTrail[TRAIL_SIZE]; // real locations
   
};

// Sets dracula's trail to real places (resolving TP's, HI's and Dn's)
static void setMyTrail(char *pastPlays, LocationID *myTrail);


// Creates a new DracView to summarise the current state of the game
DracView newDracView(char *pastPlays, PlayerMessage messages[])
{
    DracView dracView = malloc(sizeof(struct dracView));
    dracView->game = newGameView(pastPlays, messages);
    setMyTrail(pastPlays, dracView->myTrail);
    return dracView;
}

// Frees all memory previously allocated for the DracView toBeDeleted
void disposeDracView(DracView toBeDeleted)
{
    disposeGameView(toBeDeleted->game);
    free(toBeDeleted);
}


//// Functions to return simple information about the current state of the game

// Get the current round
Round giveMeTheRound(DracView currentView)
{
    return getRound(currentView->game);
}

// Get the current score
int giveMeTheScore(DracView currentView)
{
    return getScore(currentView->game);
}

// Get the current health points for a given player
int howHealthyIs(DracView currentView, PlayerID player)
{
    return getHealth(currentView->game, player);
}

// Get the current location id of a given player
LocationID whereIs(DracView currentView, PlayerID player)
{
    if (player == PLAYER_DRACULA) {
        return currentView->myTrail[0];
    }
    
    return getLocation(currentView->game, player);
}

// Get the most recent move of a given player
void lastMove(DracView currentView, PlayerID player,
              LocationID *start, LocationID *end)
{
    LocationID trail[TRAIL_SIZE];
    if (player == PLAYER_DRACULA) {
        getHistory(currentView->game, player, trail);
        *start = trail[1];
        *end = trail[0];
       
    }
    else {
        getHistory(currentView->game, player, trail);
        *start = trail[1];
        *end = trail[0];
    }
    return;
}

// Find out what minions are placed at the specified location
void whatsThere(DracView currentView, LocationID where,
                int *numTraps, int *numVamps)
{
    int traps, vamps;
    getMinions(currentView->game, where, &traps, &vamps);
   
    *numTraps = traps;
    *numVamps = vamps;
}

//// Functions that return information about the history of the game

// Fills the trail array with the location ids of the last 6 turns
void giveMeTheTrail(DracView currentView, PlayerID player,
                    LocationID trail[TRAIL_SIZE])
{
    if(player == PLAYER_DRACULA){
        for(int i=0; i < TRAIL_SIZE; i++){
            trail[i] = currentView->myTrail[i];
        }
    } else {
        getHistory(currentView->game, player, trail);
    }
}

//// Functions that query the map to find information about connectivity

// What are my (Dracula's) possible next moves (locations)
LocationID *whereCanIgo(DracView currentView, int *numLocations, bool road, bool sea)
{
    return whereCanTheyGo(currentView,
                           numLocations,
                          PLAYER_DRACULA,
                          road, FALSE, sea);
}

static int moveInTrail(LocationID trail[TRAIL_SIZE], LocationID move)
{
    for (int i = 0; i < TRAIL_SIZE - 1; i++) {
        if (trail[i] == move) {
            return true;
        }
    }
    return false;
}

static void swap(int index1, int index2, LocationID *conns) {
    LocationID temp = conns[index1];
    conns[index1] = conns[index2];
    conns[index2] = temp;
}

static void removeForbiddenLocations(LocationID start, LocationID *conns,
                     LocationID trail[TRAIL_SIZE],
                     int *numLocations)
{
    int i = 0;
    while (i < *numLocations) {
        if (start != conns[i] &&
                moveInTrail(trail, conns[i])) {
            swap(i, --*numLocations, conns);
        } else {
            i++;
        }
    }
}


// What are the specified player's next possible moves
LocationID *whereCanTheyGo(DracView currentView, int *numLocations,
                           PlayerID player, bool road, bool rail, bool sea)
{
    LocationID *validLocations = NULL;
    LocationID startLoc = whereIs(currentView,player);
    if(validPlace(startLoc) == false){
        *numLocations = 0;
        return validLocations;
    }

    
    Round round =getRound(currentView->game);
    // The given player has already had a turn this round, their
    // next move will be during the next round
    if (player != PLAYER_DRACULA) round++;
    

    LocationID *locations =
		connectedLocations(currentView->game,
	                       numLocations,
		                   startLoc,
		                   player,
		                   round,
		                   road, rail, sea);


    if (player == PLAYER_DRACULA) {
         LocationID  unresolvedTrail[TRAIL_SIZE];
         getHistory(currentView->game,PLAYER_DRACULA,unresolvedTrail);
         removeForbiddenLocations(whereIs(currentView, PLAYER_DRACULA), locations, unresolvedTrail, numLocations);
    }

    return locations;

}

// Sets dracula's trail to real places (resolving TP's, HI's and Dn's)
static void setMyTrail(char *pastPlays, LocationID *myTrail)
{
	int i;
    for (i = 0; i < TRAIL_SIZE; i++) myTrail[i] = NOWHERE;
	char *end = pastPlays + strlen(pastPlays) - 1;
    // we jump from Drac move to Drac move
    char *p;
    for (p = &pastPlays[32]; p < end; p += 40) {
        printf("p %s\n",p);
        //if(p[0] != 'D') continue;
        // shift trail to right by one
        LocationID realLoc = NOWHERE; //= myTrail[TRAIL_SIZE];
        
        if (p[1] == 'T' && p[2] == 'P')      realLoc = CASTLE_DRACULA;
        else if (p[1] == 'H' && p[2] == 'I') realLoc = myTrail[0];
        else if (p[1] == 'D' && p[2] == '1') realLoc = myTrail[0];
        else if (p[1] == 'D' && p[2] == '2') realLoc = myTrail[1];
        else if (p[1] == 'D' && p[2] == '3') realLoc = myTrail[2];
        else if (p[1] == 'D' && p[2] == '4') realLoc = myTrail[3];
        else if (p[1] == 'D' && p[2] == '5') realLoc = myTrail[4];
        else {
            // must be a real location
            char place[3] = { p[1], p[2], '\0' };
            realLoc = abbrevToID(place);
            if (realLoc == NOWHERE) fprintf(stderr,"Bugger:%s\n",place);
        }
        
        for (i = TRAIL_SIZE-1; i > 0; i--) {
            myTrail[i] = myTrail[i-1];
        }
        myTrail[0] = realLoc;
    }
    return;
}

