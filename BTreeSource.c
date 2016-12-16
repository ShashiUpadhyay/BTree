/* 
 * File:   BTreeSource.c
 * Author: shashiupadhyay
 *
 * Created on December 12, 2015, 6:25 PM
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <limits.h>
#include "BTreeHeader.h"

Tree *createTree() {
    Tree *btree = (Tree*) malloc(sizeof (Tree));
    btree->root_node = NULL;
    return btree;
}

Node *createNode(Data d) {
    Node *node = (Node*) malloc(sizeof (Node));
    node->data.number = d.number;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    return node;
}

void insert(Tree *bst, Data data) {
    printf("Inserting value in B-Tree %d\n", data.number);
    //    Create the first Node (root Node)
    if (bst->root_node == NULL) {
        Node* new_created_node = createNode(data);
        bst->root_node = new_created_node;
    } else {
        insertNode(bst->root_node, data);
    }
}

void insertNode(Node *currentnode, Data data) {
    Node *newnode;
    if (currentnode->data.number == data.number) {
        printf("Insertion of duplicate values are not possible\n");
        return;
    } else if (currentnode->data.number > data.number) {
        if (currentnode->left == NULL) {
            newnode = createNode(data);
            currentnode->left = newnode;
            newnode->parent = currentnode;
        } else {
            insertNode(currentnode->left, data);
        }
    } else if (currentnode->data.number < data.number) {
        if (currentnode->right == NULL) {
            newnode = createNode(data);
            currentnode->right = newnode;
            newnode->parent = currentnode;
        } else {
            insertNode(currentnode->right, data);
        }
    } else {
        printf("Cannot insert duplicate values.\n");
    }
}

Node *search(Tree *bst, Data data) {
    if (bst->root_node == NULL) {
        printf("Tree is Null \n");
        return NULL;
    } else {
        return searchNode(bst->root_node, data);
    }
    return NULL;
}

Node *searchNode(Node *currentnode, Data data) {
    if (currentnode == NULL) {
        printf("Value missing in B-Tree \n");
        return NULL;
    }
    //    printf("currentnode->data.number : %d and data.number : %d\n", currentnode->data.number, data.number);
    if (currentnode->data.number == data.number) {
        printf("Element is present %d \n", currentnode->data.number);
        return currentnode;
    } else if (currentnode->data.number < data.number) {
        return searchNode(currentnode->right, data);
    } else {
        return searchNode(currentnode->left, data);
    }
}

void printInorder(Tree *bst) {
    if (bst->root_node == NULL) {
        printf("Tree is empty \n");
    } else {
        Node *node = bst->root_node;
        printInorderdata(node);
    }
}

void printInorderdata(Node *node) {
    if (node != NULL) {
        printInorderdata(node->left);
        printf(" %d ", node->data.number);
        printInorderdata(node->right);
    }
}

void printpreorder(Tree *bst) {
    if (bst->root_node == NULL) {
        printf("Tree is empty \n");
    } else {
        Node *node = bst->root_node;
        printpreorderdata(node);
    }
}

void printpreorderdata(Node *node) {
    if (node != NULL) {
        printf(" %d ", node->data.number);
        printpreorderdata(node->left);
        printpreorderdata(node->right);
    }
}

void printpostorder(Tree *bst) {
    if (bst->root_node == NULL) {
        printf("Tree is empty \n");
    } else {
        Node *node = bst->root_node;
        printpostorderdata(node);
    }
}

void printpostorderdata(Node *node) {
    if (node != NULL) {
        printpostorderdata(node->left);
        printpostorderdata(node->right);
        printf(" %d ", node->data.number);
    }
}

Node* deleteNode(Node *node) {
    free(node);
    return NULL;
}

void removeLeaf(Tree *bst, Node *d_node) {
    Node *parentnode = d_node->parent;
    if (parentnode->right != NULL) {
        if (parentnode->right->data.number == d_node->data.number) {
            deleteNode(d_node);
            parentnode->right = NULL;
            d_node = NULL;
            return;
        }
    }
    if (parentnode->left != NULL) {
        if (parentnode->left->data.number == d_node->data.number) {
            deleteNode(d_node);
            parentnode->left = NULL;
            d_node = NULL;
            return;
        }
    }
     if (parentnode->right == NULL && parentnode->left == NULL) {
        deleteNode(bst->root_node);
        bst->root_node = NULL;
        return;
    }
}
void shortCircuit(Tree *bst, Node *d_node) {
    Node *parentnode = d_node->parent;
    if (d_node->left != NULL) {
        if ((parentnode->left != NULL) && (parentnode->left->data.number == d_node->data.number)) {
            parentnode->left = d_node->left;
            parentnode->left->parent = parentnode;
            deleteNode(d_node);
        } else {
            parentnode->right = d_node->left;
            parentnode->right->parent = parentnode;
            deleteNode(d_node);
        }
    }

    if (d_node->right != NULL) {
        if ((parentnode->left != NULL) && (parentnode->left->data.number == d_node->data.number)) {
            parentnode->left = d_node->right;
            parentnode->left->parent = parentnode;
            deleteNode(d_node);
        } else {
            parentnode->right = d_node->right;
            parentnode->right->parent = parentnode;
            deleteNode(d_node);
        }
    }

}

void promotion(Tree *bst, Node *d_node) {
    Node *currentnode = d_node->right;
    while (currentnode->left != NULL) {
        currentnode = currentnode->left;
    }

    d_node->data = currentnode->data;
    if (currentnode->left == NULL && currentnode->right == NULL) {
        printf("Node to be removed : %d \n", currentnode->data.number);
        removeLeaf(bst, currentnode);
        return;
    }

    if (currentnode->left == NULL || currentnode->right == NULL) {
        printf("Node to be removed : %d \n", currentnode->data.number);
        shortCircuit(bst, currentnode);

        return;
    }
}

void removeOtherNode(Node* current, Data value) {
    Tree *bst;
    if (current->data.number == value.number) {
        if (current->left == NULL && current->right == NULL) {
            removeLeaf(bst, current);
        } else if (current->left == NULL || current->right == NULL) {
            shortCircuit(bst, current);
        } else {
            promotion(bst, current);
        }
    } else if (current->data.number < value.number) {
        removeOtherNode(current->right, value);
    } else if (current->data.number > value.number) {

        removeOtherNode(current->left, value);
    }
}

void removeRootNode(Tree *bst) {
    Node *nodetoberemoved;
    if (bst->root_node == NULL) {
        printf("B-Tree is empty \n");
        return;
    }
    if (bst->root_node->right == NULL && bst->root_node->left == NULL) {
        deleteNode(bst->root_node);
        bst->root_node = NULL;
        return;
    } else if (bst->root_node->left == NULL && bst->root_node->right != NULL) {
        nodetoberemoved = bst->root_node;
        bst->root_node = bst->root_node->right;
        deleteNode(nodetoberemoved);
        nodetoberemoved = NULL;
    } else if (bst->root_node->left != NULL && bst->root_node->right == NULL) {
        nodetoberemoved = bst->root_node;
        bst->root_node = bst->root_node->left;
        deleteNode(nodetoberemoved);
        nodetoberemoved = NULL; 
    } else {
        Node *rootnode = bst->root_node;
        Node *nexthighestnode = getnextMaxNode(rootnode);
        bst->root_node->data = nexthighestnode->data;
        if (nexthighestnode->left == NULL && nexthighestnode->right == NULL) {
            removeLeaf(bst, nexthighestnode);
            return;
        } else if (nexthighestnode->left == NULL || nexthighestnode->right == NULL) {
            shortCircuit(bst, nexthighestnode);
            return;
        }
    }
}

void removeNode(Tree *bst, Data value) {
    if (bst->root_node == NULL) {
        printf("Tree is empty. \n");
        return;
    } else {
        printf("Searching Node in B Tree\n");
        Node *nodestatus = search(bst, value);
        if (nodestatus == NULL) {
            printf("Value not present in B-Tree. \n");
        } else {
            if (bst->root_node->data.number == value.number) {
                removeRootNode(bst);
            } else {

                removeOtherNode(bst->root_node, value);
            }
        }
    }
}

Node *getnextMaxNode(Node *d_node) {
    Node *currentnode = d_node;
    currentnode = currentnode->right;
    while (currentnode->left != NULL) {

        currentnode = currentnode->left;
    }
    return currentnode;
}

Node *getnextMinNode(Node *d_node) {
    Node *currentnode = d_node;
    currentnode = currentnode->left;
    while (currentnode->right != NULL) {

        currentnode = currentnode->right;
    }
    return currentnode;
}

Node* postorderdeleteTree(Tree *binarytree, Node* current) {

    if (current->left != NULL) {
        postorderdeleteTree(binarytree, current->left);
    }
    if (current->right != NULL) {
        postorderdeleteTree(binarytree, current->right);
    }

    deleteNode(current);
    return NULL;
}

Tree *deleteTree(Tree *bst) {
    if (bst->root_node != NULL) {
        postorderdeleteTree(bst, bst->root_node);
    }
    free(bst);
    bst = NULL;
    return NULL;
}
