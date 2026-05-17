#include "avl.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// create a new empty AVL Tree

AVLTree new_avl_tree() {
	AVLTree tree;
	tree.root = NULL;
	return tree;
}

// create a new AVL node with the given destination

AVLNode* new_avl_node(char* destination) {


	AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
	strcpy_s(node->destination, 4, destination);
	node->height = 1; // new node is initially added at leaf position
	node->left = NULL;
	node->right = NULL;
	return node;

}


// get the height of the node 

int get_height(AVLNode* node) {

	if (node == NULL) return 0;
	return node->height;
}


// get balance factor of a node

int get_balance(AVLNode* node) {


	if (node == NULL) return 0;
	return get_height(node->left) - get_height(node->right);
}

// helper function to get maximum between two integers
int max_int(int a, int b) {
	return (a > b) ? a : b;
}

// right rotate around node y

AVLNode* right_rotate(AVLNode* y) {
	AVLNode* x = y->left;
	AVLNode* T2 = x->right;

	
	x->right = y;
	y->left = T2;

	
	y->height = max_int(get_height(y->left), get_height(y->right)) + 1;
	x->height = max_int(get_height(x->left), get_height(x->right)) + 1;


	return x;
}

// left roate around node x

AVLNode* left_rotate(AVLNode* x) {
	AVLNode* y = x->right;
	AVLNode* T2 = y->left;

	
	y->left = x;
	x->right = T2;

	
	x->height = max_int(get_height(x->left), get_height(x->right)) + 1;
	y->height = max_int(get_height(y->left), get_height(y->right)) + 1;

	
	return y;
}

// insert a destination into the AVL tree 

AVLNode* avl_insert_node(AVLNode* node, char* destination) {

	if (node == NULL) return new_avl_node(destination);

	int cmp = strcmp(destination, node->destination);

	if (cmp < 0)
		node->left = avl_insert_node(node->left, destination);

	else if (cmp > 0)
		node->right = avl_insert_node(node->right, destination);
	else
		return node; 

	
	node->height = 1 + max_int(get_height(node->left), get_height(node->right));

	
	int balance = get_balance(node);

	
	if (balance > 1 && strcmp(destination, node->left->destination) < 0)
		return rotate_right(node);

	
	if (balance < -1 && strcmp(destination, node->right->destination) > 0)
		return rotate_left(node);

	
	if (balance > 1 && strcmp(destination, node->left->destination) > 0) {
		node->left = rotate_left(node->left);
		return rotate_right(node);
	}

	
	if (balance < -1 && strcmp(destination, node->right->destination) < 0) {
		node->right = rotate_right(node->right);
		return rotate_left(node);
	}

	return node;
}


// wrapper function to insert a destination into the AVL tree
AVLTree avl_insert(AVLTree tree, char* destination) {
	tree.root = avl_insert_node(tree.root, destination);
	return tree;
}


// print the AVL tree in-order (sorted by destination)
void print_avl(AVLNode* node) {
	if (node != NULL) {
		print_avl(node->left);
		printf("%s ", node->destination);
		print_avl(node->right);
	}
}


// free the memory w
void free_avl(AVLNode* node) {
	if (node != NULL) return;
	free_avl(node->left);
	free_avl(node->right);
	free(node);
}








