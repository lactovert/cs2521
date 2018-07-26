////////////////////////////////////////////////////////////////////////
// COMP2521 18x1 ... the Fury of Dracula
// GameView.c: GameView ADT implementation
//
// 2014-07-01   v1.0    Team Dracula <cs2521@cse.unsw.edu.au>
// 2017-12-01   v1.1    Team Dracula <cs2521@cse.unsw.edu.au>

#include <assert.h>
#include <err.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sysexits.h>
#include <stdio.h>

#include <string.h>


#include "Map.h"
#include "Game.h"
#include "GameView.h"
#include "Globals.h"


#define INFO_STR 7
#define ROUND_CONST 40
#define EMPTY -1
#define MAX_ENCOUNTER 4
#define ZERO 0


typedef struct _player {
    LocationID v;
    LocationID history[TRAIL_SIZE];
    int health;
} player;

struct gameView {
    Round round;
    player players[NUM_PLAYERS];
    PlayerID currentPlayer;
    int gameScore;
    LocationID traps[TRAIL_SIZE];
    LocationID imVamp[TRAIL_SIZE];
};

// helper functions prototype
static void update(LocationID id,char *abbrev, char enc[], GameView gv, PlayerID player);
static void updateHealth(LocationID id,char *abbrev, char enc[], GameView gv, PlayerID player);
static void updateLocation(GameView gv,PlayerID player, int health, char * enc);
static void updateEncounter(GameView gv, PlayerID player, char * abbrev, char enc[]);

static void shiftTrail(LocationID new, LocationID trail[]);
static void shiftTrap(LocationID traps[], char * abbrev);
static void shiftVamp(GameView gv, LocationID vamp[], char * abbrev);

static int isUnknownLoc(LocationID v);
static void doubleBack(GameView gv, char c);


// Creates a new GameView to summarise the current state of the game
GameView
newGameView (char *pastPlays, PlayerMessage messages[])
{

    GameView new;
    new = malloc(sizeof(struct gameView));
    if (new == NULL) err (EX_OSERR, "couldn't allocate GameView");

    new->round = 0;
    new->currentPlayer = new->round % 5;
    new->gameScore = GAME_START_SCORE;

    // initialize traps and immature vampires in current game to none
    // these arrays are going to be the LocationID's of traps & vamps
    for (int i = 0; i < TRAIL_SIZE; i++) {
        new->traps[i] = NOWHERE;
        new->imVamp[i] = NOWHERE;
    }

    // initialize the health and trail for all the players
    for(int i = PLAYER_LORD_GODALMING; i < NUM_PLAYERS; i++) {
        new->players[i].v = UNKNOWN_LOCATION;
        new->players[i].health = GAME_START_HUNTER_LIFE_POINTS;
        // DRACULA
        if (i == PLAYER_DRACULA) {
            new->players[i].health = GAME_START_BLOOD_POINTS;
        }
        // initialize the trail array locations with -1
        for(int j = 0; j < TRAIL_SIZE; j++) {
            new->players[i].history[j] = UNKNOWN_LOCATION;
        }
    }
    int playLength = strlen(pastPlays)+1;
    if (playLength > 0) {
        new->round = playLength/ROUND_CONST;
        char *abbrev = malloc(3 * sizeof(char));
        char *enc = malloc(4* sizeof(char));
        // playlength-1 because we count from 0;
        for (int i = 0; i < playLength-1; i+=8) {
            abbrev[0] = pastPlays[i+1];
            abbrev[1] = pastPlays[i+2];
            abbrev[2] = '\0';

            enc[0] = pastPlays[i+3];
            enc[1] = pastPlays[i+4];
            enc[2] = pastPlays[i+5];
            enc[3] = pastPlays[i+6];

            LocationID id = abbrevToID(abbrev);
            switch (pastPlays[i]) {
                // PLAYER GODALMING
                case 'G' :
                    shiftTrail(id, new->players[PLAYER_LORD_GODALMING].history);
                    new->players[PLAYER_LORD_GODALMING].v = id;
                    update(id, abbrev, enc, new, PLAYER_LORD_GODALMING);
                    break;
                // PLAYER DR SEWARD
                case 'S' :
                    shiftTrail(id, new->players[PLAYER_DR_SEWARD].history);
                    new->players[PLAYER_DR_SEWARD].v = id;
                    update(id, abbrev, enc, new, PLAYER_DR_SEWARD);
                    break;
                // PLAYER VAN HELSING
                case 'H' :
                    shiftTrail(id, new->players[PLAYER_VAN_HELSING].history);
                    new->players[PLAYER_VAN_HELSING].v = id;
                    update(id, abbrev, enc, new, PLAYER_VAN_HELSING);
                    break;
                // PLAYER MINA HARKER
                case 'M' :
                    shiftTrail(id, new->players[PLAYER_MINA_HARKER].history);
                    new->players[PLAYER_MINA_HARKER].v = id;
                    update(id, abbrev, enc, new, PLAYER_MINA_HARKER);
                    break;
                // PLAYER DRACULA
                case 'D' :
                    // if dracula's location is UNKNOWN (S?, C?, HI, or Dn)
                    if (id == NOWHERE) {
                        switch(abbrev[0]) {
                            case 'C' :
                                shiftTrail(CITY_UNKNOWN, new->players[PLAYER_DRACULA].history);
                                new->players[PLAYER_DRACULA].v = CITY_UNKNOWN;
                                break;
                            case 'S' :
                                shiftTrail(SEA_UNKNOWN, new->players[PLAYER_DRACULA].history);
                                new->players[PLAYER_DRACULA].v = SEA_UNKNOWN;
                                break;
                            case 'H' :
                                shiftTrail(HIDE, new->players[PLAYER_DRACULA].history);
                                new->players[PLAYER_DRACULA].v = HIDE;
                                break;
                            case 'D' :
                                doubleBack(new, abbrev[1]);
                                break;
                        }
                    }  else {
                        // if dracula's location is known
                        shiftTrail(id, new->players[PLAYER_DRACULA].history);
                        new->players[PLAYER_DRACULA].v = id;
                    }
                    update(id, abbrev, enc, new, PLAYER_DRACULA);
                    break;
            }
        }
        free(abbrev);
        free(enc);
    }

    return new;
}

