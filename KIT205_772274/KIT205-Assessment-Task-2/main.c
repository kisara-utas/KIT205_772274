
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


void test_in_degrees() {
	printf("TEST: in_degrees calculation ");
	Graph *g = new_graph(3);
	add_edge(g, 0, 1, 1.0f);
	add_edge(g, 0, 2, 1.0f);
	add_edge(g, 1, 2, 1.0f);

	int in_degree[3] = { 0, 0, 0 };
	for (int v = 0; v < g->V; v++) {

		EdgeNodePtr curr = g->edges[v].head;
		while (curr) {
			in_degree[curr->edge.to_vertex]++;
			curr = curr->next;
		}

	}

	assert(in_degree[0] == 0);
	assert(in_degree[1] == 1);
	assert(in_degree[2] == 2);	

	free_graph(g);
	printf("PASSED\n");
}


int main(void) {
	printf("=== Unit tests: Graph Data Structure ===\n");	
	test_new_graph();
	test_add_edge();
	test_load_graph();
	test_in_degrees();
	printf("=== All tests passed ===\n");


	printf("=== Loading Brain Network ===\n");

	Graph *g = load_graph("data/brain_small.txt");

	if (g) {

		print_graph(g);
		free_graph(g);	
		
	}

	return 0;

}
