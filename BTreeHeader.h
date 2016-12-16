/* 
 * File:   BTreeHeader.h
 * Author: shashiupadhyay
 *
 * Created on December 12, 2015, 6:25 PM
 */

#ifndef BTREEHEADER_H
#define BTREEHEADER_H

typedef struct _Data {
    int number;
} Data;

typedef struct _Node {
    Data data;
    struct _Node *left;
    struct _Node *right;
    struct _Node *parent;
} Node;

typedef struct _BST {
    Node *root_node;
} Tree;

void insert(Tree *bst, Data data);
void insertNode(Node *node, Data data);
void printInorder(Tree *bst);
void printInorderdata(Node *node);
void printpreorder(Tree *bst);
void printpreorderdata(Node *node);
void printpostorder(Tree *bst);
void printpostorderdata(Node *node);
void removeLeaf(Tree *bst, Node *d_node);
void shortCircuit(Tree *bst, Node *d_node);
void promotion(Tree *bst, Node *d_node);
void removeNode(Tree * bst, Data value);
void removeRootNode(Tree *bst);
void removeOtherNode(Node* current, Data value);
Tree *createTree();
Node *createNode(Data d);
Node *searchNode(Node *node, Data data);
Node *search(Tree *bst, Data data);
Node* deleteNode(Node *node);
Node *getnextMaxNode(Node *d_node);
Node *getnextMinNode(Node *d_node);
Node* postorderdeleteTree(Tree *binarytree, Node* current);

#endif	/* BTREEHEADER_H */

