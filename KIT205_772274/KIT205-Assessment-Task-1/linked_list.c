/* Some of this code was developed using resources such as the study modules in KIT205, Stack Overflow, Geeks for Geeks and Claude AI */


#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// creating a new empty route list 

RouteList new_route_list() {
	RouteList list;
	list.head = NULL;
	return list;
}

// inserting a destination in alphabetical order in the route list
void insert_route(RouteList* list, char* destination) {

	// creating a new node
	RouteNode* new_node = (RouteNode*)malloc(sizeof(RouteNode));
	strcpy_s(new_node->destination, sizeof(new_node->destination), destination);
	new_node->next = NULL;

	// if the list is empty or new node is before the head alphabetically 
	if (list->head == NULL || strcmp(destination, list->head->destination) < 0) {
		new_node->next = list->head;
		list->head = new_node;
		return;
	}

	// finding the correct position to insert the new node
	RouteNode* current = list->head;
	while (current->next != NULL && strcmp(current->next->destination, destination) < 0) {
		current = current->next;
	}

	// inserting after the current node
	new_node->next = current->next;
	current->next = new_node;
}

// printing all destinations in the route list
void print_routes(RouteList* list)	 {
	RouteNode* current = list->head;
	while (current != NULL) {
		printf("%s ", current->destination);
		current = current->next;
	}
	printf("\n");

}


// freeing memory (all nodes) in the route list

void free_route_list(RouteList* list) {
	RouteNode* current = list->head;
	while (current != NULL) {
		RouteNode* next = current->next;
		free(current);
		current = next;
	}
	list->head = NULL; // set head to NULL after freeing
}







