#include <stdio.h>
#include "unity.h"
#include "RedBlackTree.h"
#include "Node.h"
#include "InitNode.h"
#include "CustomAssertions.h"
#include "Rotations.h"
#include "CException.h"

Node node1, node2, node3, node4, node5, node6, node7, node8, node10, node12, node13, node15, node17, node18, node20, node30;

void setUp(void){
	resetNode(&node1, 1);
	resetNode(&node2, 2);
	resetNode(&node3, 3);
	resetNode(&node4, 4);
	resetNode(&node5, 5);
	resetNode(&node6, 6);
	resetNode(&node7, 7);
	resetNode(&node8, 8);
	resetNode(&node10, 10);
	resetNode(&node12, 12);
	resetNode(&node13, 13);
	resetNode(&node15, 15);
	resetNode(&node17, 17);
	resetNode(&node18, 18);
	resetNode(&node20, 20);
	resetNode(&node30, 30);
}

void tearDown(void){}

/** 2-node case
 *          root                      
 *           |      remove 2          
 *           v    ------------->  Throw ERR_NODE_UNAVAILABLE  
 *          1(b)                     
 */
void test_delRedBlackTree_remove_2_from_tree_with_root_1_should_throw_ERR_NODE_UNAVAILABLE(void)
{
  CEXCEPTION_T err;
  setNode(&node1, NULL, NULL, 'b');
  Node *root = &node1;
  
  Try
  {
    delRedBlackTree(&root, &node2);
    TEST_FAIL_MESSAGE("Expected ERR_NODE_UNAVAILABLE to be thrown");
  }
  Catch(err)
  {
    TEST_ASSERT_EQUAL_PTR(root, &node1);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node1);
  }
}

/** 2-node case
 *          root                     root 
 *           |      remove 1          |
 *           v    ------------->      v
 *          1(b)                     NULL
 */
void test_delRedBlackTree_remove_1_from_tree_with_root_1(void)
{
  setNode(&node1, NULL, NULL, 'b');
  Node *root = &node1;
  
  delRedBlackTree(&root, &node1);
  
  TEST_ASSERT_EQUAL_PTR(root, NULL);
}

/** 2-node case
 *       root                        root 
 *        |                           |
 *        v        remove 2           v
 *       1(b)    ------------>       1(b)
 *          \ 
 *          2(r)
 */
void test_delRedBlackTree_remove_2_from_tree_with_1_2_nodes(void)
{
  setNode(&node2, NULL, NULL, 'r');
  setNode(&node1, NULL, &node2, 'b');
  Node *root = &node1;
  
  delRedBlackTree(&root, &node2);
  
  TEST_ASSERT_EQUAL_PTR(root, &node1);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node1);
}

/** 2-node case
 *         root                       root
 *          |                          |
 *          v       remove 1           v
 *         2(b)    --------->        2(b)
 *        /
 *      1(r)
 */
void test_delRedBlackTree_remove_1_from_tree_with_2_1_nodes(void)
{
  setNode(&node1, NULL, NULL, 'r');
  setNode(&node2, &node1, NULL, 'b');
  Node *root = &node2;
  
  delRedBlackTree(&root, &node1);
  
  TEST_ASSERT_EQUAL_PTR(root, &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node2);
}

/**
 *      root                       root
 *       |                          |
 *       v          remove 1        v
 *      2(b)        --------->     2(b)
 *     /   \                      /    \
 *   1(r)   3(r)                 -      3(r)
 */
void test_delRedBlackTree_remove_1_from_tree_with_2_1_3_nodes(void)
{
  setNode(&node1, NULL, NULL, 'r');
  setNode(&node3, NULL, NULL, 'r');
  setNode(&node2, &node1, &node3, 'b');
  Node *root = &node2;
  
  _delRedBlackTree(&root, &node1);
  
  TEST_ASSERT_EQUAL_PTR(root, &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node3);
  TEST_ASSERT_EQUAL_NODE(NULL, &node3, 'b', &node2);
}

/**
 *       root                         root 
 *        |                            |
 *        v          remove 3          v
 *       2(b)       ----------->      2(b)
 *      /    \                       /    \
 *    1(r)    3(r)                 1(r)    -
 */
void test_delRedBlackTree_remove_3_from_tree_with_2_1_3_nodes(void)
{
  setNode(&node1, NULL, NULL, 'r');
  setNode(&node3, NULL, NULL, 'r');
  setNode(&node2, &node1, &node3, 'b');
  Node *root = &node2;
  
  delRedBlackTree(&root, &node3);
  
  TEST_ASSERT_EQUAL_PTR(root, &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node1);
  TEST_ASSERT_EQUAL_NODE(&node1, NULL, 'b', &node2);
}

/**
 *        root                               root 
 *         |                                  |
 *         v                                  v
 *        2(b)           remove 1            5(b)
 *       /   \         ------------>        /   \
 *     1(b)   5(r)                        2(b)   6(b)
 *           /   \                           \
 *         3(b)  6(b)                        3(r)
 */
void test_delRedBlackTree_remove_1_from_tree_with_2_1_5_3_6_nodes(void)
{
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node6, NULL, NULL, 'b');
  setNode(&node5, &node3, &node6, 'r');
  setNode(&node2, &node1, &node5, 'b');
  Node *root = &node2;
  
  delRedBlackTree(&root, &node1);
  
  TEST_ASSERT_EQUAL_PTR(root, &node5);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node3);
  TEST_ASSERT_EQUAL_NODE(NULL, &node3, 'b', &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node6);
  TEST_ASSERT_EQUAL_NODE(&node2, &node6, 'b', &node5);
}

/**
 *        root                             root
 *         |                                |
 *         v                                v
 *        2(b)           remove 3          2(b)
 *       /   \         ------------->     /   \
 *     1(b)   5(r)                      1(b)   5(b)
 *           /   \                                \
 *         3(b)  6(b)                            6(r)
 */
