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

// function prototypes

AVLTree new_avl_tree();
AVLNode* new_avl_node(char* destination);
int get_height(AVLNode* node);
int get_balance(AVLNode* node);
AVLNode* rotate_right(AVLNode* y);
AVLNode* rotate_left(AVLNode* x);
AVLNode* avl_insert_node(AVLNode* node, char* destination);
AVLTree avl_insert(AVLTree tree, char* destination);
void print_avl(AVLNode* node);
void free_avl(AVLNode* node);

#endif