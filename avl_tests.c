#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
#include "test.h"
#include "avl_tests.h"

int avl_property_test(AVLNodePtr root, TestResult *result)
{
    int h_left, h_right;
    if (!root)
        return -1;
    h_left = avl_property_test(root->child[LEFT], result);
    h_right = avl_property_test(root->child[RIGHT], result);
    if (_abs(h_left - h_right) > 1)
        printNode(root);                                       // for print debugging purposes
    *result = (_abs(h_left - h_right) > 1) ? FAILED : *result; // testing Heights/Skew
    // Max/Min testing
    *result = (root->key > root->max->key) ? FAILED : *result;
    *result = (root->key < root->min->key) ? FAILED : *result;
    return 1 + _max(h_left, h_right);
}

TestResult search_range(AVLNodePtr root, int x1, int x2, int y1, int y2)
{
    AVLNodePtr node = NULL;

    int j = y1 + y2 - y2;
    for (int i = x1; i <= x2; ++i)
    {
        node = avlSearch(root, i, j);
        if (!(node && node->key == i))
        {
            return FAILED;
        }
        j++;
    }
    return PASSED;
}

AVLNodePtr delete_range(AVLNodePtr root, int x1, int x2, int y1, int y2)
{
    int j = y1 + y2 - y2;
    for (int i = x1; i <= x2; i++)
    {
        root = avlDelete(root, i, j);
        j++;
    }
    return root;
}

AVLNodePtr insert_range(AVLNodePtr root, int x1, int x2, int y1, int y2)
{
    int j = y1 + y2 - y2;
    for (int i = x1; i <= x2; i++)
    {
        root = avlInsert(root, i, j);
        j++;
    }
    return root;
}

// checks if all nodes in the middle third has been deleted
TestResult search_range_mid_third(AVLNodePtr root, int x1, int x2, int y1, int y2)
{
    AVLNodePtr node = NULL;
    int j = y2;
    j = y1;
    for (int i = x1; i <= x2; ++i)
    {
        node = avlSearch(root, i, j);
        if (node)
        { //|| node->key == i)) {
            return FAILED;
        }
        j++;
    }
    return PASSED;
}

// checks if the rest of the nodes are still in the tree
TestResult search_range_2(AVLNodePtr root, int x1, int x2, int y1, int y2)
{
    AVLNodePtr node = NULL;
    int j = y2;
    j = y1;
    for (int i = x1; i <= x2; ++i)
    {
        node = avlSearch(root, i, j);
        if (!(node && node->key == i))
        {
            return FAILED;
        }

        if (node->child[0])
        {
            if (!(node->key == node->child[0]->parent->key))
                return FAILED;
        }

        if (node->child[1])
        {
            if (!(node->key == node->child[1]->parent->key))
                return FAILED;
        }
        j++;
    }
    return PASSED;
}

TestResult delete_third_test_2(void)
{
    AVLNodePtr root = NULL;
    TestResult result = PASSED;

    int x1 = 105000;
    int x2 = 194999;
    //    for (i = 100000; i < 200001; i++) {
    //        root = avl_insert(root, i, i);
    //    }
    root = insert_range(root, 100000, 200000, 100000, 200000);
    AVLNodePtr res = deleteThird(root, x1, x2);
    // mid range: checks if the third was really deleted
    printf("was the range deleted?\n");
    print_result(search_range_mid_third(res, 135000, 164999, 135000, 164999));

    // tree after delete_third(): checks if the first third and third third are still in tree
    printf("does the rest exist?\n");
    print_result(search_range_2(res, 100000, 105000, 100000, 105000));
    print_result(search_range_2(res, 165000, 200000, 165000, 200000));

    avl_property_test(root, &result);
    //    printf("DELETE TEST ");
    print_result(result);
    //    delete_avl_tree( root );
    return result;
}

TestResult search_insert_test(void)
{
    AVLNodePtr root = NULL;
    TestResult result = PASSED;
    root = insert_range(root, 1000000, 2000000, 1000000, 2000000);
    result = search_range(root, 1000000, 2000000, 1000000, 2000000);
    avl_property_test(root, &result);
    printf("\nINSERT + SEARCH TEST ");
    print_result(result);
    deleteAvlTree(root);
    return result;
}

