#include <stdio.h>
#include <stdlib.h>
#include "avl.h"


typedef enum {FAILED,PASSED} TestResult;

void print_result( TestResult result );

// insert all integers in [x,y] to the tree.
AVLNodePtr insert_range( AVLNodePtr root, int x1, int x2, int y1, int y2 );

// search for all integers in [x,y]. Return FAILED if at least one search has failed.
TestResult search_range( AVLNodePtr root, int x1, int x2, int y1, int y2 );

// delete all integers in [x,y] from teh tree.
AVLNodePtr delete_range( AVLNodePtr root, int x1, int x2, int y1, int y2);

// check if the tree has the AVL property in every node. If not, *result is assigned FAILED.
int avl_property_test( AVLNodePtr root, TestResult * result );

TestResult search_insert_test();

TestResult delete_test();


int avl_property_test( AVLNodePtr root, TestResult * result ){
    int h_left,h_right;
    if( !root )
        return -1;
    h_left = avl_property_test( root->child[LEFT], result );
    h_right = avl_property_test( root->child[RIGHT], result );
    *result =  (abs(h_left-h_right) > 1 ) ? FAILED:*result;
    return 1+ _max(h_left,h_right);
}

AVLNodePtr insert_range( AVLNodePtr root, int x1, int x2, int y1, int y2 ){
    int j=y1;
    for( int i=x1; i<=x2; i++ ){
        root = avlInsert(root, i, j);
        j++;
    }
    return root;
}

TestResult search_range( AVLNodePtr root, int x1, int x2, int y1, int y2 ){
    AVLNodePtr node=NULL;
    int j = y1;
    for( int i=x1; i<=x2; ++i ){
        node = avlSearch(root, i, j);
        if( !(node && node->key==i) ){
            return FAILED;
        }
        j++;
    }
    return PASSED;
}

AVLNodePtr delete_range( AVLNodePtr root, int x1, int x2, int y1, int y2){
    int j = y1;
    for( int i=x1; i<=x2; i++ ){
        root = avlDelete(root, i, j);
        j++;
    }
    return root;
}


void print_result( TestResult result ){
    if( result==PASSED )
        printf("PASSED.\n");
    else
        printf("FAILED.\n");
}

TestResult search_insert_test(){
    AVLNodePtr root = NULL;
    TestResult result = PASSED;
    root = insert_range( root, 1000000, 2000000, 1000000, 2000000 );
    result = search_range( root, 1000000, 2000000, 1000000, 2000000 );
    avl_property_test( root, &result );
    printf("INSERT + SEARCH TEST ");
    print_result( result );
    deleteAvlTree(root);
    return result;
}

TestResult delete_test(){
    int i;
    AVLNodePtr root = NULL;
    TestResult result = PASSED;
    root = insert_range( root, 1000000, 2000000, 1000000, 2000000 );
    root = delete_range( root, 1100000, 1500000, 1100000, 1500000 );
    result = search_range( root, 1000000, 1099999, 1000000, 1099999 );
    result = search_range( root, 1500001, 2000000, 1500001, 2000000 )?result:FAILED;
    for( i=1100000; i<=1500000; i++){
        if(avlSearch(root, i, i) )
            result = FAILED;
    }
    avl_property_test( root, &result );
    printf("DELETE TEST ");
    print_result( result );
    deleteAvlTree(root);
    return result;
}


//int main(){
//    printf("sfhesufvuygesfegiuyfesgiuy\n");
//    submitters();
//    printf("\n");
//    search_insert_test();
//    delete_test();
//    return 0;
//}
