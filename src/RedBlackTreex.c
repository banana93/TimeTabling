#include <stdio.h>
#include "RedBlackTree.h"
#include "ErrorCode.h"
#include "Rotations.h"
#include "Node.h"

void addRedBlackTree(Node **nodePtr, Node *newNode)
{
  _addRedBlackTree(nodePtr, newNode);
  (*nodePtr)->color = 'b';
}

void _addRedBlackTree(Node **nodePtr, Node *newNode)
{
  if(*nodePtr == NULL)
  {
    *nodePtr = newNode;
    return;
  }
 
  if(newNode->data < (*nodePtr)->data)
  {
    _addRedBlackTree(&(*nodePtr)->left, newNode);
    solveAddViolationForNewNodeLessThan(&(*nodePtr)); // this function purpose is to solve the violation for those new node data that is less than the nodePtr data
    solveAddViolationFor4NodeLessThan(&(*nodePtr));
  }
  
  else
  {
    _addRedBlackTree(&(*nodePtr)->right, newNode); 
    solveAddViolationForNewNodeMoreThan(&(*nodePtr)); // this function purpose is to solve the violation for those new node data that is more than the nodePtr data
    solveAddViolationFor4NodeMoreThan(&(*nodePtr));
  }
}

void solveAddViolationForNewNodeLessThan(Node **nodePtr)
{
  if((*nodePtr)->left->left != NULL) {
    if(((*nodePtr)->left->color == 'r' && (*nodePtr)->left->left->color == 'r' && (*nodePtr)->right == NULL) ||
       ((*nodePtr)->left->color == 'r' && (*nodePtr)->left->left->color == 'r' && (*nodePtr)->right->color == 'b')) {
     
      rightRotate(&(*nodePtr));
      (*nodePtr)->right->color = 'r';
    
    }
  } else if((*nodePtr)->left->right != NULL) {
      if(((*nodePtr)->left->color == 'r' && (*nodePtr)->left->right->color == 'r' && (*nodePtr)->right == NULL) ||
        ((*nodePtr)->left->color == 'r' && (*nodePtr)->left->right->color == 'r' && (*nodePtr)->right->color == 'b')) {
       
        leftRightRotate(&(*nodePtr));
        (*nodePtr)->right->color = 'r';
      
      }
    } 
}

void solveAddViolationForNewNodeMoreThan(Node **nodePtr)
{
  if((*nodePtr)->right->right != NULL) {
    if(((*nodePtr)->right->color == 'r' && (*nodePtr)->right->right->color == 'r' && (*nodePtr)->left == NULL) ||
      ((*nodePtr)->right->color == 'r' && (*nodePtr)->right->right->color == 'r' && (*nodePtr)->left->color == 'b')){
      
      leftRotate(&(*nodePtr));
      (*nodePtr)->left->color = 'r';
    
    } 
  } else if ((*nodePtr)->right->left != NULL) {
      if(((*nodePtr)->right->color == 'r' && (*nodePtr)->right->left->color == 'r' && (*nodePtr)->left == NULL) || 
        ((*nodePtr)->right->color == 'r' && (*nodePtr)->right->left->color == 'r' && (*nodePtr)->left->color == 'b')){
       
        rightLeftRotate(&(*nodePtr));
        (*nodePtr)->left->color = 'r';
      
      }
   }
}  

void solveAddViolationFor4NodeLessThan(Node **nodePtr)
{
  if((*nodePtr)->left->left != NULL && (*nodePtr)->right != NULL) {
    if((*nodePtr)->left->color == 'r' && (*nodePtr)->right->color == 'r' && (*nodePtr)->left->left->color == 'r') {
     
      (*nodePtr)->left->color = 'b';
      (*nodePtr)->right->color = 'b';
      (*nodePtr)->color = 'r';
    
    }
  } else if((*nodePtr)->left->right != NULL && (*nodePtr)->right != NULL) {
      if((*nodePtr)->left->color == 'r' && (*nodePtr)->right->color == 'r' && (*nodePtr)->left->right->color == 'r') {
      
        (*nodePtr)->left->color = 'b';
        (*nodePtr)->right->color = 'b';
        (*nodePtr)->color = 'r';
      
      }
    }
}