void test_delRedBlackTree_remove_3_from_tree_with_2_1_5_3_6_nodes(void)
{
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node6, NULL, NULL, 'b');
  setNode(&node5, &node3, &node6, 'r');
  setNode(&node2, &node1, &node5, 'b');
  Node *root = &node2;
  
  delRedBlackTree(&root, &node3);
  
  TEST_ASSERT_EQUAL_PTR(root, &node2);
  TEST_ASSERT_EQUAL_NODE(&node1, &node5, 'b', &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node1);
  TEST_ASSERT_EQUAL_NODE(NULL, &node6, 'b', &node5);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node6);
} 

/**
 *        root                             root
 *         |                                |
 *         v                                v
 *        2(b)           remove 6          2(b)
 *       /   \         ------------->     /   \
 *     1(b)   5(r)                      1(b)   5(b)
 *           /   \                            /
 *         3(b)  6(b)                       3(r)   
 */
void test_delRedBlackTree_remove_6_from_tree_with_2_1_5_3_6_nodes(void)
{
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node6, NULL, NULL, 'b');
  setNode(&node5, &node3, &node6, 'r');
  setNode(&node2, &node1, &node5, 'b');
  Node *root = &node2;
  
  delRedBlackTree(&root, &node6);
  
  TEST_ASSERT_EQUAL_PTR(root, &node2);
  TEST_ASSERT_EQUAL_NODE(&node1, &node5, 'b', &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node1);
  TEST_ASSERT_EQUAL_NODE(&node3, NULL, 'b', &node5);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node3);
} 

/**
 *         root                              root
 *          |                                 |
 *          v                                 v
 *         5(b)          remove 6            2(b)
 *        /    \       ------------>        /    \
 *      2(r)   6(b)                      1(b)    5(b)
 *     /   \                                     /
 *  1(b)   3(b)                                3(r)
 */
void test_delRedBlackTree_remove_6_from_tree_with_1_2_3_5_6_nodes(void)
{
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node6, NULL, NULL, 'b');
  setNode(&node2, &node1, &node3, 'r');
  setNode(&node5, &node2, &node6, 'b');
  Node *root = &node5;
  
  delRedBlackTree(&root, &node6);
  
  TEST_ASSERT_EQUAL_PTR(root, &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node1);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node3);
  TEST_ASSERT_EQUAL_NODE(&node3, NULL, 'b', &node5);
  TEST_ASSERT_EQUAL_NODE(&node1, &node5, 'b', &node2);
}

/**
 *         root                              root
 *          |                                 |
 *          v                                 v
 *         5(b)          remove 1            5(b)
 *        /    \       ------------>        /    \
 *      2(r)   6(b)                      2(b)    6(b)
 *     /   \                                \      
 *  1(b)   3(b)                             3(r)  
 */
void test_delRedBlackTree_remove_1_from_tree_with_1_2_3_5_6_nodes(void)
{
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node6, NULL, NULL, 'b');
  setNode(&node2, &node1, &node3, 'r');
  setNode(&node5, &node2, &node6, 'b');
  Node *root = &node5;
  
  delRedBlackTree(&root, &node1);
  
  TEST_ASSERT_EQUAL_PTR(root, &node5);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node6);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node3);
  TEST_ASSERT_EQUAL_NODE(NULL, &node3, 'b', &node2);
  TEST_ASSERT_EQUAL_NODE(&node2, &node6, 'b', &node5);
}

/**
 *         root                              root
 *          |                                 |
 *          v                                 v
 *         5(b)          remove 3            5(b)
 *        /    \       ------------>        /    \
 *      2(r)   6(b)                      2(b)    6(b)
 *     /   \                            /      
 *  1(b)   3(b)                       1(r)     
 */
void test_delRedBlackTree_remove_3_from_tree_with_1_2_3_5_6_nodes(void)
{
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node6, NULL, NULL, 'b');
  setNode(&node2, &node1, &node3, 'r');
  setNode(&node5, &node2, &node6, 'b');
  Node *root = &node5;
  
  delRedBlackTree(&root, &node3);
  
  TEST_ASSERT_EQUAL_PTR(root, &node5);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node6);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node1);
  TEST_ASSERT_EQUAL_NODE(&node1, NULL, 'b', &node2);
  TEST_ASSERT_EQUAL_NODE(&node2, &node6, 'b', &node5);
}

/**
 *           root                                 root 
 *            |                                    |
 *            v                                    v
 *           4(b)                                 4(b)
 *         /     \           remove 1           /     \
 *       2(r)     6(r)     ----------->       2(b)    6(r)
 *      /   \    /   \                           \    /   \
 *    1(b) 3(b) 5(b) 7(b)                       3(r) 5(b)  7(b)
 */
void test_delRedBlackTree_remove_1_from_tree_with_4_2_1_3_6_5_7_nodes(void)
{
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node5, NULL, NULL, 'b');
  setNode(&node7, NULL, NULL, 'b');
  setNode(&node2, &node1, &node3, 'r');
  setNode(&node6, &node5, &node7, 'r');
  setNode(&node4, &node2, &node6, 'b');
  Node *root = &node4;
  
  delRedBlackTree(&root, &node1);
  
  TEST_ASSERT_EQUAL_PTR(root, &node4);
  TEST_ASSERT_EQUAL_NODE(NULL, &node3, 'b', &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node3);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node5);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node7);
  TEST_ASSERT_EQUAL_NODE(&node5, &node7, 'r', &node6);
  TEST_ASSERT_EQUAL_NODE(&node2, &node6, 'b', &node4);
}

/**
 *           root                                 root 
 *            |                                    |
 *            v                                    v
 *           4(b)                                 4(b)
 *         /     \           remove 3           /     \
 *       2(r)     6(r)     ----------->       2(b)    6(r)
 *      /   \    /   \                       /       /   \
 *    1(b) 3(b) 5(b) 7(b)                  1(r)    5(b)  7(b)
 */
