
#include <stdio.h>
#include <assert.h>
#include <direct.h>
#include "graph.h"
#include "dijkstra.h"
#include "lesion.h"
#include "centrality.h"
#include "experiment.h"
#include <time.h>

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
	printf(" [ PASSED ]\n");

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
	printf(" [ PASSED ]\n");

}

void test_load_graph() {
	printf("TEST: load_graph reads graph from file correctly... ");
	Graph *g = load_graph("brain_small.txt");
	assert(g != NULL);
	assert(g->V == 8);
	assert(g->edges[0].head != NULL);

	free_graph(g);
	printf(" [ PASSED ]\n");
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
	printf(" [ PASSED ]\n");
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
	printf(" [ PASSED ]\n");

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
	printf(" [ PASSED ]\n");

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
	printf(" [ PASSED ]\n");
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
	printf(" [ PASSED ]\n");


}

void test_centrality_respects_lesion() {

	printf("TEST: Centrality skips lesioned nodes");
	Graph* g = new_graph(3);

	add_edge(g, 0, 1, 1.0f);
	add_edge(g, 1, 0, 1.0f);
	add_edge(g, 1, 2, 1.0f);
	add_edge(g, 2, 1, 1.0f);

	//lesion the bridge node 1 which means 0 and 2 cant reach each other. 

	g->active[1] = 0;

	float centrality[3];
	betweenness_centrality(g, centrality);


	//no paths possible through a lesioned node
	assert(centrality[1] == 0.0f);

	free_graph(g);
	printf(" [ PASSED ]\n");
}

void test_connectivity_full() {

	printf("TEST: Fully connected graph has connectivity 1.0.."); 

	//Triangle: every node reaches every other
	Graph *g = new_graph(3);

	add_edge(g, 0, 1, 1.0f); 
	add_edge(g, 1, 0, 1.0f);
	add_edge(g, 1, 2, 1.0f);
	add_edge(g, 2, 1, 1.0f);
	add_edge(g, 0, 2, 1.0f);
	add_edge(g, 2, 0, 1.0f);

	assert(connectivity(g) == 1.0f);

	free_graph(g);
	printf(" [ PASSED ]\n");

}

void test_connectivity_drops_after_lesion() {

	printf("TEST: Lesioning a bridge node reduces connectivity");

	//Line 0 - 1 - 2. Node 1 is the bridge
	Graph* g = new_graph(3);
	add_edge(g, 0, 1, 1.0f);
	add_edge(g, 1, 0, 1.0f);
	add_edge(g, 1, 2, 1.0f);
	add_edge(g, 2, 1, 1.0f);

	float connectivity_before = connectivity(g);
	lesion_node(g, 1); //remove the bridge
	float connectivity_after = connectivity(g);

	//removing the bridge should disconnect 0 and 2
	assert(connectivity_after < connectivity_before);

	free_graph(g);
	printf(" [ PASSED ]\n");


}

void test_restore_all() {

	printf("TEST: restore all reactivates lesioned nodes");

	Graph *g = new_graph(3);
	lesion_node(g, 1);
	assert(g->active[1] == 0);
	restore_all(g);
	assert(g->active[1] == 1);

	free_graph(g);
	printf(" [ PASSED ]\n");
}

void test_cost_models_differ() {

	printf("TEST: Cost models produce different costs");

	g_cost_model = COST_RECIPROCAL;

	float recip = strength_to_cost(0.5f); // 1/0.5 = 2.0

	g_cost_model = COST_NEG_LOG;

	float neglog = strength_to_cost(0.5f); // -log(0.5) ~  0.693

	assert(recip == 2.0f);
	assert(neglog > 0.69f && neglog < 0.70f);
	assert(recip != neglog);

	g_cost_model = COST_RECIPROCAL;
	printf(" [ PASSED ]\n");


}

static void run_investigation(Graph *brain, CostModel model, const char *model_name) {

	g_cost_model = model;

	printf("\n------- %s ------\n", model_name);


	float* c = malloc(brain->V * sizeof(float));
	betweenness_centrality(brain, c);
	print_centrality_ranking(brain, c);

	free(c);

	run_lesion_experiment(brain, 5, 100);


}



int main(void) {
	
	//SECTION 1: UNIT TESTS

	printf("\n");
	printf("============================================================\n");
	printf("  %s\n", "SECTION 1: UNIT TESTS");
	printf("============================================================\n");

	printf("\n--------Graph Data Structure----------\n");	
	test_new_graph();
	test_add_edge();
	test_load_graph();
	test_in_degrees();
	

	printf("\n--------Dijkstra's Algorithm----------\n");
	test_dijkstra_simple();
	test_dijkstra_prefers_strong_path();
	test_dijkstra_unreachable();
	

	printf("\n--------Betweenness Centrality--------\n");
	test_centrality_identifies_hub();
	test_centrality_respects_lesion();
	

	printf("\n---------Lesion Simulation-------------\n");
	test_connectivity_full();
	test_connectivity_drops_after_lesion();
	test_restore_all();

	printf("\n-----------Cost Models-----------------\n");
	test_cost_models_differ();


	printf("\n****** All unit tests passed ********\n");


	// SECTION 2: BRAIN NETWORK STRUCTURE
	printf("\n");
	printf("============================================================\n");
	printf("  %s\n", "SECTION 2: BRAIN NETWORK STRUCTURE (8 REGIONS)");
	printf("============================================================\n\n");

	Graph* g = load_graph("brain_small.txt");

	if (g) {

		print_graph(g);
		free_graph(g);

	}


	// SECTION 3: LESION SIMULATION

	printf("\n");
	printf("============================================================\n");
	printf("  %s\n", "SECTION 3: LESION INVESTIGATION");
	printf("============================================================\n");

	srand((unsigned int)time(NULL));

	Graph* brain = load_graph("brain_small.txt");

	if (brain) {

		run_investigation(brain, COST_RECIPROCAL, "COST MODEL: 1 / strength");
		run_investigation(brain, COST_NEG_LOG, "COST MODEL: -log(strength) (Alternate Approach)");
		free_graph(brain);
	}

	g_cost_model = COST_RECIPROCAL;

	return 0;

}
