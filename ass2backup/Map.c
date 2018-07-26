////////////////////////////////////////////////////////////////////////
// COMP2521 18x1 ... the Fury of Dracula
// Map.c: an implementation of a Map type
// You can change this as much as you want!
//
// 2017-11-30   v1.0    Team Dracula <cs2521@cse.unsw.edu.au>

#include <assert.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>

#include "Map.h"
#include "Places.h"
#include "Queue.h"

#define TRUE 1
#define FALSE 0
typedef struct vNode *VList;
struct vNode {
    LocationID  v;    // ALICANTE, etc
    TransportID type; // ROAD, RAIL, BOAT
    VList       next; // link to next node
};

struct map {
    int nV; // #vertices
    int nE; // #edges
    VList connections[NUM_MAP_LOCATIONS]; // array of lists
};

static void addConnections(Map);
static void bfs(Map map, LocationID from, int hops, LocationID conn[], int i);

// Create a new empty graph (for a map)
// #Vertices always same as NUM_PLACES
Map
newMap (void)
{
    Map g = malloc (sizeof *g);
    if (g == NULL) err (EX_OSERR, "couldn't allocate Map");

    (*g) = (struct map){
        .nV = NUM_MAP_LOCATIONS,
        .nE = 0,
        .connections = { NULL }
    };

    addConnections (g);
    return g;
}

// Remove an existing graph
void
disposeMap (Map g)
{
    // wait, what?
    if (g == NULL) return;

    for (int i = 0; i < g->nV; i++) {
        VList curr = g->connections[i];
        while (curr != NULL) {
            VList next = curr->next;
            free (curr);
            curr = next;
        }
    }
    free (g);
}

static VList
insertVList (VList L, LocationID v, TransportID type)
{
    VList new = malloc (sizeof(struct vNode));
    if (new == NULL) err (EX_OSERR, "couldn't allocate vNode");

    (*new) = (struct vNode){
        .v = v,
        .type = type,
        .next = L
    };
    return new;
}

static int
inVList (VList L, LocationID v, TransportID type)
{
    for (VList cur = L; cur != NULL; cur = cur->next)
        if (cur->v == v && cur->type == type)
            return 1;

    return 0;
}

// Add a new edge to the Map/Graph
static void
addLink (Map g, LocationID start, LocationID end, TransportID type)
{
    assert (g != NULL);

    // don't add edges twice
    if (inVList (g->connections[start], end, type)) return;

    g->connections[start] = insertVList(g->connections[start],end,type);
    g->connections[end] = insertVList(g->connections[end],start,type);
    g->nE++;
}

static const char *
typeToString (TransportID t)
{
    switch (t) {
    case ROAD: return "road";
    case RAIL: return "rail";
    case BOAT: return "boat";
    default:   return "????";
    }
}

// Display content of Map/Graph
void
showMap (Map g)
{
    assert (g != NULL);

    printf ("V=%d, E=%d\n", g->nV, g->nE);
    for (int i = 0; i < g->nV; i++)
        for (VList n = g->connections[i]; n != NULL; n = n->next)
            printf ("%s connects to %s by %s\n",
                idToName (i), idToName (n->v), typeToString (n->type));
}

// Return count of nodes
int
numV (Map g)
{
    assert (g != NULL);
    return g->nV;
}

// Return count of edges of a particular type
int
numE (Map g, TransportID type)
{
    assert (g != NULL);
    assert (0 <= type && type <= ANY);

    int nE = 0;
    for (int i = 0; i < g->nV; i++)
        for (VList n = g->connections[i]; n != NULL; n = n->next)
            if (n->type == type || type == ANY)
                nE++;

    return nE;
}

// Add edges to Graph representing map of Europe
static void
addConnections (Map g)
{
#define IS_SENTINEL(x) ((x).v == -1 && (x).w == -1 && (x).t == ANY)
    for (int i = 0; ! IS_SENTINEL (CONNECTIONS[i]); i++)
        addLink (g, CONNECTIONS[i].v, CONNECTIONS[i].w, CONNECTIONS[i].t);
}


// Returns the number of direct connections between two nodes
// Also fills the type[] array with the various connection types
// Returns 0 if no direct connection (i.e. not adjacent in graph)
int connections(Map g, LocationID start, LocationID conn[], PlayerID player, Round round, bool road, bool rail, bool sea) {
    assert(g != NULL);
    int i = 0;
    conn[i++] = start;
    if (player == PLAYER_DRACULA) {
        for(VList curr = g->connections[start]; curr != NULL; curr = curr->next) {
            if (road == true && curr->type == ROAD && curr->v != ST_JOSEPH_AND_ST_MARYS) {
                conn[i++] = curr->v;
            }
            if (sea == true && curr->type == BOAT) {
                conn[i++] = curr->v;
                for (VList curr1 = g->connections[conn[i-1]]; curr1!=NULL; curr1= curr1->next) {
                    if (curr1->type == BOAT) {
                        conn[i] = curr1->v;
                        i++;
                    }
                }
            }
        }
        
    } else { // for hunter
        for (VList curr = g->connections[start]; curr != NULL; curr = curr->next) {
            int railHops = (round + player) % 4;
            if (railHops == 0) rail = false;
            if (road == true && curr->type == ROAD) {
                conn[i++] = curr->v;
            }
            if (rail == true && curr->type == RAIL) {
                bfs(g, curr->v, railHops, conn, i);
            }
            if (sea == true && curr->type == BOAT && idToType(start)!=SEA) {
                conn[i++] = curr->v;
                //if(idToType(curr->v)==SEA) continue;
                for (VList curr1 = g->connections[conn[i-1]]; curr1!=NULL; curr1 = curr1->next) {
                    if (curr1->type == BOAT) {
                        conn[i++] = curr1->v;
                    }
                }
            } else if (sea == true && idToType(start) == SEA) {
                conn[i++] = curr->v;
            }
        }
    }
    return i;
}

static void bfs(Map map, LocationID from, int hops, LocationID conn[], int i) {
    Queue q = newQueue();
    QueueJoin(q, from);
    
    Queue hop = newQueue();
    QueueJoin(q, hops);
    
    while (!QueueIsEmpty(q)) {
        from = QueueLeave(q);
        hops = QueueLeave(hop);
        if (hops == 0) continue;
        conn[i++] = from;
        for (VList curr = map->connections[from]; curr != NULL; curr = curr->next) {
            if (curr->type == RAIL) {
                QueueJoin(q, curr->v);
                QueueJoin(q, hops-1);
            
            }
        }
    }
    dropQueue(q);
    dropQueue(hop);
}
