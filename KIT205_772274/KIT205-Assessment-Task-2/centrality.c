#include "centrality.h"
#include "dijkstra.h"

void betweenness_centrality(Graph* graph, float* centrality) {

	int V = graph->V;

	//start all counts at 0
	for (int v = 0; v < V; v++) {

		centrality[v] = 0.0f;

	}

	float *dist = malloc(V * sizeof(float));
	int   *prev = malloc(V * sizeof(int));

	//Run shortest paths from every active source

	for (int s = 0; s < V; s++) {

		if (!graph->active[s]) {

			continue;
			
		}

		dijkstra(graph, s, dist, prev);

		// for every target, trace the path backwards and credit intermediates

		for (int t = 0; t < V; t++) {

			if (t == s || !graph->active[t]) continue;
			if (dist[t] >= INFINITY_DIST) continue;

			int at = prev[t];
			while (at != -1 && at != s) {
				centrality[at] += 1.0f;
				at = prev[at];
			}


		}


	}

	free(dist);
	free(prev);

}

//Simple selection style print
void print_centrality_ranking(Graph *graph, float *centrality) {

	int V = graph->V;
	int *printed = malloc(V * sizeof(int));
	for (int v = 0; v < V; v++) printed[v] = 0;

	printf("\n====Betweenness Centrality Ranking====\n");
	printf("(higher = more critical relay region)\n\n");

	for (int rank = 0; rank < V; rank++) {

		int best = -1;
		float best_val = -1.0f;
		for (int v = 0; v < V; v++) {

			if (!printed[v] && centrality[v] > best_val) {

				best_val = centrality[v];
				best = v;
			}


		}

		if (best == -1) break;

		printed[best] = 1;

		printf(" %2d. %-16s %.1f\n", rank + 1,
			graph->labels[best] ? graph->labels[best] : "?",
			centrality[best]);

	}

	printf("\n");
	free(printed);
}