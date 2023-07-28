#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

// I highly recommend watching the next lectures (in that order) for a better understanding of the implementation:
// 1. https://www.youtube.com/watch?v=U1JYwHcFfso&pp=ygUFYXZsIDc%3D
// 2. https://www.youtube.com/watch?v=xVka6z1hu-I&pp=ygULcmFuZ2UgdHJlZXM%3D

int _max(int x, int y) {
    return (x < y) ? y : x;
}

int _abs(int x) {
    return (x < 0) ? -x : x;
}

//helping functoins
void updateHeight(AVLNodePtr node) {
    if (node == NULL)
        return;

    int leftheight = (node->child[LEFT] != NULL) ? node->child[LEFT]->height : -1;
    int rightheight = (node->child[RIGHT] != NULL) ? node->child[RIGHT]->height : -1;

    node->height = 1 + _max(leftheight, rightheight);
}
void updateRank(AVLNodePtr node) {
    if (node == NULL)
        return;

    int leftRank = (node->child[LEFT] != NULL) ? node->child[LEFT]->rank : 0;
    int rightRank = (node->child[RIGHT] != NULL) ? node->child[RIGHT]->rank : 0;

    node->rank = 1 + leftRank + rightRank;
}
void updateMaxNodeSubtree(AVLNodePtr node) {
    if (node == NULL)
        return;
    else if (node->child[RIGHT] == NULL)
        node->max = node;
    else
        node->max = node->child[RIGHT]->max;
}
void updateMinNodeSubtree(AVLNodePtr node) {
    if (node == NULL)
        return;
    else if (node->child[LEFT] == NULL)
        node->min = node;
    else
        node->min = node->child[LEFT]->min;
}
//Update both Height and Rank together for a cleaner code
void updateNodeProperties(AVLNodePtr node) {
    if (node == NULL)
        return;
    updateHeight(node);
    updateRank(node);
    updateMaxNodeSubtree(node);
    updateMinNodeSubtree(node);
}
//Update Node's parent
void updateParentProperties(AVLNodePtr node) {
    if (node == NULL) return;
    if (node->parent == NULL) return;
    updateNodeProperties(node->parent);
}
// Iterative method to update at most log n Ancestors
void updateAncestorProperties(AVLNodePtr node) {
    AVLNodePtr current = node;
    if (current == NULL || current->parent == NULL)
        return;

    updateNodeProperties(current);

    while (current) {
        updateParentProperties(current);
        current = current->parent;
    }
}
int getBalance(AVLNodePtr node) {
    if (node == NULL) {
        return -1;
    }

    int leftheight = (node->child[LEFT] != NULL) ? node->child[LEFT]->height : -1;
    int rightheight = (node->child[RIGHT] != NULL) ? node->child[RIGHT]->height : -1;

    return rightheight - leftheight;
}
//The method's cases correspond to those covered in the above-referenced AVL tree lecture.
AVLNodePtr rebalance(AVLNodePtr root){
    if (root == NULL)
        return NULL;

    int balance = getBalance(root);

    if (balance > 1){
        // Case 1 & 2
        if (root->child[RIGHT] && getBalance(root->child[RIGHT]) >= 0) {
            return leftRotate(root);
        }
            // Case 3 (skew(root->child[RIGHT]) = -1)
        else {
            if (root->child[RIGHT]) {
                rightRotate(root->child[RIGHT]);
            }
            return leftRotate(root);
        }
    }
    else if (balance < -1) {
        // Case 1 & 2
        if (root->child[LEFT] && getBalance(root->child[LEFT]) <= 0) {
            return rightRotate(root);
        }
            // Case 3 (skew(root->child[LEFT]) = 1)
        else {
            if (root->child[LEFT]) {
                leftRotate(root->child[LEFT]);
            }
            return rightRotate(root);
        }
    }

    updateNodeProperties(root);

    return root;
}
// Iterative method to rebalance at most log n ancestors - can change the root node if needed.
AVLNodePtr rebalanceAncestors(AVLNodePtr node) {
    if (node == NULL || node->parent == NULL)
        return node;

    node = rebalance(node);
    AVLNodePtr current = node->parent;

    while (current) {
        current = rebalance(current);
        node = current;
        current = current->parent;
    }
    return node;
}
/**

            Y            RightRotate(Y) =>           X
          /  \                                     /  \
         X    C                                   A    Y
       /  \              LeftRotate(X) <=            /  \
      A    B                                        B    C

 * Performs a right rotation on the given AVL tree node 'Y' (current node).
 * The right rotation transforms the structure of the tree to maintain the AVL balance property.
 * After the rotation, the right child 'X' of 'Y' becomes the new root of the rotated subtree,
 * while 'Y' becomes the left child of 'X'. If 'B' is the right child of 'X', it becomes the left child of 'Y'.
 *
 * @param node The AVL tree node to perform the right rotation on ('Y').
 * @return The new root node ('X') of the rotated subtree after the right rotation.
 */
