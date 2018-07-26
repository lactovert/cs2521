////////////////////////////////////////////////////////////////////////
// COMP2521 18x1 ... the Fury of Dracula
// testGameView.c: test the GameView ADT
//
// As supplied, these are very simple tests.  You should write more!
// Don't forget to be rigorous and thorough while writing tests.
//
// 2014-07-01   v1.0    Team Dracula <cs2521@cse.unsw.edu.au>
// 2017-12-01   v1.1    Team Dracula <cs2521@cse.unsw.edu.au>

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "GameView.h"

int
main (int argc, char *argv[])
{
    do {////////////////////////////////////////////////////////////////
        puts ("Test basic empty initialisation");

        char *trail = "";
        PlayerMessage messages[] = {};
        GameView gv = newGameView (trail, messages);

        assert (getCurrentPlayer (gv) == PLAYER_LORD_GODALMING);
        assert (getRound (gv) == 0);
        assert (getHealth (gv, PLAYER_DR_SEWARD) ==
                GAME_START_HUNTER_LIFE_POINTS);
        assert (getHealth (gv, PLAYER_DRACULA) ==
                GAME_START_BLOOD_POINTS);
        assert (getScore (gv) == GAME_START_SCORE);
        assert (getLocation (gv, PLAYER_LORD_GODALMING) ==
                UNKNOWN_LOCATION);

        puts ("passed");
        disposeGameView (gv);
    } while (0);


    do {////////////////////////////////////////////////////////////////
        puts ("Test for Dracula trail and basic functions");

        char *trail =
            "GST.... SAO.... HZU.... MBB.... DC?....";
        PlayerMessage messages[] = {
            "Hello", "Rubbish", "Stuff", "", "Mwahahah"};
        GameView gv = newGameView (trail, messages);

        assert (getCurrentPlayer (gv) == PLAYER_LORD_GODALMING);
        assert (getRound (gv) == 1);
        assert (getLocation (gv, PLAYER_LORD_GODALMING) == STRASBOURG);
        assert (getLocation (gv, PLAYER_DR_SEWARD) == ATLANTIC_OCEAN);
        assert (getLocation (gv, PLAYER_VAN_HELSING) == ZURICH);
        assert (getLocation (gv, PLAYER_MINA_HARKER) == BAY_OF_BISCAY);
        assert (getLocation (gv, PLAYER_DRACULA) == CITY_UNKNOWN);
        assert (getHealth (gv, PLAYER_DRACULA) ==
                GAME_START_BLOOD_POINTS);

        puts ("passed");
        disposeGameView (gv);
    } while (0);


    do {////////////////////////////////////////////////////////////////
        puts ("Test for encountering Dracula and hunter history");

        char *trail =
            "GST.... SAO.... HCD.... MAO.... DGE.... "
            "GGED...";
        PlayerMessage messages[] = {
            "Hello", "Rubbish",  "Stuff", "", "Mwahahah",
            "Aha!"};
        GameView gv = newGameView (trail, messages);

        assert (getLocation (gv, PLAYER_DRACULA) == GENEVA);
        assert (getHealth (gv, PLAYER_LORD_GODALMING) == 5);
        assert (getHealth (gv, PLAYER_DRACULA) == 30);
        assert (getLocation (gv, PLAYER_LORD_GODALMING) == GENEVA);

        LocationID history[TRAIL_SIZE];
        getHistory (gv, PLAYER_DRACULA, history);
        assert (history[0] == GENEVA);
        assert (history[1] == UNKNOWN_LOCATION);

        getHistory (gv, PLAYER_LORD_GODALMING, history);
        assert (history[0] == GENEVA);
        assert (history[1] == STRASBOURG);
        assert (history[2] == UNKNOWN_LOCATION);

        getHistory (gv, PLAYER_DR_SEWARD, history);
        assert (history[0] == ATLANTIC_OCEAN);
        assert (history[1] == UNKNOWN_LOCATION);

        puts ("passed");
        disposeGameView (gv);
    } while (0);


    do {////////////////////////////////////////////////////////////////
        puts ("Test for Dracula doubling back at sea, "
              "and losing blood points (Hunter View)");

        char *trail =
            "GGE.... SGE.... HGE.... MGE.... DS?.... "
            "GST.... SST.... HST.... MST.... DD1....";
        PlayerMessage messages[] = {
            "Hello", "Rubbish", "Stuff", "", "Mwahahah",
            "Aha!", "", "", "", "Back I go"};
        GameView gv = newGameView (trail, messages);

        assert (getCurrentPlayer (gv) == 0);
        assert (getHealth (gv, PLAYER_DRACULA) ==
                GAME_START_BLOOD_POINTS - 4);
        assert (getLocation (gv, PLAYER_DRACULA) == DOUBLE_BACK_1);

        LocationID history[TRAIL_SIZE];
        getHistory (gv, PLAYER_DRACULA, history);
        assert (history[0] == DOUBLE_BACK_1);
        assert (history[1] == SEA_UNKNOWN);

        puts ("passed");
        disposeGameView (gv);
    } while (0);


    do {////////////////////////////////////////////////////////////////
        puts ("Test for Dracula doubling back at sea, "
              "and losing blood points (Drac View)");

        char *trail =
            "GGE.... SGE.... HGE.... MGE.... DEC.... "
            "GST.... SST.... HST.... MST.... DD1....";
        PlayerMessage messages[] = {
            "Hello", "Rubbish", "Stuff", "", "Mwahahah",
            "Aha!", "", "", "", "Back I go"};
        GameView gv = newGameView (trail, messages);

        assert (getCurrentPlayer (gv) == 0);
        assert (getHealth (gv, PLAYER_DRACULA) ==
                GAME_START_BLOOD_POINTS - 4);
        assert (getLocation (gv, PLAYER_DRACULA) == DOUBLE_BACK_1);

        LocationID history[TRAIL_SIZE];
        getHistory (gv, PLAYER_DRACULA, history);
        assert (history[0] == DOUBLE_BACK_1);
        assert (history[1] == ENGLISH_CHANNEL);

        puts ("passed");
        disposeGameView (gv);
    } while (0);


    do {////////////////////////////////////////////////////////////////
        puts ("Test for connections");
        char *trail = "";
        PlayerMessage messages[] = {};
        GameView gv = newGameView (trail, messages);

        do {
            puts ("Checking Galatz road connections");
            int size, *edges = connectedLocations (gv, &size,
                GALATZ, PLAYER_LORD_GODALMING, 0, true, false, false);

            bool seen[NUM_MAP_LOCATIONS] = {false};
            for (int i = 0; i < size; i++)
                seen[edges[i]] = true;

            assert (size == 5);
            assert (seen[GALATZ]);
            assert (seen[CONSTANTA]);
            assert (seen[BUCHAREST]);
            assert (seen[KLAUSENBURG]);
            assert (seen[CASTLE_DRACULA]);

            free (edges);
        } while (0);

        do {
            puts ("Checking Ionian Sea sea connections");
            int size, *edges = connectedLocations (gv, &size,
                IONIAN_SEA, PLAYER_LORD_GODALMING, 0,
                false, false, true);

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

            free (edges);
        } while (0);

        do {
            puts ("Checking Athens rail connections (none)");
            int size, *edges = connectedLocations (gv, &size,
                ATHENS, PLAYER_LORD_GODALMING, 0,
                false, true, false);

            assert (size == 1);
            assert (edges[0] == ATHENS);

            free (edges);
        } while (0);

        puts ("passed");
        disposeGameView (gv);
    } while (0);
    
    
    // Own Test 
    do {
        puts("//=================Private test==================//");
        puts("Test for player staying in the same location");
        puts("and encountering Dracula twice");
        char *trail =
            "GST.... SAO.... HCD.... MAO.... DGE.... "
            "GGED... SAO.... HCD.... MAO.... DGE.... "
            "GGED...";
            PlayerMessage messages[] = {
            "Hello", "Rubbish",  "Stuff", "", "Mwahahah",
            "Aha!"};
        GameView gv = newGameView (trail, messages);

        assert (getLocation (gv, PLAYER_DRACULA) == GENEVA);
        printf("godalming health :%d\n",getHealth (gv, PLAYER_LORD_GODALMING));
        assert (getHealth (gv, PLAYER_LORD_GODALMING) == GAME_START_HUNTER_LIFE_POINTS
            - 2 * LIFE_LOSS_DRACULA_ENCOUNTER + LIFE_GAIN_REST);
        assert (getHealth (gv, PLAYER_DRACULA) == 20);
        assert (getLocation (gv, PLAYER_LORD_GODALMING) == GENEVA);

        LocationID history[TRAIL_SIZE];
        getHistory (gv, PLAYER_DRACULA, history);
        assert (history[0] == GENEVA);
        assert (history[1] == GENEVA);
        assert (history[2] == UNKNOWN_LOCATION);

        getHistory (gv, PLAYER_LORD_GODALMING, history);
        assert (history[0] == GENEVA);
        assert (history[1] == GENEVA);
        assert (history[2] == STRASBOURG);
        assert (history[3] == UNKNOWN_LOCATION);

        getHistory (gv, PLAYER_DR_SEWARD, history);
        assert (history[0] == ATLANTIC_OCEAN);
        assert (history[1] == ATLANTIC_OCEAN);
        assert (history[2] == UNKNOWN_LOCATION);
        
        getHistory (gv, PLAYER_VAN_HELSING, history);
        assert (history[0] == CASTLE_DRACULA);
        assert (history[1] == CASTLE_DRACULA);
        assert (history[2] == UNKNOWN_LOCATION);
        
        getHistory (gv, PLAYER_MINA_HARKER, history);
        assert (history[0] == ATLANTIC_OCEAN);
        assert (history[1] == ATLANTIC_OCEAN);
        assert (history[2] == UNKNOWN_LOCATION);
        puts ("passed");
        disposeGameView (gv);
    } while(0);
    
    do {
        puts("Test for player health when idle");

        char *trail =
            "GMN.... SAM.... HMR.... MAO.... DCD.... "
            "GMN.... SAM.... HMR.... MAO.... DCD.... "
            "GMN.... SAM.... HMR.... MAO.... DCD.... "
            ;
            PlayerMessage messages[] = {
            "Hello", "Rubbish",  "Stuff", "", "Mwahahah",
            "Aha!"};
        GameView gv = newGameView (trail, messages);

        assert (getLocation (gv, PLAYER_DRACULA) == CASTLE_DRACULA);
        assert (getHealth (gv, PLAYER_LORD_GODALMING) == GAME_START_HUNTER_LIFE_POINTS);
        assert (getHealth (gv, PLAYER_DRACULA) == GAME_START_BLOOD_POINTS+ 3 * LIFE_GAIN_CASTLE_DRACULA);
        assert (getLocation (gv, PLAYER_LORD_GODALMING) == MANCHESTER);

        LocationID history[TRAIL_SIZE];
        getHistory (gv, PLAYER_DRACULA, history);
        assert (history[0] == CASTLE_DRACULA);
        assert (history[1] == CASTLE_DRACULA);
        assert (history[2] == CASTLE_DRACULA);
        assert (history[3] == UNKNOWN_LOCATION);
        
        getHistory (gv, PLAYER_LORD_GODALMING, history);
        assert (history[0] == MANCHESTER);
        assert (history[1] == MANCHESTER);
        assert (history[2] == MANCHESTER);
        assert (history[3] == UNKNOWN_LOCATION);

        getHistory (gv, PLAYER_DR_SEWARD, history);
        assert (history[0] == AMSTERDAM);
        assert (history[1] == AMSTERDAM);
        assert (history[2] == AMSTERDAM);
        assert (history[3] == UNKNOWN_LOCATION);
        
        getHistory (gv, PLAYER_VAN_HELSING, history);
        assert (history[0] == MARSEILLES);
        assert (history[1] == MARSEILLES);
        assert (history[2] == MARSEILLES);
        assert (history[3] == UNKNOWN_LOCATION);
        
        getHistory (gv, PLAYER_MINA_HARKER, history);
        assert (history[0] == ATLANTIC_OCEAN);
        assert (history[1] == ATLANTIC_OCEAN);
        assert (history[2] == ATLANTIC_OCEAN);
        assert (history[3] == UNKNOWN_LOCATION);
        
        assert(getScore(gv) == GAME_START_SCORE-3);
        assert(getRound(gv) == 3);
        
        puts ("passed");
        disposeGameView (gv);
    } while(0);
    
    do {
        puts("Test for dracula sailing sea");
        puts("Rome->Tyrrhenian Sea(-2)->Naples");

        char *trail =
            "GMN.... SAM.... HMR.... MAO.... DRO.... "
            "GMN.... SAM.... HMR.... MAO.... DNP.... "
            "GMN.... SAM.... HMR.... MAO.... DTS.... "
            "GMN.... SAM.... HMR.... MAO.... DCG.... "
            "GMN.... SAM.... HMR.... MAO.... DMS.... ";
            
            PlayerMessage messages[] = {
            "Hello", "Rubbish",  "Stuff", "", "Mwahahah",
            "Aha!"};
        GameView gv = newGameView (trail, messages);
        assert (getLocation (gv, PLAYER_DRACULA) == MEDITERRANEAN_SEA);
        assert (getHealth (gv, PLAYER_DRACULA) 
            == GAME_START_BLOOD_POINTS -2 * LIFE_LOSS_SEA);

        LocationID history[TRAIL_SIZE];
        getHistory (gv, PLAYER_DRACULA, history);
        assert (history[0] == MEDITERRANEAN_SEA);
        assert (history[1] == CAGLIARI);
        assert (history[2] == TYRRHENIAN_SEA);
        assert (history[3] == NAPLES);
        assert (history[4] == ROME);
        assert (history[5] == UNKNOWN_LOCATION);
        assert(getScore(gv) 
            == GAME_START_SCORE - 5 * SCORE_LOSS_DRACULA_TURN);
        assert(getRound(gv) == 5);
        
        puts ("passed");
        disposeGameView (gv);
    } while(0);
    return EXIT_SUCCESS;
}
