/* Some of this code was developed using resources such as the study modules in KIT205, Stack Overflow, Geeks for Geeks and Claude AI */

#pragma once


#ifndef DATABASE_H
#define DATABASE_H

#include "bst.h"
#include "avl.h"

// prototype 1 - BST of Linked Lists

typedef struct Database1 {
	BST airports; 
} Database1;

// prototype 2 - BST of AVL Trees

// a new BST node type that contains an AVL tree of routes instead of a linked list is needed for prototype 2

typedef struct AVLBSTNode {
	char code[4]; 
	AVLTree routes; 
	struct AVLBSTNode* left; 
	struct AVLBSTNode* right; 
} AVLBSTNode;


typedef struct Database2 {
	AVLBSTNode* root;
} Database2;

// Database 1 function prototypes
Database1 new_database1();
void db1_add_route(Database1* db, char* from, char* to);
void db1_print_airports(Database1* db);
void db1_print_routes(Database1* db, char* airport);
void free_database1(Database1* db);

// Database 2 function prototypes
Database2 new_database2();
AVLBSTNode* new_avlbst_node(char* code);
AVLBSTNode* avlbst_insert(AVLBSTNode* root, char* code);
AVLBSTNode* avlbst_find(AVLBSTNode* root, char* code);
void db2_add_route(Database2* db, char* from, char* to);
void db2_print_airports(Database2* db);
void db2_print_routes(Database2* db, char* airport);
void free_database2(AVLBSTNode* root);



#endif