
#include "dijkstra.h"

/*
 * Dijkstra's shortest path algorithm
 *
 * Finds the shortest path from a source vertex to all other vertices in a graph.
 */


void dijkstra(Graph *graph, int source, float *dist, int *prev) {


	int V = graph->V;
	int* visited = malloc(V * sizeof(int)); // Track visited vertices
	
	// Initialise distances and previous vertex arrays
	for (int v = 0; v < V; v++) {
		dist[v] = INFINITY_DIST;
		prev[v] = -1;
		visited[v] = 0; // Mark all vertices as unvisited
	}
	
	dist[source] = 0.0f; // Distance to source is 0


	// main loop to process every vertex once
	for (int count = 0; count < V; count++) {

		int u = -1;
		float min_dist = INFINITY_DIST;

		for (int v = 0; v < V; v++) {
			if (!visited[v] && graph->active[v] && dist[v] < min_dist) {
				min_dist = dist[v];
				u = v;
			}
		}

		if (u == -1) {
			break; // No more reachable vertices
		}

		visited[u] = 1; // Mark the vertex as visited

		EdgeNodePtr curr = graph->edges[u].head;
		while (curr) {
			int neighbour = curr->edge.to_vertex;
			float strength = curr->edge.weight;
			if (graph->active[neighbour] && strength > 0.0f) {
				float cost = 1.0f / strength;

				if (dist[u] + cost < dist[neighbour]) {
					dist[neighbour] = dist[u] + cost;
					prev[neighbour] = u;
				}

			}

			curr = curr->next;
		}
	}

	free(visited);


}



// print the path from source to target using the prev[] array

void print_path(Graph *graph, int *prev, float *dist, int source, int target) {

	if (dist[target] >= INFINITY_DIST) {
		printf("No path from %s to %s\n", graph->labels[source], graph->labels[target]);
		return;
	}

	int* path = malloc(graph->V * sizeof(int));
	int len = 0;
	int at = target;

	while (at != -1) {
		path[len++] = at;
		at = prev[at];
	}

	printf(" %s", graph->labels[source]);
	for (int i = len - 2; i >= 0; i--) {
		printf(" -> %s", graph->labels[path[i]]);
	}

	printf(" (total cost: %.3f)\n", dist[target]);

	free(path);
	
}