// Frees all memory previously allocated for the GameView toBeDeleted
void
disposeGameView (GameView toBeDeleted)
{
    if (toBeDeleted == NULL)
        err(EX_OSERR, "couldn't free NULL");
    free(toBeDeleted);
    return;
}

//// Functions to return simple information 
//// about the current state of the game

// Get the current round
Round
getRound (GameView gv)
{
    if (gv == NULL)
        err(EX_OSERR, "empty game");
    return gv->round;
}

// Get the id of current player - ie whose turn is it?
PlayerID
getCurrentPlayer (GameView gv)
{
    if (gv == NULL)
        err(EX_OSERR, "empty game");
    return gv->currentPlayer;
}

// Get the current score
int
getScore (GameView gv)
{
    if (gv == NULL)
        err(EX_OSERR, "empty game");
    return gv->gameScore;
}

// Get the current health points for a given player
int
getHealth (GameView gv, PlayerID player)
{
    if (gv == NULL)
        err(EX_OSERR, "empty game");
    if ((player < 0) || (player > 4))
        err(EX_OSERR, "invalid player");
    return gv->players[player].health;
}

// Get the current location id of a given player
LocationID
getLocation (GameView gv, PlayerID player)
{
    if (gv == NULL)
        err(EX_OSERR, "empty game");
    if ((player < PLAYER_LORD_GODALMING) || (player > PLAYER_DRACULA))
        err(EX_OSERR, "invalid player");
    return gv->players[player].v;
}


//// Functions that return information about the history of the game

// Fills the trail array with the location ids of the last 6 turns
void
getHistory (GameView gv, PlayerID player, LocationID trail[TRAIL_SIZE])
{
    
    if ((player < PLAYER_LORD_GODALMING) || (player > PLAYER_DRACULA))
        err(EX_OSERR, "invalid player");
    for (int i = 0; i < TRAIL_SIZE; i++) {
        trail[i] = gv->players[player].history[i];
    }
}

