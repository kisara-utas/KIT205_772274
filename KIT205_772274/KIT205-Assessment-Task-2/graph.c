#define _CRT_SECURE_NO_WARNINGS
#include "graph.h"

// create a new empty graph with V vertices

Graph* new_graph(int V) {

	Graph *g = malloc(sizeof(Graph));
	if (!g) return NULL;


	g->V = V;
	g->edges = malloc(V * sizeof(EdgeList));
	g->labels = malloc(V * sizeof(char *));
	g->active = malloc(V * sizeof(int));

	if (!g->edges || !g->labels || !g->active) {
		free_graph(g);
		return NULL;
	}

	for (int v = 0; v < V; v++) {
		g->edges[v].head = NULL;
		g->labels[v] = NULL;
		g->active[v] = 1; // all regions start as intact
	}

	return g;

}


void add_edge(Graph* self, int from, int to, float w) {

	EdgeNodePtr new_node = malloc(sizeof(*new_node));
	if (!new_node) return;

	new_node->edge.to_vertex = to;
	new_node->edge.weight = w;
	new_node->next = self->edges[from].head;
	self->edges[from].head = new_node;

}


/* 
 * Loading graph from file. 
 * Format:
 *  <num_vertices>
 *  <label_0> 
 *  ...
 *  <from>, <to>, <weight>
 *  ...
 * Edges added in both directions (undirected).
 */

Graph* load_graph(const char* filename) {

	FILE* file = fopen(filename, "r");

	// If file not found, try alternative paths
	if (file == NULL) {
		char buffer[256];

		// Try relative path from project directory
		snprintf(buffer, sizeof(buffer), "data/%s", filename);
		printf("Trying: %s\n", buffer);
		file = fopen(buffer, "r");

		// Try from one level up
		if (file == NULL) {
			snprintf(buffer, sizeof(buffer), "../KIT205-Assessment-Task-2/data/%s", filename);
			printf("Trying: %s\n", buffer);
			file = fopen(buffer, "r");
		}

		// Try from two levels up
		if (file == NULL) {
			snprintf(buffer, sizeof(buffer), "../../KIT205-Assessment-Task-2/data/%s", filename);
			printf("Trying: %s\n", buffer);
			file = fopen(buffer, "r");
		}

		if (file == NULL) {
			printf("Error opening file: %s (all attempts failed)\n", filename);
			return NULL;
		}
	}

	int V;
	if (fscanf(file, "%d\n", &V) != 1) {
		printf("Error reading vertex count\n");
		fclose(file);
		return NULL;
	}

	Graph* g = new_graph(V);
	if (!g) {
		fclose(file);
		return NULL;
	}


	for (int v = 0; v < V; v++) {
		char label[MAX_LABEL_LEN];
		if (fscanf(file, "%63s\n", label) == 1) {
			g->labels[v] = malloc(strlen(label) + 1);
			if (g->labels[v]) strcpy(g->labels[v], label);
		}
	}

	int from, to;
	float weight;
	while (fscanf(file, "%d, %d, %f\n", &from, &to, &weight) == 3) {
		add_edge(g, from, to, weight);
		add_edge(g, to, from, weight); // undirected
	}

	fclose(file);
	return g;

}

void print_graph(Graph* self) {
	printf("\n");
	printf("============================================================\n");
	printf("  Brain Network Graph  (%d regions)\n", self->V);
	printf("============================================================\n");

	for (int v = 0; v < self->V; v++) {
		const char* label = self->labels[v] ? self->labels[v] : "?";

		/* Region header line */
		printf("  [%d] %-16s", v, label);
		if (!self->active[v]) printf(" (LESIONED)");
		printf("\n");

		/* Connections, indented underneath */
		EdgeNodePtr curr = self->edges[v].head;
		if (!curr) {
			printf("        (no connections)\n");
		}
		while (curr) {
			int nb = curr->edge.to_vertex;
			const char* nb_label = self->labels[nb] ? self->labels[nb] : "?";
			printf("        -> %-16s (strength %.2f)\n", nb_label, curr->edge.weight);
			curr = curr->next;
		}
		printf("\n");
	}
	printf("============================================================\n\n");
}

void free_graph(Graph* self) {

	if (!self) return;
	if (self->edges) {

		for (int v = 0; v < self->V; v++) {

			EdgeNodePtr curr = self->edges[v].head;
			while (curr) {
				EdgeNodePtr tmp = curr;
				curr = curr->next;
				free(tmp);
			}

		}

		free(self->edges);

	}

	if(self->labels) {
		for (int v = 0; v < self->V; v++) {
			free(self->labels[v]);
		}

		free(self->labels);
	}

	free(self->active);
	free(self);


}