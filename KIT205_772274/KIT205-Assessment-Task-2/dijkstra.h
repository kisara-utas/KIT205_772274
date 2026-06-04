#pragma once

#ifndef DIJKSTRA_H
#define	DIJKSTRA_H

#include "graph.h"
#define INFINITY_DIST 1e9f

/*
 * Runs Dijsktra's algorithm on the given graph from source
 * It fills dist[] with the shortest-path cost from source to every vertex, 
 * and prev[] with the previous vertex in the path (-1 if none)
 * 
 * Edge cost is derived from connection strength as 1/strength, 
 * so stronger connections form shorter and cheaper paths. 
 * 
 * Lesioned vertices (active[v] == 0) are treated as unreachable
 * 
 * Caller must allocate dist[] and prev[] arrays of size graph->V

*/

void dijkstra(Graph *graph, int source, float *dist, int *prev);

// helper function to print the shortest path from source to target using prev[] array

void print_path(Graph *graph, int *prev, float *dist, int source, int target);


#endif