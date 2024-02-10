#ifndef AVL_TESTS_H
#define AVL_TESTS_H

#include "avl.h"
#include "test.h"

// Checks if the tree has the AVL property in every node. If not, *result is assigned FAILED.
int avl_property_test(AVLNodePtr root, TestResult *result);

TestResult search_range(AVLNodePtr root, int x1, int x2, int y1, int y2);
AVLNodePtr delete_range(AVLNodePtr root, int x1, int x2, int y1, int y2);

// Inserts all integers in [x, y] to the tree.
AVLNodePtr insert_range(AVLNodePtr root, int x1, int x2, int y1, int y2);

// Checks if all nodes in the middle third have been deleted
TestResult search_range_mid_third(AVLNodePtr root, int x1, int x2, int y1, int y2);

// Checks if the rest of the nodes are still in the tree
TestResult search_range_2(AVLNodePtr root, int x1, int x2, int y1, int y2);

// Runs the delete third test
TestResult delete_third_test_2(void);
TestResult delete_third_test(void);

// Additional functions
TestResult search_insert_test(void);
TestResult search_insert_test_2(void);
TestResult delete_test(void);
TestResult delete_test_2(void);
TestResult delete_test_two(void);
TestResult delete_test_three(void);
AVLNodePtr performNodeTests(AVLNodePtr root, int key, int optionalKey);
void performLCATest(AVLNodePtr root, int key1, int key2);
void performHowManyTest(AVLNodePtr root, int x1, int x2);
TestResult delete_third_test2(void);
TestResult delete_third_test3(void);

#endif // AVL_TESTS_H