void test_delRedBlackTree_remove_3_from_tree_with_4_2_1_3_6_5_7_nodes(void) 
{
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node5, NULL, NULL, 'b');
  setNode(&node7, NULL, NULL, 'b');
  setNode(&node2, &node1, &node3, 'r');
  setNode(&node6, &node5, &node7, 'r');
  setNode(&node4, &node2, &node6, 'b');
  Node *root = &node4;
  
  delRedBlackTree(&root, &node3);
  
  TEST_ASSERT_EQUAL_PTR(root, &node4);
  TEST_ASSERT_EQUAL_NODE(&node1, NULL, 'b', &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node1);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node5);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node7);
  TEST_ASSERT_EQUAL_NODE(&node5, &node7, 'r', &node6);
  TEST_ASSERT_EQUAL_NODE(&node2, &node6, 'b', &node4);
}

/**
 *           root                                 root 
 *            |                                    |
 *            v                                    v
 *           4(b)                                 4(b)
 *         /     \           remove 5           /     \
 *       2(r)     6(r)     ----------->       2(r)    6(b)
 *      /   \    /   \                       /   \       \
 *    1(b) 3(b) 5(b) 7(b)                  1(b) 3(b)     7(r)
 */
void test_delRedBlackTree_remove_5_from_tree_with_4_2_1_3_6_5_7_nodes(void) 
{
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node5, NULL, NULL, 'b');
  setNode(&node7, NULL, NULL, 'b');
  setNode(&node2, &node1, &node3, 'r');
  setNode(&node6, &node5, &node7, 'r');
  setNode(&node4, &node2, &node6, 'b');
  Node *root = &node4;
  
  delRedBlackTree(&root, &node5);
  
  TEST_ASSERT_EQUAL_PTR(root, &node4);
  TEST_ASSERT_EQUAL_NODE(&node1, &node3, 'r', &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node7);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node1);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node3);
  TEST_ASSERT_EQUAL_NODE(NULL, &node7, 'b', &node6);
  TEST_ASSERT_EQUAL_NODE(&node2, &node6, 'b', &node4);
}

/**
 *           root                                 root 
 *            |                                    |
 *            v                                    v
 *           4(b)                                 4(b)
 *         /     \           remove 7           /      \
 *       2(r)     6(r)     ----------->       2(r)     6(b)
 *      /   \    /   \                       /   \    /  
 *    1(b) 3(b) 5(b) 7(b)                  1(b) 3(b) 5(r)    
 */
void test_delRedBlackTree_remove_7_from_tree_with_4_2_1_3_6_5_7_nodes(void) 
{
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node5, NULL, NULL, 'b');
  setNode(&node7, NULL, NULL, 'b');
  setNode(&node2, &node1, &node3, 'r');
  setNode(&node6, &node5, &node7, 'r');
  setNode(&node4, &node2, &node6, 'b');
  Node *root = &node4;
  
  delRedBlackTree(&root, &node7);
  
  TEST_ASSERT_EQUAL_PTR(root, &node4);
  TEST_ASSERT_EQUAL_NODE(&node1, &node3, 'r', &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node5);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node1);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node3);
  TEST_ASSERT_EQUAL_NODE(&node5, NULL, 'b', &node6);
  TEST_ASSERT_EQUAL_NODE(&node2, &node6, 'b', &node4);
}

/**
 *  This test code is also part of the delRedBlackTree() 
 */
void test_isRed_given_a_node_with_red_color_should_return_1(void) 
{
  int result;
  setNode(&node1, NULL, NULL, 'r');
  Node *root = &node1;
  
  result = isRed(&root);
  TEST_ASSERT_EQUAL(1, result);
}

void test_isRed_given_a_node_with_black_color_should_return_0(void) 
{
  int result;
  setNode(&node1, NULL, NULL, 'b');
  Node *root = &node1;
  
  result = isRed(&root);
  TEST_ASSERT_EQUAL(0, result);
}

void test_isBlack_given_a_node_with_black_color_should_return_1(void)
{
  int result;
  setNode(&node2, NULL, NULL, 'b');
  Node *root = &node2;
  
  result = isBlack(&root);
  TEST_ASSERT_EQUAL(1, result);
}

void test_isBlack_given_a_node_with_red_color_should_return_0(void)
{
  int result;
  setNode(&node2, NULL, NULL, 'r');
  Node *root = &node2;
  
  result = isBlack(&root);
  TEST_ASSERT_EQUAL(0, result);
}

void test_isBlack_given_NULL_should_return_1(void)
{
  int result;
  Node *root = NULL;
  
  result = isBlack(&root);
  TEST_ASSERT_EQUAL(1, result);
}

void test_isDoubleBlack_given_a_node_with_double_black_color_should_return_1(void)
{
  int result;
  setNode(&node4, NULL, NULL, 'd');
  setNode(&node3, NULL, NULL, 'b');
  Node *root = &node4;
  Node *removeNode = &node3;
  
  result = isDoubleBlack(&root, removeNode);
  TEST_ASSERT_EQUAL(1, result);
}

void test_isDoubleBlack_given_a_node_with_black_color_should_return_0(void)
{
  int result;
  setNode(&node4, NULL, NULL, 'b');
  setNode(&node3, NULL, NULL, 'r');
  Node *root = &node4;
  Node *removeNode = &node3;
  
  result = isDoubleBlack(&root, removeNode);
  TEST_ASSERT_EQUAL(0, result);
}
  
/**
 *          root                         root                     root
 *           |                            |                        |
 *           v                            v        left            v
 *          2(r)          remove 1       2(r)     rotate          4(r)
 *         /   \        ------------>      \     --------->      /   \
 *      1(b)   4(b)                        4(b)               2(b)    5(b)
 *                \                          \
 *                5(r)                       5(r)
 */
