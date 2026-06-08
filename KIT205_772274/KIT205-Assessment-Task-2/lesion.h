#pragma once

#ifndef LESION_H
#define LESION_H

#include "graph.h"

/*
 * This will serve as a connectivity metric: fraction of ordered (s,t) pairs of Active vertices
 * where t is reachable from s. Returns a value in [0.0,0.1].
 * 1.0 = every active region can reach every other (fully connected).
 * Lower = network has broken into disconnected pieces
 */
float connectivity(Graph *graph);

//Lesion (deactivate) a single vertex
void lesion_node(Graph *graph, int v);

//restore all vertices to active (undo all lesions)
void restore_all(Graph *graph);


#endif