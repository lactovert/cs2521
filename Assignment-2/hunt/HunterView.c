// HunterView.c ... HunterView ADT implementation
// COMP1927 16s2 ... basic HunterView (supplied code)
// Code by TheGroup from COMP1927 14s2 (modified by gac & jas & angf)

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "Globals.h"
#include "Game.h"
#include "GameView.h"
#include "HunterView.h"
#include "Places.h"


// Representation of the Hunter's view of the game

struct hunterView {
    GameView game;
    LocationID dracTrail[TRAIL_SIZE]; // real locations
};

static void setDracTrail(char *pastPlays, LocationID *myTrail);


// Creates a new HunterView to summarise the current state of the game
HunterView newHunterView(char *pastPlays, PlayerMessage messages[])
{
    HunterView hunterView = malloc(sizeof(struct hunterView));
    hunterView->game = newGameView(pastPlays, messages);
    setDracTrail(pastPlays, hunterView->dracTrail);
    return hunterView;
}


// Frees all memory previously allocated for the HunterView toBeDeleted
void disposeHunterView(HunterView toBeDeleted)
{
    free(toBeDeleted->game);
    free(toBeDeleted);
}


//// Functions to return simple information about the current state of the game

// Get the current round
Round giveMeTheRound(HunterView currentView)
{
    return getRound(currentView->game);
}

// Get the id of current player
PlayerID whoAmI(HunterView currentView)
{
    return getCurrentPlayer(currentView->game);
}

// Get the current score
int giveMeTheScore(HunterView currentView)
{
    return getScore(currentView->game);
}

// Get the current health points for a given player
int howHealthyIs(HunterView currentView, PlayerID player)
{
    return getHealth(currentView->game, player);
}



// Get the current location id of a given player
LocationID whereIs(HunterView currentView, PlayerID player)
{
    if(player == PLAYER_DRACULA){
        return currentView->dracTrail[0];
    }
    return getLocation(currentView->game, player);
}

//// Functions that return information about the history of the game

// Fills the trail array with the location ids of the last 6 turns
void giveMeTheTrail(HunterView currentView, PlayerID player,
                    LocationID trail[TRAIL_SIZE])
{
    getHistory(currentView->game, player, trail);
}

//// Functions that query the map to find information about connectivity

// What are my possible next moves (locations)
LocationID *whereCanIgo(HunterView currentView, int *numLocations,
                        bool road, bool rail, bool sea)
{
    return whereCanTheyGo(currentView,
	                      numLocations,
	                      getCurrentPlayer(currentView->game),
	                      road, rail, sea);
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

static void removeForbiddenLocations(HunterView dv, LocationID *conns,
                     LocationID trail[TRAIL_SIZE],
                     int *numLocations)
{
    int i = 0;
    while (i < *numLocations) {
        if (whereIs(dv, PLAYER_DRACULA) != conns[i] &&
                moveInTrail(trail, conns[i])) {
            swap(i, --*numLocations, conns);
        } else {
            i++;
        }
    }
}

// What are the specified player's next possible moves
LocationID *whereCanTheyGo(HunterView currentView, int *numLocations,
                           PlayerID player, bool road, bool rail, bool sea)
{
    printf("calling conn\n");
    LocationID *validLocations = NULL;
    LocationID startLoc = whereIs(currentView,player);
    if(validPlace(startLoc) == false){
        *numLocations = 0;
        return validLocations;
    }

    Round round =getRound(currentView->game);
    // If the given player already had a turn this round, their
    // next move will be during the next round
    if (player < whoAmI(currentView)) round++;
   
    LocationID *locations =
		connectedLocations(currentView->game,
	                       numLocations,
		                   startLoc,
		                   player,
		                   round,
		                   road, rail, sea);

    if (player == PLAYER_DRACULA) {
        removeForbiddenLocations(currentView, locations, currentView->dracTrail, numLocations);
    }

    return locations;
   
}

// Sets dracula's trail to real places (resolving TP's, HI's and Dn's)
static void setDracTrail(char *pastPlays, LocationID *myTrail){
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
        else if (p[1] == 'H' && p[2] == 'I' && myTrail[0] < NUM_MAP_LOCATIONS) 
            realLoc = myTrail[0];
        else if (p[1] == 'D' && p[2] == '1' && myTrail[0] < NUM_MAP_LOCATIONS) 
            realLoc = myTrail[0];
        else if (p[1] == 'D' && p[2] == '2' && myTrail[1] < NUM_MAP_LOCATIONS) 
            realLoc = myTrail[1];
        else if (p[1] == 'D' && p[2] == '3' && myTrail[2] < NUM_MAP_LOCATIONS) 
            realLoc = myTrail[2];
        else if (p[1] == 'D' && p[2] == '4' && myTrail[3] < NUM_MAP_LOCATIONS) 
            realLoc = myTrail[3];
        else if (p[1] == 'D' && p[2] == '5' && myTrail[4] < NUM_MAP_LOCATIONS) 
            realLoc = myTrail[4];
        else {
            // must be a real location
            char place[3] = { p[1], p[2], '\0' };
            realLoc = abbrevToIDExtended(place);
            if (realLoc == NOWHERE) fprintf(stderr,"Bugger:%s\n",place);
        }
        
        for (i = TRAIL_SIZE-1; i > 0; i--) {
            myTrail[i] = myTrail[i-1];
        }
        myTrail[0] = realLoc;
    }
    return;
}

