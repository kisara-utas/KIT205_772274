
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


void test_add_edge() {

	printf("TEST: add_edge inserts edges correctly...");
	Graph *g = new_graph(3);
	add_edge(g, 0, 1, 0.5f);
	add_edge(g, 0, 2, 0.9f);

	int count = 0;
	EdgeNodePtr curr = g->edges[0].head;
	while (curr) { count++; curr = curr->next; }
	assert(count == 2);
	assert(g->edges[1].head == NULL);

	free_graph(g);
	printf("PASSED\n");

}

void test_load_graph() {
	printf("TEST: load_graph reads graph from file correctly... ");
	Graph *g = load_graph("data/brain_small.txt");
	assert(g != NULL);
	assert(g->V == 8);
	assert(g->edges[0].head != NULL);
	
	free_graph(g);
	printf("PASSED\n");
}