void solveAddViolationFor4NodeMoreThan(Node **nodePtr)
{
  if((*nodePtr)->right->left != NULL && (*nodePtr)->left != NULL) {
    if((*nodePtr)->right->color == 'r' && (*nodePtr)->left->color == 'r' && (*nodePtr)->right->left->color == 'r') {
      
      (*nodePtr)->left->color = 'b';
      (*nodePtr)->right->color = 'b';
      (*nodePtr)->color = 'r';
    
    } 
  } else if((*nodePtr)->right->right != NULL && (*nodePtr)->left != NULL) {
      if((*nodePtr)->right->color == 'r' && (*nodePtr)->left->color == 'r' && (*nodePtr)->right->right->color == 'r') {
      
        (*nodePtr)->left->color = 'b';
        (*nodePtr)->right->color = 'b';
        (*nodePtr)->color = 'r';
        
      }
    }
}

Node *delRedBlackTree(Node **nodePtr, Node *delNode)
{
  Node *node = _delRedBlackTree(nodePtr, delNode);
  
  if((*nodePtr) != NULL)
    (*nodePtr)->color = 'b';
  
  return node;
}

Node *_delRedBlackTree(Node **nodePtr, Node *delNode)
{
  Node *tempNode = *nodePtr;
  Node *node;
  
  if(tempNode == NULL)
    Throw(ERR_NODE_UNAVAILABLE);
  
  if(tempNode->data == delNode->data) {
    *nodePtr = NULL;
    return tempNode;
  } else if(tempNode->data < delNode->data) {
      node = _delRedBlackTree(&tempNode->right, delNode); 
    } else if (tempNode->data > delNode->data) { 
        node = _delRedBlackTree(&tempNode->left, delNode);
      }

    if(nodePtr != NULL) {
      solveRemoveViolationFor3Nodes(nodePtr);
      solveRemoveViolationFor4Nodes(nodePtr);
    }
    
  return node;
}

void solveRemoveViolationFor3Nodes(Node **nodePtr)
{
  if((*nodePtr)->left == NULL && (*nodePtr)->right != NULL) {
    if((*nodePtr)->right->right != NULL && (*nodePtr)->right->left != NULL) {
     
      leftRotate(&(*nodePtr));
      (*nodePtr)->left->right->color = 'r';
    
    }
  } else if((*nodePtr)->left != NULL && (*nodePtr)->right == NULL) {
      if((*nodePtr)->left->left != NULL && (*nodePtr)->left->right != NULL) {
        
        rightRotate(&(*nodePtr));
        (*nodePtr)->right->left->color = 'r';
      
      }
    } else if((*nodePtr)->left != NULL && (*nodePtr)->right != NULL) {
        if((*nodePtr)->left->left == NULL && (*nodePtr)->right->right != NULL && (*nodePtr)->right->left == NULL) {
    
          (*nodePtr)->right->color = 'b';
          (*nodePtr)->right->right->color = 'r';
      
        } else if((*nodePtr)->left->left == NULL && (*nodePtr)->right->right == NULL && (*nodePtr)->right->left != NULL) {
          
            (*nodePtr)->right->color = 'b';
            (*nodePtr)->right->left->color = 'r';
        
          } else if((*nodePtr)->right->right == NULL && (*nodePtr)->left->left == NULL && (*nodePtr)->left->right != NULL) {
              
              (*nodePtr)->left->color = 'b';
              (*nodePtr)->left->right->color = 'r';
            
            } else if ((*nodePtr)->right->right == NULL && (*nodePtr)->left->right == NULL && (*nodePtr)->left->left != NULL) {
                
                (*nodePtr)->left->color = 'b';
                (*nodePtr)->left->left->color = 'r';
              
              }
      } 
}

void solveRemoveViolationFor4Nodes(Node **nodePtr)
{
  if((*nodePtr)->left != NULL && (*nodePtr)->right != NULL) {
    if((*nodePtr)->right->right != NULL && (*nodePtr)->left->left == NULL && (*nodePtr)->left->right != NULL) {
      
      (*nodePtr)->left->color = 'b';
      (*nodePtr)->left->right->color = 'r';
    
    } else if((*nodePtr)->right->right != NULL && (*nodePtr)->left->left != NULL && (*nodePtr)->left->right == NULL) {
      
        (*nodePtr)->left->color = 'b';
        (*nodePtr)->left->left->color = 'r';
      
      } else if((*nodePtr)->left->left != NULL && (*nodePtr)->right->right != NULL && (*nodePtr)->right->left == NULL) {
          
          (*nodePtr)->right->color = 'b';
          (*nodePtr)->right->right->color = 'r';
        
        } else if((*nodePtr)->left->left != NULL && (*nodePtr)->right->right == NULL && (*nodePtr)->right->left != NULL) {
         
            (*nodePtr)->right->color = 'b';
            (*nodePtr)->right->left->color = 'r';
          
          }
  }
}