void test_delRedBlackTree_remove_1_from_tree_with_1_2_4_5_nodes(void)
{
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node5, NULL, NULL, 'r');
  setNode(&node4, NULL, &node5, 'b');
  setNode(&node2, &node1, &node4, 'r');
  Node *root = &node2;
  Node *result;
  
  result = _delRedBlackTree(&root, &node1);
  
  TEST_ASSERT_EQUAL_PTR(result, &node1);
  TEST_ASSERT_EQUAL_PTR(root, &node4);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node5);
  TEST_ASSERT_EQUAL_NODE(&node2, &node5, 'r', &node4);
}

/**
 *          root                         root                     root
 *           |                            |        right           |
 *           v                            v        left            v
 *          2(b)          remove 1       2(b)     rotate          4(b)
 *         /   \        ------------>      \     --------->      /   \
 *      1(b)   5(b)                        5(b)               2(b)    5(b)
 *            /                           /  
 *          4(r)                        4(r)    
 */
void test_delRedBlackTree_remove_one_from_tree_with_1_2_4_5_nodes_with_using_right_left_rotation(void)
{
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node4, NULL, NULL, 'r');
  setNode(&node5, &node4, NULL, 'b');
  setNode(&node2, &node1, &node5, 'b');
  Node *root = &node2;
  Node *result;
  
  result = _delRedBlackTree(&root, &node1);
  
  TEST_ASSERT_EQUAL(result, &node1);
  TEST_ASSERT_EQUAL_PTR(root, &node4);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node5);
  TEST_ASSERT_EQUAL_NODE(&node2, &node5, 'b', &node4);
} 

/**
 *         root                          root                        root         
 *          |                             |                           |
 *          v                             v                           v
 *         4(b)                          4(b)         right         2(b)
 *        /   \         remove 5         /            rotate       /    \
 *      2(b)   5(b)   ------------>   2(b)          --------->   1(b)   4(b)
 *     /                              /
 *   1(r)                           1(r)
 */
void test__delRedBlackTree_remove_5_from_tree_with_1_2_4_5_nodes(void)
{
  setNode(&node1, NULL, NULL, 'r');
  setNode(&node5, NULL, NULL, 'b');
  setNode(&node2, &node1, NULL, 'b');
  setNode(&node4, &node2, &node5, 'b');
  Node *root = &node4;
  Node *result;
  
  result = _delRedBlackTree(&root, &node5);
  
  TEST_ASSERT_EQUAL_PTR(result, &node5);
  TEST_ASSERT_EQUAL_PTR(root, &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node1);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node4);
  TEST_ASSERT_EQUAL_NODE(&node1, &node4, 'b', &node2);
}

/**
 *         root                             root                        root         
 *          |                                |                           |
 *          v                                v          left             v
 *         4(b)                            4(b)         right           3(b)
 *        /   \         remove 5           /           rotate          /   \
 *      2(b)   5(b)  ------------->     2(b)         ------------>   2(b)  4(b)
 *         \                               \
 *         3(r)                            3(r)
 */
void test__delRedBlackTree_remove_five_from_tree_with_1_2_4_5_nodes_with_using_left_right_rotate(void)
{
  setNode(&node3, NULL, NULL, 'r');
  setNode(&node5, NULL, NULL, 'b');
  setNode(&node2, NULL, &node3, 'b');
  setNode(&node4, &node2, &node5, 'b');
  Node *root = &node4;
  Node *result;
  
  result = _delRedBlackTree(&root, &node5);
  
  TEST_ASSERT_EQUAL_PTR(result, &node5);
  TEST_ASSERT_EQUAL_PTR(root, &node3);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node4);
  TEST_ASSERT_EQUAL_NODE(&node2, &node4, 'b', &node3);
}

/**
 *        root                              root
 *         |                                 |
 *         v                                 v
 *        2(b)         remove 1            2(d)
 *       /   \       ------------>            \
 *     1(b)  3(b)                             3(r)
 */
void test__delRedBlackTree_remove_1_from_tree_with_1_2_3_nodes(void)
{
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node2, &node1, &node3, 'b');
  Node *root = &node2;
  Node *result;
  
  result = _delRedBlackTree(&root, &node1);
  
  TEST_ASSERT_EQUAL_PTR(root, &node2);
  TEST_ASSERT_EQUAL_PTR(result, &node1);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node3);
  TEST_ASSERT_EQUAL_NODE(NULL, &node3, 'd', &node2);
}

/**
 *        root                              root
 *         |                                 |
 *         v                                 v
 *        2(b)         remove 3            2(d)
 *       /   \       ------------>        /    
 *     1(b)  3(b)                       1(r)     
 */
void test__delRedBlackTree_remove_3_from_tree_with_1_2_3_nodes(void)
{
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node2, &node1, &node3, 'b');
  Node *root = &node2;
  Node *result;
  
  result = _delRedBlackTree(&root, &node3);
    
  TEST_ASSERT_EQUAL_PTR(root, &node2);
  TEST_ASSERT_EQUAL_PTR(result, &node3);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node1);
  TEST_ASSERT_EQUAL_NODE(&node1, NULL, 'd', &node2);
}

/**
 *        root                              root
 *         |                                 |
 *         v                                 v
 *        2(r)         remove 3            2(b)
 *       /   \       ------------>        /    
 *     1(b)  3(b)                       1(r)     
 */
void test__delRedBlackTree_remove_three_from_tree_with_1_2_3_nodes(void)
{
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node2, &node1, &node3, 'r');
  Node *root = &node2;
  Node *result;
  
  result = _delRedBlackTree(&root, &node3);
    
  TEST_ASSERT_EQUAL_PTR(root, &node2);
  TEST_ASSERT_EQUAL_PTR(result, &node3);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node1);
  TEST_ASSERT_EQUAL_NODE(&node1, NULL, 'b', &node2);
}