TestResult search_insert_test_2(void)
{
    AVLNodePtr root = NULL;
    TestResult result = PASSED;

    // Insert a large range of nodes from 1,000,000 to 10,000,000
    root = insert_range(root, 1000000, 10000000, 1000000, 10000000);

    // Perform search within the range and AVL property test
    result = search_range(root, 1000000, 10000000, 1000000, 10000000);
    avl_property_test(root, &result);

    printf("\nINSERT + SEARCH TEST 2 ");
    print_result(result);

    // Delete the AVL tree to free memory
    deleteAvlTree(root);

    return result;
}

TestResult delete_test(void)
{
    int i;
    AVLNodePtr root = NULL;
    TestResult result = PASSED;
    root = insert_range(root, 1000000, 2000000, 1000000, 2000000);
    //    performHowManyTest(root,0,2000000);
    //    performHowManyTest(root,1100000,1500000);
    root = delete_range(root, 1100000, 1500000, 1100000, 1500000);
    //    performHowManyTest(root,0,2000000);
    result = search_range(root, 1000000, 1099999, 1000000, 1099999);
    result = search_range(root, 1500001, 2000000, 1500001, 2000000) ? result : FAILED;
    //    root = avlDelete(root,2000000,2000000 );
    //    root = avlDelete(root,1000000,1000000 );
    for (i = 1100000; i <= 1500000; i++)
    {
        if (avlSearch(root, i, i))
            result = FAILED;
    }
    avl_property_test(root, &result);
    printf("\nDELETE TEST ");
    print_result(result);
    deleteAvlTree(root);
    return result;
}

TestResult delete_test_2(void)
{
    int i;
    AVLNodePtr root = NULL;
    TestResult result = PASSED;

    // Insert a large range of nodes from 1,000,000 to 10,000,000
    root = insert_range(root, 1000000, 10000000, 1000000, 10000000);

    // Delete a range of nodes from 4,000,000 to 7,000,000
    root = delete_range(root, 4000000, 7000000, 4000000, 7000000);

    // Perform search and AVL property test
    result = search_range(root, 1000000, 3999999, 1000000, 3999999);
    result = search_range(root, 7000001, 10000000, 7000001, 10000000) ? result : FAILED;
    for (i = 4000000; i <= 7000000; i++)
    {
        if (avlSearch(root, i, i))
            result = FAILED;
    }

    avl_property_test(root, &result);
    printf("\nDELETE TEST 2 ");
    print_result(result);
    deleteAvlTree(root);

    return result;
}

TestResult delete_test_two(void)
{
    printf("delete_test_two:\n");
    int i;
    AVLNodePtr root = NULL;
    TestResult result = PASSED;
    root = insert_range(root, 1, 10, 1, 10);
    root = delete_range(root, 3, 5, 3, 5);
    result = search_range(root, 1, 2, 1, 2);
    result = search_range(root, 6, 10, 6, 10) ? result : FAILED;
    for (i = 3; i <= 5; i++)
    {
        if (avlSearch(root, i, i))
            result = FAILED;
    }
    avl_property_test(root, &result);
    printf("DELETE TEST #2 ");
    print_result(result);
    deleteAvlTree(root);
    return result;
}

// DELETE LATER !
TestResult delete_test_three(void)
{
    printf("delete_test_three:\n\n");
    int i;
    // int key1 = 0;
    // int key2 = 20;
    int optionalKey = 10;
    AVLNodePtr root = NULL;
    TestResult result = PASSED;
    root = insert_range(root, 1, 6000, 1, 6000);
    printf("------------deleteThird------------\n");
    root = deleteThird(root, 0, 999);
    avl_property_test(root, &result);
    printf("------------END deleteThird------------\n");
    printInorder(root);
    // LCA test
    //    performLCATest(root, key1, key2);
    root = performNodeTests(root, 0, optionalKey);
    // Perform the tests on the nodes and print the results
    //    root = performNodeTests(root, key, optionalKey);
    //    performLCATest(root, 14, 22);
    //    performLCATest(root, 0, 200);
    // LCA test
    //    performLCATest(root, key1, key2);
    result = search_range(root, 1, 333, 1, 333) ? result : FAILED;
    result = search_range(root, 667, 6000, 667, 6000) ? result : FAILED;
    for (i = 334; i <= 666; i++)
    {
        if (avlSearch(root, i, i))
            result = FAILED;
    }
    root = deleteThird(root, 0, 999);
    result = howMany(root, 0, 999) == 444 ? result : FAILED;
    result = howMany(root, 0, 6000) == 5445 ? result : FAILED;
    for (i = 223; i <= 777; i++)
    {
        if (avlSearch(root, i, i))
            result = FAILED;
    }
    avl_property_test(root, &result);
    printf("DELETE TEST #3 ");
    print_result(result);
    deleteAvlTree(root);
    return result;
}

