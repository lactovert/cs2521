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

void
decideDraculaMove (DracView dv)
{   
    Map g = newMap();
    Round round = giveMeTheRound(dv);
    int start = whereIs(dv, PLAYER_DRACULA);
    int conn = connections(g ,start ,PLAYER_DRACULA ,round ,true ,false ,true);
    LocationID *array = whereCanIgo(dv, &conn, true, false);
    for (int i = 0; i < TRAIL_SIZE; i ++) {
        int traps = 0;
        int vamps = 0;
        whatsThere(dv, array[i], &traps, &vamps);
        if (traps != 0 || vamps!=0) {
            continue;
        } else {
            registerBestPlay (idToAbbrev(array[i]), "wololololo");
            break;
        }
    }
    disposeMap(g);
}
