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

Node node1, node2, node3, node4, node5, node6, node7, node8, node9, node10, node11, node12, node13, node15, node17, node18, node20, node30;

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

void test_calculateFitnessScore_should_return_0_when_empty_class(){
	TEST_ASSERT_EQUAL(0,calculateFitnessScore(class));
}

/***********************************************************************************
 *  calculateFitnessScore() 
 ***********************************************************************************/
void test_calculateFitnessScore_should_return_1_when_only_violating_TutionOverloadedInSingleDay(){
	class[1][0][0].group[0] = &group[0];
	class[1][0][0].group[1] = NULL;
	class[1][0][1].group[0] = &group[0];
	class[1][0][1].group[1] = NULL;
	class[1][0][2].group[0] = &group[0];
	class[1][0][2].group[1] = NULL;
	class[1][0][3].group[0] = &group[0];
	class[1][0][3].group[1] = NULL;
	class[1][0][4].group[0] = &group[0];
	class[1][0][4].group[1] = NULL;

  TEST_ASSERT_EQUAL(1,calculateFitnessScore(class));
}

void test_calculateFitnessScore_should_return_1_when_lecturerAppearInTwoVenue(){

  class[0][0][0].lecturer = &lecturer[0];
  class[3][0][0].lecturer = &lecturer[0];

  TEST_ASSERT_EQUAL(1,calculateFitnessScore(class));
}

void test_calculateFitnessScore_should_return_1_when_studentAppearInTwoVenue(){

  class[0][0][0].group[0] = &group[0];
  class[0][0][0].group[1] = NULL;
	class[1][0][0].group[0] = &group[0];
  class[1][0][0].group[1] = NULL;

  TEST_ASSERT_EQUAL(1,calculateFitnessScore(class));
}

void test_calculateFitnessScore_should_return_15_when_determineViolationForCourseVenueSize_violates(){
	class[1][0][0].group[0] = &group[0]; // 				12
  class[1][0][0].group[1] = &group[1]; // 				13
  class[1][0][0].group[2] = &group[2]; // 				15
																			 //total = 	40
  class[1][0][0].group[3] = NULL;			 //venue = 	25
																			 //violate = 15
	
  TEST_ASSERT_EQUAL(15,calculateFitnessScore(class));
}

void test_calculateFitnessScore_should_return_12_when_violates_all_but_TuitionOverload(){
  /**
   *  checkIfTutionOverloadedInSingleDay = 0
   *  checkIfLecturerAppearInTwoVenue = 1
   *  checkStudentViolation = 1
   *  determineViolationForCourseVenueSize = 10
   *  total should be 5
   */
	class[0][0][0].group[0] = &group[0];
	class[0][0][0].group[1] = &group[1];
	class[0][0][0].group[2] = &group[2];
	class[0][0][0].group[3] = &group[3];
  class[0][0][0].group[4] = NULL;
  class[0][0][0].lecturer = &lecturer[0];
  class[1][0][0].group[0] = &group[0];
  class[1][0][0].group[1] = NULL;
	class[1][0][0].lecturer = &lecturer[0];

  TEST_ASSERT_EQUAL(12,calculateFitnessScore(class));
}

void test_calculateFitnessScore_should_return_12_when_violates_all_but_checkIfLecturerAppearInTwoVenue(){
  /**
   *  checkIfTutionOverloadedInSingleDay = 1
   *  checkIfLecturerAppearInTwoVenue = 0
   *  checkStudentViolation = 1
   *  determineViolationForCourseVenueSize = 10
   *  total should be 5
   */
	
	class[0][0][0].group[0] = &group[0];
	class[0][0][0].group[1] = &group[1];
	class[0][0][0].group[2] = &group[2];
	class[0][0][0].group[3] = &group[3];
	class[0][0][0].group[4] = NULL;
  class[0][0][0].lecturer = &lecturer[0];
	class[0][0][1].group[0] = &group[0];
	class[0][0][1].group[1] = NULL;
  class[0][0][1].lecturer = &lecturer[0];
	class[0][0][2].group[0] = &group[0];
	class[0][0][2].group[1] = NULL;
  class[0][0][2].lecturer = &lecturer[0];
	
	class[3][0][2].group[0] = &group[0];
	class[3][0][2].group[1] = NULL;
  class[3][0][2].lecturer = &lecturer[1];
	class[3][0][3].group[0] = &group[0];
	class[3][0][3].group[1] = NULL;
  class[3][0][3].lecturer = &lecturer[1];
	

  TEST_ASSERT_EQUAL(12,calculateFitnessScore(class));
}

