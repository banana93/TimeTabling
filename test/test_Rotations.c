#include <stdio.h>
#include "unity.h"
#include "Rotations.h"
#include "Node.h"
#include "InitNode.h"

Node node1, node5, node6, node7, node8, node10, node13, node15, node17, node20, node30;

void setUp(void){
	resetNode(&node1, 1);
	resetNode(&node5, 5);
	resetNode(&node6, 6);
	resetNode(&node7, 7);
	resetNode(&node8, 8);
	resetNode(&node10, 10);
	resetNode(&node13, 13);
	resetNode(&node15, 15);
	resetNode(&node17, 17);
	resetNode(&node20, 20);
	resetNode(&node30, 30);
}

void tearDown(void){}

/**
 *          root
 *           |                   root
 *           v                    |
 *           10                   v
 *          /                     5
 *         5       ------>       /  \
 *        /                     1   10
 *       1
 */
void test_rightRotation_3_nodes(void)
{
	setNode(&node1, NULL, NULL, 'b');
	setNode(&node5, &node1, NULL, 'b');
	setNode(&node10, &node5, NULL, 'b');
	Node *root = &node10;
	
	rightRotate(&root);
	
	TEST_ASSERT_EQUAL_PTR(node1.left, NULL);
	TEST_ASSERT_EQUAL_PTR(node1.right, NULL);
	TEST_ASSERT_EQUAL_PTR(node10.left, NULL);
	TEST_ASSERT_EQUAL_PTR(node10.right, NULL);
	TEST_ASSERT_EQUAL_PTR(node5.left, &node1);
	TEST_ASSERT_EQUAL_PTR(node5.right, &node10);
	TEST_ASSERT_EQUAL_PTR(root, &node5);
}

/**
 *          root                        root
 *           |                           |
 *           v                           v
 *          10                           5
 *         /  \                         / \
 *        5    20    --------->        1   10
 *       /                                  \
 *      1                                   20
 */
void test_rightRotation_4_nodes(void)
{
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node5, &node1, NULL, 'b');
  setNode(&node20, NULL, NULL, 'b');
  setNode(&node10, &node5, &node20, 'b');
  Node *root = &node10;
  
  rightRotate(&root);
  
  TEST_ASSERT_EQUAL_PTR(node1.left, NULL);
  TEST_ASSERT_EQUAL_PTR(node1.right, NULL);
  TEST_ASSERT_EQUAL_PTR(node5.left, &node1);
  TEST_ASSERT_EQUAL_PTR(node5.right, &node10);
  TEST_ASSERT_EQUAL_PTR(node10.left, NULL);
  TEST_ASSERT_EQUAL_PTR(node10.right, &node20);
  TEST_ASSERT_EQUAL_PTR(node20.left, NULL);
  TEST_ASSERT_EQUAL_PTR(node20.left, NULL);
}

/**
 *          root                          root                                            
 *           |                             |
 *           v                             v
 *          20                            10
 *         /  \                          /  \
 *       10    30    ---------->        1   20
 *      /  \                               /  \
 *     1   15                             15   30
 */
void test_rightRotation_5_nodes(void)
{
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node15, NULL, NULL, 'b');
  setNode(&node10, &node1, &node15, 'b');
  setNode(&node30, NULL, NULL, 'b');
  setNode(&node20, &node10, &node30, 'b');
  Node *root = &node20;
  
  rightRotate(&root);
  
  TEST_ASSERT_EQUAL_PTR(node1.left, NULL);
  TEST_ASSERT_EQUAL_PTR(node1.right, NULL);
  TEST_ASSERT_EQUAL_PTR(node10.left, &node1);
  TEST_ASSERT_EQUAL_PTR(node10.right, &node20);
  TEST_ASSERT_EQUAL_PTR(node20.left, &node15);
  TEST_ASSERT_EQUAL_PTR(node20.right, &node30);
  TEST_ASSERT_EQUAL_PTR(node15.left, NULL);
  TEST_ASSERT_EQUAL_PTR(node15.right, NULL);
  TEST_ASSERT_EQUAL_PTR(node30.left, NULL);
  TEST_ASSERT_EQUAL_PTR(node30.right, NULL);
}

/**
 *         root                      root
 *          |                         |
 *          v                         v
 *         10                        15
 *           \                      /  \
 *            15    --------->    10    20
 *             \
 *              20
 */
void test_leftRotate_3_nodes(void)
{
  setNode(&node20, NULL, NULL, 'b');
  setNode(&node15, NULL, &node20, 'b');
  setNode(&node10, NULL, &node15, 'b');
  Node *root = &node10;
  
  leftRotate(&root);
  
  TEST_ASSERT_EQUAL_PTR(node10.left, NULL);
  TEST_ASSERT_EQUAL_PTR(node10.right, NULL);
  TEST_ASSERT_EQUAL_PTR(node15.left, &node10);
  TEST_ASSERT_EQUAL_PTR(node15.right, &node20);
  TEST_ASSERT_EQUAL_PTR(node20.left, NULL);
  TEST_ASSERT_EQUAL_PTR(node20.right, NULL);
}