/**
 *        root                              root
 *         |                                 |
 *         v                                 v
 *        2(b)         remove 1            2(b)
 *       /   \       ------------>            \
 *     1(b)  3(b)                             3(r)
 */
void test__delRedBlackTree_remove_one_from_tree_with_1_2_3_nodes(void)
{
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node2, &node1, &node3, 'r');
  Node *root = &node2;
  Node *result;
  
  result = _delRedBlackTree(&root, &node1);
  
  TEST_ASSERT_EQUAL_PTR(root, &node2);
  TEST_ASSERT_EQUAL_PTR(result, &node1);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node3);
  TEST_ASSERT_EQUAL_NODE(NULL, &node3, 'b', &node2);
}

/**
 *       root                           root                            root
 *        |                              |                               |
 *        v                              v                               v
 *      2(b)                            2(b)            left            4(b)
 *     /   \          remove 1             \           rotate          /    \
 *   1(b)  4(r)      ----------->          4(r)      ------------>   2(b)   5(b)
 *        /   \                           /   \                         \
 *      3(b)  5(b)                      3(b)  5(b)                      3(r)
 */
void test__delRedBlackTree_remove_1_from_tree_with_1_2_3_4_5_nodes(void)
{
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node5, NULL, NULL, 'b');
  setNode(&node4, &node3, &node5, 'r');
  setNode(&node2, &node1, &node4, 'b');
  Node *root = &node2;
  Node *result;
  
  result = delRedBlackTree(&root, &node1);
  
  TEST_ASSERT_EQUAL_PTR(root, &node4);
  TEST_ASSERT_EQUAL_PTR(result, &node1);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node5);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node3);
  TEST_ASSERT_EQUAL_NODE(NULL, &node3, 'b', &node2);
  TEST_ASSERT_EQUAL_NODE(&node2, &node5, 'b', &node4);
}

/**
 *         root                         root                        root
 *          |                            |                           |
 *          v                            v                           v
 *         5(b)                         5(b)      rotate           3(b)
 *        /   \        remove 6        /           right          /   \
 *      3(r)  6(b)  ---------------> 3(r)      -------------->  2(b)  5(b)
 *     /   \                        /   \                            /
 *  2(b)   4(b)                   2(b)  4(b)                       4(r)
 */
void test__delRedBlackTree_remove_6_from_tree_with_2_3_4_5_6_nodes(void)
{
  setNode(&node2, NULL, NULL, 'b');
  setNode(&node4, NULL, NULL, 'b');
  setNode(&node6, NULL, NULL, 'b');
  setNode(&node3, &node2, &node4, 'r');
  setNode(&node5, &node3, &node6, 'b');
  Node *root = &node5;
  Node *result;
  
  result = delRedBlackTree(&root, &node6);
  
  TEST_ASSERT_EQUAL_PTR(root, &node3);
  TEST_ASSERT_EQUAL_PTR(result, &node6);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node4);
  TEST_ASSERT_EQUAL_NODE(&node4, NULL, 'b', &node5);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node2);
  TEST_ASSERT_EQUAL_NODE(&node2, &node5, 'b', &node3);
}

/**
 *        root                             root                              root                          root             
 *         |                                |                                 |                             |
 *         v                                v                                 v                             v
 *        2(b)                             2(b)                              5(b)                         5(b)
 *       /   \           remove 1        //   \          case 3             /   \       case 1           /   \
 *     1(b)  5(r)      ------------>         5(r)     -------------->    2(r)   6(b)  ------------>    3(r)   6(b)
 *          /   \                           /   \                      //   \                         /   \
 *        3(b)  6(b)                      3(b)  6(b)                       3(b)                     2(b)  4(b)
 *           \                               \                                \
 *          4(r)                            4(r)                              4(r)
 */
void test__delRedBlackTree_remove_1_from_tree_with_1_2_3_4_5_6_nodes_by_using_case_3_and_1(void)
{
  setNode(&node4, NULL, NULL, 'r');
  setNode(&node6, NULL, NULL, 'b');
  setNode(&node1, NULL, NULL, 'b');
  setNode(&node3, NULL, &node4, 'b');
  setNode(&node5, &node3, &node6, 'r');
  setNode(&node2, &node1, &node5, 'b');
  Node *root = &node2;
  Node *result;
  
  result = delRedBlackTree(&root, &node1);
  
  TEST_ASSERT_EQUAL_PTR(root, &node5);
  TEST_ASSERT_EQUAL_PTR(result, &node1);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node4);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node6);
  TEST_ASSERT_EQUAL_NODE(&node2, &node4, 'r', &node3);
  TEST_ASSERT_EQUAL_NODE(&node3, &node6, 'b', &node5);
}

/* 
 * 
 *           root                 root                      root
 *            |       remove 20    |       rotate left       |  
 *            v      ----->        v      --------->         v
 *           15(b)                15(b)                     5(b)
 *          /  \                /   \\                    /   \
 *       5(r)   20(b)        5(r)   NULL               2(b)   15(b)
 *      /  \                /   \                            /
 *   2(b)  7(b)           2(b)  7(b)                       7(r)
 */
void test_delRedBlackTree_3_node_remove_20_from_tree_with_root_15_root_should_point_to_5()
{
   
    setNode(&node2, NULL, NULL, 'b');
    setNode(&node7, NULL, NULL, 'b');
    setNode(&node20, NULL, NULL, 'b');
    setNode(&node5, &node2, &node7, 'r');
    setNode(&node15, &node5, &node20, 'b');
    Node *root = &node15;
    Node *node;
    
    
    node = delRedBlackTree(&root, &node20);  
    TEST_ASSERT_EQUAL(20 , node->data);
    TEST_ASSERT_EQUAL_NODE(NULL , NULL, 'b', &node2);
    TEST_ASSERT_EQUAL_NODE(NULL , NULL, 'r', &node7);
    TEST_ASSERT_EQUAL(root->data,5);
    TEST_ASSERT_EQUAL_NODE(&node7, NULL, 'b', &node15);
    TEST_ASSERT_EQUAL_NODE(&node2, &node15 , 'b', &node5);
    
}

