/* Some of this code was developed using resources such as the study modules in KIT205, Stack Overflow, Geeks for Geeks and Claude AI */

#include <stdio.h>
#include "linked_list.h"
#include "bst.h"
#include "avl.h"
#include "database.h"
#include <time.h>

void test_linked_list() {
	printf("\n---------Testing Linked List Implementation---------\n");

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
	printf("Test 7 - Free empty list: Freed\n"); // expected output: Freed

	free_route_list(&list);
	printf("---------Finished Testing Linked List Implementation---------\n");
}

void test_bst() {
    printf("\n---------Testing BST Implementation---------\n");

   
    BST tree = new_bst();
    printf("Test 1 - Empty BST: ");
    print_bst(tree.root);
    printf("(empty)\n");

   
    tree = insert_bst(tree, "MEL");
    printf("Test 2 - One airport:\n");
    print_bst(tree.root);  // expected output: MEL

    
    tree = insert_bst(tree, "LAX");
    printf("Test 3 - Insert left:\n");
    print_bst(tree.root);  // expected output: LAX MEL

    
    tree = insert_bst(tree, "SYD");
    printf("Test 4 - Insert right:\n");
    print_bst(tree.root);  // expected output: LAX MEL SYD

   
    tree = insert_bst(tree, "MEL");
    printf("Test 5 - Duplicate:\n");
    print_bst(tree.root);  // expected output: LAX MEL SYD (no change)

    
    BSTNode* found = find_bst(tree.root, "LAX");
    printf("Test 6 - Find LAX: %s\n", found ? found->code : "NOT FOUND");  // expected output: LAX


    BSTNode* not_found = find_bst(tree.root, "BKK");
    printf("Test 7 - Find BKK: %s\n", not_found ? not_found->code : "NOT FOUND");  // expected output: NOT FOUND


    tree = insert_bst(tree, "BKK");  // goes left of LAX
    tree = insert_bst(tree, "NRT");  // goes right of MEL left of SYD
    printf("Test 8 - Larger tree:\n");
    print_bst(tree.root);  // expected output: BKK LAX MEL NRT SYD

   
    BSTNode* found_left = find_bst(tree.root, "BKK");
    printf("Test 9 - Find BKK (left subtree): %s\n", found_left ? found_left->code : "NOT FOUND");  // expected output: BKK

    
    BSTNode* found_right = find_bst(tree.root, "NRT");
    printf("Test 10 - Find NRT (right subtree): %s\n", found_right ? found_right->code : "NOT FOUND");  // expected output: NRT


    BST empty_tree = new_bst();
    free_bst(empty_tree.root);
    printf("Test 11 - Free empty BST: Freed\n");

    free_bst(tree.root);
    printf("---------Finished Testing BST Implementation---------\n\n");
}

void test_avl() {

    printf("\n---------Testing AVL Tree Implementation---------\n");

    
    AVLTree tree = new_avl_tree();
    printf("Test 1 - Empty AVL tree: ");
    print_avl(tree.root);
    printf("(empty)\n");

    
    tree = avl_insert(tree, "MEL");
    printf("Test 2 - One destination: ");
    print_avl(tree.root);  // expected output: MEL
    printf("\n");

   
    tree = avl_insert(tree, "LAX");
    printf("Test 3 - Insert left: ");
    print_avl(tree.root);  // expected output: LAX MEL
    printf("\n");

    
    tree = avl_insert(tree, "SYD");
    printf("Test 4 - Insert right: ");
    print_avl(tree.root);  // expected output: LAX MEL SYD
    printf("\n");

    
    tree = avl_insert(tree, "BKK");
    tree = avl_insert(tree, "AKL");
    printf("Test 5 - Left Left rotation: ");
    print_avl(tree.root);  // expected output: AKL BKK LAX MEL SYD
    printf("\n");

    
    tree = avl_insert(tree, "ZRH");
    tree = avl_insert(tree, "ZZZ");
    printf("Test 6 - Right Right rotation: ");
    print_avl(tree.root);  // expected output: AKL BKK LAX MEL SYD ZRH ZZZ
    printf("\n");

    
    tree = avl_insert(tree, "MEL");
    printf("Test 7 - Duplicate: ");
    print_avl(tree.root);  // expected output: no change
    printf("\n");

    
    AVLTree empty = new_avl_tree();
    free_avl(empty.root);
    printf("Test 8 - Free empty AVL: Freed\n");

  
    AVLTree lr_tree = new_avl_tree();
    lr_tree = avl_insert(lr_tree, "SYD");
    lr_tree = avl_insert(lr_tree, "AKL");
    lr_tree = avl_insert(lr_tree, "MEL"); 
    printf("Test 9 - Left Right rotation: ");
    print_avl(lr_tree.root);  // expected output: AKL MEL SYD
    printf("\n");
    free_avl(lr_tree.root);

    
    AVLTree rl_tree = new_avl_tree();
    rl_tree = avl_insert(rl_tree, "AKL");
    rl_tree = avl_insert(rl_tree, "SYD");
    rl_tree = avl_insert(rl_tree, "MEL"); 
    printf("Test 10 - Right Left rotation: ");
    print_avl(rl_tree.root);  // expected output[: AKL MEL SYD
    printf("\n");
    free_avl(rl_tree.root);

    
    AVLTree free_test = new_avl_tree();
    free_test = avl_insert(free_test, "MEL");
    free_test = avl_insert(free_test, "SYD");
    free_test = avl_insert(free_test, "LAX");
    free_avl(free_test.root);
    printf("Test 11 - Free non-empty AVL: Freed\n");

    free_avl(tree.root);
    printf("---------Finished Testing AVL Tree Implementation---------\n\n");


}

