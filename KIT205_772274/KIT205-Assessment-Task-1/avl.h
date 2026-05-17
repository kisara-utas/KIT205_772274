#pragma once

#ifndef AVL_H
#define AVL_H

// A node in the AVL tree

typedef struct AVLNode {
	char destination[4]; // IATA code
	int height;
	struct AVLNode* left;
	struct AVLNode* right;
} AVLNode;

// The AVL Tree
typedef struct AVLTree {
	AVLNode* root;
} AVLTree;

#endif