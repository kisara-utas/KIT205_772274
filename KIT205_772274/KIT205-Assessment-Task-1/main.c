#include <stdio.h>
#include "linked_list.h"
#include "bst.h"
#include "avl.h"

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


int main() {
	printf("KIT205 - Flight Routes Database - Done by Kisara Batugedara (772274)\n");
	printf("Running tests for prototypes...\n");
	test_linked_list();
	test_bst();
    test_avl();
	
	return 0;
}