//// Functions that query the map to find information about connectivity

// Returns an array of LocationIDs for all directly connected locations

LocationID *
connectedLocations (GameView gv, int *numLocations,
    LocationID from, PlayerID player, Round round,
    bool road, bool rail, bool sea)
{
    if (gv == NULL)
        err(EX_OSERR, "empty game");
    if ((player < 0) || (player > 4))
        err(EX_OSERR, "invalid player");
    if (round > getRound(gv))
        err(EX_OSERR, "invalid round");
    
    Map map = newMap();
    LocationID *conn = malloc(sizeof(LocationID) * numV(map));
    for (int i = 0; i < numV(map); i++) {
        conn[i] = EMPTY;
    }
    
    *numLocations = connections(map, from, conn, 
        player, round, road, rail, sea);
    disposeMap(map);
    
    return conn;
}


// shifts the player's location history array to the right
// 0th index is current location
static void shiftTrail(LocationID new, LocationID trail[]) {
    for (int n = TRAIL_SIZE-2; n >= 0; n--) {
        trail[n+1] = trail[n];
    }

    trail[ZERO] = new;
}

// shifts the traps array to the right
// the array stores the locationID's of each trap
// traps expire after 6 rounds, i.e. the 5th (last) index
// 0th index is recentmostly planted trap
static void shiftTrap(LocationID traps[], char * abbrev) {
    for (int n = TRAIL_SIZE-2; n >= 0; n--) {
            traps[n+1] = traps[n];
    }

    LocationID new = abbrevToID(abbrev);
    traps[ZERO] = new;
}

// shifts the immature vampire array to the right
// the array stores the locationID's of each vampire
// vampires mature after 6 rounds, i.e. the 5th (last) index
// 0th index is recentmostly planted vampire
static void shiftVamp(GameView gv, LocationID vamp[], char * abbrev) {
    if (vamp[TRAIL_SIZE-1] != NOWHERE) {
        // When the Vampire matures, deduct gameScore by 
        // SCORE_LOSS_VAMPIRE_MATURES
        gv->gameScore -= SCORE_LOSS_VAMPIRE_MATURES;
    }

    for (int n = TRAIL_SIZE-2; n >= 0; n--) {
            vamp[n+1] = vamp[n];
    }

    LocationID new = abbrevToID(abbrev);
    vamp[ZERO] = new;
}

static void removeEnc(GameView gv,LocationID id, PlayerID player) {
    for (int i = 0; i<TRAIL_SIZE; i++) {
        if (gv->imVamp[i] == id)
            gv->imVamp[i] = NOWHERE;
        if (gv->traps[i] == id) {
            gv->traps[i] = NOWHERE;
        }
    }
}

static void update (LocationID id, char *abbrev, char enc[], GameView gv, PlayerID player) {
    updateHealth(id, abbrev, enc, gv, player);
    updateLocation(gv, player, getHealth(gv, player), enc);
    updateEncounter(gv, player, abbrev, enc);
    // everytime dracula ends his turn
    // game score decreases by 1
    if (player == PLAYER_DRACULA)
        gv->gameScore -= SCORE_LOSS_DRACULA_TURN;
}

