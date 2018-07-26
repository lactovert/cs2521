////////////////////////////////////////////////////////////////////////
// COMP2521 18x1 ... the Fury of Dracula
// dracula.c: your "Fury of Dracula" Dracula AI
//
// 2014-07-01   v1.0    Team Dracula <cs2521@cse.unsw.edu.au>
// 2017-12-01   v1.1    Team Dracula <cs2521@cse.unsw.edu.au>

#include "DracView.h"
#include "Game.h"
#include "dracula.h"

#include "Map.h"
#include "GameView.h"

#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE !TRUE

static int isInTrail(LocationID now, LocationID trail[TRAIL_SIZE]);
static int theresAHunter (DracView dv, LocationID curr);

void
decideDraculaMove (DracView dv)
{   

    Round round = giveMeTheRound(dv);
    if (round == 0) {
        LocationID array[NUM_MAP_LOCATIONS];
        for (int i = 0; i < NUM_MAP_LOCATIONS; i++) {
            array[i] = i; 
        }
        
        LocationID *playerG;
        int gConn = 0;
        playerG = whereCanTheyGo(dv, &gConn, PLAYER_LORD_GODALMING, true, true, true);
        
        LocationID *playerS;
        int sConn = 0;
        playerS = whereCanTheyGo(dv, &sConn, PLAYER_DR_SEWARD, true, true, true);
        
        LocationID *playerH;
        int hConn = 0;
        playerH = whereCanTheyGo(dv, &hConn, PLAYER_LORD_GODALMING, true, true, true);
        
        LocationID *playerM;
        int mConn = 0;
        playerM = whereCanTheyGo(dv, &mConn, PLAYER_DR_SEWARD, true, true, true);
        
        for (int i = 0; i < NUM_MAP_LOCATIONS; i++) {
            for (int j = 0; j < gConn; j++) {
                if (array[i] == playerG[j] ||
                    array[i] == playerS[j] ||
                    array[i] == playerH[j] ||
                    array[i] == playerM[j]) continue;
            }
            if (theresAHunter(dv, array[i])) continue;
            registerBestPlay(idToAbbrev(array[i]),"Wololo!");
            return;
        }
    } else {
        int conn = 0;
        LocationID myTrail[TRAIL_SIZE] = {-1, -1, -1, -1, -1, -1};
        giveMeTheTrail(dv, PLAYER_DRACULA, myTrail);
        
        if (howHealthyIs(dv, PLAYER_DRACULA) <= 10 &&
            !isInTrail(TELEPORT, myTrail) && 
            !isInTrail(CASTLE_DRACULA, myTrail)) {
            registerBestPlay("TP", "bye bye!");
        }
        
        LocationID *array;
        array = whereCanIgo(dv, &conn, true, true);
        char *abbrev = idToAbbrev(whereIs(dv, PLAYER_DRACULA));
        for (int i = 0; i < conn; i++) {
            if (isInTrail(array[i], myTrail)==TRUE)
                continue;
            abbrev = idToAbbrev(array[i]);
            registerBestPlay (abbrev, "fangtastic!");
            return;
        }
    }
    
}

static int isInTrail(LocationID now, LocationID trail[TRAIL_SIZE]) {
    for(int i = 0; i<TRAIL_SIZE; i++) {
        if(trail[i] == now) return TRUE;
    }
    return FALSE;
}

static int theresAHunter (DracView dv, LocationID curr) {
    LocationID currG = whereIs(dv, PLAYER_LORD_GODALMING);
    LocationID currS = whereIs(dv, PLAYER_DR_SEWARD);
    LocationID currH = whereIs(dv, PLAYER_VAN_HELSING);
    LocationID currM = whereIs(dv, PLAYER_MINA_HARKER);
    
    if (curr == currG || curr == currS || curr == currH ||
        curr == currM) return TRUE;
        
    return FALSE;
}
