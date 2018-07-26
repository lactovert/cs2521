// Map.h ... interface to Map data type
// COMP1927 16s2 ... supplied code
// Code by TheGroup from COMP1927 14s2

#ifndef MAP_H
#define MAP_H

#include "Places.h"

typedef struct edge{
    LocationID  start;
    LocationID  end;
    TransportID type;
} Edge;

// graph representation is hidden 
typedef struct MapRep *Map; 

// operations on graphs 
Map  newMap();  
void disposeMap(Map g); 
void showMap(Map g); 
int  numV(Map g);
int  numE(Map g, TransportID t);
LocationID *reachableLocations(Map map, int *numLocations, LocationID from, int drac, int railLength, int road, int sea);

#endif