AVLNodePtr rightRotate(AVLNodePtr node) {
    if (node == NULL || node->child[LEFT] == NULL) {
        return node; // No right rotation is possible; return the node itself.
    }

    AVLNodePtr X = node->child[LEFT]; // 'X' is the right child of 'Y' (current node).
    AVLNodePtr B = X->child[RIGHT]; // 'B' is the right child of 'X'.

    // Update parent pointers to adjust the tree structure.
    X->parent = node->parent; // 'X' inherits 'Y's parent.

    // Update 'Y's parent data.
    if (node->parent) {
        if (node->parent->child[LEFT] == node)
            node->parent->child[LEFT] = X; // 'X' becomes the left child of the current parent.
        else
            node->parent->child[RIGHT] = X; // 'X' becomes the right child of the current parent.
    }

    node->parent = X; // 'Y' becomes the left child of 'X'.
    if (B)
        B->parent = node; // If 'B' exists, update its parent to be 'Y'.

    // Perform rotation by updating child pointers.
    X->child[RIGHT] = node; // Update 'X' to point to 'Y' as its right child.
    node->child[LEFT] = B; // 'Y' adopts 'B' as its left child.

    // Update node properties to maintain the AVL balance.
    updateNodeProperties(node);
    updateNodeProperties(X);
    updateNodeProperties(X->parent);

    return X; // Return the new root node ('X') of the rotated subtree.
}
AVLNodePtr leftRotate(AVLNodePtr node) {
    if (node == NULL || node->child[RIGHT] == NULL) {
        return node;
    }

    AVLNodePtr Y = node->child[RIGHT];
    AVLNodePtr B = Y->child[LEFT];

    // Update parent pointers
    Y->parent = node->parent;
    if (node->parent) {
        if (node->parent->child[LEFT] == node)
            node->parent->child[LEFT] = Y;
        else
            node->parent->child[RIGHT] = Y;
    }

    node->parent = Y;
    if (B)
        B->parent = node;

    // Perform rotation
    Y->child[LEFT] = node;
    node->child[RIGHT] = B;

    // Update Node's Properties
    updateNodeProperties(node);
    updateNodeProperties(Y);
    updateNodeProperties(Y->parent);

    return Y;
}
AVLNodePtr First(AVLNodePtr node) {
    AVLNodePtr current = node;
    while (current && current->child[LEFT])
        current = current->child[LEFT];

    return current;
}
AVLNodePtr Last(AVLNodePtr node) {
    AVLNodePtr current = node;
    while (current && current->child[RIGHT])
        current = current->child[RIGHT];

    return current;
}
AVLNodePtr getSuccessor(AVLNodePtr node) {
    if (!node)
        return NULL;

    if (node->child[RIGHT])
        return node->child[RIGHT]->min;
    else {
        AVLNodePtr current = node;
        while (current && current->parent) {
            if (current->parent->child[LEFT] == current)
                return current->parent;
            current = current->parent;
        }
        return current;
    }
}
AVLNodePtr getPredecessor(AVLNodePtr node) {
    if (!node)
        return NULL;

    if (node->child[LEFT])
        return node->child[LEFT]->max;
    else {
        AVLNodePtr current = node;
        while (current && current->parent) {
            if (current->parent->child[RIGHT] == current)
                return current->parent;
            current = current->parent;
        }
        return current;
    }
}
AVLNodePtr getSubtreeAt(AVLNodePtr root, int index)
{
    int leftChildSubtreeSize = 0;
    if (root == NULL || index < 0)
        return NULL;
    if (root->child[LEFT])
        leftChildSubtreeSize = root->child[LEFT]->rank;
    if (index == leftChildSubtreeSize)
        return root;
    if (index < leftChildSubtreeSize)
        return getSubtreeAt(root->child[LEFT], index);
    if (index > leftChildSubtreeSize)
        return getSubtreeAt(root->child[RIGHT], index - leftChildSubtreeSize - 1);
    return NULL;
}
/***
 * @param node
 * @return int index of a node in the travesale soreted inorder relative to the root
 ***/