void test_calculateFitnessScore_should_return_12_when_violates_all_but_checkStudentViolation(){
  /**
   *  checkIfTutionOverloadedInSingleDay = 1
   *  checkIfLecturerAppearInTwoVenue = 1
   *  checkStudentViolation = 0
   *  determineViolationForCourseVenueSize = 10
   *  total should be 5
   */
	
	class[0][0][0].group[0] = &group[0];
	class[0][0][0].group[1] = &group[1];
	class[0][0][0].group[2] = &group[2];
	class[0][0][0].group[3] = &group[3];
	class[0][0][0].group[4] = NULL;
  class[0][0][0].lecturer = &lecturer[0];
	class[0][0][1].group[0] = &group[0];
	class[0][0][1].group[1] = NULL;
  class[0][0][1].lecturer = &lecturer[0];
	class[0][0][2].group[0] = &group[0];
	class[0][0][2].group[1] = NULL;
  class[0][0][2].lecturer = &lecturer[0];
	
	class[3][0][2].group[0] = &group[1];
	class[3][0][2].group[1] = NULL;
  class[3][0][2].lecturer = &lecturer[0];
	class[3][0][3].group[0] = &group[0];
	class[3][0][3].group[1] = NULL;
  class[3][0][3].lecturer = &lecturer[1];
	class[3][0][4].group[0] = &group[0];
	class[3][0][4].group[1] = NULL;
  class[3][0][4].lecturer = &lecturer[1];
	

  TEST_ASSERT_EQUAL(12,calculateFitnessScore(class));
}

void test_calculateFitnessScore_should_return_3_when_violates_all_but_determineViolationForCourseVenueSize(){
  /**
   *  checkIfTutionOverloadedInSingleDay = 1
   *  checkIfLecturerAppearInTwoVenue = 1
   *  checkStudentViolation = 1
   *  determineViolationForCourseVenueSize = 0
   *  total should be 3
   */
  
	class[0][0][0].group[0] = &group[0];
	class[0][0][0].group[2] = NULL;
  class[0][0][0].lecturer = &lecturer[0];
	class[0][0][1].group[0] = &group[0];
	class[0][0][1].group[1] = NULL;
  class[0][0][1].lecturer = &lecturer[0];
	class[0][0][2].group[0] = &group[0];
	class[0][0][2].group[1] = NULL;
  class[0][0][2].lecturer = &lecturer[0];
	
	class[3][0][2].group[0] = &group[0];
	class[3][0][2].group[1] = NULL;
  class[3][0][2].lecturer = &lecturer[0];
	class[3][0][3].group[0] = &group[0];
	class[3][0][3].group[1] = NULL;
  class[3][0][3].lecturer = &lecturer[0];

	

  TEST_ASSERT_EQUAL(3,calculateFitnessScore(class));
}

void test_calculateFitnessScore_should_return_13_when_violates_all(){ 
  /**
   *  checkIfTutionOverloadedInSingleDay = 1
   *  checkIfLecturerAppearInTwoVenue = 1
   *  checkStudentViolation = 1
   *  determineViolationForCourseVenueSize = 10
   *  total should be 13
   */
	
	class[0][0][0].group[0] = &group[0];
	class[0][0][0].group[1] = &group[1];
	class[0][0][0].group[2] = &group[2];
	class[0][0][0].group[3] = &group[3];
	class[0][0][0].group[4] = NULL;
  class[0][0][0].lecturer = &lecturer[0];
	class[0][0][1].group[0] = &group[0];
	class[0][0][1].group[1] = NULL;
  class[0][0][1].lecturer = &lecturer[0];
	class[0][0][2].group[0] = &group[0];
	class[0][0][2].group[1] = NULL;
  class[0][0][2].lecturer = &lecturer[0];
	
	class[3][0][2].group[0] = &group[0];
	class[3][0][2].group[1] = NULL;
  class[3][0][2].lecturer = &lecturer[0];
	class[3][0][3].group[0] = &group[0];
	class[3][0][3].group[1] = NULL;
  class[3][0][3].lecturer = &lecturer[0];
	

  TEST_ASSERT_EQUAL(13,calculateFitnessScore(class));
}

