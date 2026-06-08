#include "experiment.h"
#include "centrality.h"
#include "lesion.h"
#include <stdlib.h>


/*
 *Targeted attack: lesion the top-k most central nodes and return the connectivity
 */

static float targeted_attack(Graph *graph, int *ranking, int k) {

	restore_all(graph);

	for (int i = 0; i < k; i++) {

		if (ranking[i] != -1) {

			lesion_node(graph, ranking[i]);
		}

	}

	return connectivity(graph);

}

/*
 *  Random attack: lesion k random distinct nodes and return the connectivity
 */

static float random_attack(Graph *graph, int k) {

	restore_all(graph);
	int V = graph->V;
	int removed = 0;

	while (removed < k) {

		int v = rand() % V;

		// only count newly-removed nodes
		if (graph->active[v]) {

			lesion_node(graph, v);
			removed++;

		}

	}

	return connectivity(graph);

}

void run_lesion_experiment(Graph *graph, int max_remove, int trials) {

	int V = graph->V;

	//compute centrality once on the healthy network and then rank
	float *centrality = malloc(V * sizeof(float));
	int *ranking = malloc(V * sizeof(int));

	betweenness_centrality(graph, centrality);
	rank_by_centrality(V, centrality, ranking);

	float baseline = connectivity(graph);

	printf("\n====================Lesion Experiment: Targeted vs Random Node Removal================\n");
	printf(" Baseline connectivity (healthy): %.4f\n", baseline);
	printf(" Random results averaged over %d trials\n\n", trials);
	printf(" %-8s %-14s %-14s %-12s\n", "Removed", "Targeted", "Random(avg)", "Difference");
	printf("-----------------------------------------------------------------------------\n");


	for (int k = 1; k <= max_remove && k < V; k++) {

		//targeted: deterministic, run once
		float targeted = targeted_attack(graph, ranking, k);

		//random: average over several trials
		float random_sum = 0.0f;

		for (int t = 0; t < trials; t++) {

			random_sum += random_attack(graph, k);
		}

		float random_avg = random_sum / trials;

		printf(" %-8d %-14.4f %-14.4f %-+12.4f\n", k, targeted, random_avg, random_avg - targeted);


	}

	printf(" -----------------------------------------------------------------------------------------\n");
	printf(" (Positive difference = targeted removal hurts more)\n\n");

	restore_all(graph);
	free(centrality);
	free(ranking);




}