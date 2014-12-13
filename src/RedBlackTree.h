#ifndef RedBlackTree_H
#define RedBlackTree_H

#include "Rotations.h"
#include "Node.h"
#include "InitNode.h"

void addRedBlackTree(Node **nodePtr, Node *newNode);
void _addRedBlackTree(Node **nodePtr, Node *newNode);
void solveAddViolationForNewNodeLessThan(Node **nodePtr);
void solveAddViolationForNewNodeMoreThan(Node **nodePtr);
void solveAddViolationFor4NodeLessThan(Node **nodePtr);
void solveAddViolationFor4NodeMoreThan(Node **nodePtr);
Node *delRedBlackTree(Node **nodePtr, Node *delNode);
Node *_delRedBlackTree(Node **nodePtr, Node *delNode);
Node *_delRedBlackTreeX(Node **nodePtr, Node *delNode);
int isRed(Node **nodePtr);
int isBlack(Node **nodePtr);
int isDoubleBlack(Node **nodePtr, Node *removeNode);
void checkCase(Node **nodePtr, Node *removeNode);
void solveCase1LeftRemoveViolation(Node **nodePtr, Node *removeNode);
void solveCase1RightRemoveViolation(Node **nodePtr, Node *removeNode);
void solveCase2LeftRemoveViolation(Node **nodePtr, Node *removeNode);
void solveCase2RightRemoveViolation(Node **nodePtr, Node *removeNode);
void solveCase3LeftRemoveViolation(Node **nodePtr, Node *removeNode);
void solveCase3RightRemoveViolation(Node **nodePtr, Node *removeNode);
Node *removeNextLargerSuccessor(Node **nodePtr);
int compare(Node **nodePtr, Node *newNode);
void genericRedBlackTreeAdd(Node **nodePtr, Node *newNode, int (*compare)(Node **nodePtr, Node *newNode));
void _genericRedBlackTreeAdd(Node **nodePtr, Node *newNode, int (*Compare)(Node **nodePtr, Node *newNode));
Node *removeLargestValue(Node **nodePtr);

#endif // RedBlackTree_H
