////////////////////////////////////////////////////////////////////////
// COMP2521 18x1 ... the Fury of Dracula
// hunter.c: your "Fury of Dracula" hunter AI.
//
// 2014-07-01   v1.0    Team Dracula <cs2521@cse.unsw.edu.au>
// 2017-12-01   v1.1    Team Dracula <cs2521@cse.unsw.edu.au>

#include "Game.h"
#include "HunterView.h"
#include "hunter.h"

#include "Map.h"

#include <stdlib.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define MAX_CONN 20

// prototypes of helper functions
static int canChaseDrac(HunterView hv, LocationID array[],int conn, LocationID poss[]);
static void initializeTrail (LocationID trail[], int size);
static int theresAHunter (HunterView hv, LocationID curr);

void
decideHunterMove (HunterView hv)
{
    PlayerID player = whoAmI(hv);
    Round round = giveMeTheRound(hv);
    if(round == 0) {
        char *abbrev;
        // in circle 1
        if(player == PLAYER_LORD_GODALMING) abbrev = "BD";
        // circle 2
        if(player == PLAYER_DR_SEWARD) abbrev = "CA";
        // circle 3
        if(player == PLAYER_VAN_HELSING) abbrev = "ST";
        // circle 4
        if(player == PLAYER_MINA_HARKER) abbrev = "KL";
        registerBestPlay(abbrev, "Hello World??");
        round++;
    } else {
        int conn = 0;
        // array containing the trail of the player just to avoid
        // going to the same place again and again
        LocationID trail[TRAIL_SIZE];
        initializeTrail(trail, TRAIL_SIZE);
        // array containing all the possible connected city from dracula
        // current location
        LocationID poss[MAX_CONN];
        initializeTrail(poss, MAX_CONN);
        // initialise the array containing the locations that
        // the hunter is direcly connected to
        giveMeTheTrail(hv, whoAmI(hv), trail);
        LocationID *array = whereCanIgo(hv, &conn, true, true, true);

        LocationID drac = whereIs(hv, PLAYER_DRACULA);
        LocationID hunter = whereIs(hv, whoAmI(hv));
        if(player != PLAYER_MINA_HARKER) {
            // if its not mina harkers turn
            // check whether hunter can chase dracula
            if (drac >= MIN_MAP_LOCATION && drac <= MAX_MAP_LOCATION) {
                // flag that determines whether the hunter
                // can chase dracula
                int c = canChaseDrac(hv, array, conn, poss);
                if (c != -1) {
                    registerBestPlay(idToAbbrev(array[c]), "chasing");
                    return;
                } else {
                    // when health drops below 4, rest
                    if (howHealthyIs(hv, whoAmI(hv)) <= 3) {
                        registerBestPlay(idToAbbrev(hunter), "rest");
                    } else {
                        registerBestPlay
                            (idToAbbrev(array[rand()%conn]), "test");
                    }
                }
            } else {
                // if hunter cant chase dracula
                // the proceed to travel to the connected locations in random
                if (howHealthyIs(hv, whoAmI(hv)) <= 3) {
                    registerBestPlay(idToAbbrev(hunter), "rest");
                } else {
                    for(int i=0;;i++) {
                        if(theresAHunter(hv, array[rand()%conn])) {
                            registerBestPlay
                                (idToAbbrev(array[rand()%conn]), "test");
                            break;
                        }
                    }
                    return;
                }
            }
        } else {
            // if mina harker's job is to go around
            // KLAUSENBURG, CASTLE_DRACULA, and GALATZ
            if(whereIs(hv, PLAYER_MINA_HARKER)==KLAUSENBURG) {
                registerBestPlay("CD","Merry go round!");
                return;
            } else if(whereIs(hv, PLAYER_MINA_HARKER)==CASTLE_DRACULA){
                registerBestPlay("GA","Merry go round!");
                return;
            } else if(whereIs(hv, PLAYER_MINA_HARKER)==GALATZ){
                registerBestPlay("KL","Merry go round!");
                return;
            } else {
                // special case if mina harker dies, then she
                // will travel randomly
                registerBestPlay(idToAbbrev(array[rand()%conn]), "test");
                return;
            }
        }
    }
}


// return index if we can possibly chase the drac
// return -1 if not
// fills the poss array with possible locationIDs
static int canChaseDrac(HunterView hv, LocationID array[], int conn, LocationID poss[]) {
    LocationID drac = whereIs(hv, PLAYER_DRACULA);
    if (!(drac >= MIN_MAP_LOCATION && drac <= MAX_MAP_LOCATION))
        return -1;


    // c will contain the number of locations dracula can go to
    int c = 0;
    poss = whereCanTheyGo(hv, &c ,
                           PLAYER_DRACULA, true, false, true);
    for (int i = 0; i < conn; i++) {
        if (array[i] == drac)
            return i;
        for (int j = 0; j < c; j++) {
            if (array[i] == poss[j] && 
                (drac >= MIN_MAP_LOCATION && drac <= MAX_MAP_LOCATION))
                return i;
        }
    }
    return -1;
}
// set the elements in the trail array to -1
static void initializeTrail(LocationID trail[], int size) {
    for (int i = 0; i < size; i++)
        trail[i] = -1;
}
// to check whether there is a hunter in a particular city
static int theresAHunter (HunterView hv, LocationID curr) {
    LocationID currG = whereIs(hv, PLAYER_LORD_GODALMING);
    LocationID currS = whereIs(hv, PLAYER_DR_SEWARD);
    LocationID currH = whereIs(hv, PLAYER_VAN_HELSING);
    LocationID currM = whereIs(hv, PLAYER_MINA_HARKER);
    
    if (curr == currG || curr == currS || curr == currH ||
        curr == currM) return TRUE;
        
    return FALSE;
}

