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

  for(venue = 0 ; venue < MAX_VENUE; venue++) {
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

void test_calculateFitnessScore_should_return_2_when_only_violating_TutionOverloadedInSingleDay(){
  addDetailsIntoChromosome(class, &course[0], &lecturer[0], 'l');
  addDetailsIntoChromosome(class, &course[0], &lecturer[0], 'l');

  // extra 2 to violate twice, returns 2  
  addDetailsIntoChromosome(class, &course[0], &lecturer[0], 'l');
  addDetailsIntoChromosome(class, &course[0], &lecturer[0], 'l');

  TEST_ASSERT_EQUAL(2,calculateFitnessScore(class));
}

void test_calculateFitnessScore_should_return_1_when_lecturerAppearInTwoVenue(){
  addDetailsIntoChromosome(class, &course[0], &lecturer[0], 'l');
  class[3][0][0].course = &course[1];
  class[3][0][0].lecturer = &lecturer[0];
  class[3][0][0].typeOfClass = 'l';

  TEST_ASSERT_EQUAL(1,calculateFitnessScore(class));
}

void test_calculateFitnessScore_should_return_1_when_studentAppearInTwoVenue(){
  addDetailsIntoChromosome(class, &course[0], &lecturer[0], 'l');
  class[3][0][0].course = &course[0];
  class[3][0][0].lecturer = &lecturer[1];
  class[3][0][0].typeOfClass = 'l';

  TEST_ASSERT_EQUAL(1,calculateFitnessScore(class));
}

void test_calculateFitnessScore_should_return_1_when_determineViolationForCourseVenueSize_violates(){
	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');

  TEST_ASSERT_EQUAL(1,calculateFitnessScore(class));
}

void test_calculateFitnessScore_should_return_8_when_violates_all_but_TuitionOverload(){
  /**
   *  checkIfTutionOverloadedInSingleDay = 0
   *  checkLecturerNotInchargeOfCourse = 4
   *  checkIfLecturerAppearInTwoVenue = 1
   *  checkStudentViolation = 1
   *  determineViolationForCourseVenueSize = 2
   *  total should be 8
   */

	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');
	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');
	addDetailsIntoChromosome(class, &course[2], &lecturer[3], 'l');
	
	class[3][0][2].course = &course[2];
  class[3][0][2].lecturer = &lecturer[3];
  class[3][0][2].typeOfClass = 'l';
	

  TEST_ASSERT_EQUAL(4,calculateFitnessScore(class));
}

void test_calculateFitnessScore_should_return_8_when_violates_all_but_checkLecturerNotInchargeOfCourse(){
  /**
   *  checkIfTutionOverloadedInSingleDay = 2
   *  checkLecturerNotInchargeOfCourse = 0
   *  checkIfLecturerAppearInTwoVenue = 1
   *  checkStudentViolation = 1
   *  determineViolationForCourseVenueSize = 4
   *  total should be 8
   */

	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');
	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');
	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');
	
	class[3][0][2].course = &course[3];
  class[3][0][2].lecturer = &lecturer[3];
  class[3][0][2].typeOfClass = 'l';
	

  TEST_ASSERT_EQUAL(8,calculateFitnessScore(class));
}

void test_calculateFitnessScore_should_return_11_when_violates_all_but_checkIfLecturerAppearInTwoVenue(){
  /**
   *  checkIfTutionOverloadedInSingleDay = 2
   *  checkLecturerNotInchargeOfCourse = 4
   *  checkIfLecturerAppearInTwoVenue = 0
   *  checkStudentViolation = 1
   *  determineViolationForCourseVenueSize = 4
   *  total should be 11
   */
	
  addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');
	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');
	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');
	
	class[3][0][0].course = &course[3];
  class[3][0][0].lecturer = &lecturer[2];
  class[3][0][0].typeOfClass = 'l';
	

  TEST_ASSERT_EQUAL(7,calculateFitnessScore(class));
}

void test_calculateFitnessScore_should_return_9_when_violates_all_but_checkStudentViolation(){
  /**
   *  checkIfTutionOverloadedInSingleDay = 1
   *  checkLecturerNotInchargeOfCourse = 4
   *  checkIfLecturerAppearInTwoVenue = 1
   *  checkStudentViolation = 0
   *  determineViolationForCourseVenueSize = 3
   *  total should be 9
   */
	
  addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');
	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');
	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');
	
	class[3][0][0].course = &course[2];
  class[3][0][0].lecturer = &lecturer[3];
  class[3][0][0].typeOfClass = 'l';
	

  TEST_ASSERT_EQUAL(5,calculateFitnessScore(class));
}

void test_calculateFitnessScore_should_return_8_when_violates_all_but_determineViolationForCourseVenueSize(){
  /**
   *  checkIfTutionOverloadedInSingleDay = 2
   *  checkLecturerNotInchargeOfCourse = 4
   *  checkIfLecturerAppearInTwoVenue = 1
   *  checkStudentViolation = 1
   *  determineViolationForCourseVenueSize = 0
   *  total should be 8
   */
  
	addDetailsIntoChromosome(class, &course[2], &lecturer[3], 'l');
	addDetailsIntoChromosome(class, &course[2], &lecturer[3], 'l');
	addDetailsIntoChromosome(class, &course[2], &lecturer[3], 'l');
	
	class[3][0][0].course = &course[2];
  class[3][0][0].lecturer = &lecturer[3];
  class[3][0][0].typeOfClass = 'l';
	

  TEST_ASSERT_EQUAL(4,calculateFitnessScore(class));
}

void test_calculateFitnessScore_should_return_12_when_violates_all(){ 
  /**
   *  checkIfTutionOverloadedInSingleDay = 2
   *  checkLecturerNotInchargeOfCourse = 4
   *  checkIfLecturerAppearInTwoVenue = 1
   *  checkStudentViolation = 1
   *  determineViolationForCourseVenueSize = 4
   *  total should be 12
   */
	
	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');
	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');
	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');
	
	class[3][0][0].course = &course[3];
  class[3][0][0].lecturer = &lecturer[3];
  class[3][0][0].typeOfClass = 'l';
	

  TEST_ASSERT_EQUAL(8,calculateFitnessScore(class));
}

/**
 *          root                      root
 *           |        add fitness      |
 *           v          score 1        v
 *          NULL    ------------->     1
 */
void test_calculateFitnessScore_and_genericRedBlackTreeAdd_should_be_able_to_add_fitness_score_2_into_the_redBlackTree(void) {
  int numberOfClashes = 0;
	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');
  
  numberOfClashes = calculateFitnessScore(class);
  resetNode(&node1, numberOfClashes);
  class[0][0][0].classNode = &node1;
  setNode(&node1, NULL, NULL, 'b');
  Node *root = NULL;
  
  genericRedBlackTreeAdd(&root, &node1, compare);
  TEST_ASSERT_EQUAL(1, numberOfClashes);
  TEST_ASSERT_EQUAL_PTR(&node1, root);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node1);
  TEST_ASSERT_EQUAL(1, class[0][0][0].classNode->data);
}

