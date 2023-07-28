#ifndef AVL_H
#define AVL_H

typedef enum Position {LEFT, RIGHT} Position;

typedef struct AVLNode * AVLNodePtr;

typedef struct AVLNode{
    AVLNodePtr child[2];
	AVLNodePtr parent, max, min;
    int key, height, y, rank, skew; // rank parameter is augmented parameter that store the subtree size and not the actual rank of the node (which is something that difficult to augment in height balanced tree)
} AVLNode;

// return the maximum of x and y.
int _max( int x, int y );

// return the absolute value of x.
int _abs( int x );

// AVL Operations and Queries

// search for a node with key <x> and return the node if exists. Otherwise, returns NULL.
AVLNodePtr avlSearch(AVLNodePtr root, int x, int y );

// insert a new node with key <x> into the subtree. If the key exists do nothing. Returns a pointer to root of the tree.
AVLNodePtr avlInsert(AVLNodePtr root, int x, int y );

// delete the node with key <x> (if exists). Returns a pointer to the root of the tree.
AVLNodePtr avlDelete(AVLNodePtr root, int x, int y );

/**
 * Deletes nodes within the given interval [x1, x2] from the rooted AVL tree subtree.
 * The function ensures that the middle third of nodes in the specified interval, where x1 < x < x2,
 * is removed from the subtree. The total number of nodes within the interval must be divisible by 3
 * for the deletion to occur; otherwise, no nodes will be deleted.
 *
 * @param root The root of the AVL tree subtree to process.
 * @param x1 The lower bound of the interval [x1, x2].
 * @param x2 The upper bound of the interval [x1, x2].
 *
 * @return The root of the AVL tree after the deletion process.
 */
AVLNodePtr deleteThird(AVLNodePtr root, int x1, int x2);

// return a new initialized avl node with key <x>. Returns NULL if malloc fails.
AVLNodePtr newAvlNode(int x, int y );

// Free all nodes in the tree.
void deleteAvlTree(AVLNodePtr root );

//Help methods
void updateHeight(AVLNodePtr node);
void updateRank(AVLNodePtr node);
void updateMaxNodeSubtree(AVLNodePtr node);
void updateMinNodeSubtree(AVLNodePtr node);
void updateNodeProperties(AVLNodePtr node);
void updateParentProperties(AVLNodePtr node);
void updateAncestorProperties(AVLNodePtr node);
int getBalance(AVLNodePtr node);
AVLNodePtr rebalance(AVLNodePtr root);
AVLNodePtr rebalanceAncestors(AVLNodePtr node);
AVLNodePtr rightRotate(AVLNodePtr node);
AVLNodePtr leftRotate(AVLNodePtr node);
AVLNodePtr First(AVLNodePtr node);
AVLNodePtr Last(AVLNodePtr node);
AVLNodePtr getSuccessor(AVLNodePtr node);
AVLNodePtr getPredecessor(AVLNodePtr node);
AVLNodePtr getSubtreeAt(AVLNodePtr root, int index);
int getIndex(AVLNodePtr node);
int getRelativeIndex(AVLNodePtr root,AVLNodePtr node);
AVLNodePtr getLca(AVLNodePtr root, int x1, int x2);
AVLNodePtr lca(AVLNodePtr root, int x1, int x2);
AVLNodePtr search(AVLNodePtr root, int x, int y);
int howMany(AVLNodePtr root, int x1, int x2);
void printNode (AVLNodePtr node);
void printInorder(AVLNodePtr root);
void printPreorder(AVLNodePtr root);
void swapIfNotEqual(int *x1, int *x2);

#endif
