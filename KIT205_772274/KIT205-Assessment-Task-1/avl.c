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



