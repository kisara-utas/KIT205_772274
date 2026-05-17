/* Some of this code was developed using resources such as the study modules in KIT205, Stack Overflow, Geeks for Geeks and Claude AI */

#include "database.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


// Database 1 - BST of Linked Lists

Database1 new_database1() {
    Database1 db;
    db.airports = new_bst();
    return db;
}

// Add a route from one airport to another
void db1_add_route(Database1* db, char* from, char* to) {
    db->airports = insert_bst(db->airports, from);
    db->airports = insert_bst(db->airports, to);

    BSTNode* from_node = find_bst(db->airports.root, from);
    if (from_node != NULL) {
        insert_route(&from_node->routes, to);
    }

    BSTNode* to_node = find_bst(db->airports.root, to);
    if (to_node != NULL) {
        insert_route(&to_node->routes, from);
    }
}

// Print all airports in alphabetical order
void db1_print_airports(Database1* db) {
    printf("Airports:\n");
    print_bst(db->airports.root);
}


// Print all routes from a given airport
void db1_print_routes(Database1* db, char* airport) {
    BSTNode* node = find_bst(db->airports.root, airport);
    if (node == NULL) {
        printf("Airport %s not found\n", airport);
        return;
    }
    printf("Routes from %s: ", airport);
    print_routes(&node->routes);
}

void free_database1(Database1* db) {
    free_bst(db->airports.root);
    db->airports.root = NULL;
}


// Database 2 - BST of AVL Trees

Database2 new_database2() {
    Database2 db;
    db.root = NULL;
    return db;
}

AVLBSTNode* new_avlbst_node(char* code) {
    AVLBSTNode* node = (AVLBSTNode*)malloc(sizeof(AVLBSTNode));
    strcpy_s(node->code, 4, code);
    node->routes = new_avl_tree();
    node->left = NULL;
    node->right = NULL;
    return node;
}


AVLBSTNode* avlbst_insert(AVLBSTNode* root, char* code) {
    if (root == NULL) return new_avlbst_node(code);
    int cmp = strcmp(code, root->code);
    if (cmp < 0) root->left = avlbst_insert(root->left, code);
    else if (cmp > 0) root->right = avlbst_insert(root->right, code);
    return root;
}

AVLBSTNode* avlbst_find(AVLBSTNode* root, char* code) {
    if (root == NULL) return NULL;
    int cmp = strcmp(code, root->code);
    if (cmp == 0) return root;
    if (cmp < 0) return avlbst_find(root->left, code);
    return avlbst_find(root->right, code);
}


void db2_add_route(Database2* db, char* from, char* to) {
  
    db->root = avlbst_insert(db->root, from);
    db->root = avlbst_insert(db->root, to);

    
    AVLBSTNode* from_node = avlbst_find(db->root, from);
    if (from_node != NULL) {
        from_node->routes = avl_insert(from_node->routes, to);
    }

    
    AVLBSTNode* to_node = avlbst_find(db->root, to);
    if (to_node != NULL) {
        to_node->routes = avl_insert(to_node->routes, from);
    }
}

void db2_print_airports_helper(AVLBSTNode* root) {
    if (root == NULL) return;
    db2_print_airports_helper(root->left);
    printf("%s\n", root->code);
    db2_print_airports_helper(root->right);
}


void db2_print_airports(Database2* db) {
    printf("Airports:\n");
    db2_print_airports_helper(db->root);
}

void db2_print_routes(Database2* db, char* airport) {
    AVLBSTNode* node = avlbst_find(db->root, airport);
    if (node == NULL) {
        printf("Airport %s not found\n", airport);
        return;
    }
    printf("Routes from %s: ", airport);
    print_avl(node->routes.root);
    printf("\n");
}

void free_database2(AVLBSTNode* root) {
    if (root == NULL) return;
    free_database2(root->left);
    free_database2(root->right);
    free_avl(root->routes.root);
    free(root);
}