/**
 *         root                          root
 *          |                             |
 *          v                             v
 *         10                            15
 *        /  \                          /  \
 *       5    15      ------------->  10   20
 *             \                      /
 *              20                   5
 */
void test_leftRotate_4_nodes(void)
{
  setNode(&node5, NULL, NULL, 'b');
  setNode(&node20, NULL, NULL, 'b');
  setNode(&node15, NULL, &node20, 'b');
  setNode(&node10, &node5, &node15, 'b');
  Node *root = &node10;
  
  leftRotate(&root);
  
  TEST_ASSERT_EQUAL_PTR(node5.left, NULL);
  TEST_ASSERT_EQUAL_PTR(node5.right, NULL);
  TEST_ASSERT_EQUAL_PTR(node10.left, &node5);
  TEST_ASSERT_EQUAL_PTR(node10.right, NULL);
  TEST_ASSERT_EQUAL_PTR(node15.left, &node10);
  TEST_ASSERT_EQUAL_PTR(node15.right, &node20);
  TEST_ASSERT_EQUAL_PTR(node20.left, NULL);
  TEST_ASSERT_EQUAL_PTR(node20.right, NULL);
}

/**
 *        root                        root
 *         |                           |
 *         v                           v
 *        10                          20
 *       /  \                        /  \
 *      5   20       ----------->  10   30
 *         /  \                   /  \
 *        15   30                5   15
 */
void test_leftRotate_5_nodes(void)
{
  setNode(&node5, NULL, NULL, 'b');
  setNode(&node15, NULL, NULL, 'b');
  setNode(&node30, NULL, NULL, 'b');
  setNode(&node20, &node15, &node30, 'b');
  setNode(&node10, &node5, &node20, 'b');
  Node *root = &node10;
  
  leftRotate(&root);
  
  TEST_ASSERT_EQUAL_PTR(node5.left, NULL);
  TEST_ASSERT_EQUAL_PTR(node5.right, NULL);
  TEST_ASSERT_EQUAL_PTR(node15.left, NULL);
  TEST_ASSERT_EQUAL_PTR(node15.right, NULL);
  TEST_ASSERT_EQUAL_PTR(node10.left, &node5);
  TEST_ASSERT_EQUAL_PTR(node10.right, &node15);
  TEST_ASSERT_EQUAL_PTR(node20.left, &node10);
  TEST_ASSERT_EQUAL_PTR(node20.right, &node30);
  TEST_ASSERT_EQUAL_PTR(node30.left, NULL);
  TEST_ASSERT_EQUAL_PTR(node30.right, NULL);
}

/**
 *       root                    root                  root
 *        |                       |                     |
 *        v                       v                     v
 *       10                      10                     7
 *       /                      /                      / \
 *      5        ---------->   7       --------->     5   10
 *       \                    /
 *        7                  5
 */
void test_leftRightRotate_3_nodes(void)
{
  setNode(&node7, NULL, NULL, 'b');
  setNode(&node5, NULL, &node7, 'b');
  setNode(&node10, &node5, NULL, 'b');
  Node *root = &node10;
  
  leftRightRotate(&root);
  
  TEST_ASSERT_EQUAL_PTR(node5.left, NULL);
  TEST_ASSERT_EQUAL_PTR(node5.right, NULL);
  TEST_ASSERT_EQUAL_PTR(node10.left, NULL);
  TEST_ASSERT_EQUAL_PTR(node10.right, NULL);
  TEST_ASSERT_EQUAL_PTR(node7.left, &node5);
  TEST_ASSERT_EQUAL_PTR(node7.right, &node10);
}

/**
 *      root                     root                   root
 *       |                        |                      |
 *       v                        v                      v
 *      10                       10                      7
 *     /                        /                       / \
 *    5       -------->        7        --------->     5   10
 *   / \                      /                       /
 *  1   7                    5                       1
 *                          /
 *                         1
 */
void test_leftRightRotate_4_nodes(void)
{
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node7, NULL, NULL, 'b');
  setNode(&node5, &node1, &node7, 'b');
  setNode(&node10, &node5, NULL, 'b');
  Node *root = &node10;
  
  leftRightRotate(&root);
  
  TEST_ASSERT_EQUAL_PTR(node1.left, NULL);
  TEST_ASSERT_EQUAL_PTR(node1.right, NULL);
  TEST_ASSERT_EQUAL_PTR(node10.left, NULL);
  TEST_ASSERT_EQUAL_PTR(node10.right, NULL);
  TEST_ASSERT_EQUAL_PTR(node5.left, &node1);
  TEST_ASSERT_EQUAL_PTR(node5.right, NULL);
  TEST_ASSERT_EQUAL_PTR(node7.left, &node5);
  TEST_ASSERT_EQUAL_PTR(node7.right, &node10);
}