/* 
 * 
 *           root                 root                      root                      root
 *            |    remove 20       |      case3              |         case1           |
 *            v      ----->        v      --------->         v         ------->        v
 *           15(b)                15(b)                     5(b)                      5(b)
 *          /  \                /   \\                    /   \                     /    \
 *       5(r)   20(b)        5(r)   NULL               2(b)   15(r)               2(b)   7(r)
 *      /  \                /   \                            /                          /   \
 *   2(b)  7(b)           2(b)  7(b)                       7(b)                      6(b)   15(b)
 *        /                    /                          /
 *      6(r)                 6(r)                       6(r)
 *
 */
void test_delRedBlackTree_3_node_combination_test_remove_20_from_tree_with_root_15_root_should_point_to_5()
{
    
    setNode(&node2, NULL, NULL, 'b');
    setNode(&node6, NULL, NULL, 'r');
    setNode(&node7, &node6, NULL, 'b');
    setNode(&node20, NULL, NULL, 'b');
    setNode(&node5, &node2, &node7, 'r');
    setNode(&node15, &node5, &node20, 'b');
    Node *root = &node15;
    Node *node;
   
    node = delRedBlackTree(&root, &node20);  
    TEST_ASSERT_EQUAL(20 , node->data);
    TEST_ASSERT_EQUAL(root->data,5);
    TEST_ASSERT_EQUAL_NODE(NULL , NULL, 'b', &node6);
    TEST_ASSERT_EQUAL_NODE(&node6, &node15, 'r', &node7);
    TEST_ASSERT_EQUAL_NODE(&node2, &node7 , 'b', &node5);
    TEST_ASSERT_EQUAL_NODE(NULL , NULL, 'b', &node2);
        
    TEST_ASSERT_EQUAL_NODE(NULL , NULL, 'b', &node15);
}

/**
 *         parent                       parent
 *           |         successor          \\
 *           v             2               v
 *         2(b)      ------------>         -
 *        /   \
 *       -     - 
 *
 */
void test_removeNextLargerSuccessor_remove_2_from_the_tree_with_2_node(void)
{
  setNode(&node2, NULL, NULL, 'b');
  Node *parent = &node2;
  Node *removeNode;
  
  removeNode = removeNextLargerSuccessor(&parent);
  TEST_ASSERT_NULL(parent);
  TEST_ASSERT_EQUAL(1, isDoubleBlack(&parent, removeNode));
}

/**
 *       parent                         parent
 *         |                              |
 *         v         successor            v
 *       2(b)           1               2(b)
 *      /         ------------>
 *   1(r)
 */
void test_removeNextLargerSuccessor_remove_1_from_the_tree_with_2_1_nodes(void)
{
  setNode(&node1, NULL, NULL, 'r');
  setNode(&node2, &node1, NULL, 'b');
  Node *parent = &node2;
  Node *removeNode;
  
  removeNode = removeNextLargerSuccessor(&parent);
  TEST_ASSERT_EQUAL_PTR(&node1, removeNode);
  TEST_ASSERT_EQUAL_PTR(parent, &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node2);
}

/**
 *       parent                         parent
 *         |                              |
 *         v          successor           v
 *       2(b)             2             3(b)
 *           \      -------------->
 *           3(r)
 */
void test_removeNextLargerSuccessor_remove_3_from_the_tree_with_2_3_nodes(void)
{
  setNode(&node3, NULL, NULL, 'r');
  setNode(&node2, NULL, &node3, 'b');
  Node *parent = &node2;
  Node *removeNode;
  
  removeNode = removeNextLargerSuccessor(&parent);
  TEST_ASSERT_EQUAL_PTR(&node2, removeNode);
  TEST_ASSERT_EQUAL_PTR(parent, &node3);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node3);
}

/**
 *       parent                            parent
 *         |             successor           |
 *         v                 1               v
 *        2(b)         ------------>       2(b)
 *       /   \                                \  
 *     1(r)  3(r)                             3(r)
 */
void test_removeNextLargerSuccessor_remove_3_from_the_tree_with_2_1_3_nodes(void)
{
  setNode(&node1, NULL, NULL, 'r');
  setNode(&node3, NULL, NULL, 'r');
  setNode(&node2, &node1, &node3, 'b');
  Node *parent = &node2;
  Node *removeNode;
  
  removeNode = removeNextLargerSuccessor(&parent);
  TEST_ASSERT_EQUAL_PTR(&node1, removeNode);
  TEST_ASSERT_EQUAL_PTR(parent, &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node3);
  TEST_ASSERT_EQUAL_NODE(NULL, &node3, 'b', &node2);
}

/**
 *      parent                          parent
 *        |                               |
 *        v                               v
 *      12(b)          successor        12(b)
 *     /    \              1           /    \
 *   5(b)    18(b)    ---------->    5(b)   18(b)
 *  /   \    /   \                  /   \   /   \
 * 1(r)  - 13(r)  -                -    - 13(r)  -
 */
void test_removeNextLargerSuccessor_remove_1_from_the_tree_with_1_5_12_13_18_nodes(void)
{
  setNode(&node1, NULL, NULL, 'r');
  setNode(&node13, NULL, NULL, 'r');
  setNode(&node5, &node1, NULL, 'b');
  setNode(&node18, &node13, NULL, 'b');
  setNode(&node12, &node5, &node18, 'b');
  Node *parent = &node12;
  Node *removeNode;
  
  removeNode = removeNextLargerSuccessor(&parent);
  TEST_ASSERT_EQUAL_PTR(&node1, removeNode);
  TEST_ASSERT_EQUAL_PTR(parent, &node12);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node13);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node5);
  TEST_ASSERT_EQUAL_NODE(&node13, NULL, 'b', &node18);
  TEST_ASSERT_EQUAL_NODE(&node5, &node18, 'b', &node12);
}

