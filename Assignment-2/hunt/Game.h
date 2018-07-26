////////////////////////////////////////////////////////////////////////
// COMP2521 18x1 ... the Fury of Dracula
// Game.h: interface to the game engine
//
// 2012-01-01   v1.0    Team Dracula <cs2521@cse.unsw.edu.au>
// 2017-11-25   v1.1    Team Dracula <cs2521@cse.unsw.edu.au>
//
// // // // // // // // DO NOT CHANGE THIS FILE! // // // // // // // //

#ifndef GAME_H_
#define GAME_H_

#define MESSAGE_SIZE 100
#define LIMIT_LIMIT_MSECS 1500

// a type to contain a message (or taunt) provided by a player

typedef char PlayerMessage[MESSAGE_SIZE];

// registerBestPlay() registers your best move so far with the game engine.
// This overrides any previous moves provided by your player.
//
// the array message will be stored in the game history
// it must contain a null (ie '\0') with only letters, spaces, 
//   digits, and/or punctuation characters before it, as the array 
//   will be passed to printf("%s") when displaying messages to users.

void registerBestPlay (char *play, PlayerMessage message);

#endif // !defined(GAME_H_)
