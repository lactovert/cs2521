////////////////////////////////////////////////////////////////////////
// COMP2521 18x1 ... the Fury of Dracula
// Globals.h: global game definitions for "Fury of Dracula"
//
// 2014-09-22   v1.0    Team Dracula <cs2521@cse.unsw.edu.au>
// 2017-11-30   v1.1    Team Dracula <cs2521@cse.unsw.edu.au>
//
// // // // // // // // DO NOT CHANGE THIS FILE! // // // // // // // //

#ifndef GLOBALS_H_
#define GLOBALS_H_

// Globals
typedef int Round;

#define TRAIL_SIZE 6

// Players
typedef enum {
    PLAYER_LORD_GODALMING,
    PLAYER_DR_SEWARD,
    PLAYER_VAN_HELSING,
    PLAYER_MINA_HARKER,
    PLAYER_DRACULA
} PlayerID;
#define NUM_PLAYERS 5

// Score
#define GAME_START_SCORE                366
#define SCORE_LOSS_DRACULA_TURN         1
#define SCORE_LOSS_HUNTER_HOSPITAL      6
#define SCORE_LOSS_VAMPIRE_MATURES      13

// Dracula Health
#define GAME_START_BLOOD_POINTS         40
#define LIFE_LOSS_HUNTER_ENCOUNTER      10
#define LIFE_LOSS_SEA                   2
#define LIFE_GAIN_CASTLE_DRACULA        10

// Hunter Health
#define GAME_START_HUNTER_LIFE_POINTS   9
#define LIFE_LOSS_TRAP_ENCOUNTER        2
#define LIFE_LOSS_DRACULA_ENCOUNTER     4
#define LIFE_GAIN_REST                  3

#endif // !defined(GLOBALS_H_)
