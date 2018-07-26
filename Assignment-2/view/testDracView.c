////////////////////////////////////////////////////////////////////////
// COMP2521 18x1 ... the Fury of Dracula
// testDracView.c: test the DracView ADT
//
// As supplied, these are very simple tests.  You should write more!
// Don't forget to be rigorous and thorough while writing tests.
//
// 2014-07-01   v1.0    Team Dracula <cs2521@cse.unsw.edu.au>
// 2017-12-02   v1.1    Team Dracula <cs2521@cse.unsw.edu.au>
//
// Edited by : Jansen Malem    (z5141970)
//             Elena Hadinata  (z5159267)
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DracView.h"

int
main (int argc, char *arcv[])
{
    do {////////////////////////////////////////////////////////////////
        puts ("Test for basic functions, "
              "just before Dracula's first move");

        char *trail =
            "GST.... SAO.... HZU.... MBB....";
        PlayerMessage messages[] = {
            "Hello", "Rubbish", "Stuff", ""};
        DracView dv = newDracView (trail, messages);

        assert (giveMeTheRound (dv) == 0);
        assert (whereIs (dv, PLAYER_LORD_GODALMING) == STRASBOURG);
        assert (whereIs (dv, PLAYER_DR_SEWARD) == ATLANTIC_OCEAN);
        assert (whereIs (dv, PLAYER_VAN_HELSING) == ZURICH);
        assert (whereIs (dv, PLAYER_MINA_HARKER) == BAY_OF_BISCAY);
        assert (whereIs (dv, PLAYER_DRACULA) == UNKNOWN_LOCATION);
        assert (howHealthyIs (dv, PLAYER_DRACULA) ==
                GAME_START_BLOOD_POINTS);

        puts ("passed");
        disposeDracView (dv);
    } while (0);


    do {////////////////////////////////////////////////////////////////
        puts ("Test for encountering Dracula and hunter history");

        char *trail =
            "GST.... SAO.... HCD.... MAO.... DGE.... "
            "GGED... SAO.... HCD.... MAO....";
        PlayerMessage messages[] = {
            "Hello", "Rubbish", "Stuff", "", "Mwahahah",
            "Aha!", "", "", "" };
        DracView dv = newDracView (trail, messages);

        assert (giveMeTheRound (dv) == 1);
        assert (whereIs (dv, PLAYER_DRACULA) == GENEVA);
        assert (howHealthyIs (dv, PLAYER_LORD_GODALMING) == 5);
        assert (howHealthyIs (dv, PLAYER_DRACULA) == 30);
        assert (whereIs (dv, PLAYER_LORD_GODALMING) == GENEVA);

        LocationID history[TRAIL_SIZE];
        giveMeTheTrail (dv, PLAYER_DRACULA, history);
        assert (history[0] == GENEVA);
        assert (history[2] == UNKNOWN_LOCATION);

        giveMeTheTrail (dv, PLAYER_LORD_GODALMING, history);
        assert (history[0] == GENEVA);
        assert (history[1] == STRASBOURG);
        assert (history[2] == UNKNOWN_LOCATION);

        giveMeTheTrail (dv, PLAYER_DR_SEWARD, history);
        assert (history[0] == ATLANTIC_OCEAN);
        assert (history[1] == ATLANTIC_OCEAN);
        assert (history[2] == UNKNOWN_LOCATION);

        puts ("passed");
        disposeDracView (dv);
    } while (0);


    do {////////////////////////////////////////////////////////////////
        puts ("Test for Dracula leaving minions");

        char *trail =
            "GGE.... SGE.... HGE.... MGE.... DED.V.. "
            "GST.... SST.... HST.... MST.... DMNT... "
            "GST.... SST.... HST.... MST....";
        PlayerMessage messages[] = {
            "Hello", "Rubbish", "Stuff", "", "Mwahahah",
            "Aha!", "", "", "", "Drop a V",
            "Party in Strasbourg", "Party", "Party", "Party"};
        DracView dv = newDracView (trail, messages);

        int nT, nV;
        whatsThere (dv, EDINBURGH, &nT, &nV);
        assert (nT == 0 && nV == 1);
        whatsThere (dv, MANCHESTER, &nT, &nV);
        assert (nT == 1 && nV == 0);
        assert (whereIs (dv, PLAYER_DRACULA) == MANCHESTER);

        LocationID history[TRAIL_SIZE];
        giveMeTheTrail (dv, PLAYER_DRACULA, history);
        assert (history[0] == MANCHESTER);
        assert (history[1] == EDINBURGH);
        assert (history[2] == UNKNOWN_LOCATION);

        giveMeTheTrail (dv, PLAYER_MINA_HARKER, history);
        assert (history[0] == STRASBOURG);
        assert (history[1] == STRASBOURG);
        assert (history[2] == GENEVA);
        assert (history[3] == UNKNOWN_LOCATION);

        puts ("passed");
        disposeDracView (dv);
    } while (0);


    do {////////////////////////////////////////////////////////////////
        puts ("Checking Galatz road connections");
        char *trail = "GGA....";
        PlayerMessage messages[] = {"Gone to Galatz"};
        DracView dv = newDracView (trail, messages);

        int size, *edges = whereCanTheyGo (
            dv, &size, PLAYER_LORD_GODALMING, true, false, false);
        bool seen[NUM_MAP_LOCATIONS] = {false};
        for (int i = 0; i < size; i++)
            seen[edges[i]] = true;

        assert (size == 5);
        assert (seen[GALATZ]);
        assert (seen[CONSTANTA]);
        assert (seen[BUCHAREST]);
        assert (seen[KLAUSENBURG]);
        assert (seen[CASTLE_DRACULA]);

        puts ("passed");
        free (edges);
        disposeDracView (dv);
    } while (0);


    do {////////////////////////////////////////////////////////////////
        puts ("Checking Ionian Sea sea connections");
        char *trail = "GIO....";
        PlayerMessage messages[] = {"Sailing the Ionian"};
        DracView dv = newDracView (trail, messages);

        int size, *edges = whereCanTheyGo (
            dv, &size, PLAYER_LORD_GODALMING, false, false, true);
        bool seen[NUM_MAP_LOCATIONS] = {false};
        for (int i = 0; i < size; i++)
            seen[edges[i]] = true;

        assert (size == 7);
        assert (seen[IONIAN_SEA]);
        assert (seen[BLACK_SEA]);
        assert (seen[ADRIATIC_SEA]);
        assert (seen[TYRRHENIAN_SEA]);
        assert (seen[ATHENS]);
        assert (seen[VALONA]);
        assert (seen[SALONICA]);

        puts ("passed");
        free (edges);
        disposeDracView (dv);
    } while (0);


    do {////////////////////////////////////////////////////////////////
        puts ("Checking Athens rail connections (none)");

        char *trail = "GAT....";
        PlayerMessage messages[] = {"Leaving Athens by train"};
        DracView dv = newDracView (trail, messages);

        int size, *edges = whereCanTheyGo (
            dv, &size, PLAYER_LORD_GODALMING, false, true, false);
        assert (size == 1);
        assert (edges[0] == ATHENS);


        puts ("passed");
        free (edges);
        disposeDracView (dv);
    } while (0);
    
    do {////////////////////////////////////////////////////////////////
        puts ("Checking Dracula double back 2");
        char *trail = "GST.... SMA.... HSZ.... MSW.... DNP.V.. " 
                      "GCO.... SBO.... HCN.... MIR.... DBIT... " 
                      "GFR.... SBU.... HVR.... MAO.... DHIT... " 
                      "GHA.... SPA.... HCN.... MLS.... DD2T... "
                      "GNS.... SMR.... HBS.... MSN....";
 
        PlayerMessage messages[] = {"Leaving Athens by train"};
        DracView dv = newDracView (trail, messages);
        
        LocationID from;
        LocationID to;
        lastMove(dv,PLAYER_DRACULA,&from,&to);
        
        assert(from == HIDE && to == DOUBLE_BACK_2);

        assert(whereIs(dv,PLAYER_DRACULA) == BARI);
    } while (0);

    return EXIT_SUCCESS;
}
