#pragma once


#ifndef EXPERIMENT_H
#define EXPERIMEMT_H

#include "graph.h"

//Runs the targeted-vs-random lesion experiment

void run_lesion_experiment(Graph* graph, int max_remove, int trials);


#endif 
