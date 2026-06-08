#include "lesion.h"

/*
 *BFS from source, which counts how many active vertices are reachable without counjting the source
 * itself. SKips lesioned vertices entirely
 */
static int count_reachable(Graph* graph, int source) {

	int V = graph->V;
	int* visited = malloc(V * sizeof(int));

	for (int v = 0; v < V; v++) visited[v] = 0;

	//simple array based queue
	int* queue = malloc(V * sizeof(int));
	int front = 0, back = 0;

	visited[source] = 1;
	queue[back++] = source;
	int reached = 0;

	while (front < back) {

		int u = queue[front++];

		EdgeNodePtr curr = graph->edges[u].head;

		while (curr) {

			int nb = curr->edge.to_vertex;

			//only traverse to actice nodes
			if (graph->active[nb] && !visited[nb]) {

				visited[nb] = 1;
				reached++;
				queue[back++] = nb;
			}

			curr = curr->next;

		}


	}

	free(visited);
	free(queue);
	return reached;

}


float connectivity(Graph* graph) {

	int V = graph->V;

	//count active vertices
	int active_count = 0;
	for (int v = 0; v < V; v++) {

		if (graph->active[v]) active_count++;

	}

	//need atleast 2 active nodes to have any pairs
	if (active_count < 2) return 0.0f;

	// sum reachable pairs over all active sources
	long reachable_pairs = 0;
	for (int s = 0; s < V; s++) {

		if (!graph->active[s]) continue;

		reachable_pairs += count_reachable(graph, s);

	}

	//total possible ordered pairs among active nodes
	long total_pairs = (long)active_count * (active_count - 1);

	return (float)reachable_pairs / (float)total_pairs;


}