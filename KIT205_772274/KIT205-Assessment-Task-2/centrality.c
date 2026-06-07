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