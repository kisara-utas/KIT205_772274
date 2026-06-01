// Some of this code was developed using the KIT205 Study Modules and Tutorials, StackOverflow, GeeksforGeeks, and Claude AI.

#pragma once

#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_LABEL_LEN 64

// the weight represents connection strength between brain regions (0.0 - 1.0)

typedef struct edge {
	int to_vertex;
	float weight;
} Edge;

// linked list of edges 
typedef struct edgeNode {
	Edge edge;
	struct edgeNode* next;

} *EdgeNodePtr;


typedef struct edgeList {
	EdgeNodePtr head;
} EdgeList;


typedef struct graph {
	int V;
	EdgeList *edges;
	char **labels; //brain region labels
	int *active; // 1 = region is intact, 0 = removed
} Graph;


Graph *new_graph(int V);
void  add_edge(Graph *self, int from, int to, float w);
Graph *load_graph(const char *filename);
void  free_graph(Graph *self);
void  print_graph(Graph *self);

#endif 
