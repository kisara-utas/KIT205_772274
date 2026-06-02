
#include <stdio.h>
#include <assert.h>
#include "graph.h"

void test_new_graph() {

	printf("TEST: new_graph creates graph with correct vertex count... ");
	Graph* g = new_graph(5);
	assert(g != NULL);
	assert(g->V == 5);
	for (int v = 0; v < 5; v++) {
		assert(g->edges[v].head == NULL);
		assert(g->active[v] == 1);
	}

	free_graph(g);
	printf("PASSED\n");

}