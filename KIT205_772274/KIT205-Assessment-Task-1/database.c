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

    
    BSTNode* node = find_bst(db->airports.root, from);
    if (node != NULL) {
        insert_route(&node->routes, to);
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