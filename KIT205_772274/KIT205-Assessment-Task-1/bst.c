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

// Insert a new airport code into the BST

BST insert_bst(BST tree, char* code) {
	BSTNode* new_node = new_bst_node(code);

	if (tree.root == NULL) {
		tree.root = new_node;
		return tree;
	}

	BSTNode* current = tree.root;

	while (1) {
		int cmp = strcmp(code, current->code); // Compare the new code with the current node's code
		if (cmp < 0) { // New code is less than current node's code alphabetically
			if (current->left == NULL) {
				current->left = new_node;
				break;
			}
			current = current->left;
		}
		else if (cmp > 0) { // New code is greater than current node's code alphabetically
			if (current->right == NULL) {
				current->right = new_node;
				break;
			}
			current = current->right;
		}
		else { // Duplicate code, do not insert
			free(new_node);
			break;
		}
	}

	return tree;

}

// Find an airport node in the BST by airport code

BSTNode* find_bst(BSTNode* root, char* code) {

	if (root == NULL) return NULL; // Base case: not found
	int cmp = strcmp(code, root->code); // Compare the target code with the current node's code
	if (cmp == 0) return root; // Found 
	if (cmp < 0) return find_bst(root->left, code); //  code is less than current node's code, search left subtree	
	return find_bst(root->right, code); //  code is greater than current node's code, search right subtree

}




