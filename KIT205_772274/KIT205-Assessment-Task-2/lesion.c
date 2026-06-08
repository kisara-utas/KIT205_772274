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