/**
 *       root                   root                  root
 *        |                      |                     |
 *        v                      v                     v
 *       10                      10                    7
 *      /  \                    /  \                  / \
 *     5    15   --------->    7    15  -------->    5   10
 *    / \                     / \                   /   /  \
 *   1   7                   5   8                 1   8    15 
 *        \                 /
 *         8               1
 */
void test_leftRightRotate_6_nodes(void)
{
  setNode(&node1, NULL, NULL, 'b');
	setNode(&node8, NULL, NULL, 'b');
	setNode(&node7, NULL, &node8, 'b');
	setNode(&node5, &node1, &node7, 'b');
	setNode(&node15, NULL, NULL, 'b');
	setNode(&node10, &node5, &node15, 'b');
  Node *root = &node10;

  leftRightRotate(&root);

  TEST_ASSERT_EQUAL_PTR(node1.left, NULL);
  TEST_ASSERT_EQUAL_PTR(node1.right, NULL);
  TEST_ASSERT_EQUAL_PTR(node8.left, NULL);
  TEST_ASSERT_EQUAL_PTR(node8.right, NULL);
  TEST_ASSERT_EQUAL_PTR(node5.left, &node1);
  TEST_ASSERT_EQUAL_PTR(node5.right, NULL);
  TEST_ASSERT_EQUAL_PTR(node15.left, NULL);
  TEST_ASSERT_EQUAL_PTR(node15.right, NULL);
  TEST_ASSERT_EQUAL_PTR(node10.left, &node8);
  TEST_ASSERT_EQUAL_PTR(node10.right, &node15);
  TEST_ASSERT_EQUAL_PTR(node7.left, &node5);
  TEST_ASSERT_EQUAL_PTR(node7.right, &node10);
}

/**
 *          root              root              root
 *           |                 |                 |
 *           v                 v                 v
 *          10                10                 7
 *         /  \              /  \               / \
 *        5   15   ----->   7   15  ----->    5    10         
 *      /  \               /                 / \     \
 *     1    7             5                 1   6    15  
 *         /             / \                 
 *        6             1   6               
 */
void test_leftRightRotate_given_6_nodes(void)
{
	setNode(&node1, NULL, NULL, 'b');
	setNode(&node6, NULL, NULL, 'b');
	setNode(&node7, &node6, NULL, 'b');
	setNode(&node5, &node1, &node7, 'b');
	setNode(&node15, NULL, NULL, 'b');
	setNode(&node10, &node5, &node15, 'b');
  Node *root = &node10;

  leftRightRotate(&root);

  TEST_ASSERT_EQUAL_PTR(node1.left, NULL);
  TEST_ASSERT_EQUAL_PTR(node1.right, NULL);
  TEST_ASSERT_EQUAL_PTR(node6.left, NULL);
  TEST_ASSERT_EQUAL_PTR(node6.right, NULL);
  TEST_ASSERT_EQUAL_PTR(node5.left, &node1);
  TEST_ASSERT_EQUAL_PTR(node5.right, &node6);
  TEST_ASSERT_EQUAL_PTR(node15.left, NULL);
  TEST_ASSERT_EQUAL_PTR(node15.right, NULL);
  TEST_ASSERT_EQUAL_PTR(node10.left, NULL);
  TEST_ASSERT_EQUAL_PTR(node10.right, &node15);
  TEST_ASSERT_EQUAL_PTR(node7.left, &node5);
  TEST_ASSERT_EQUAL_PTR(node7.right, &node10);
}

/**
 *        root            root           root
 *         |               |              |
 *         v               v              v
 *        10              10             15
 *          \              \             / \   
 *           20  ----->     15 ----->  10   20 
 *          /                \        
 *        15                  20
 */
void test_rightLeftRotate_3_nodes(void)
{
	setNode(&node15, NULL, NULL, 'b');
	setNode(&node20, &node15, NULL, 'b');
	setNode(&node10, NULL, &node20, 'b');
  Node *root = &node10;

  rightLeftRotate(&root);

  TEST_ASSERT_EQUAL_PTR(node20.left, NULL);
  TEST_ASSERT_EQUAL_PTR(node20.right, NULL);
  TEST_ASSERT_EQUAL_PTR(node10.left, NULL);
  TEST_ASSERT_EQUAL_PTR(node10.right, NULL);
  TEST_ASSERT_EQUAL_PTR(node15.left, &node10);
  TEST_ASSERT_EQUAL_PTR(node15.right, &node20);
}

