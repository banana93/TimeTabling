#include "unity.h"
#include <stdio.h>
#include "TimeTabling.h"
#include "LinkedList.h"
#include "Node.h"
#include "RedBlackTree.h"
#include "ErrorCode.h"
#include "CustomAssertions.h"
#include "Rotations.h"
#include "InitNode.h"
#include "mock_Random.h"
#include "CException.h"

void setUp(void){
	int venue = 0;
  int day = 0, time = 0;
	int i;
  
  for(venue = 0; venue < MAX_VENUE; venue++) {
    for(day = 0; day < MAX_DAY; day++) {
      for(time = 0; time < MAX_TIME_SLOTS; time++) {
				class[venue][day][time].lecturer = NULL;
				class[venue][day][time].course = NULL;
				class[venue][day][time].typeOfClass = 0;
				for(i = 0 ; i < 5 ; i++){
					class[venue][day][time].group[i] = NULL;
				}
			}
		}
	}
}

void tearDown(void){}

void test_checkViolationWhenSwapClasses_should_return_1_when_it_detects_there_is_still_violation_if_it_swaps(void) {
  int result = 0;
  class[0][0][0].lecturer = &lecturer[0];
  class[3][0][0].lecturer = &lecturer[0];
  
  result = checkViolationWhenSwapClasses(class);
  TEST_ASSERT_EQUAL(1, result);
}

void test_checkViolationWhenSwapClasses_should_return_0_when_it_does_not_detect_any_violation_after_swap(void) {
  int result = 0;
  class[0][0][0].lecturer = &lecturer[0];
  class[0][0][0].course = &course[0];
  
  result = checkViolationWhenSwapClasses(class);
  TEST_ASSERT_EQUAL(0, result);
}

void test_createPopulationsOfChromosomeNotRandomize_should_be_able_to_create_populations_that_follows_the_order_of_classList(void) {
  createPopulationsOfChromosomeNotRandomize(sizeof(classList)/sizeof(Class));

  TEST_ASSERT_EQUAL(1, compareClass(populationOfClasses[0].class[0][0][0], classList[0]));
  TEST_ASSERT_EQUAL(1, compareClass(populationOfClasses[5].class[0][0][0], classList[0]));
  TEST_ASSERT_EQUAL(1, compareClass(populationOfClasses[19].class[0][0][1], classList[1]));
}

void test_calculateHeightOfTree_should_be_able_to_return_the_result_of_the_height_of_the_rbt(void) {
  int heightOfTree = 0;
  double numberOfNodes = 6;
  
  heightOfTree = calculateHeightOfTree(numberOfNodes);
  TEST_ASSERT_EQUAL(5, heightOfTree);
}

// void test_performMutation_should_be_able_to_choose_the_specific_class_number_1_from_the_population_due_to_mock_random_function(void) {
  // createPopulationsOfChromosomeNotRandomize(sizeof(classList)/sizeof(Class));
  
  
// }
