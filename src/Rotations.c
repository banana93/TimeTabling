#include <stdio.h>
#include "Rotations.h"
#include "Node.h"

void rightRotate(Node **nodePtr)
{
  Node *node1, *node2;
  
  node1 = (*nodePtr)->left;
  node2 = node1->right;
  
  node1->right = *nodePtr;
  (*nodePtr)->left = node2;
  *nodePtr = node1;
}

void leftRotate(Node **nodePtr)
{
  Node *node1, *node2;
  
  node1 = (*nodePtr)->right;
  node2 = node1->left;
  
  node1->left = *nodePtr;
  (*nodePtr)->right = node2;
  *nodePtr = node1;
}

void leftRightRotate(Node **nodePtr)
{
  leftRotate(&(*nodePtr)->left);
  rightRotate(&(*nodePtr));
}

void rightLeftRotate(Node **nodePtr)
{
  rightRotate(&(*nodePtr)->right);
  leftRotate(&(*nodePtr));
}