int getIndex(AVLNodePtr node) {
    if (!node)
        return 0;

    int index = 0;

    if (node->child[LEFT])
        index = node->child[LEFT]->rank;

    AVLNodePtr current = node;
    while (current->parent) {
        if (current->parent->child[RIGHT] == current) {
            if (current->parent->child[LEFT])
                index += current->parent->child[LEFT]->rank + 1;
            else
                index++;
        }
        current = current->parent;
    }

    return index;
}
/***
 * @param node
 * @return int index of a node in the travesale inorder relative to the a tree rooted in a given node
 ***/
int getRelativeIndex(AVLNodePtr root,AVLNodePtr node) {
    if (!node)
        return 0;

    int index = 0;

    if (node->child[LEFT])
        index = node->child[LEFT]->rank;

    AVLNodePtr current = node;
    while (current->parent && current->parent != root) {
        if (current->parent->child[RIGHT] == current) {
            if (current->parent->child[LEFT])
                index += current->parent->child[LEFT]->rank + 1;
            else
                index++;
        }
        current = current->parent;
    }

    return index;
}
/***
 *
 * @param root
 * @param x1
 * @param x2
 * @return LCA of x1 and x2 even if those keys are not exists in the tree
 ***/
AVLNodePtr getLca(AVLNodePtr root, int x1, int x2) {
    AVLNodePtr lcaa;
    if (root == NULL)
        return NULL;

    swapIfNotEqual(&x1, &x2);

    AVLNodePtr node1 = search(root, x1, x1);
    AVLNodePtr node2 = search(root, x2, x2);

    // If both keys exist
    if (node1->key == x1 && node2->key == x2)
        return lca(root, x1, x2);

    if (node1->key < x1)
        node1 = getSuccessor(node1);
    if (node2->key > x2)
        node2 = getPredecessor(node2);

    lcaa = lca(root, node1->key, node2->key);
    if ( lcaa->key >= x1 && lcaa->key <= x2 )
        return lcaa;
    else
        return NULL;
}
AVLNodePtr lca(AVLNodePtr root, int x1, int x2){
    // Base case
    if (root == NULL)
        return root;

    // If either n1 or n2 matches with root's key, report
    // the presence by returning root (Note that if a key is
    // ancestor of other, then the ancestor key becomes LCA
    if (root->key == x1 || root->key == x2)
        return root;

    // Look for keys in left and right subtrees
    AVLNodePtr leftLca = lca(root->child[LEFT], x1, x2);
    AVLNodePtr rightLca = lca(root->child[RIGHT], x1, x2);

    // If both of the above calls return Non-NULL, then one
    // key is present in once subtree and other is present
    // in other, So this node is the LCA
    if (leftLca && rightLca)
        return root;

    // Otherwise check if left subtree or right subtree is LCA
    return (leftLca != NULL) ? leftLca : rightLca;
}
AVLNodePtr search(AVLNodePtr root, int x, int y){
    if (root == NULL)
        return NULL;

    if (root->key == x && root->y == y)
        return root;

    // Leaf
    if (root->child[LEFT] == NULL && root->child[RIGHT] == NULL)
        return root;

    if (root->key < x && root->child[RIGHT])
        return search(root->child[RIGHT], x, y);
    else if (root->key > x && root->child[LEFT])
        return search(root->child[LEFT], x, y);

    return root;
}
int howMany(AVLNodePtr root, int x1, int x2){
    int smallerNodeIndex = -1;
    int biggerNodeIndex = -1;
    if (root == NULL)
        return 0;

    swapIfNotEqual(&x1, &x2);

    AVLNodePtr smallerNode = search(root, x1, x1);
    AVLNodePtr biggerNode = search(root, x2, x2);

    if (smallerNode->key == x1 && biggerNode->key == x2 && smallerNode==biggerNode)
        return 1;

    if (smallerNode->key == x1)
        smallerNodeIndex = getIndex(smallerNode);
    else{
        if (smallerNode->key < x1)
            smallerNode = getSuccessor(smallerNode);
    }

    if (biggerNode->key == x2)
        biggerNodeIndex = getIndex(biggerNode);
    else{
        if (biggerNode->key > x2)
            biggerNode = getPredecessor(biggerNode);
    }

    if (smallerNode==biggerNode && smallerNode->key >= x1 && smallerNode->key <= x2)
        return 1;

    if (smallerNodeIndex > -1 && biggerNodeIndex > -1)
        return smallerNode == biggerNode ? 1 : abs(biggerNodeIndex-smallerNodeIndex) + 1;
    else{
        if (smallerNode==biggerNode && smallerNode->key >= x1 && smallerNode->key <= x2)
            return 1;
        if (smallerNodeIndex == -1)
            smallerNodeIndex = getIndex(smallerNode);
        if (biggerNodeIndex == -1)
            biggerNodeIndex = getIndex(biggerNode);
    }

    if (smallerNode->key >= x1 && biggerNode->key <= x2 && smallerNode->key <= biggerNode->key)
        return smallerNode == biggerNode ? 1 : abs(biggerNodeIndex-smallerNodeIndex) + 1;
    else
        return -1;

}
AVLNodePtr newAvlNode(int x, int y){
    AVLNodePtr newnode = (AVLNodePtr) malloc(sizeof(AVLNode));
    if (!newnode)
        return NULL;

    newnode->key = x;
    newnode->y = y;
    newnode->child[LEFT] = NULL;
    newnode->child[RIGHT] = NULL;
    newnode->parent = NULL;
    updateNodeProperties(newnode);
    return newnode;
}
void deleteAvlTree(AVLNodePtr root) {
    if (root == NULL)
        return;

    deleteAvlTree(root->child[LEFT]);
    deleteAvlTree(root->child[RIGHT]);

    free(root);
}
AVLNodePtr avlSearch(AVLNodePtr root, int x, int y) {
    if (root == NULL)
        return NULL;

    if (root->key == x && root->y == y)
        return root;

    if (root->key < x)
        return avlSearch(root->child[RIGHT], x, y);
    else
        return avlSearch(root->child[LEFT], x, y);
}
AVLNodePtr avlInsert(AVLNodePtr root, int x, int y) {
    if (!root) {
        return newAvlNode(x, y);
    }

    if (x < root->key) {
        root->child[LEFT] = avlInsert(root->child[LEFT], x, y);
        root->child[LEFT]->parent = root;
    }
    else if (x > root->key) {
        root->child[RIGHT] = avlInsert(root->child[RIGHT], x, y);
        root->child[RIGHT]->parent = root;
    }
    else {
        root->y = y > root->y ? y : root->y;
        return root;
    }

    // Call rebalance function
    root = rebalance(root);

    return root;
}
AVLNodePtr avlDelete(AVLNodePtr root, int x, int y) {
    if (!root)
        return root;

    AVLNodePtr nodeToDelete = avlSearch(root, x, y);
    if (!nodeToDelete)
        return root;

    if (x < root->key)
        root->child[LEFT] = avlDelete(root->child[LEFT], x, y);
    else if (x > root->key)
        root->child[RIGHT] = avlDelete(root->child[RIGHT], x, y);
    else {
        if (y != root->y)
            return root;

        // A Node with one child
        if (root->child[LEFT] == NULL || root->child[RIGHT] == NULL) {
            AVLNodePtr child = root->child[LEFT] ? root->child[LEFT] : root->child[RIGHT];

            // No children at all
            if (!child) {
                child = root;
                root = NULL;
            }
            else {
                AVLNodePtr rootParent = root->parent;
                if (rootParent->child[LEFT] == root) {
                    rootParent->child[LEFT] = child;
                }
                else {
                    rootParent->child[RIGHT] = child;
                }
                child->parent = rootParent;
                root = child;

                // Update node properties and parent properties
                updateAncestorProperties(child);
                updateAncestorProperties(rootParent);
            }

            free(nodeToDelete);
        }
        else {
            AVLNodePtr successor = getSuccessor(root);
            AVLNodePtr successorParent = successor->parent;
            AVLNodePtr successorRightChild = successor->child[RIGHT];
            AVLNodePtr nodeToDeleteRightChild = root->child[RIGHT];
            AVLNodePtr nodeToDeleteLeftChild = root->child[LEFT];
            AVLNodePtr nodeToDeleteParent = root->parent;

            if (successorParent != root) {
                successorParent->child[LEFT] = successorRightChild;
                if (successorRightChild) {
                    successorRightChild->parent = successorParent;
                }

                successor->child[RIGHT] = nodeToDeleteRightChild;
                if (nodeToDeleteRightChild) {
                    nodeToDeleteRightChild->parent = successor;
                }

                successor->child[LEFT] = nodeToDeleteLeftChild;
                if (nodeToDeleteLeftChild) {
                    nodeToDeleteLeftChild->parent = successor;
                }

                if (nodeToDeleteParent) {
                    if (nodeToDeleteParent->child[LEFT] == root) {
                        nodeToDeleteParent->child[LEFT] = successor;
                    } else {
                        nodeToDeleteParent->child[RIGHT] = successor;
                    }
                } else {
                    root = successor;
                }

                successor->parent = nodeToDeleteParent;

                // Update node properties
                updateNodeProperties(successorParent);
                updateAncestorProperties(successorParent);
            } else {
                successor->child[LEFT] = nodeToDeleteLeftChild;
                if (nodeToDeleteLeftChild) {
                    nodeToDeleteLeftChild->parent = successor;
                }

                if (nodeToDeleteParent) {
                    if (nodeToDeleteParent->child[LEFT] == root) {
                        nodeToDeleteParent->child[LEFT] = successor;
                    } else {
                        nodeToDeleteParent->child[RIGHT] = successor;
                    }
                } else {
                    root = successor;
                }

                successor->parent = nodeToDeleteParent;
            }
            free(nodeToDelete);
            root = avlDelete(successor, x, y);

        }
    }

    if (root == NULL)
        return root;


    root = rebalance(root);

    return root;
}
AVLNodePtr deleteThird(AVLNodePtr root, int x1, int x2) {
    if (root == NULL)
        return root; // Base case: If the tree is empty, return NULL.

    // Ensure that x1 is the smaller value and x2 is the larger value.
    swapIfNotEqual(&x1, &x2);

    // Calculate the number of nodes between x1 and x2 (inclusive).
    int count = howMany(root, x1, x2);

    // Variables to support the node deletion process.
    int next = 0; // Number of nodes to skip in the deletion process.
    int eligible = !(count % 3); // Flag indicating if count is divisible by 3.
    int lowerBoundIndexRelativeToRoot = 0; // Index of lower bound relative to the root.
    int biggerBoundIndexRelativeToRoot = 0; // Index of bigger bound relative to the root.

    // Find the Least Common Ancestor (LCA) of nodes with values x1 and x2.
    AVLNodePtr LCA = getLca(root, x1, x2);

    // Find nodes with values x1 and x2 in the LCA subtree.
    AVLNodePtr lower = search(LCA, x1, x1);
    AVLNodePtr bigger = search(LCA, x2, x2);

    AVLNodePtr nodeL;
    AVLNodePtr nodeR;
    AVLNodePtr preNodeR;
    AVLNodePtr sucNodeL;

    // Print the initial number of nodes between x1 and x2.
    printf("Before There are %d nodes between %d to %d\n", count, x1, x2);

    // Proceed with node deletion only if the number of nodes is divisible by 3.
    if (eligible) {
        count /= 3; // Divide the number of nodes by 3.
        next = count; // Number of nodes to skip during deletion.

        // Ensure that the lower node is the successor of x1.
        // If not, move to the successor.
        if (lower->key < x1) {
            lower = getSuccessor(lower);
        }

        // Get the index of the lower and bigger bounds relative to the root.
        lowerBoundIndexRelativeToRoot = getIndex(lower);
        biggerBoundIndexRelativeToRoot = getIndex(bigger);

        // Get the nodes to the left and right of the range for deletion.
        nodeL = getSubtreeAt(root, lowerBoundIndexRelativeToRoot + next - 1);
        nodeR = getSubtreeAt(root, biggerBoundIndexRelativeToRoot - next + 1);
        sucNodeL = getSuccessor(nodeL);
        preNodeR = getPredecessor(nodeR);

        // Delete nodes in pairs (nodeL and sucNodeL, preNodeR and nodeR).
        while (nodeL != preNodeR && nodeR != sucNodeL && preNodeR != sucNodeL) {
            root = avlDelete(root, preNodeR->key, preNodeR->y);
            root = avlDelete(root, sucNodeL->key, sucNodeL->y);
            sucNodeL = getSuccessor(nodeL);
            preNodeR = getPredecessor(nodeR);
        }

        // Rebalance ancestors of the nodes that were deleted.
        if (getSuccessor(nodeR))
            root = rebalanceAncestors(getSuccessor(nodeR));
        if (getPredecessor(nodeL))
            root = rebalanceAncestors(getPredecessor(nodeL));

        // Check if the expected number of nodes between x1 and x2 was deleted.
        // If not, delete one more node from the LCA subtree.
        if (howMany(root, x1, x2) != count * 2)
            root = avlDelete(root, sucNodeL->key, sucNodeL->y);

        // Rebalance ancestors again if needed.
        if (getSuccessor(nodeR))
            root = rebalanceAncestors(getSuccessor(nodeR));
        if (getPredecessor(nodeL))
            root = rebalanceAncestors(getPredecessor(nodeL));

        // Recalculate the number of nodes between x1 and x2 after the deletion.
        count = howMany(root, x1, x2);
        printf("After There are %d nodes between %d to %d\n", count, x1, x2);
    }

    // Return the root of the AVL tree after the deletion process.
    return root;
}
void printNode(AVLNodePtr node){
    if (node) {
        printf("(key: %d, y: %d, subtree size: %d, index: %d) \n" ,node->key ,node->y ,node->rank, getIndex(node));
    }
}
void printInorder(AVLNodePtr root) {
    if (root) {
        printInorder(root->child[LEFT]);
        printf("(%d,%d) ", root->key, root->y);
        printInorder(root->child[RIGHT]);
    }
}
void printPreorder(AVLNodePtr root) {
    if (root) {
        printf("%d ", root->key);
        printPreorder(root->child[LEFT]);
        printPreorder(root->child[RIGHT]);
    }
}
void swapIfNotEqual(int *x1, int *x2) {
    if (*x1 != *x2) {
        int temp = (*x1 > *x2) ? *x1 : *x2;
        *x1 = (*x2 == temp) ? *x1 : *x2;
        *x2 = temp;
    }
}
