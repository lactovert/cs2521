////////////////////////////////////////////////////////////////////////
// COMP2521 18x1 ... the Fury of Dracula
// Map.h: an interface to a Map data type
//
// 2017-11-30   v1.0    Team Dracula <cs2521@cse.unsw.edu.au>

#ifndef MAP_H_
#define MAP_H_

#include "Places.h"
#include "Globals.h"
#include <stdbool.h>

typedef struct edge {
    LocationID start;
    LocationID end;
    TransportID type;
} edge;

// graph representation is hidden
typedef struct map *Map;

// operations on graphs
Map newMap (void);
void disposeMap (Map);
void showMap (Map);
int numV (Map);
int numE (Map, TransportID);

int connections(Map g, LocationID start, PlayerID player, Round round, bool road, bool rail, bool sea);
void connectionsArray(Map g, LocationID start, LocationID conn[], PlayerID player, Round round, bool road, bool rail, bool sea);
#endif // !defined(MAP_H_)
