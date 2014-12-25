#include "unity.h"
#include "RedBlackTree.h"
#include "Node.h"
#include "InitNode.h"
#include "CustomAssertions.h"
#include "Rotations.h"
#include "CException.h"
#include "ErrorCode.h"

Node node1, node2, node3, node4, node5, node6, node7, node8, node9, node10, node11, node12, node13, node15, node17, node18, node20, node30;

void setUp(void){
	resetNode(&node1);
	resetNode(&node2);
	resetNode(&node3);
	resetNode(&node4);
	resetNode(&node5);
	resetNode(&node6);
	resetNode(&node7);
	resetNode(&node8);
	resetNode(&node9);
	resetNode(&node10);
	resetNode(&node11);
	resetNode(&node12);
	resetNode(&node13);
	resetNode(&node15);
	resetNode(&node17);
	resetNode(&node18);
	resetNode(&node20);
	resetNode(&node30);
}

void tearDown(void){}

void test_compare_should_return_negative_1_due_to_fitness_score_is_less_than_nodePtr(void) {
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node2, NULL, NULL, 'b');
	
	Population pop3 = { .violation = 10};
	Population pop2 = { .violation = 5};
	node3.data = &pop3;
	node2.data = &pop2;
	
  Node *root = &node3;
  
  TEST_ASSERT_EQUAL(-1, compare(&root, &node2));
}

void test_compare_should_return_0_when_the_both_the_node_have_the_same_fitness_score(void) {
  setNode(&node2, NULL, NULL, 'b');
  setNode(&node2, NULL, NULL, 'b');
	
  Population pop2 = { .violation = 5};
	node2.data = &pop2;
	
	Node *root = &node2;
  
  TEST_ASSERT_EQUAL(0, compare(&root, &node2));
}

void test_compare_should_return_1_when_the_fitness_score_of_the_newNode_is_larger_than_rootPtr(void) {
  setNode(&node2, NULL, NULL, 'b');
  setNode(&node3, NULL, NULL, 'b');
	
  Population pop3 = { .violation = 10};
	Population pop2 = { .violation = 5};
	node3.data = &pop3;
	node2.data = &pop2;
	
	Node *root = &node2;
  
  TEST_ASSERT_EQUAL(1, compare(&root, &node3));
}

void test_compare_should_throw_ERR_NODE_UNAVAILABLE_due_to_it_is_comparing_NULL(void) {
  CEXCEPTION_T err;
  setNode(&node2, NULL, NULL, 'b');
  Node *root = NULL;
  
  Try {
    compare(&root, &node2);
    TEST_FAIL_MESSAGE("Expect it to throw ERR_NODE_UNAVAILABLE");
  } Catch(err) {
      TEST_ASSERT_EQUAL_MESSAGE(ERR_NODE_UNAVAILABLE, err, "Expected ERR_NODE_UNAVAILABLE exception");
    }
  
}

/**
 *         root      add fitness         root
 *          |         score 2             |
 *          v       ------------>         v
 *        NULL                            2
 */
 
void test_genericRedBlackTreeAdd_given_start_with_empty_node_should_be_able_to_add_fitness_score_2_into_the_tree(void) {
  setNode(&node2, NULL, NULL, 'b');
  Node *root = NULL;

	Population pop2 = { .violation = 5};
	node2.data = &pop2;
  
  genericRedBlackTreeAdd(&root, &node2, compare);
  TEST_ASSERT_EQUAL_PTR(&node2, root);
}

/**
 *      root                         root
 *       |        add fitness         |
 *       v         score 1            v
 *       3     -------------->        3
 *                                   /
 *                                  1
 */
void test_genericRedBlackTreeAdd_should_add_fitness_score_1_to_the_left_hand_side_of_node3_in_a_tree(void) {
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node1, NULL, NULL, 'b');
	
  Population pop3 = { .violation = 10};
	Population pop1 = { .violation = 5};
	node3.data = &pop3;
	node1.data = &pop1;
	
	Node *root = &node3;
  
  genericRedBlackTreeAdd(&root, &node1, compare);
  TEST_ASSERT_EQUAL_PTR(&node3, root);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node1);
  TEST_ASSERT_EQUAL_NODE(&node1, NULL, 'b', &node3);
}

