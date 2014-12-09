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
	resetNode(&node1, 1);
	resetNode(&node2, 2);
	resetNode(&node3, 3);
	resetNode(&node4, 4);
	resetNode(&node5, 5);
	resetNode(&node6, 6);
	resetNode(&node7, 7);
	resetNode(&node8, 8);
	resetNode(&node9, 9);
	resetNode(&node10, 10);
	resetNode(&node11, 11);
	resetNode(&node12, 12);
	resetNode(&node13, 13);
	resetNode(&node15, 15);
	resetNode(&node17, 17);
	resetNode(&node18, 18);
	resetNode(&node20, 20);
	resetNode(&node30, 30);
}

void tearDown(void){}

void test_compare_should_return_negative_1_due_to_fitness_score_is_less_than_nodePtr(void) {
  setNode(&node3, NULL, NULL, 'b');
  setNode(&node2, NULL, NULL, 'b');
  Node *root = &node3;
  
  TEST_ASSERT_EQUAL(-1, compare(&root, &node2));
}

void test_compare_should_return_0_when_the_both_the_node_have_the_same_fitness_score(void) {
  setNode(&node2, NULL, NULL, 'b');
  setNode(&node2, NULL, NULL, 'b');
  Node *root = &node2;
  
  TEST_ASSERT_EQUAL(0, compare(&root, &node2));
}

void test_compare_should_return_1_when_the_fitness_score_of_the_newNode_is_larger_than_rootPtr(void) {
  setNode(&node2, NULL, NULL, 'b');
  setNode(&node3, NULL, NULL, 'b');
  Node *root = &node2;
  
  TEST_ASSERT_EQUAL(1, compare(&root, &node3));
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
  Node *root = &node3;
  
  Try {
    genericRedBlackTreeAdd(&root, &node3, compare);
    TEST_FAIL_MESSAGE("Expected ERR_EQUIVALENT_NODE to be thrown");
  } Catch(err) {
      TEST_ASSERT_EQUAL_MESSAGE(ERR_EQUIVALENT_NODE, err, "Expected ERR_EQUIVALENT_NODE exception");
    }
}