/**
 *      parent's left                        parent's left
 *            |                                    |
 *            v                                    v
 *          10(b)                                10(b)
 *       /         \                          /         \
 *     5(b)       15(b)    successor 1      5(b)       15(b)
 *    /   \       /   \   ------------>    /   \       /   \
 *  1(b) 7(b)  13(b) 20(b)               2(b) 7(b)  13(b) 20(b)
 *     \
 *    2(r)
 */
void test_removeNextLargerSuccessor_given_nodes_1_2_5_10_13_15_20_should_remove_successor_1(void)
{
    setNode(&node2, NULL, NULL, 'r');
    setNode(&node7, NULL, NULL, 'b');
    setNode(&node13, NULL, NULL, 'b');
    setNode(&node20, NULL, NULL, 'b');
    setNode(&node1, NULL, &node2, 'b');
    setNode(&node5, &node1, &node7, 'b');
    setNode(&node15, &node13, &node20, 'b');
    setNode(&node10, &node5, &node15, 'b');
    Node *parent = &node10, *removeNode;

    removeNode = removeNextLargerSuccessor(&parent);

    TEST_ASSERT_EQUAL_PTR(&node10, parent);
    TEST_ASSERT_EQUAL_PTR(&node1, removeNode);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node2);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node7);
    TEST_ASSERT_EQUAL_NODE(&node2, &node7, 'b', &node5);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node13);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node20);
    TEST_ASSERT_EQUAL_NODE(&node13, &node20, 'b', &node15);
    TEST_ASSERT_EQUAL_NODE(&node5, &node15, 'b', &node10);
}

/** Encounter case 2b on the left child after remove successor
 *
 *      parent's left                      parent's left                   parent's left
 *            |                                  |                               |
 *            v                                  v                               v
 *          10(b)                              10(b)                           10(b)
 *       /         \       successor 1      /         \                     /        \
 *     5(r)       15(r)   ------------>   5(r)       15(r)  ------------> 5(b)       15(r)
 *    /   \       /   \                  //  \       /   \                   \       /   \
 *  1(b) 7(b)  13(b) 20(b)             NULL 7(b)  13(b) 20(b)               7(r)  13(b) 20(b)
 */
void test_removeNextLargerSuccessor_given_nodes_1_5_7_10_13_15r_20_should_remove_successor_1(void)
{
    setNode(&node7, NULL, NULL, 'b');
    setNode(&node13, NULL, NULL, 'b');
    setNode(&node20, NULL, NULL, 'b');
    setNode(&node1, NULL, NULL, 'b');
    setNode(&node5, &node1, &node7, 'r');
    setNode(&node15, &node13, &node20, 'r');
    setNode(&node10, &node5, &node15, 'b');
    Node *parent = &node10, *removeNode;

    removeNode = removeNextLargerSuccessor(&parent);

    TEST_ASSERT_EQUAL_PTR(&node10, parent);
    TEST_ASSERT_EQUAL_PTR(&node1, removeNode);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node7);
    TEST_ASSERT_EQUAL_NODE(NULL, &node7, 'b', &node5);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node13);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node20);
    TEST_ASSERT_EQUAL_NODE(&node13, &node20, 'r', &node15);
    TEST_ASSERT_EQUAL_NODE(&node5, &node15, 'b', &node10);
}

/** Encounter case 2a on the left child and 2b on the right child after remove successor
 *
 *      parent's left                      parent's left                   parent's left                   parent's left
 *            |                                  |                               |                               ||
 *            v                                  v                               v                               v
 *          10(b)                              10(b)                           10(b)                           10(d)
 *       /         \       successor 1      /         \                     //        \                     /        \
 *     5(b)       15(b)   ------------>   5(b)       15(b)  ------------> 5(d)       15(b)  ------------> 5(b)       15(r)
 *    /   \       /   \                  //  \       /   \                   \       /   \                   \       /   \
 *  1(b) 7(b)  13(b) 20(b)             NULL 7(b)  13(b) 20(b)               7(r)  13(b) 20(b)               7(r)  13(b) 20(b)
 */
void test_removeNextLargerSuccessor_given_nodes_1_5_7_10_13_15_20_should_remove_successor_1(void)
{
    setNode(&node7, NULL, NULL, 'b');
    setNode(&node13, NULL, NULL, 'b');
    setNode(&node20, NULL, NULL, 'b');
    setNode(&node1, NULL, NULL, 'b');
    setNode(&node5, &node1, &node7, 'b');
    setNode(&node15, &node13, &node20, 'b');
    setNode(&node10, &node5, &node15, 'b');
    Node *parent = &node10, *removeNode;

    removeNode = removeNextLargerSuccessor(&parent);

    TEST_ASSERT_EQUAL_PTR(&node10, parent);
    TEST_ASSERT_EQUAL_PTR(&node1, removeNode);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node7);
    TEST_ASSERT_EQUAL_NODE(NULL, &node7, 'b', &node5);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node13);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node20);
    TEST_ASSERT_EQUAL_NODE(&node13, &node20, 'r', &node15);
    TEST_ASSERT_EQUAL_NODE(&node5, &node15, 'd', &node10);
}

/** Encounter case 1b on the left child after remove successor
 *
 *      parent's left                      parent's left                   parent's left
 *            |                                  |                               |
 *            v                                  v                               v
 *          10(b)                              10(b)                           10(b)
 *       /         \       successor 1      /         \                      /        \
 *     5(b)       15(b)   ------------>   5(b)       15(b)  ------------> 6(b)       15(b)
 *    /   \       /   \                  //  \       /   \               /   \       /   \
 *  1(b) 7(b)  13(b) 20(b)             NULL 7(b)  13(b) 20(b)          5(b) 7(b)  13(b) 20(b)
 *       /                                  /
 *     6(r)                               6(r)
 */