/**
 *     root                            root
 *      |        add fitness            |
 *      v          score 4              v
 *      2      ---------------->        2
 *                                       \
 *                                        4
 */
void test_genericRedBlackTreeAdd_should_add_fitness_score_4_to_the_right_hand_side_of_node2_in_a_tree(void) {
  setNode(&node2, NULL, NULL, 'b');
  setNode(&node4, NULL, NULL, 'b');
  Population pop4 = { .violation = 10};
	Population pop2 = { .violation = 5};
	node4.data = &pop4;
	node2.data = &pop2;
	Node *root = &node2;
  
  genericRedBlackTreeAdd(&root, &node4, compare);
  TEST_ASSERT_EQUAL_PTR(&node2, root);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node4);
  TEST_ASSERT_EQUAL_NODE(NULL, &node4, 'b', &node2);
}

/**
 *    root                    
 *     |    add fitness      
 *     v     score 3           Throw an error
 *     3   -------------->   due to ERR_EQUIVALENT_NODE
 */
void test_genericRedBlackTreeAdd_should_throw_ERR_EQUIVALENT_NODE_due_to_newNode_is_same_node_as_nodePtr(void) {
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node3, NULL, NULL, 'b');
  CEXCEPTION_T err;
	Population pop3 = { .violation = 10};
	node3.data = &pop3;
  Node *root = &node3;
  
  Try {
    genericRedBlackTreeAdd(&root, &node3, compare);
    TEST_FAIL_MESSAGE("Expected ERR_EQUIVALENT_NODE to be thrown");
  } Catch(err) {
      TEST_ASSERT_EQUAL_MESSAGE(ERR_EQUIVALENT_NODE, err, "Expected ERR_EQUIVALENT_NODE exception");
    }
}

/**
 *        root                              root
 *         |                                 |
 *         v                                 v
 *        2(b)         remove 3            2(b)
 *       /   \       ------------>        /   
 *     1(r)  3(r)                      1(r)   
 */
void test_removeLargestValue_it_should_remove_node_3_from_2_1_3_tree(void) {
  setNode(&node3, NULL, NULL, 'r');
  setNode(&node1, NULL, NULL, 'r');
  setNode(&node2, &node1, &node3, 'b');
  Population pop3 = { .violation = 10};
	Population pop2 = { .violation = 5};
	Population pop1 = { .violation = 1};
	node3.data = &pop3;
	node2.data = &pop2;
	node1.data = &pop1;
	Node *root = &node2;
  Node *removeNode;
  
  removeNode = removeLargestValue(&root);
  TEST_ASSERT_EQUAL_PTR(&node2, root);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node1);
  TEST_ASSERT_EQUAL_NODE(&node1, NULL, 'b', &node2);
  TEST_ASSERT_EQUAL(10, removeNode->data->violation);
	
}

/**
 *        root                              root
 *         |                                 |
 *         v                                 v
 *        2(b)         remove 3            2(b)
 *       /   \       ------------>        /   
 *     1(r)  3(r)                      1(r)   
 */
void test_removeSmallestValue_it_should_remove_node_1_from_2_1_3_tree(void) {
  setNode(&node3, NULL, NULL, 'r');
  setNode(&node1, NULL, NULL, 'r');
  setNode(&node2, &node1, &node3, 'b');
  Population pop3 = { .violation = 10};
	Population pop2 = { .violation = 5};
	Population pop1 = { .violation = 1};
	node3.data = &pop3;
	node2.data = &pop2;
	node1.data = &pop1;
	Node *root = &node2;
  Node *removeNode;
  
  removeNode = removeSmallestValue(&root);
  TEST_ASSERT_EQUAL_PTR(&node2, root);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node3);
  TEST_ASSERT_EQUAL_NODE(NULL, &node3, 'b', &node2);
  TEST_ASSERT_EQUAL(1, removeNode->data->violation);
	
}