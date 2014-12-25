#include <stdio.h>
#include "RedBlackTree.h"
#include "Rotations.h"
#include "Node.h"
#include "ErrorCode.h"
#include "CException.h"

/**
*	Important notes / information
*
*	exampleFunction(Node **nodePtr)
*	(**nodePtr).data //This is same
*	(*nodePtr)->data //with this
*
*	change root method
*	*nodePtr=&node5;
*/
#define leftChild (*rootPtr)->left
#define rightChild (*rootPtr)->right
#define leftLeftChild (*rootPtr)->left->left
#define leftRightChild (*rootPtr)->left->right
#define rightLeftChild (*rootPtr)->right->left
#define rightRightChild (*rootPtr)->right->right


/**
*	Input : root pointer / parent pointer
*	Output: void(no output)
*
*	Description:
*	Perform _addRedBlackTree and choose root to black after added.
*
*/
void addRedBlackTree(Node **rootPtr, Node *newNode){
	
	_addRedBlackTree(rootPtr, newNode);
	
	(*rootPtr)->color = 'b';
}

/**
*	Input : root pointer / parent pointer
*	Output: void(no output)
*
*	Description:
*	Add a new node into the tree at the proper leaf location
*
*/
void _addRedBlackTree(Node **rootPtr, Node *newNode){
	
	
	if(*rootPtr != NULL && (*rootPtr)->left != NULL && (*rootPtr)->right != NULL &&
		(*rootPtr)->left->color == 'r' && (*rootPtr)->right->color == 'r'){
		
		(*rootPtr)->color = 'r';
		(*rootPtr)->left->color = 'b';
		(*rootPtr)->right->color = 'b';
	}
	
	if(*rootPtr == NULL){
		*rootPtr = newNode;
		(*rootPtr)->color = 'r';
		return;
	}
		
	else if(newNode->data->violation < (*rootPtr)->data->violation)
		_addRedBlackTree(&((*rootPtr)->left), newNode);
	
	else if(newNode->data->violation > (*rootPtr)->data->violation)
		_addRedBlackTree(&((*rootPtr)->right), newNode);
	
	else
		Throw(ERR_EQUIVALENT_NODE);
		
	checkViolationAndRotate(rootPtr);
}

/**
*	Input : root pointer / parent pointer
*	Output: removed Node
*
*	Description:
*	Perform _deleteRedBlackTree and when it returns, change the rootPtr to Black.
*
*/
Node *delRedBlackTree(Node **rootPtr, Node *newNode){
	Node *retNode = _delRedBlackTree(rootPtr, newNode);
	
	if(*rootPtr != NULL)
		(*rootPtr)->color = 'b';
		
	return retNode;
}

/**
*	Input : root pointer / parent pointer
*	Output: removed Node
*
*	Description:
*	Recursive until the value is found, remove and return it.
*	If the value can't be found, error will be thrown
*/
Node *_delRedBlackTree(Node **rootPtr, Node *newNode){

	Node *retNode;
	Node *successorNode;
	
	if(!*rootPtr || !newNode)
		Throw(ERR_NODE_UNAVAILABLE);
		
	else if((*rootPtr)->data == newNode->data){
		Node *temporaryLeftChild = NULL;
		Node *temporaryRightChild = NULL;
		
		//for retaining the color instead of being overwritten
		Node temporarySuccessorNode; 
		
		char rootColor;
		retNode = *rootPtr;
		
		if(rightChild){
			successorNode = removeNextLargerSuccessor(&rightChild);
			temporarySuccessorNode = *successorNode;
			temporaryLeftChild = leftChild;
			temporaryRightChild = rightChild;
			
			rootColor = (*rootPtr)->color;
			*rootPtr = successorNode;
			(*rootPtr)->color = rootColor;
			
			leftChild = temporaryLeftChild;
			rightChild = temporaryRightChild;

			restructureTree(rootPtr, &temporarySuccessorNode);			
		}
		
		else if(leftChild){
			successorNode = leftChild;
			leftChild->color = (*rootPtr)->color;
			(*rootPtr) = leftChild;
		}
			
		else
		*rootPtr = NULL;

		return retNode;
	}
	
	else if(newNode->data < (*rootPtr)->data)
		retNode = _delRedBlackTree(&leftChild, newNode);
	
	else if(newNode->data > (*rootPtr)->data)
		retNode = _delRedBlackTree(&rightChild, newNode);
	
	restructureTree(rootPtr, retNode);
	
	return retNode;
}