void test_removeNextLargerSuccessor_given_nodes_1_5_6_7_10_13_15_20_should_remove_successor_1(void)
{
    setNode(&node6, NULL, NULL, 'r');
    setNode(&node7, &node6, NULL, 'b');
    setNode(&node13, NULL, NULL, 'b');
    setNode(&node20, NULL, NULL, 'b');
    setNode(&node1, NULL, NULL, 'b');
    setNode(&node5, &node1, &node7, 'b');
    setNode(&node15, &node13, &node20, 'b');
    setNode(&node10, &node5, &node15, 'b');
    Node *parent = &node10, *removeNode;

    removeNode = removeNextLargerSuccessor(&parent);

    TEST_ASSERT_EQUAL_PTR(&node10, parent);
    TEST_ASSERT_EQUAL_PTR(&node1, removeNode);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node5);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node7);
    TEST_ASSERT_EQUAL_NODE(&node5, &node7, 'b', &node6);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node13);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node20);
    TEST_ASSERT_EQUAL_NODE(&node13, &node20, 'b', &node15);
    TEST_ASSERT_EQUAL_NODE(&node6, &node15, 'b', &node10);
}

/** Encounter case 3 on the left child after remove successor (with case 2b appear after rotate)
 *
 *      parent's left                      parent's left                   parent's left                        parent's left
 *            |                                  |                               |                                    |
 *            v                                  v                               v                                    v
 *          10(b)                              10(b)                           10(b)                                10(b)
 *       /         \       successor 1      /         \                      /        \                          /        \
 *     5(b)       15(b)   ------------>   5(b)       15(b)  ------------> 7(b)       15(b)   ------------>     7(b)       15(b)
 *    /   \       /   \                  //  \       /   \               /   \       /   \                    /   \       /   \
 *  1(b) 7(r)  13(b) 20(b)             NULL 7(r)  13(b) 20(b)          5(r) 8(b)  13(b) 20(b)               5(b) 8(b)  13(b) 20(b)
 *       /  \                               /  \                      //  \                                    \
 *     6(b) 8(b)                          6(b) 8(b)                 NULL 6(b)                                 6(r)
 */
void test_removeNextLargerSuccessor_given_nodes_1_5_6_7_8_10_13_15_20_should_remove_successor_1(void)
{
    setNode(&node6, NULL, NULL, 'b');
    setNode(&node8, NULL, NULL, 'b');
    setNode(&node7, &node6, &node8, 'r');
    setNode(&node13, NULL, NULL, 'b');
    setNode(&node20, NULL, NULL, 'b');
    setNode(&node1, NULL, NULL, 'b');
    setNode(&node5, &node1, &node7, 'b');
    setNode(&node15, &node13, &node20, 'b');
    setNode(&node10, &node5, &node15, 'b');
    Node *parent = &node10, *removeNode;

    removeNode = removeNextLargerSuccessor(&parent);

    TEST_ASSERT_EQUAL_PTR(&node10, parent);
    TEST_ASSERT_EQUAL_PTR(&node1, removeNode);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node6);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node8);
    TEST_ASSERT_EQUAL_NODE(NULL, &node6, 'b', &node5);
    TEST_ASSERT_EQUAL_NODE(&node5, &node8, 'b', &node7);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node13);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node20);
    TEST_ASSERT_EQUAL_NODE(&node13, &node20, 'b', &node15);
    TEST_ASSERT_EQUAL_NODE(&node7, &node15, 'b', &node10);
}

/** Encounter case 3 on the left child after remove successor (with case 1a appear after rotate)
 *
 *      parent's left                      parent's left                   parent's left                        parent's left
 *            |                                  |                               |                                    |
 *            v                                  v                               v                                    v
 *          10(b)                              10(b)                           10(b)                                10(b)
 *       /         \       successor 1      /         \                      /        \                          /        \
 *     4(b)       15(b)   ------------>   4(b)       15(b)  ------------> 7(b)       15(b)   ------------>     7(b)       15(b)
 *    /   \       /   \                  //  \       /   \               /   \       /   \                    /   \       /   \
 *  1(b) 7(r)  13(b) 20(b)             NULL 7(r)  13(b) 20(b)          4(r) 8(b)  13(b) 20(b)               5(r) 8(b)  13(b) 20(b)
 *       /  \                               /  \                      //  \                                /   \
 *     5(b) 8(b)                          5(b) 8(b)                 NULL 5(b)                            4(b) 6(b)
 *        \                                  \                              \
 *       6(r)                               6(r)                           6(r)
 */
void test_removeNextLargerSuccessor_given_nodes_1_4_5_6_7_8_10_13_15_20_should_remove_successor_1(void)
{
    setNode(&node6, NULL, NULL, 'r');
    setNode(&node5, NULL, &node6, 'b');
    setNode(&node8, NULL, NULL, 'b');
    setNode(&node7, &node5, &node8, 'r');
    setNode(&node13, NULL, NULL, 'b');
    setNode(&node20, NULL, NULL, 'b');
    setNode(&node1, NULL, NULL, 'b');
    setNode(&node4, &node1, &node7, 'b');
    setNode(&node15, &node13, &node20, 'b');
    setNode(&node10, &node4, &node15, 'b');
    Node *parent = &node10, *removeNode;

    removeNode = removeNextLargerSuccessor(&parent);

    TEST_ASSERT_EQUAL_PTR(&node10, parent);
    TEST_ASSERT_EQUAL_PTR(&node1, removeNode);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node4);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node6);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node8);
    TEST_ASSERT_EQUAL_NODE(&node4, &node6, 'r', &node5);
    TEST_ASSERT_EQUAL_NODE(&node5, &node8, 'b', &node7);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node13);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node20);
    TEST_ASSERT_EQUAL_NODE(&node13, &node20, 'b', &node15);
    TEST_ASSERT_EQUAL_NODE(&node7, &node15, 'b', &node10);
}