void test_database() {
    printf("---------Testing Database Implementation---------\n");

    // === PROTOTYPE 1 TESTS ===
    printf("--- Prototype 1: BST of Linked Lists ---\n");

  
    Database1 db1 = new_database1();
    printf("Test 1 - Empty database airports: \n");
    db1_print_airports(&db1);  // expected output: nothing

   
    db1_add_route(&db1, "MEL", "SYD");
    printf("Test 2 - Add MEL->SYD, print airports:\n");
    db1_print_airports(&db1);  // expected output: MEL SYD

    
    printf("Test 3 - Routes from MEL: ");
    db1_print_routes(&db1, "MEL");  // expected output: SYD

    
    printf("Test 4 - Routes from SYD (many-to-many): ");
    db1_print_routes(&db1, "SYD");  // expected output: MEL

    
    db1_add_route(&db1, "MEL", "LAX");
    db1_add_route(&db1, "MEL", "BKK");
    db1_add_route(&db1, "SYD", "LAX");
    printf("Test 5 - More routes, print airports:\n");
    db1_print_airports(&db1);  // expected output: BKK LAX MEL SYD

   
    printf("Test 6 - Routes from MEL: ");
    db1_print_routes(&db1, "MEL");  // expected output : BKK LAX SYD

    
    printf("Test 7 - Airport not found: ");
    db1_print_routes(&db1, "ZZZ");  // expected output: not found message

    free_database1(&db1);
    printf("Test 8 - Free database 1: Freed\n\n");

    

    // === PROTOTYPE 2 TESTS ===
    printf("--- Prototype 2: BST of AVL Trees ---\n");

    
    Database2 db2 = new_database2();
    printf("Test 9 - Empty database airports:\n");
    db2_print_airports(&db2);  // expected output: nothing

    
    db2_add_route(&db2, "MEL", "SYD");
    printf("Test 10 - Add MEL->SYD, print airports:\n");
    db2_print_airports(&db2);  // expected output: MEL SYD

   
    printf("Test 11 - Routes from MEL: ");
    db2_print_routes(&db2, "MEL");  // expected output: SYD

    
    printf("Test 12 - Routes from SYD (many-to-many): ");
    db2_print_routes(&db2, "SYD");  // expected output: MEL

    
    db2_add_route(&db2, "MEL", "LAX");
    db2_add_route(&db2, "MEL", "BKK");
    db2_add_route(&db2, "SYD", "LAX");
    printf("Test 13 - More routes, print airports:\n");
    db2_print_airports(&db2);  // expected output: BKK LAX MEL SYD

    
    printf("Test 14 - Routes from MEL: ");
    db2_print_routes(&db2, "MEL");  // expected output: BKK LAX SYD

   
    printf("Test 15 - Airport not found: ");
    db2_print_routes(&db2, "ZZZ");  // expected output: not found message

    free_database2(db2.root);
    printf("Test 16 - Free database 2: Freed\n");

    

    printf("---------Finished Testing Database Implementation---------\n\n");
}

void evaluate_performance() {
    printf("---------Performance Evaluation---------\n");
    printf("Testing insertion performance for both prototypes\n\n");

    int sizes[] = { 1000, 5000, 10000, 50000, 100000, 500000, 1000000 };
    int num_sizes = 7;

    printf("%-10s %-20s %-20s\n", "N", "Prototype1 (ms)", "Prototype2 (ms)");
    printf("%-10s %-20s %-20s\n", "---", "---------------", "---------------");

    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];

        // Test Prototype 1 - BST of Linked Lists
        Database1 db1 = new_database1();
        clock_t start1 = clock();
        for (int j = 0; j < n; j++) {
            char from[4], to[4];
            from[0] = 'A' + (j % 26);
            from[1] = 'A' + ((j / 26) % 26);
            from[2] = 'A' + ((j / 676) % 26);
            from[3] = '\0';
            to[0] = 'A' + ((j + 1) % 26);
            to[1] = 'A' + (((j + 1) / 26) % 26);
            to[2] = 'A' + (((j + 1) / 676) % 26);
            to[3] = '\0';
            db1_add_route(&db1, from, to);
        }
        clock_t end1 = clock();
        double time1 = ((double)(end1 - start1)) / CLOCKS_PER_SEC * 1000;
        free_database1(&db1);

        // Test Prototype 2 - BST of AVL Trees
        Database2 db2 = new_database2();
        clock_t start2 = clock();
        for (int j = 0; j < n; j++) {
            char from[4], to[4];
            from[0] = 'A' + (j % 26);
            from[1] = 'A' + ((j / 26) % 26);
            from[2] = 'A' + ((j / 676) % 26);
            from[3] = '\0';
            to[0] = 'A' + ((j + 1) % 26);
            to[1] = 'A' + (((j + 1) / 26) % 26);
            to[2] = 'A' + (((j + 1) / 676) % 26);
            to[3] = '\0';
            db2_add_route(&db2, from, to);
        }
        clock_t end2 = clock();
        double time2 = ((double)(end2 - start2)) / CLOCKS_PER_SEC * 1000;
        free_database2(db2.root);

        printf("%-10d %-20.4f %-20.4f\n", n, time1, time2);
    }

    printf("\n---------Finished Performance Evaluation---------\n");
}


int main() {
	printf("KIT205 - Flight Routes Database - Done by Kisara Batugedara (772274)\n");
	printf("Running tests for prototypes...\n");
	test_linked_list();
	test_bst();
    test_avl();
    test_database();
	evaluate_performance();
	
	return 0;
}