/**
*	Input : root pointer / parent pointer
*	Output: removed Node
*
*	Description:
*	Remove the next larger successor of the node deleted, and return it.
*/
Node *removeNextLargerSuccessor(Node **rootPtr){
	Node *removedNode;

	if(leftChild){
		removedNode = removeNextLargerSuccessor(&leftChild);
		restructureTree(rootPtr, removedNode);
	}
	
	else if(!rightChild){
		removedNode = *rootPtr;
		*rootPtr = NULL;
		return removedNode;
	}
	
	else if(rightChild){
		removedNode = *rootPtr;
		*rootPtr = rightChild;
		(*rootPtr)->color = 'b';
		return removedNode;
	}
	
	return removedNode;

}

/**
*	Input : root pointer / parent pointer, removedNode
*	Output: void(no output)
*
*	Description:
*	Condition checking before choosing to perform case1, case2 or case3
*/
void restructureTree(Node **rootPtr, Node *removedNode){		
		("hi");

	if(isDoubleBlack(leftChild, removedNode)){
		("hi left");
		if(isBlack(rightChild)){
			if(isRed(rightLeftChild) || isRed(rightRightChild))
				removeLeftCaseOne(rootPtr);
			else if(isBlack(rightLeftChild) && isBlack(rightRightChild))
				removeLeftCaseTwo(rootPtr, removedNode);
		}
		else if(isRed(rightChild))
			removeLeftCaseThree(rootPtr, removedNode);
	}
	else if(isDoubleBlack(rightChild, removedNode)){
		("hi right");
		if(isBlack(leftChild)){
			if(isRed(leftRightChild) || isRed(leftLeftChild))
				removeRightCaseOne(rootPtr);
			else if(isBlack(leftLeftChild) && isBlack(leftRightChild))
				removeRightCaseTwo(rootPtr, removedNode);
		}
		else if(isRed(leftChild))
			removeRightCaseThree(rootPtr, removedNode);
	}
}

/**
*	Input : root pointer / parent pointer
*	Output: void(no output)
*
*	Description:
*	To perform case 1 for left case
*/
void removeLeftCaseOne(Node **rootPtr){
	char rootColor = (*rootPtr)->color;
	
	if(isRed(rightRightChild))
		leftRotate(rootPtr);
	
	else if(isRed(rightLeftChild))
		rightLeftRotate(rootPtr);
		
	if((*rootPtr)->left)
		leftChild->color = 'b';
	if((*rootPtr)->right)
		rightChild->color = 'b';
		
	(*rootPtr)->color = rootColor;

}

/**
*	Input : root pointer / parent pointer
*	Output: void(no output)
*
*	Description:
*	To perform case 1 for right case
*/
void removeRightCaseOne(Node **rootPtr){
	char rootColor = (*rootPtr)->color;
	
	if(isRed(leftLeftChild))
		rightRotate(rootPtr);
	
	else if(isRed(leftRightChild))
		leftRightRotate(rootPtr);
		
	if((*rootPtr)->left)
		leftChild->color = 'b';
	if((*rootPtr)->right)
		rightChild->color = 'b';
		
	(*rootPtr)->color = rootColor;

}

/**
*	Input : root pointer / parent pointer, removedNode
*	Output: void(no output)
*
*	Description:
*	To perform case 2 for left case
*/
void removeLeftCaseTwo(Node **rootPtr, Node *removedNode){
	
	if(isBlack(*rootPtr))
		(*rootPtr)->color = 'd';
	else if(isRed(*rootPtr))
		(*rootPtr)->color = 'b';

	if(isDoubleBlack(leftChild, removedNode) && leftChild)
		leftChild->color = 'b';
		
	if(rightChild)
		rightChild->color = 'r';
}

/**
*	Input : root pointer / parent pointer, removedNode
*	Output: void(no output)
*
*	Description:
*	To perform case 2 for right case
*/
void removeRightCaseTwo(Node **rootPtr, Node *removedNode){
	
	if(isBlack(*rootPtr))
		(*rootPtr)->color = 'd';
	else if(isRed(*rootPtr))
		(*rootPtr)->color = 'b';

	if(isDoubleBlack(rightChild, removedNode) && rightChild)
		rightChild->color = 'b';
		
	if(leftChild)
		leftChild->color = 'r';
}

/**
*	Input : root pointer / parent pointer, removedNode
*	Output: void(no output)
*
*	Description:
*	To perform case 3 for left case
*/
void removeLeftCaseThree(Node **rootPtr, Node *removedNode){

	leftRotate(rootPtr);
	(*rootPtr)->color = 'b';
	leftChild->color = 'r';
	
	if(isDoubleBlack(leftLeftChild, removedNode) && isBlack(leftRightChild)){
		if(isRed(leftRightChild->left) || isRed(leftRightChild->right))
			removeLeftCaseOne(&leftChild);
		else if(isBlack(leftRightChild->left) && isBlack(leftRightChild->right))
			removeLeftCaseTwo(&leftChild, removedNode);
	}

}