/**
 *          root                      root
 *           |        add fitness      |
 *           v          score 1        v
 *          NULL    ------------->     1
 */
void test_calculateFitnessScore_and_genericRedBlackTreeAdd_should_be_able_to_add_fitness_score_2_into_the_redBlackTree(void) {
  int numberOfClashes = 0;
  // lecturerAppearInTwoVenue() Violation
  class[0][0][0].lecturer = &lecturer[0];
  class[3][0][0].lecturer = &lecturer[0];
	
	Population pop1;
	copyClass(class, pop1.class);
	
  numberOfClashes = calculateFitnessScore(pop1.class);
	pop1.violation = numberOfClashes;

  setNode(&node1, NULL, NULL, 'b');
	node1.data = &pop1;
  Node *root = NULL;
  
  addRedBlackTree(&root, &node1);
  TEST_ASSERT_EQUAL(1, numberOfClashes);
  TEST_ASSERT_EQUAL_PTR(&node1, root);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node1);
}

/**
 *       root                   root                     root
 *        |     add fitness      |     add fitness        |
 *        v       score 3        v       score 1          v
 *       NULL  ------------>     3    ------------>       3
 *                                                       /
 *                                                      1
 */
void test_calculateFitnessScore_and_genericRedBlackTreeAdd_should_be_able_to_add_fitness_score_2_1_into_redBlackTree(void) {
  int firstNumberOfClashes = 0, secondNumberOfClashes = 0;

  // determineViolationForCourseVenueSize() Violation
 	class[0][0][0].group[0] = &group[5]; // 				14
  class[0][0][0].group[1] = &group[6]; // 				16
  class[0][0][0].group[2] = &group[1]; // 				13
																			 //total = 	43
  class[0][0][0].group[3] = NULL;			 //venue = 	40
																			 //violate = 3
	Population pop3;
	copyClass(class, pop3.class);
	
  firstNumberOfClashes = calculateFitnessScore(pop3.class);
	pop3.violation = firstNumberOfClashes;

  setNode(&node3, NULL, NULL, 'b');
  node3.data = &pop3;
  Node *root = NULL;
  
  addRedBlackTree(&root, &node3);
  setUp();
	
  // lecturerAppearInTwoVenue() Violation
  class[0][0][0].lecturer = &lecturer[0];
  class[3][0][0].lecturer = &lecturer[0];
  
  Population pop1;
	copyClass(class, pop1.class);
  secondNumberOfClashes = calculateFitnessScore(pop1.class);
	
	pop1.violation = secondNumberOfClashes;


  setNode(&node1, NULL, NULL, 'b');
  node1.data = &pop1;
  
  addRedBlackTree(&root, &node1);
  TEST_ASSERT_EQUAL_PTR(&node3, root);
  TEST_ASSERT_EQUAL_NODE(&node1, NULL, 'b', &node3);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node1);
}

/**
 *      root                  root                    root                   root
 *       |    add fitness      |     add fitness       |     add fitness      |
 *       v     score 3         v      score 1          v      score 6         v
 *      NULL  ----------->     3    ------------>      3     ----------->     3
 *                                                    /                     /   \
 *                                                   1                     1     6
 */
