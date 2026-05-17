#pragma once

#ifndef BST_H
#define BST_H

#include "linked_list.h"

// A node in a BST of airports 

typedef struct BSTNode {
	char code[4]; // Airport IATA code
	RouteList routes; // List of routes from this airport
	struct BSTNode* left; // Pointer to the left child
	struct BSTNode* right; // Pointer to the right child

} BSTNode;



#endif