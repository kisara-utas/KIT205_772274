#pragma once

#ifndef CENTRALITY_H
#define CENTRALITY_H

#include "graph.h"

/*
 * This function computes betweenness centrality for every vertex.
 * 
 * For each source s, runs Dijkstra to get shortest-path trees, then for each target t
 * reconstructs the path and increments a counter for every intermediate vertex without counting
 * the endpoints s and t
 */
void betweenness_centrality(Graph* graph, float* centrality);


//print regions ranked by centrality (highest first)
void print_centrality_ranking(Graph* graph, float* centrality);

#endif
