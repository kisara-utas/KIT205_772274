#include "graph.h"

// create a new empty graph with V vertices

Graph* new_graph(int V) {

	Graph *g = malloc(sizeof(Graph));
	if (!g) return NULL;


	g->V = V;
	g->edges = malloc(V * sizeof(EdgeList));
	g->labels = malloc(V * sizeof(char *));
	g->active = malloc(V * sizeof(int));

	if (!g->edges || !g->labels || !g->active) {
		free_graph(g);
		return NULL;
	}

	for (int v = 0; v < V; v++) {
		g->edges[v].head = NULL;
		g->labels[v] = NULL;
		g->active[v] = 1; // all regions start as intact
	}

	return g;

}