/**
 *       root                   root                     root
 *        |     add fitness      |     add fitness        |
 *        v       score 2        v       score 1          v
 *       NULL  ------------>     2    ------------>       2
 *                                                       /
 *                                                      1
 */
void test_calculateFitnessScore_and_genericRedBlackTreeAdd_should_be_able_to_add_fitness_score_2_1_into_redBlackTree(void) {
  int firstNumberOfClashes = 0, secondNumberOfClashes = 0;

  // TuitionOverloadInSingleDay() Violation
  addDetailsIntoChromosome(class, &course[0], &lecturer[0], 'l');
  addDetailsIntoChromosome(class, &course[0], &lecturer[0], 'l');

  // extra 2 to violate twice, returns 2  
  addDetailsIntoChromosome(class, &course[0], &lecturer[0], 'l');
  addDetailsIntoChromosome(class, &course[0], &lecturer[0], 'l');

  firstNumberOfClashes = calculateFitnessScore(class);
  resetNode(&node2, firstNumberOfClashes);
  class[0][0][0].classNode = &node2;
  setNode(&node2, NULL, NULL, 'b');
  Node *root = NULL;
  
  genericRedBlackTreeAdd(&root, &node2, compare);
  setUp();
  
  // determineViolationForCourseVenueSize() Violation
	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');
  
  secondNumberOfClashes = calculateFitnessScore(class);
  resetNode(&node1, secondNumberOfClashes);
  class[0][0][1].classNode = &node1;
  setNode(&node1, NULL, NULL, 'b');
  root = &node2;
  
  genericRedBlackTreeAdd(&root, &node1, compare);
  TEST_ASSERT_EQUAL_PTR(&node2, root);
  TEST_ASSERT_EQUAL_NODE(&node1, NULL, 'b', &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node1);
  TEST_ASSERT_EQUAL(2, class[0][0][0].classNode->data);
  TEST_ASSERT_EQUAL(1, class[0][0][1].classNode->data);
}