TestResult delete_third_test(void)
{
    int i;
    AVLNodePtr root = NULL;
    TestResult result = PASSED;
    root = insert_range(root, 1000000, 2000000, 1000000, 2000000);
    root = delete_range(root, 1100000, 1500000, 1100000, 1500000);
    avl_property_test(root, &result);
    root = deleteThird(root, 0, 2000000);
    avl_property_test(root, &result);
    result = search_range(root, 1000000, 1099999, 1000000, 1099999) ? result : FAILED;
    result = search_range(root, 1800001, 2000000, 1800001, 2000000) ? result : FAILED;
    for (i = 1100000; i <= 1500000; i++)
    {
        if (avlSearch(root, i, i))
            result = FAILED;
    }
    for (i = 1600001; i <= 1800000; i++)
    {
        if (avlSearch(root, i, i))
            result = FAILED;
    }
    avl_property_test(root, &result);
    printf("DELETE TEST THIRD #1");
    print_result(result);
    deleteAvlTree(root);
    return result;
}

AVLNodePtr performNodeTests(AVLNodePtr root, int key, int optionalKey)
{
    AVLNodePtr node, predecessor, successor;

    printf("--------------- Test Begins ---------------\n");
    printf("Keys provided for the tests: %d, %d\n", key, optionalKey);

    // Search for the key in the AVL tree
    node = avlSearch(root, key, key);

    // If the key is found, print its information and delete it
    if (node)
    {
        printf("Node found:\n");
        // Check if the found node is the root
        if (node == root)
        {
            printf("The found node is the root of the tree.\n");
        }
        printNode(node);
        printf("\n");

        // Find the predecessor of the found node
        predecessor = getPredecessor(node);
        if (predecessor)
        {
            printf("Predecessor:\n");
            printNode(predecessor);
        }
        else
        {
            printf("Predecessor not found.\n");
        }

        // Find the successor of the found node
        successor = getSuccessor(node);
        if (successor)
        {
            printf("Successor:\n");
            printNode(successor);
        }
        else
        {
            printf("Successor not found.\n");
        }
        performHowManyTest(root, First(root)->key, Last(root)->key);
        // Delete the node from the AVL tree
        root = avlDelete(root, node->key, node->y);
        printf("Node deleted.\n");
    }
    else
    {
        printf("Node not found.\n");
    }

    // Perform the tests on the modified AVL tree
    printf("Updated AVL Tree:\n");
    //    print_avl_tree(root);
    printf("\n");

    // Print information of the root node
    printf("Root:\n");
    printNode(root);

    // Find the predecessor of the root node
    predecessor = getPredecessor(root);
    if (predecessor)
    {
        printf("Predecessor of the root:\n");
        printNode(predecessor);
    }
    else
    {
        printf("Predecessor of the root not found.\n");
    }

    // Find the successor of the root node
    successor = getSuccessor(root);
    if (successor)
    {
        printf("Successor of the root:\n");
        printNode(successor);
    }
    else
    {
        printf("Successor of the root not found.\n");
    }

    // Search for an optional key if provided
    if (optionalKey != -1)
    {
        node = avlSearch(root, optionalKey, optionalKey);
        printf("Search for optional key %d:\n", optionalKey);
        printNode(node);
    }
    performHowManyTest(root, First(root)->key, Last(root)->key);
    printf("-------------------------------------------\n");
    TestResult result = PASSED;
    avl_property_test(root, &result);
    printf("DELETE TEST ");
    print_result(result);

    return root;
}

void performLCATest(AVLNodePtr root, int key1, int key2)
{
    AVLNodePtr lcaNode;

    printf("--------------- LCA Test ---------------\n");
    printf("Keys provided for the LCA test: %d, %d\n", key1, key2);

    printf("Finding LCA of %d and %d:\n", key1, key2);
    lcaNode = getLca(root, key1, key2);
    printNode(lcaNode);

    // Check if the LCA is the root of the tree
    if (lcaNode == root)
    {
        printf("LCA is the root of the tree.\n");
    }
    else
    {
        printf("LCA is not the root of the tree.\n");
    }

    printf("--------------- LCA Test End ---------------\n");
}

