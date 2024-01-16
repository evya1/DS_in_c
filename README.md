# AVL Tree Library

This is a C library providing an implementation of an AVL (Adelson-Velsky and Landis) tree. AVL trees are self-balancing binary search trees that maintain their balance through rotations, ensuring efficient operations for insertion, deletion, and search.

## Table of Contents

-   [Introduction](#introduction)
-   [Structures](#structures)
-   [Functions](#functions)
    -   [AVL Operations](#avl-operations)
    -   [Interval Deletion](#interval-deletion)
    -   [Node Manipulation](#node-manipulation)
    -   [Tree Operations](#tree-operations)
    -   [Helper Methods](#helper-methods)
-   [Usage](#usage)
-   [License](#license)

## Introduction

This library provides a flexible and efficient implementation of AVL trees with additional features such as interval deletion and various tree operations. AVL trees maintain balance, ensuring logarithmic time complexity for key-based operations.

## Structures

### AVLNode Structure

```c
typedef struct AVLNode {
    AVLNodePtr child[2];
    AVLNodePtr parent, max, min;
    int key, height, y, size;
} AVLNode;
```

-   `child[#]`: Pointers to the left and right children of the node.
-   `parent`: Pointer to the parent node.
-   `max`: Pointer to the node with the maximum key in the subtree rooted at the current node.
-   `min`: Pointer to the node with the minimum key in the subtree rooted at the current node.
-   `key`: The key value of the node.
-   `height`: The height of the node in the tree.
-   `y`: A parameter used in the AVL tree (rank parameter).
-   `size`: The size of the subtree rooted at the current node.

## Functions

### AVL Operations

-   `avlSearch`: Search for a node with a given key and return the node if it exists, otherwise, return NULL.
-   `avlInsert`: Insert a new node with a given key into the subtree.
-   `avlDelete`: Delete the node with a given key if it exists.
-   `deleteThird`: Delete nodes within a specified interval [x1, x2] from the AVL tree, ensuring the middle third is removed.

### Node Manipulation

-   `newAvlNode`: Create and return a new AVL node with a given key.
-   `deleteAvlTree`: Free all nodes in the tree.

### Tree Operations

-   Various methods for updating node properties, balancing, rotation, finding successors/predecessors, and more.

### Helper Methods

-   Various helper methods for tree manipulation and information retrieval.

## Usage

To use this AVL tree library, include the avl.h header file in your C program. Make sure to link your program with the source file containing the implementation of these functions.

Example:

```c
#include "avl.h"

int main() {
    AVLNodePtr root = NULL;

    // Perform AVL tree operations...

    // Cleanup
    deleteAvlTree(root);

    return 0;
}
```