/**
 *        root             root                   root
 *         |                |                      |
 *         v                v                      v
 *        10               10                     15
 *          \                \                   /  \
 *          20               15                10    20
 *         /  \    ----->      \     ------->          \
 *       15   30                20                     30
 *                               \ 
 *                                30   
 */
void test_rightLeftRotate_4_nodes(void)
{
	setNode(&node15, NULL, NULL, 'b');
	setNode(&node30, NULL, NULL, 'b');
	setNode(&node20, &node15, &node30, 'b');
	setNode(&node10, NULL, &node20, 'b');
  Node *root = &node10;

  rightLeftRotate(&root);

  TEST_ASSERT_EQUAL_PTR(node30.left, NULL);
  TEST_ASSERT_EQUAL_PTR(node30.right, NULL);
  TEST_ASSERT_EQUAL_PTR(node10.left, NULL);
  TEST_ASSERT_EQUAL_PTR(node10.right, NULL);
  TEST_ASSERT_EQUAL_PTR(node20.left, NULL);
  TEST_ASSERT_EQUAL_PTR(node20.right, &node30);
  TEST_ASSERT_EQUAL_PTR(node15.left, &node10);
  TEST_ASSERT_EQUAL_PTR(node15.right, &node20);
}

/**
 *           root           root            root 
 *            |              |               | 
 *            v              v               v
 *           10              10              15
 *          /  \            / \             /  \
 *         5   20          5  15           10   20      
 *            /  \           / \          /  \   \ 
 *           15  30  --->  13  20   ---> 5   13  30  
 *          /                   \         
 *         13                   30       
 */
void test_rightLeftRotate_6_nodes(void)
{
	setNode(&node5, NULL, NULL, 'b');
	setNode(&node13, NULL, NULL, 'b');
	setNode(&node15, &node13, NULL, 'b');
	setNode(&node30, NULL, NULL, 'b');
	setNode(&node20, &node15, &node30, 'b');
	setNode(&node10, &node5, &node20, 'b');
  Node *root = &node10;

  rightLeftRotate(&root);

  TEST_ASSERT_EQUAL_PTR(node5.left, NULL);
  TEST_ASSERT_EQUAL_PTR(node5.right, NULL);
  TEST_ASSERT_EQUAL_PTR(node13.left, NULL);
  TEST_ASSERT_EQUAL_PTR(node13.right, NULL);
  TEST_ASSERT_EQUAL_PTR(node30.left, NULL);
  TEST_ASSERT_EQUAL_PTR(node30.right, NULL);
  TEST_ASSERT_EQUAL_PTR(node20.left, NULL);
  TEST_ASSERT_EQUAL_PTR(node20.right, &node30);
  TEST_ASSERT_EQUAL_PTR(node10.left, &node5);
  TEST_ASSERT_EQUAL_PTR(node10.right, &node13);
  TEST_ASSERT_EQUAL_PTR(node15.left, &node10);
  TEST_ASSERT_EQUAL_PTR(node15.right, &node20);
}

/**
 *          root           root              root 
 *           |              |                 |
 *           v              v                 v
 *          10             10                15
 *         /  \           / \               /  \
 *        5   20         5  15            10    20      
 *           /  \             \          /     /  \   
 *          15  30  --->      20   ---> 5     17  30  
 *           \               /  \         
 *           17             17  30       
 */
void test_rightLeftRotate_given_6_nodes(void)
{
	setNode(&node5, NULL, NULL, 'b');
	setNode(&node17, NULL, NULL, 'b');
	setNode(&node15, NULL, &node17, 'b');
	setNode(&node30, NULL, NULL, 'b');
	setNode(&node20, &node15, &node30, 'b');
	setNode(&node10, &node5, &node20, 'b');
  Node *root = &node10;

  rightLeftRotate(&root);

  TEST_ASSERT_EQUAL_PTR(node5.left, NULL);
  TEST_ASSERT_EQUAL_PTR(node5.right, NULL);
  TEST_ASSERT_EQUAL_PTR(node17.left, NULL);
  TEST_ASSERT_EQUAL_PTR(node17.right, NULL);
  TEST_ASSERT_EQUAL_PTR(node30.left, NULL);
  TEST_ASSERT_EQUAL_PTR(node30.right, NULL);
  TEST_ASSERT_EQUAL_PTR(node20.left, &node17);
  TEST_ASSERT_EQUAL_PTR(node20.right, &node30);
  TEST_ASSERT_EQUAL_PTR(node10.left, &node5);
  TEST_ASSERT_EQUAL_PTR(node10.right, NULL);
  TEST_ASSERT_EQUAL_PTR(node15.left, &node10);
  TEST_ASSERT_EQUAL_PTR(node15.right, &node20);
}