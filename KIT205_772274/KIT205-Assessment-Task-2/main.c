
#include <stdio.h>
#include <assert.h>
#include <direct.h>
#include "graph.h"
#include "dijkstra.h"

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
	Graph *g = load_graph("brain_small.txt");
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


void test_dijkstra_simple() {

	printf("TEST: Dijkstra finds shortest path on simple graph..");

	Graph* g = new_graph(3);
	add_edge(g, 0, 1, 1.0f);
	add_edge(g, 1, 0, 1.0f);
	add_edge(g, 1, 2, 1.0f); 
	add_edge(g, 2, 1, 1.0f); 

	float dist[3];
	int prev[3];
	dijkstra(g, 0, dist, prev);

	assert(dist[0] == 0.0f);
	assert(dist[1] == 1.0f);	
	assert(dist[2] == 2.0f);	
	assert(prev[2] == 1);

	free_graph(g);
	printf("PASSED\n");

}

void test_dijkstra_prefers_strong_path() {

	printf("TEST: Dijkstra prefers stronger (cheaper) connections...");

	// 0 to 2 directly via a weak edge (0.25 -> cost 4.0)
	// or via 1 with two strong edges (1.0 each -> cost 2.0)
	// Dijkstra should prefer the stronger path through 1

	Graph *g = new_graph(3);
	add_edge(g, 0, 2, 0.25f);
	add_edge(g, 2, 0, 0.25f);
	add_edge(g, 0, 1, 1.0f); 
	add_edge(g, 1, 0, 1.0f);
	add_edge(g, 1, 2, 1.0f);
	add_edge(g, 2, 1, 1.0f);


	float dist[3];
	int prev[3];
	dijkstra(g, 0, dist, prev);

	assert(dist[2] == 2.0f);
	assert(prev[2] == 1);

	free_graph(g);
	printf("PASSED\n");

}

void test_dijkstra_unreachable() {

	printf("TEST: Dijkstra marks unreachable nodes as infinity..");

	Graph *g = new_graph(3);
	add_edge(g, 0, 1, 1.0f); 
	add_edge(g, 1, 0, 1.0f);

	float dist[3];
	int prev[3];
	dijkstra(g, 0, dist, prev);


	assert(dist[2] >= INFINITY_DIST);
	assert(prev[2] == -1);


	free_graph(g);
	printf("PASSED\n");
}

void test_centrality_identifies_hub() {
	
	printf("TEST: Centrality identifies the bridge node");

	/*
	* node 2 is the only bridge between {0,1} and {3,4}.
	* 0-2-3
	* 1-2-4
	* Node 2 should have the highest centrality (all cross paths go through it)
	*/

	Graph *g = new_graph(5);
	add_edge(g, 0, 2, 1.0f);
	add_edge(g, 2, 0, 1.0f);
	add_edge(g, 1, 2, 1.0f);
	add_edge(g, 2, 1, 1.0f);
	add_edge(g, 2, 3, 1.0f);
	add_edge(g, 3, 2, 1.0f);
	add_edge(g, 2, 4, 1.0f);
	add_edge(g, 4, 2, 1.0f);

	float centrality[5];
	betweenness_centrality(g, centrality);

	//Node 2 must be strictly the most central
	for (int v = 0; v < 5; v++) {
		if (v != 2) assert(centrality[2] > centrality[v]);
	}

	// leaf nodes are on no through paths, so centrality becomes 0
	assert(centrality[0] == 0.0f);

	free_graph(g);
	printf("PASSED\n");


}




int main(void) {
	char cwd[256];
	_getcwd(cwd, sizeof(cwd));
	printf("Working directory: %s\n", cwd);

	printf("=== Unit tests: Graph Data Structure ===\n");	
	test_new_graph();
	test_add_edge();
	test_load_graph();
	test_in_degrees();
	printf("=== All tests passed ===\n");


	printf("=== Loading Brain Network ===\n");

	Graph *g = load_graph("brain_small.txt");

	if (g) {

		print_graph(g);
		free_graph(g);	
		
	}

	printf("=== Running Dijkstra's Algorithm ===\n");

	test_dijkstra_simple();
	test_dijkstra_prefers_strong_path();
	test_dijkstra_unreachable();

	printf("=== All Dijkstra tests passed ===\n");

	return 0;

}
