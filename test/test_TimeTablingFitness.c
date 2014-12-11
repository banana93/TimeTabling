#include "unity.h"
#include <stdio.h>
#include "TimeTabling.h"
#include "Node.h"
#include "RedBlackTree.h"
#include "ErrorCode.h"
#include "CustomAssertions.h"
#include "Rotations.h"
#include "InitNode.h"

Node node1, node2, node3, node4, node5, node6, node7, node8, node9, node10, node11, node12, node13, node15, node17, node18, node20, node30;

void setUp(void){
	int venue = 0;
  int day = 0, time = 0;
  
  for(venue = 0; venue < 4; venue++) {
    for(day = 0; day < MAX_DAY; day++) {
      for(time = 0; time < MAX_TIME_SLOTS; time++) {
				class[venue][day][time].lecturer = NULL;
				class[venue][day][time].course = NULL;
				class[venue][day][time].typeOfClass = 0;
			}
		}
	}
}

void tearDown(void){}

void test_calculateFitnessScore_should_return_0_when_empty_class(){
	TEST_ASSERT_EQUAL(0,calculateFitnessScore(class));
}

void test_calculateFitnessScore_should_return_1_when_only_violating_lecturerNotInCharge(){
	
  lecturer[0].courseCodeInCharge[0] = "ABCD1234";
  addDetailsIntoChromosome(class, &course[0], &lecturer[0], 'l');

  TEST_ASSERT_EQUAL(1,calculateFitnessScore(class));
}

void test_calculateFitnessScore_should_return_2_when_only_violating_TutionOverloadedInSingleDay(){
  lecturer[0].courseCodeInCharge[0] = "AAMP2041";
  lecturer[0].courseCodeInCharge[1] = NULL;

  addDetailsIntoChromosome(class, &course[0], &lecturer[0], 'l');
  addDetailsIntoChromosome(class, &course[0], &lecturer[0], 'l');

  // extra 2 to violate twice, returns 2  
  addDetailsIntoChromosome(class, &course[0], &lecturer[0], 'l');
  addDetailsIntoChromosome(class, &course[0], &lecturer[0], 'l');

  TEST_ASSERT_EQUAL(2,calculateFitnessScore(class));
}

void test_calculateFitnessScore_should_return_1_when_lecturerAppearInTwoVenue(){
  lecturer[0].courseCodeInCharge[0] = "AAMP2041";
  lecturer[0].courseCodeInCharge[1] = "AAMB2034";
  lecturer[0].courseCodeInCharge[2] = NULL;

  addDetailsIntoChromosome(class, &course[0], &lecturer[0], 'l');
  class[3][0][0].course = &course[1];
  class[3][0][0].lecturer = &lecturer[0];
  class[3][0][0].typeOfClass = 'l';

  TEST_ASSERT_EQUAL(1,calculateFitnessScore(class));
}

void test_calculateFitnessScore_should_return_1_when_studentAppearInTwoVenue(){
  lecturer[0].courseCodeInCharge[0] = "AAMP2041";
  lecturer[0].courseCodeInCharge[1] = NULL;
  lecturer[1].courseCodeInCharge[0] = "AAMP2041";
  lecturer[1].courseCodeInCharge[1] = NULL;

  addDetailsIntoChromosome(class, &course[0], &lecturer[0], 'l');
  class[3][0][0].course = &course[0];
  class[3][0][0].lecturer = &lecturer[1];
  class[3][0][0].typeOfClass = 'l';

  TEST_ASSERT_EQUAL(1,calculateFitnessScore(class));
}

void test_calculateFitnessScore_should_return_1_when_determineViolationForCourseVenueSize_violates(){
  lecturer[3].courseCodeInCharge[0] = "ABCD1234";
  lecturer[3].courseCodeInCharge[1] = NULL;
	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');

  TEST_ASSERT_EQUAL(1,calculateFitnessScore(class));
}

void test_calculateFitnessScore_should_return_(){
  lecturer[0].courseCodeInCharge[0] = NULL; // to remove value declared on top
  lecturer[1].courseCodeInCharge[0] = NULL; // to remove value declared on top
  lecturer[2].courseCodeInCharge[0] = NULL; // to remove value declared on top
  lecturer[3].courseCodeInCharge[0] = NULL; // to remove value declared on top
	
//checkIfTutionOverloadedInSingleDay = 2
//checkLecturerNotInchargeOfCourse = 4
//checkIfLecturerAppearInTwoVenue = 1
//checkStudentViolation = 1
//determineViolationForCourseVenueSize = 4
//total should be 12
	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');
	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');
	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');
	
	class[3][0][0].course = &course[3];
  class[3][0][0].lecturer = &lecturer[3];
  class[3][0][0].typeOfClass = 'l';
	

  TEST_ASSERT_EQUAL(12,calculateFitnessScore(class));
}

/**
 *          root                      root
 *           |        add fitness      |
 *           v          score 1        v
 *          NULL    ------------->     1
 */
void test_calculateFitnessScore_and_genericRedBlackTreeAdd_should_be_able_to_add_the_details_into_the_redBlackTree(void) {
  int numberOfClashes = 0;
  lecturer[0].courseCodeInCharge[0] = NULL; // to remove value declared on top
  lecturer[1].courseCodeInCharge[0] = NULL; // to remove value declared on top
  lecturer[2].courseCodeInCharge[0] = NULL; // to remove value declared on top
  lecturer[3].courseCodeInCharge[0] = NULL; // to remove value declared on top
  lecturer[3].courseCodeInCharge[0] = "ABCD1234";
  lecturer[3].courseCodeInCharge[1] = NULL;
	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');
  
  numberOfClashes = calculateFitnessScore(class);
  printf("numberOfClashes: %d\n", numberOfClashes);
  resetNode(&node1, numberOfClashes);
  class[0][0][0].classNode = &node1;
  
  setNode(&node1, NULL, NULL, 'b');
  Node *root = NULL;
  
  genericRedBlackTreeAdd(&root, &node1, compare);
  TEST_ASSERT_EQUAL_PTR(&node1, root);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node1);
  TEST_ASSERT_EQUAL(1, class[0][0][0].classNode->data);
  
}
