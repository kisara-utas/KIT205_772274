#include <stdio.h>
#include "linked_list.h"

void test_linked_list() {
	printf("---------Testing Linked List Implementation---------\n");

	RouteList list = new_route_list();
	printf("Test 1 - Empty list: "); 
	print_routes(&list); //  expected output: prints nothing

	insert_route(&list, "MEL");
	printf("Test 2 - One item: ");
	print_routes(&list); // expected output: MEL

	insert_route(&list, "BKK");
	printf("Test 3 - Insert before: ");
	print_routes(&list); // expected output: BKK MEL

	insert_route(&list, "SYD");
	printf("Test 4 - Insert after: "); // expected output: BKK MEL SYD
	print_routes(&list);

	insert_route(&list, "LAX");
	printf("Test 5 - Insert in middle: ");
	print_routes(&list); // expected output: BKK LAX MEL SYD

	insert_route(&list, "MEL");
	printf("Test 6 - Duplicate: ");
	print_routes(&list);  // expected output: BKK LAX MEL MEL SYD (duplicates allowed)

	RouteList empty = new_route_list();
	free_route_list(&empty);
	printf("Test 7 - Free empty list: OK\n"); // expected output: OK

	free_route_list(&list);
	printf("---------Finished Testing Linked List Implementation---------\n");
}

int main() {
	printf("KIT205 - Flight Route Database\n");
	printf("Running tests...\n");
	test_linked_list();
	
	return 0;
}