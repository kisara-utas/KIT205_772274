#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Create a new empty BST
BST new_bst() {
	BST tree;
	tree.root = NULL;
	return tree;
}

// Create a new BST node with the given airport code
BSTNode* new_bst_node(char* code) {
	BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
	strcpy_s(node->code, sizeof(node->code), code);
	node->routes = new_route_list();
	node->left = NULL;
	node->right = NULL;
	return node;
}

