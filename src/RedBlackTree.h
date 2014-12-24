#ifndef RedBlackTree_H
#define RedBlackTree_H

#include "Node.h"

int compareViolation(Node *nodePtr, Node *newNode);
void addRedBlackTree(Node **rootPtr, Node *newNode, int (*compare)(Node *rootPtr, Node *newNode));
void _addRedBlackTree(Node **rootPtr, Node *newNode, int (*compare)(Node *rootPtr, Node *newNode));
Node *delRedBlackTree(Node **rootPtr, Node *newNode);
Node *_delRedBlackTree(Node **rootPtr, Node *newNode);
Node *fileEqualRedBlackTree(Node **rootPtr, Node *newNode, int(*compare)(Node *rootPtr));

void restructureTree(Node **rootPtr, Node *removedNode);
void removeLeftCaseOne(Node **rootPtr);
void removeRightCaseOne(Node **rootPtr);

void removeLeftCaseTwo(Node **rootPtr, Node *removedNode);
void removeRightCaseTwo(Node **rootPtr, Node *removedNode);

void removeLeftCaseThree(Node **rootPtr, Node *removedNode);
void removeRightCaseThree(Node **rootPtr, Node *removedNode);

Node *removeNextLargerSuccessor(Node **rootPtr);


int isRed(Node *node);
int isBlack(Node *node);
int isDoubleBlack(Node *node, Node *removedNode);


//To check violation and rotate if needed
void checkViolationAndRotate(Node **rootPtr);

#define addPopulation(root, newNode) addRedBlackTree(root, newNode, compareViolation)

#endif // RedBlackTree_H
