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

// The BST itself, which contains a pointer to the root node
typedef struct BST {
	BSTNode* root; // Pointer to the root node of the BST
} BST;

// Function prototypes for BST operations
BST new_bst(); // Create a new empty BST
BSTNode* new_bst_node(char* code); // Create a new BST node with the given airport code
BST insert_bst(BST tree, char* code); // Insert a new airport code into the BST
BSTNode* find_bst(BSTNode* root, char* code); // Find a node in the BST by airport code
void print_bst(BSTNode* root); // Print the BST in-order (sorted by airport code)
void free_bst(BSTNode* root); // Free the memory used by the BST


#endif