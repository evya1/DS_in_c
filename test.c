#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum {FAILED,PASSED} TestResult;

void print_result_2(TestResult result );

// insert all integers in [x,y] to the tree.
AVLNodePtr insert_range( AVLNodePtr root, int x1, int x2, int y1, int y2 );

// search for all integers in [x,y]. Return FAILED if at least one search has failed.
TestResult search_range_2( AVLNodePtr root, int x1, int x2, int y1, int y2 );

// delete all integers in [x,y] from teh tree.
AVLNodePtr delete_range( AVLNodePtr root, int x1, int x2, int y1, int y2);

// check if the tree has the AVL property in every node. If not, *result is assigned FAILED.
int avl_property_test( AVLNodePtr root, TestResult * result );

TestResult search_insert_test();

TestResult delete_test();
int test(void);

void print_result_2(TestResult result ){
    if( result==PASSED )
        printf("PASSED.\n");
    else
        printf("FAILED.\n");
}

//checks if all nodes in the middle third has been deleted
TestResult search_range_mid_third(AVLNodePtr root, int x1, int x2, int y1, int y2) {
    AVLNodePtr node = NULL;
    int j = y1;
    for (int i = x1; i <= x2; ++i) {
        node = avlSearch(root, i, j);
        if (node) { //|| node->key == i)) {
            return FAILED;
        }
        j++;
    }
    return PASSED;
}

//checks if the rest of the nodes are still in the tree
TestResult search_range_2(AVLNodePtr root, int x1, int x2, int y1, int y2) {
    AVLNodePtr node = NULL;
    int j = y1;
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

TestResult delete_third_test_2(void) {
    AVLNodePtr root = NULL;
    TestResult result = PASSED;
    int i;
    int x1 = 105000;
    int x2 = 194999;
//    for (i = 100000; i < 200001; i++) {
//        root = avl_insert(root, i, i);
//    }
    root = insert_range( root, 100000 , 200000, 100000, 200000 );
    AVLNodePtr res = deleteThird(root, x1, x2);
    //mid range: checks if the third was really deleted
    printf("was the range deleted?\n");
    print_result_2(search_range_mid_third(res, 135000, 164999, 135000, 164999));

    //tree after delete_third(): checks if the first third and third third are still in tree
    printf("does the rest exist?\n");
    print_result_2(search_range_2(res, 100000, 105000, 100000, 105000));
    print_result_2(search_range_2(res, 165000, 200000, 165000, 200000));

    avl_property_test( root, &result );
//    printf("DELETE TEST ");
    print_result_2(result);
//    delete_avl_tree( root );
    return result;
}

int main1(void){
    delete_third_test_2();
    return 0;
}