static void updateHealth(LocationID id,char *abbrev, char enc[], GameView gv, PlayerID player) {
    if (player == PLAYER_DRACULA) {
        for (int i = 0; i < MAX_ENCOUNTER; i++) {
            if(enc[i]=='H') {
                gv->players[PLAYER_DRACULA].health -= LIFE_LOSS_HUNTER_ENCOUNTER;
                gv->players[player].health -= LIFE_LOSS_DRACULA_ENCOUNTER;
            }
        }
        if (id == NOWHERE) {
            if (abbrev[0]=='S')
                gv->players[PLAYER_DRACULA].health -=  LIFE_LOSS_SEA;
        } else if (id == CASTLE_DRACULA) {
            gv->players[PLAYER_DRACULA].health +=  LIFE_GAIN_CASTLE_DRACULA;
        } else { //<<== needs to take care of score when dracula is at sea
            if (idToType(id)==SEA)
                gv->players[PLAYER_DRACULA].health -=  LIFE_LOSS_SEA;
        }
    } else {
        // if hunter is at St John St Mary with health <= 0
        // revive
        if (strcmp(abbrev, "JM") == ZERO  && getHealth(gv, player) <= ZERO) {
            gv->players[player].health = GAME_START_HUNTER_LIFE_POINTS;
        } else if (gv->players[player].history[ZERO] == gv->players[player].history[ZERO+1]) {
            if (gv->players[player].health < 9) {
                gv->players[player].health += LIFE_GAIN_REST;
            }
        }
        for (int i = 0; i < MAX_ENCOUNTER; i++) {
            switch (enc[i]) {
                case 'T' :
                    gv->players[player].health -= LIFE_LOSS_TRAP_ENCOUNTER;
                    removeEnc(gv, id, player);
                    break;
                case 'D' :
                    gv->players[PLAYER_DRACULA].health -= LIFE_LOSS_HUNTER_ENCOUNTER;
                    gv->players[player].health -= LIFE_LOSS_DRACULA_ENCOUNTER;
                    break;
                case 'V' :
                    removeEnc(gv, id, player);
                    break;
             }
        }
    }


}

static void updateLocation(GameView gv, PlayerID player, int health, char enc[]) {
    if (health <= 0 ) {
        switch (player) {
            case PLAYER_DRACULA :
                //game ends
                break;
            default :
                // hunter gets teleported to hospital
                gv->gameScore -= SCORE_LOSS_HUNTER_HOSPITAL;
                gv->players[player].health = 0;
                gv->players[player].v = ST_JOSEPH_AND_ST_MARYS;
                shiftTrail(ST_JOSEPH_AND_ST_MARYS, gv->players[player].history);
        }
    }
}

static void updateEncounter(GameView gv, PlayerID player, char * abbrev, char enc[]) {
    for (int i = 0; i < MAX_ENCOUNTER; i++) {
        switch (enc[i]) {
            case 'T' :
                shiftTrap(gv->traps, abbrev);
                break;
            case 'V' :
                shiftVamp(gv, gv->imVamp, abbrev);
                break;
        }
    }

}

// checks whether a location is known to players or not
// stops idToType from breaking
static int isUnknownLoc (LocationID v) {
    return (!(v >= ADRIATIC_SEA && v <= ZURICH));
}

//ask tutor wheter TP will add new history

void doubleBack(GameView gv, char c) {
    int n = c - '0';
    // check how many sea city gone through when double backing and deduct the dracula health
    for (int j = 0; j < n; j++) {
        if (gv->players[PLAYER_DRACULA].history[j] == SEA_UNKNOWN) {
            gv->players[PLAYER_DRACULA].health -= LIFE_LOSS_SEA;
        } else if (!(isUnknownLoc(gv->players[PLAYER_DRACULA].history[j]))) {
            if(idToType(gv->players[PLAYER_DRACULA].history[j])==SEA) {
                gv->players[PLAYER_DRACULA].health -= LIFE_LOSS_SEA;
            }
        }
    }

    switch (n) {
        case 1 :
            shiftTrail(DOUBLE_BACK_1, gv->players[PLAYER_DRACULA].history);
            break;
        case 2 :
            shiftTrail(DOUBLE_BACK_2, gv->players[PLAYER_DRACULA].history);
            break;
        case 3 :
            shiftTrail(DOUBLE_BACK_3, gv->players[PLAYER_DRACULA].history);
            break;
        case 4 :
            shiftTrail(DOUBLE_BACK_4, gv->players[PLAYER_DRACULA].history);
            break;
        case 5 :
            shiftTrail(DOUBLE_BACK_5, gv->players[PLAYER_DRACULA].history);
            break;
    }

    gv->players[PLAYER_DRACULA].v = gv->players[PLAYER_DRACULA].history[0];
}
