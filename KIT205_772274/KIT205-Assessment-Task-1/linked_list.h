#pragma once
#ifndef LINKED_LIST_H
#define LINKED_LIST_H


typedef struct RouteNode {
	char destination[4];    // Destination IATA code
	struct RouteNode* next; // Pointer to the next route node 
} RouteNode;


typedef struct RouteList {
	RouteNode* head; // Pointer to the head node of the list
} RouteList;

// Function prototypes
RouteList new_route_list();
void insert_route(RouteList* list, char* destination);
void print_routes(RouteList* list);
void free_route_list(RouteList* list);

#endif 