void performHowManyTest(AVLNodePtr root, int x1, int x2)
{
    int result = howMany(root, x1, x2);

    printf("--------------- How Many Test ---------------\n");

    printf("How Many between %d to %d?\n", x1, x2);
    printf("There are %d nodes\n", result);

    printf("--------------- How Many Test End ---------------\n");
}

TestResult delete_third_test2(void)
{
    AVLNodePtr root = NULL;
    TestResult result = PASSED;
    root = insert_range(root, 1000000, 2000001, 1000000, 2000001);
    //    root = delete_range( root, 1100000, 1500000, 1100000, 1500000 );
    avl_property_test(root, &result);
    root = deleteThird(root, 0, 2000003);
    avl_property_test(root, &result);
    root = deleteThird(root, 0, 1700002);
    avl_property_test(root, &result);
    root = deleteThird(root, 1700002, 2000003);
    avl_property_test(root, &result);
    root = deleteThird(root, 1000001, 2000003);
    avl_property_test(root, &result);
    root = deleteThird(root, 1000001, 1111111);
    avl_property_test(root, &result);
    root = deleteThird(root, 1823599, 1911413);
    avl_property_test(root, &result);
    root = deleteThird(root, 1000002, 1111111);
    avl_property_test(root, &result);
    root = deleteThird(root, 1000004, 1111111);
    avl_property_test(root, &result);
    root = deleteThird(root, 0, 2000003);
    avl_property_test(root, &result);
    root = deleteThird(root, 1234567, 2000003);
    avl_property_test(root, &result);
    root = deleteThird(root, 0, 1085566);
    avl_property_test(root, &result);
    root = deleteThird(root, 0, 1234567);
    avl_property_test(root, &result);
    root = deleteThird(root, 1878787, 2000003);
    avl_property_test(root, &result);
    root = deleteThird(root, 1500000, 1987654);
    avl_property_test(root, &result);
    root = deleteThird(root, 1500000, 1999999);
    avl_property_test(root, &result);
    root = deleteThird(root, 1098989, 1999999);
    avl_property_test(root, &result);
    root = deleteThird(root, 1002079, 1098989);
    avl_property_test(root, &result);
    root = deleteThird(root, 0, 1004079);
    avl_property_test(root, &result);
    root = deleteThird(root, 0, 1001079);
    avl_property_test(root, &result);
    root = deleteThird(root, 1001077, 1001079);
    avl_property_test(root, &result);
    root = deleteThird(root, 1001057, 1001078);
    avl_property_test(root, &result);
    root = deleteThird(root, 1001027, 1001059);
    avl_property_test(root, &result);
    root = deleteThird(root, 1001001, 1001027);
    avl_property_test(root, &result);
    root = deleteThird(root, 1001001, 1001009);
    avl_property_test(root, &result);
    root = deleteThird(root, 1000101, 1500079);
    avl_property_test(root, &result);
    root = deleteThird(root, 1000003, 2000003);
    avl_property_test(root, &result);
    root = deleteThird(root, 0, 2000003);
    avl_property_test(root, &result);
    root = insert_range(root, 1300000, 1700001, 1300000, 1700001);
    avl_property_test(root, &result);
    root = deleteThird(root, 1000001, 2000003);
    avl_property_test(root, &result);
    deleteAvlTree(root);
    printf("DELETE TEST THIRD #2 ");
    print_result(result);
    return result;
}

TestResult delete_third_test3(void)
{
    AVLNodePtr root = NULL;
    TestResult result = PASSED;
    root = insert_range(root, 1, 1000, 1, 1000);
    //    root = delete_range( root, 1100000, 1500000, 1100000, 1500000 );
    avl_property_test(root, &result);
    root = deleteThird(root, 0, 300);
    avl_property_test(root, &result);
    root = deleteThird(root, 301, 600);
    avl_property_test(root, &result);
    root = deleteThird(root, 601, 900);
    avl_property_test(root, &result);
    root = deleteThird(root, 500, 840);
    avl_property_test(root, &result);
    root = deleteThird(root, 0, 980);
    avl_property_test(root, &result);
    deleteAvlTree(root);
    printf("DELETE TEST THIRD #3 ");
    print_result(result);
    return result;
}
