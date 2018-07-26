// Graph.c ... implementation of Graph ADT
// Written by John Shepherd, May 2013

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "Graph.h"
#include "Queue.h"

// graph representation (adjacency matrix)
typedef struct GraphRep {
	int    nV;    // #vertices
	int    nE;    // #edges
	int  **edges; // matrix of weights (0 == no edge)
} GraphRep;
//prototype
static int isValidWeight(Graph g, Vertex v, Vertex w, int max);
static void arrayReverse (int src[], int dest[], int srcLen);

// check validity of Vertex
int validV(Graph g, Vertex v)
{
	return (g != NULL && v >= 0 && v < g->nV);
}

// make an edge
Edge mkEdge(Graph g, Vertex v, Vertex w)
{
	assert(g != NULL && validV(g,v) && validV(g,w));
	Edge new = {v,w}; // struct assignment
	return new;
}

// insert an Edge
// - sets (v,w) and (w,v)
void insertEdge(Graph g, Vertex v, Vertex w, int wt)
{
	assert(g != NULL && validV(g,v) && validV(g,w));
	if (g->edges[v][w] == 0) {
		g->edges[v][w] = wt;
		g->edges[w][v] = wt;
		g->nE++;
	}
}

// remove an Edge
// - unsets (v,w) and (w,v)
void removeEdge(Graph g, Vertex v, Vertex w)
{
	assert(g != NULL && validV(g,v) && validV(g,w));
	if (g->edges[v][w] != 0) {
		g->edges[v][w] = 0;
		g->edges[w][v] = 0;
		g->nE--;
	}
}

// create an empty graph
Graph newGraph(int nV)
{
	assert(nV > 0);
	int v, w;
	Graph new = malloc(sizeof(GraphRep));
	assert(new != 0);
	new->nV = nV; new->nE = 0;
	new->edges = malloc(nV*sizeof(int *));
	assert(new->edges != 0);
	for (v = 0; v < nV; v++) {
		new->edges[v] = malloc(nV*sizeof(int));
		assert(new->edges[v] != 0);
		for (w = 0; w < nV; w++)
			new->edges[v][w] = 0;
	}
	return new;
}

// free memory associated with graph
void dropGraph(Graph g)
{
	assert(g != NULL);
	// not needed for this lab
}

// display graph, using names for vertices
void showGraph(Graph g, char **names)
{
	assert(g != NULL);
	printf("#vertices=%d, #edges=%d\n\n",g->nV,g->nE);
	int v, w;
	for (v = 0; v < g->nV; v++) {
		printf("%d %s\n",v,names[v]);
		for (w = 0; w < g->nV; w++) {
			if (g->edges[v][w]) {
				printf("\t%s (%d)\n",names[w],g->edges[v][w]);
			}
		}
		printf("\n");
	}
}

// find a path between two vertices using breadth-first traversal
// only allow edges whose weight is less than "max"
int findPath(Graph g, Vertex src, Vertex dest, int max, int *path)
{
	assert(g != NULL);
	// pre stores the order of the visited vertex
    int *pre = malloc(sizeof(int)*g->nV);
    // st stores the distance of
    int *st = malloc(sizeof(int)*g->nV);
    // initialise both array to be empty
    for(int i = 0; i < g->nV; i++) {
        pre[i] = -1;
        st[i] = -1;
    }
    // counter is the order of vertices we visit
    int counter = 0;
    // edge to start
    Edge e = mkEdge(g, src, src);
    // visits e.w
    pre[e.w] = counter++;
    
    Queue new = newQueue();
    QueueJoin(new, e.w);
    QueueJoin(new, e.v);
    
    while(!QueueIsEmpty(new)) {
        Vertex newVert = QueueLeave(new);
        Vertex oldVert = QueueLeave(new);
        st[newVert] = oldVert;
        for (int i = 0; i < g->nV; i++) {      
            // checks if the weight of the edges is less than max  
            if(isValidWeight(g, newVert, i, max)) {
                // if the edges has not been visited then traverse
                if (pre[i]== -1) {
                    QueueJoin(new, i);
                    QueueJoin(new, newVert);
                    pre[i] = counter++;
                }
            } 
       }
    }

    int *trace = malloc(sizeof(Vertex) * counter);

    int pathNum = 0;
    // traceback the path
    int end = dest;
    while(end!=src) {
        if(trace[pathNum] == -1) {
            return 0;
        }
        trace[pathNum] = end;
        pathNum++;
        end = st[end];
    }
    trace[pathNum] = src;
    pathNum ++;
    // move the elements in trace in reverse to path
    arrayReverse (trace, path, pathNum);
    
    free(st);
    free(pre);
    free(trace);
    dropQueue(new);
    return pathNum;

}

static int isValidWeight (Graph g, Vertex v, Vertex w, int max) {
    return (g->edges[v][w] > 0) && (g->edges[v][w] <= max);
}

static void arrayReverse (int src[], int dest[], int srcLen) {
    if(srcLen == 0) return;
    int back = srcLen-1;
    int i = 0;
    while (back >= 0) {
        dest[i] = src[back--];
        i++;
    }

}
