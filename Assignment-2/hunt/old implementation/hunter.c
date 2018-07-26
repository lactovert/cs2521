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

void
decideHunterMove (HunterView hv)
{ 
    Map g = newMap();
    // Lord Godalming
    int start = whereIs(hv, PLAYER_LORD_GODALMING);
    Round round = giveMeTheRound(hv);
    int conn = connections(g, start, PLAYER_LORD_GODALMING, round, true, true,true);
    LocationID *array = whereCanIgo(hv, &conn, true, true, false);
    for (int i = 0; i < TRAIL_SIZE; i ++) {
        registerBestPlay (idToAbbrev(array[i+1]), "Go Go Go!");
        break;
    }
    
    
    // Dr Seward
    start = whereIs(hv, PLAYER_DR_SEWARD);
    round = giveMeTheRound(hv);
    conn = connections(g, start, PLAYER_DR_SEWARD, round, true, true, true);
    array = whereCanIgo(hv, &conn, true, true, false);
    for (int i = 0; i < TRAIL_SIZE; i ++) {
        registerBestPlay (idToAbbrev(array[i+1]), "Go Go Go!");
        break;
    }
    // Van Helsing
    start = whereIs(hv, PLAYER_VAN_HELSING);
    round = giveMeTheRound(hv);
    conn = connections(g, start, PLAYER_VAN_HELSING, round, true, true, true);
    array = whereCanIgo(hv, &conn, true, true, false);
    for (int i = 0; i < TRAIL_SIZE; i ++) {
        registerBestPlay (idToAbbrev(array[i+1]), "Go Go Go!");
        break;
    }
    
    // Mina Harker
    start = whereIs(hv, PLAYER_MINA_HARKER);
    round = giveMeTheRound(hv);
    conn = connections(g, start, PLAYER_MINA_HARKER, round, true, true, true);
    array = whereCanIgo(hv, &conn, true, true, false);
    for(int i = 0; i < TRAIL_SIZE; i ++) {
        registerBestPlay (idToAbbrev(array[i+1]), "Go Go Go!");
        break;
    }
    
    
    disposeMap(g);
}
