#include "experiment.h"
#include "centrality.h"
#include "lesion.h"
#include <stdlib.h>


/*
 *Targeted attack: lesion the top-k most central nodes and return the connectivity
 */

static float targeted_attack(Graph* graph, int* ranking, int k) {

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

static float random_attack(Graph* graph, int k) {

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