/**
 *      root                  root                    root                   root
 *       |    add fitness      |     add fitness       |     add fitness      |
 *       v     score 2         v      score 1          v      score 8         v
 *      NULL  ----------->     2    ------------>      2     ----------->     2
 *                                                    /                     /   \
 *                                                   1                     1     8
 */
void test_calculateFitnessScore_and_genericRedBlackTreeAdd_should_be_able_to_add_fitness_score_2_1_8_into_redBlackTree(void) {
  int firstNumberOfClashes = 0, secondNumberOfClashes = 0, thirdNumberOfClashes;

  // TuitionOverloadInSingleDay() Violation
  addDetailsIntoChromosome(class, &course[0], &lecturer[0], 'l');
  addDetailsIntoChromosome(class, &course[0], &lecturer[0], 'l');

  // extra 2 to violate twice, returns 2  
  addDetailsIntoChromosome(class, &course[0], &lecturer[0], 'l');
  addDetailsIntoChromosome(class, &course[0], &lecturer[0], 'l');

  firstNumberOfClashes = calculateFitnessScore(class);
  resetNode(&node2, firstNumberOfClashes);
  class[0][0][0].classNode = &node2;
  setNode(&node2, NULL, NULL, 'b');
  Node *root = NULL;
  
  genericRedBlackTreeAdd(&root, &node2, compare);
  setUp();
  
  // determineViolationForCourseVenueSize() Violation
	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');
  
  secondNumberOfClashes = calculateFitnessScore(class);
  resetNode(&node1, secondNumberOfClashes);
  class[0][0][1].classNode = &node1;
  setNode(&node1, NULL, NULL, 'b');
  root = &node2;
  
  genericRedBlackTreeAdd(&root, &node1, compare);
  setUp();
  
  // checkLecturerNotInchargeOfCourse() Violation
  /**
   *  checkIfTutionOverloadedInSingleDay = 2
   *  checkLecturerNotInchargeOfCourse = 0
   *  checkIfLecturerAppearInTwoVenue = 1
   *  checkStudentViolation = 1
   *  determineViolationForCourseVenueSize = 4
   *  total should be 8
   */

	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');
	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');
	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');
	
	class[3][0][2].course = &course[3];
  class[3][0][2].lecturer = &lecturer[3];
  class[3][0][2].typeOfClass = 'l';
  
  thirdNumberOfClashes = calculateFitnessScore(class);
  resetNode(&node8, thirdNumberOfClashes);
  class[0][0][2].classNode = &node8;
  setNode(&node8, NULL, NULL, 'b');
  root = &node2;
  
  genericRedBlackTreeAdd(&root, &node8, compare);
  
  TEST_ASSERT_EQUAL_PTR(&node2, root);
  TEST_ASSERT_EQUAL_NODE(&node1, &node8, 'b', &node2);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node1);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node8);
  TEST_ASSERT_EQUAL(2, class[0][0][0].classNode->data);
  TEST_ASSERT_EQUAL(1, class[0][0][1].classNode->data);
  TEST_ASSERT_EQUAL(8, class[0][0][2].classNode->data);
  TEST_ASSERT_EQUAL(2, firstNumberOfClashes);
  TEST_ASSERT_EQUAL(1, secondNumberOfClashes);
  TEST_ASSERT_EQUAL(8, thirdNumberOfClashes);
}
