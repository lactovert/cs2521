int isAdjacent(Graph g, Vertex v, Vertex w) {
    assert (g!= NULL && validV(v0 && validV(w));
    VList curr = g->edges[v];
    while (curr !=NULL) {
        if(curr->v == w) return 1;
        curr = curr->next;
    }
}

int degree (Graph g, Vertex v) {
    assert (g!= NULL && validV(v0 && validV(w));
    int d = 0;
    VList curr = g->edges[v];
    while (curr !=NULL) {
        d++;
        curr = curr->next;
    }
    return d;
}
