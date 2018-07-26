#include <stdio.h>
#include <stdlib.h>

int dfs(Graph g) {
    
    int count = 0;
    Stack s = newStack(mkEdge(0,0));
    while(!stackIsEmpty(s)) {
        Edge e = stackPop(s);
        pre[e.v] = count++;
        for(int i =0; g->adj[e.w][i]; i++) {
            if(pre[i]==-1) {
                stackPush(s, mkEdge(e.w, i));
            }
        }
    }
    free(pre);
    free(st);
}

static int dfsr(Graph g) {
    int *pre = malloc(sizeof(Vertex) * g->nV);
    int *st = malloc(sizeof(Vertex) * g->nV);
    while(isNotFull(pre)) {
        dfs on the next pre[n] = -1
        count ++
    }
    return count++
}