void test_calculateFitnessScore_and_genericRedBlackTreeAdd_should_be_able_to_add_fitness_score_2_1_8_into_redBlackTree(void) {
  int firstNumberOfClashes = 0, secondNumberOfClashes = 0, thirdNumberOfClashes;

  // determineViolationForCourseVenueSize() Violation
 	class[0][0][0].group[0] = &group[5]; // 				10
  class[0][0][0].group[1] = &group[6]; // 				13
  class[0][0][0].group[2] = &group[1]; // 				20
																			 //total = 	43
  class[0][0][0].group[3] = NULL;			 //venue = 	40
																			 //violate = 3

	Population pop3;
	copyClass(class, pop3.class);
	
  firstNumberOfClashes = calculateFitnessScore(pop3.class);
	pop3.violation = firstNumberOfClashes;
  setNode(&node3, NULL, NULL, 'b');
	node3.data = &pop3;
  Node *root = NULL;
  
  addRedBlackTree(&root, &node3);
  setUp();
  
  // lecturerAppearInTwoVenue() Violation
  class[0][0][0].lecturer = &lecturer[0];
  class[3][0][0].lecturer = &lecturer[0];
	
  Population pop1;
	copyClass(class, pop1.class);
	
  secondNumberOfClashes = calculateFitnessScore(class);
	pop1.violation = secondNumberOfClashes;

  setNode(&node1, NULL, NULL, 'b');
	node1.data = &pop1;
  
  addRedBlackTree(&root, &node1);
  setUp();
  
  // checkLecturerNotInchargeOfCourse() Violation
  /**
   *  checkIfTutionOverloadedInSingleDay = 1
   *  checkIfLecturerAppearInTwoVenue = 1
   *  checkStudentViolation = 1
   *  determineViolationForCourseVenueSize = 3
   *  total should be 6
   */
	
 	class[0][0][0].group[0] = &group[5];
  class[0][0][0].group[1] = &group[6]; 
  class[0][0][0].group[2] = &group[1];
	class[0][0][0].group[3] = NULL;
  class[0][0][0].lecturer = &lecturer[0];
	class[0][0][1].group[0] = &group[0];
	class[0][0][1].group[1] = NULL;
  class[0][0][1].lecturer = &lecturer[0];
	class[0][0][2].group[0] = &group[0];
	class[0][0][2].group[1] = NULL;
  class[0][0][2].lecturer = &lecturer[0];
	
	class[3][0][2].group[0] = &group[0];
	class[3][0][2].group[1] = NULL;
  class[3][0][2].lecturer = &lecturer[0];
	class[3][0][3].group[0] = &group[0];
	class[3][0][3].group[1] = NULL;
  class[3][0][3].lecturer = &lecturer[0];
  
	Population pop6;
	copyClass(class, pop6.class);
	
  thirdNumberOfClashes = calculateFitnessScore(class);
	pop6.violation = thirdNumberOfClashes;

  setNode(&node6, NULL, NULL, 'b');
  node6.data = &pop6;
  
  addRedBlackTree(&root, &node6);
  
  TEST_ASSERT_EQUAL_PTR(&node3, root);
  TEST_ASSERT_EQUAL_NODE(&node1, &node6, 'b', &node3);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node1);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node6);
  TEST_ASSERT_EQUAL(3, firstNumberOfClashes);
  TEST_ASSERT_EQUAL(1, secondNumberOfClashes);
  TEST_ASSERT_EQUAL(5, thirdNumberOfClashes);
}

// void test_swapClasses_given_both_the_newClass_should_be_able_to_swap_places(void) {
  // Class newClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS];
  // class[0][0][0].group[0] = &group[0];
  // class[0][0][0].lecturer = &lecturer[0];
  // class[0][0][0].typeOfClass = 'l';
  
  // class[0][0][1].group[0]  = &group[1];
  // class[0][0][1].lecturer = &lecturer[1];
  // class[0][0][1].typeOfClass = 'p';
  
  // swapClasses(&class[0][0][0], &class[0][0][1]);
  // TEST_ASSERT_EQUAL('p', class[0][0][0].typeOfClass);
  // TEST_ASSERT_EQUAL('l', class[0][0][1].typeOfClass);
  // TEST_ASSERT_EQUAL_STRING("A2", class[0][0][0].group[0]->groupName);
  // TEST_ASSERT_EQUAL_STRING("A1", class[0][0][1].group[0]->groupName);
  // TEST_ASSERT_EQUAL_STRING("Chan CK", class[0][0][0].lecturer->lecturerName);
  // TEST_ASSERT_EQUAL_STRING("Poh TV", class[0][0][1].lecturer->lecturerName);
  // TEST_ASSERT_EQUAL_STRING("FASC", class[0][0][0].lecturer->department);
  // TEST_ASSERT_EQUAL_STRING("FASC", class[0][0][1].lecturer->department);
  
// }