/**
*	Input : root pointer / parent pointer, removedNode
*	Output: void(no output)
*
*	Description:
*	To perform case 3 for right case
*/
void removeRightCaseThree(Node **rootPtr, Node *removedNode){
	
	rightRotate(rootPtr);
	(*rootPtr)->color = 'b';
	rightChild->color = 'r';
	
	if(isDoubleBlack(rightRightChild, removedNode) && isBlack(rightLeftChild)){
		if(isRed(rightLeftChild->left) || isRed(rightLeftChild->right))
			removeRightCaseOne(&rightChild);
		else if(isBlack(rightLeftChild->left) && isBlack(rightLeftChild->right))
			removeRightCaseTwo(&rightChild, removedNode);
	}

}

int isRed(Node *node){
	if(node && node->color == 'r')
		return 1;
	else
		return 0;
}
int isBlack(Node *node){
	if(!node)
		return 1;
	if(node && node->color == 'b')
		return 1;
	else
		return 0;
}

/**
* Note: x == not possible
*	node		removed node		return
*	---------------------------------------
*	NULL			NULL			  x
*	NULL			red			  	  0
*	NULL			black			  1
*	NULL			double black	  x
*	red				NULL			  x
*	red				red			  	  0
*	red				black			  0
*	red				double black	  x
*	black			NULL			  x
*	black			red			  	  0
*	black			black			  0
*	black			double black	  x
*	double black	NULL			  x
*	double black	red			  	  1
*	double black	black			  1
*	double black	double black	  x
*/
int isDoubleBlack(Node *node, Node *removedNode){
	if(node  && node->color == 'd')
		return 1;
	if(!node && isBlack(removedNode))
		return 1;
	return 0;
	
}

/**
*	Note:	Version that made by student (still have error)
*
*	Input : root pointer / parent pointer
*	Output: void(no output)
*
*	Description:
*	To check simple violation and rotate. 
*	Only used in addRedBlackTree because the requirements are sufficient for add, but not delete
*	New functions implemented to fulfill delRedBlackTree requirement.
*/
void checkViolationAndRotate(Node **rootPtr){

		
	if((*rootPtr)->left != NULL && (*rootPtr)->left->color == 'r'){
		if((*rootPtr)->left->left != NULL || (*rootPtr)->left->right != NULL){
			if((*rootPtr)->left->left != NULL &&(*rootPtr)->left->left->color == 'r')
				rightRotate(rootPtr);
		
			else if((*rootPtr)->left->right != NULL && (*rootPtr)->left->right->color == 'r')
				leftRightRotate(rootPtr);
				
			else 
				return;
				
			(*rootPtr)->right->color = 'r';
		}
	}
	
	else if((*rootPtr)->right != NULL && (*rootPtr)->right->color == 'r'){
		if((*rootPtr)->right->right != NULL || (*rootPtr)->right->left != NULL){
			if((*rootPtr)->right->right != NULL &&(*rootPtr)->right->right->color == 'r')
				leftRotate(rootPtr);
				
			else if((*rootPtr)->right->left != NULL &&(*rootPtr)->right->left->color == 'r')
				rightLeftRotate(rootPtr);
			
			else 
				return;
				
			(*rootPtr)->left->color = 'r';
		}
	}
}

/*
	Note:	Version that made ourself

Node *_delRedBlackTree(Node **rootPtr, Node *newNode){

	Node *retNode;
	
	if(*rootPtr != NULL && (*rootPtr)->left != NULL && (*rootPtr)->right != NULL &&
		(*rootPtr)->left->color == 'b' && (*rootPtr)->right->color == 'b'){
		
		(*rootPtr)->color = 'b';
		(*rootPtr)->left->color = 'r';
		(*rootPtr)->right->color = 'r';
	}
	
	if(*rootPtr == NULL || newNode == NULL)
		Throw(ERROR_NO_NODE);
		
	else if((*rootPtr)->data == newNode->data){
		 retNode = *rootPtr;
		*rootPtr = NULL;
		return retNode;
	}
	
	else if(newNode->data < (*rootPtr)->data)
		retNode = _delRedBlackTree(&((*rootPtr)->left), newNode);
	
	else if(newNode->data > (*rootPtr)->data)
		retNode = _delRedBlackTree(&((*rootPtr)->right), newNode);
	
	checkViolationAndRotate(rootPtr);
	return retNode;

}
*/
