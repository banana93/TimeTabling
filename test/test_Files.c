//	test_TimeTabling .c	//

#include "unity.h"
#include <stdio.h>
#include "TimeTabling.h"
#include "Node.h"
#include "RedBlackTree.h"
#include "ErrorCode.h"
#include "CustomAssertions.h"
#include "Rotations.h"
#include "InitNode.h"
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
				class[venue][day][time].classNode = NULL;
				for(i = 0 ; i < 5 ; i++){
					class[venue][day][time].group[i] = NULL;
				}
			}
		}
	}
}

void tearDown(void){}
void test_indexForward_should_throw_error_when_exceeded_index_inserted(){
	CEXCEPTION_T e;
	int venue = 0, day = 0, time = 6;
	
	Try{
	indexForward(&venue, &day, &time);
	}Catch(e){
		TEST_ASSERT_EQUAL( ERR_EXCEEDED_INDEX, e);
	}
}

void test_indexForward_should_return_0_1_0(){

	int venue = 0, day = 0, time = 4;
	
	indexForward(&venue, &day, &time);
	
	TEST_ASSERT_EQUAL( 0, venue);
	TEST_ASSERT_EQUAL( 1, day);
	TEST_ASSERT_EQUAL( 0, time);
}

void test_indexForward_should_return_1_0_0(){

	int venue = 0, day = 2, time = 4;
	
	indexForward(&venue, &day, &time);
	
	TEST_ASSERT_EQUAL( 1, venue);
	TEST_ASSERT_EQUAL( 0, day);
	TEST_ASSERT_EQUAL( 0, time);
}

void test_indexForward_should_return_0_0_0_for_reset(){

	int venue = 3, day = 2, time = 4;
	
	indexForward(&venue, &day, &time);
	
	TEST_ASSERT_EQUAL( 0, venue);
	TEST_ASSERT_EQUAL( 0, day);
	TEST_ASSERT_EQUAL( 0, time);
}

void test_indexBackward_should_throw_error_when_exceeded_index_inserted(){
	CEXCEPTION_T e;
	int venue = 0, day = 0, time = 18;
	
	Try{
	indexBackward(&venue, &day, &time);
	}Catch(e){
		TEST_ASSERT_EQUAL( ERR_EXCEEDED_INDEX, e);
	}
}

void test_indexBackward_should_return_0_0_2(){
	int venue = 0, day = 0, time = 3;
	
	indexBackward(&venue, &day, &time);
	
	TEST_ASSERT_EQUAL( 0, venue);
	TEST_ASSERT_EQUAL( 0, day);
	TEST_ASSERT_EQUAL( 2, time);
	
}

void test_indexBackward_should_return_1_0_4(){
	int venue = 1, day = 1, time = 0;
	
	indexBackward(&venue, &day, &time);
	
	TEST_ASSERT_EQUAL( 1, venue);
	TEST_ASSERT_EQUAL( 0, day);
	TEST_ASSERT_EQUAL( 4, time);

}

void test_indexBackward_should_return_3_1_4(){
	int venue = 3, day = 2, time = 0;
	
	indexBackward(&venue, &day, &time);
	
	TEST_ASSERT_EQUAL( 3, venue);
	TEST_ASSERT_EQUAL( 1, day);
	TEST_ASSERT_EQUAL( 4, time);

}

void test_checkChromosomeIsEmpty_given_a_chromosome_that_is_not_empty_should_return_class001(void) {
 class[0][0][0].course = &course[0];
 class[0][0][0].lecturer = &lecturer[0];

  Class *result;

  result = checkChromosomeIsEmpty(class);
  TEST_ASSERT_EQUAL_PTR(&class[0][0][1],result);
}

void test_checkChromosomeIsEmpty_given_a_chromosome_that_is_not_empty_should_return_class002(void) {
	class[0][0][0].course = &course[0];
	class[0][0][0].lecturer = &lecturer[0];
	class[0][0][1].course = &course[1];
	class[0][0][1].lecturer = &lecturer[1];
	
  Class *result;
  result = checkChromosomeIsEmpty(class);
  TEST_ASSERT_EQUAL_PTR(&class[0][0][2],result);
}


void test_addDetailsIntoChromosome_given_the_details_should_be_able_to_add_into_the_class000(void) {
                                            
  addDetailsIntoChromosome(class, &course[0], &lecturer[0], &group[0], 'l');
  
  TEST_ASSERT_EQUAL_STRING("AAMP2041", class[0][0][0].course->courseCode);
  TEST_ASSERT_EQUAL_STRING("Mathematics", class[0][0][0].course->courseName);
  TEST_ASSERT_EQUAL_STRING("RMB2", class[0][0][0].course->programme[0]->programmeName);
  TEST_ASSERT_EQUAL_STRING("A1", class[0][0][0].course->programme[0]->group[0]->groupName);
  TEST_ASSERT_EQUAL_STRING("A2", class[0][0][0].course->programme[0]->group[1]->groupName);
  TEST_ASSERT_EQUAL(2, class[0][0][0].course->hoursOfLecture);
  TEST_ASSERT_EQUAL(2, class[0][0][0].course->hoursOfPractical);
  TEST_ASSERT_EQUAL(1, class[0][0][0].course->hoursOfTutorial);
  TEST_ASSERT_EQUAL(12, class[0][0][0].group[0]->groupSize);
  TEST_ASSERT_EQUAL(20, class[0][0][0].course->sizeOfProgramme);
  TEST_ASSERT_EQUAL_STRING("Poh TV", class[0][0][0].lecturer->lecturerName);
  TEST_ASSERT_EQUAL_STRING("FASC", class[0][0][0].lecturer->department);
  TEST_ASSERT_EQUAL('l', class[0][0][0].typeOfClass);
}

void test_addDetailsIntoChromosome_given_the_details_should_be_able_to_add_into_the_class001(void) {

                                            
  addDetailsIntoChromosome(class, &course[0], &lecturer[0], &group[0], 'l');
  addDetailsIntoChromosome(class, &course[1], &lecturer[1], &group[1], 't');
  
  TEST_ASSERT_EQUAL_STRING("AAMP2041", class[0][0][0].course->courseCode);
  TEST_ASSERT_EQUAL_STRING("Mathematics", class[0][0][0].course->courseName);
  TEST_ASSERT_EQUAL_STRING("RMB2", class[0][0][0].course->programme[0]->programmeName);
  TEST_ASSERT_EQUAL_STRING("A1", class[0][0][0].course->programme[0]->group[0]->groupName);
  TEST_ASSERT_EQUAL_STRING("A2", class[0][0][0].course->programme[0]->group[1]->groupName);
  TEST_ASSERT_EQUAL(2, class[0][0][0].course->hoursOfLecture);
  TEST_ASSERT_EQUAL(2, class[0][0][0].course->hoursOfPractical);
  TEST_ASSERT_EQUAL(1, class[0][0][0].course->hoursOfTutorial);
  TEST_ASSERT_EQUAL(12, class[0][0][0].course->programme[0]->group[0]->groupSize);
  TEST_ASSERT_EQUAL(20, class[0][0][0].course->sizeOfProgramme);
  TEST_ASSERT_EQUAL_STRING("Poh TV", class[0][0][0].lecturer->lecturerName);
  TEST_ASSERT_EQUAL_STRING("FASC", class[0][0][0].lecturer->department);
	TEST_ASSERT_EQUAL('l', class[0][0][0].typeOfClass);
  
  TEST_ASSERT_EQUAL_STRING("AAMB2034", class[0][0][1].course->courseCode);
  TEST_ASSERT_EQUAL_STRING("English", class[0][0][1].course->courseName);
  TEST_ASSERT_EQUAL_STRING("RMB3", class[0][0][1].course->programme[0]->programmeName);
  TEST_ASSERT_EQUAL_STRING("B1", class[0][0][1].course->programme[0]->group[0]->groupName);
  TEST_ASSERT_EQUAL_STRING("B2", class[0][0][1].course->programme[0]->group[1]->groupName);
  TEST_ASSERT_EQUAL(2, class[0][0][1].course->hoursOfLecture);
  TEST_ASSERT_EQUAL(1, class[0][0][1].course->hoursOfTutorial);
  TEST_ASSERT_EQUAL(0, class[0][0][1].course->hoursOfPractical);
  TEST_ASSERT_EQUAL(15, class[0][0][1].course->programme[0]->group[0]->groupSize);
  TEST_ASSERT_EQUAL(30, class[0][0][1].course->sizeOfProgramme);
  TEST_ASSERT_EQUAL_STRING("Chan CK", class[0][0][1].lecturer->lecturerName);
  TEST_ASSERT_EQUAL_STRING("FASC", class[0][0][1].lecturer->department);
	TEST_ASSERT_EQUAL('t', class[0][0][1].typeOfClass);
}

void test_performMutation_it_should_be_able_to_calculateFitnessScore_and_genericRedBlackTreeAdd_into_the_redBlackTree(void) {
  int resultOfMutation = 0;
  
  fillInTheChromosomeWithReducingViolation(classList, sizeof(classList)/sizeof(Class));
  resultOfMutation = performMutation(class);
  printf("resultOfMutation: %d\n", resultOfMutation);
}



//	test_TimeTablingConstraints.c	//

#include "unity.h"
#include <stdio.h>
#include "TimeTabling.h"
#include "Node.h"
#include "RedBlackTree.h"
#include "ErrorCode.h"
#include "CustomAssertions.h"
#include "Rotations.h"
#include "InitNode.h"
										
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

/***********************************************************************************
 *  checkIfTutionOverloadedInSingleDay() 
 ***********************************************************************************/
 void test_checkIfTutionOverloadedInSingleDay_shoud_return_0_for_empty_class(){
		
	TEST_ASSERT_EQUAL(0, checkIfTutionOverloadedInSingleDay(class, 0));
 }

void test_checkIfTutionOverloadedInSingleDay_shoud_return_1_for_exceeding_lecture_on_same_day_same_venue(){
		
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


	TEST_ASSERT_EQUAL(1, checkIfTutionOverloadedInSingleDay(class, 0));
 }
 
void test_checkIfTutionOverloadedInSingleDay_shoud_return_2_for_exceeding_lecture_in_different_venue(){
		
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
	class[2][0][4].group[0] = &group[0];
	class[2][0][4].group[1] = NULL;

	TEST_ASSERT_EQUAL(2, checkIfTutionOverloadedInSingleDay(class, 0));
}
 
 void test_checkIfTutionOverloadedInSingleDay_shoud_return_1_for_exceeding_lecture_in_all_different_venue(){
		
	class[0][0][0].group[0] = &group[0];
	class[0][0][0].group[1] = NULL;
	class[1][0][1].group[0] = &group[0];
	class[1][0][1].group[1] = NULL;
	class[2][0][2].group[0] = &group[0];
	class[2][0][2].group[1] = NULL;
	class[3][0][3].group[0] = &group[0];
	class[3][0][3].group[1] = NULL;
	class[3][0][4].group[0] = &group[0];
	class[3][0][4].group[1] = NULL;


	TEST_ASSERT_EQUAL(1, checkIfTutionOverloadedInSingleDay(class, 0));
}

/***********************************************************************************
 *  determineViolationForCourseVenueSize() 
 ***********************************************************************************/
void test_determineViolationForCourseVenueSize_should_return_10_because_the_size_of_group_exceed_the_venue_size(void) {
  int result;
  class[0][0][0].group[0] = &group[0];
	class[0][0][0].group[1] = &group[1];
	class[0][0][0].group[2] = &group[2];
	class[0][0][0].group[3] = &group[3];
	class[0][0][0].group[4] = NULL;
  
  result = determineViolationForCourseVenueSize(class,0,0,0);
  
  TEST_ASSERT_EQUAL(10, result);
}

void test_determineViolationForCourseVenueSize_should_return_0_because_the_size_of_group_did_not_the_venue_size(void) {
  int result;
  
	class[0][0][0].group[0] = &group[2];
	class[0][0][0].group[1] = &group[7];
	class[0][0][0].group[2] = NULL;
	
	result = determineViolationForCourseVenueSize(class,0,0,0);
  
  TEST_ASSERT_EQUAL(0, result);
}

void test_determineViolationForCourseVenueSize_should_return_0_because_no_class(void) {
  int result;
	
	result = determineViolationForCourseVenueSize(class,0,0,0);
  
  TEST_ASSERT_EQUAL(0, result);
}

/***********************************************************************************
 *  checkIfLecturerAppearInTwoVenue() 
 ***********************************************************************************/
void test_checkIfLecturerAppearInTwoVenue_shoud_return_0(){
		
	class[0][0][0].lecturer = &lecturer[0];
	class[1][0][0].lecturer = &lecturer[1];
	class[2][0][0].lecturer = &lecturer[2];

	TEST_ASSERT_EQUAL(0,checkIfLecturerAppearInTwoVenue(class,0,0));
}
 
void test_checkIfLecturerAppearInTwoVenue_shoud_return_0_with_no_same_lecturer(){
		
	class[0][1][1].lecturer = &lecturer[3];
	class[1][1][1].lecturer = &lecturer[2];
	class[2][1][1].lecturer = &lecturer[1];
	class[3][1][1].lecturer = &lecturer[0];

	TEST_ASSERT_EQUAL(0,checkIfLecturerAppearInTwoVenue(class,1,1));
}
 
void test_checkIfLecturerAppearInTwoVenue_shoud_return_1_with_same_lecturer(){
		
	class[0][1][1].lecturer = &lecturer[0];
	class[1][1][1].lecturer = &lecturer[0];
	class[2][1][1].lecturer = &lecturer[0];
	class[3][1][1].lecturer = &lecturer[0];

	TEST_ASSERT_EQUAL(3,checkIfLecturerAppearInTwoVenue(class,1,1));
}

void test_checkIfLecturerAppearInTwoVenue_shoud_return_1_with_same_lecturer2(){
		
	class[0][1][1].lecturer = &lecturer[0];
	class[1][1][1].lecturer = &lecturer[2];
	class[2][1][1].lecturer = &lecturer[1];
	class[3][1][1].lecturer = &lecturer[0];

	TEST_ASSERT_EQUAL(1,checkIfLecturerAppearInTwoVenue(class,1,1));
}

/***********************************************************************************
 *  checkStudentViolation() 
 ***********************************************************************************/
void test_checkStudentViolation_should_return_3_if_same_programme_same_group_but_appear_at_all_different_venue(void) {

  class[0][1][1].group[0] = &group[0];
  class[0][1][1].group[1] = NULL;
  class[1][1][1].group[0] = &group[0];
  class[1][1][1].group[1] = NULL;
	class[2][1][1].group[0] = &group[0];
  class[2][1][1].group[1] = NULL;
	class[3][1][1].group[0] = &group[0];
  class[3][1][1].group[1] = NULL;
  
  TEST_ASSERT_EQUAL(3, checkStudentViolation(class, 1, 1));
}

void test_checkStudentViolation_should_return_0_if_different_programme_different_group_but_appear_at_different_venue(void) {
  class[0][1][1].group[0] = &group[0];
  class[0][1][1].group[1] = NULL;
  class[1][1][1].group[0] = &group[2];
  class[1][1][1].group[1] = NULL;
	class[2][1][1].group[0] = &group[4];
  class[2][1][1].group[1] = NULL;
	class[3][1][1].group[0] = &group[6];
  class[3][1][1].group[1] = NULL;
  
  TEST_ASSERT_EQUAL(0, checkStudentViolation(class, 1, 1));
}


//	test_TimeTablingCrossover .c	//

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
	int i;
  
  for(venue = 0; venue < MAX_VENUE; venue++) {
    for(day = 0; day < MAX_DAY; day++) {
      for(time = 0; time < MAX_TIME_SLOTS; time++) {
				class[venue][day][time].lecturer = NULL;
				class[venue][day][time].course = NULL;
				class[venue][day][time].typeOfClass = 0;
				class[venue][day][time].classNode = NULL;
				for(i = 0 ; i < 5 ; i++){
					class[venue][day][time].group[i] = NULL;
				}
			}
		}
	}
}

void tearDown(void){}

void test_performCrossover(){
	Class topFitness[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS];
	Class topFitness2[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS];
	Class testList[52];
	int topFitnessScore, topFitnessScore2;
	
 clearClassList(sizeof(testList)/sizeof(Class) , &testList);
 randomizeClassList(sizeof(testList)/sizeof(Class),&testList);
 clearClass(topFitness);
 fillInTheChromosomeWithReducingViolation(testList, sizeof(testList)/sizeof(Class));
 copyClass(class, topFitness);
 
 clearClass(class);
 
 clearClassList(sizeof(testList)/sizeof(Class) , &testList);
 randomizeClassList(sizeof(testList)/sizeof(Class),&testList);
 clearClass(topFitness2);
 fillInTheChromosomeWithReducingViolation(testList, sizeof(testList)/sizeof(Class));
 copyClass(class, topFitness2);
 
 topFitnessScore = calculateFitnessScore(topFitness);
 topFitnessScore2 = calculateFitnessScore(topFitness2);

 performCrossover(topFitness,topFitness2);
 
 printf("%d\n",compareClass(topFitness[3][2][3],topFitness2[0][2][0]));
 
}


//	test_TimeTablingFitness .c	//

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
  //lecturerAppearInTwoVenue() Violation
  class[0][0][0].lecturer = &lecturer[0];
  class[3][0][0].lecturer = &lecturer[0];
  
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

  firstNumberOfClashes = calculateFitnessScore(class);
  resetNode(&node3, firstNumberOfClashes);
  class[0][0][0].classNode = &node3;
  setNode(&node3, NULL, NULL, 'b');
  Node *root = NULL;
  
  genericRedBlackTreeAdd(&root, &node3, compare);
  setUp();
  
  // lecturerAppearInTwoVenue() Violation
  class[0][0][0].lecturer = &lecturer[0];
  class[3][0][0].lecturer = &lecturer[0];
  
  secondNumberOfClashes = calculateFitnessScore(class);
  resetNode(&node1, secondNumberOfClashes);
  class[0][0][1].classNode = &node1;
  setNode(&node1, NULL, NULL, 'b');
  root = &node3;
  
  genericRedBlackTreeAdd(&root, &node1, compare);
  TEST_ASSERT_EQUAL_PTR(&node3, root);
  TEST_ASSERT_EQUAL_NODE(&node1, NULL, 'b', &node3);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node1);
  TEST_ASSERT_EQUAL(3, class[0][0][0].classNode->data);
  TEST_ASSERT_EQUAL(1, class[0][0][1].classNode->data);
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

  firstNumberOfClashes = calculateFitnessScore(class);
  resetNode(&node3, firstNumberOfClashes);
  class[0][0][0].classNode = &node3;
  setNode(&node3, NULL, NULL, 'b');
  Node *root = NULL;
  
  genericRedBlackTreeAdd(&root, &node3, compare);
  setUp();
  
  // lecturerAppearInTwoVenue() Violation
  class[0][0][0].lecturer = &lecturer[0];
  class[3][0][0].lecturer = &lecturer[0];
  
  secondNumberOfClashes = calculateFitnessScore(class);
  resetNode(&node1, secondNumberOfClashes);
  class[0][0][1].classNode = &node1;
  setNode(&node1, NULL, NULL, 'b');
  root = &node3;
  
  genericRedBlackTreeAdd(&root, &node1, compare);
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
  
  thirdNumberOfClashes = calculateFitnessScore(class);
  resetNode(&node5, thirdNumberOfClashes);
  class[0][0][2].classNode = &node5;
  setNode(&node5, NULL, NULL, 'b');
  root = &node3;
  
  genericRedBlackTreeAdd(&root, &node5, compare);
  
  TEST_ASSERT_EQUAL_PTR(&node3, root);
  TEST_ASSERT_EQUAL_NODE(&node1, &node5, 'b', &node3);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node1);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node5);
  TEST_ASSERT_EQUAL(3, class[0][0][0].classNode->data);
  TEST_ASSERT_EQUAL(1, class[0][0][1].classNode->data);
  TEST_ASSERT_EQUAL(5, class[0][0][2].classNode->data);
  TEST_ASSERT_EQUAL(3, firstNumberOfClashes);
  TEST_ASSERT_EQUAL(1, secondNumberOfClashes);
  TEST_ASSERT_EQUAL(5, thirdNumberOfClashes);
}

void test_swapClasses_given_both_the_newClass_should_be_able_to_swap_places(void) {
  Class newClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS];
  class[0][0][0].group[0] = &group[0];
  class[0][0][0].lecturer = &lecturer[0];
  class[0][0][0].typeOfClass = 'l';
  
  class[0][0][1].group[0]  = &group[1];
  class[0][0][1].lecturer = &lecturer[1];
  class[0][0][1].typeOfClass = 'p';
  
  swapClasses(&class[0][0][0], &class[0][0][1]);
  TEST_ASSERT_EQUAL('p', class[0][0][0].typeOfClass);
  TEST_ASSERT_EQUAL('l', class[0][0][1].typeOfClass);
  TEST_ASSERT_EQUAL_STRING("A2", class[0][0][0].group[0]->groupName);
  TEST_ASSERT_EQUAL_STRING("A1", class[0][0][1].group[0]->groupName);
  TEST_ASSERT_EQUAL_STRING("Chan CK", class[0][0][0].lecturer->lecturerName);
  TEST_ASSERT_EQUAL_STRING("Poh TV", class[0][0][1].lecturer->lecturerName);
  TEST_ASSERT_EQUAL_STRING("FASC", class[0][0][0].lecturer->department);
  TEST_ASSERT_EQUAL_STRING("FASC", class[0][0][1].lecturer->department);
  
}


//	test_TimeTablingList .c		//
#include "unity.h"
#include <stdio.h>
#include "TimeTabling.h"
#include "Node.h"
#include "RedBlackTree.h"
#include "ErrorCode.h"
#include "CustomAssertions.h"
#include "Rotations.h"
#include "InitNode.h"
#include "CException.h"

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
				class[venue][day][time].classNode = NULL;
				for(i = 0 ; i < 5 ; i++){
					class[venue][day][time].group[i] = NULL;
				}
			}
		}
	}
}

void tearDown(void){}

void test_fillInTheChromosomeWithReducingViolation_should_less_violation_than_normal_fillInTheChromosome(){
	int normalFill, reducedViolationFill;
	
	fillInTheChromosome(classList, sizeof(classList)/sizeof(Class));
	normalFill = calculateFitnessScore(class);
	
	setUp();
	
	fillInTheChromosomeWithReducingViolation(classList, sizeof(classList)/sizeof(Class));
	reducedViolationFill = calculateFitnessScore(class);
	
	//proofed that fillInTheChromosomeWithReducingViolation is better
	TEST_ASSERT_EQUAL(309 , normalFill);
	TEST_ASSERT_EQUAL(171, reducedViolationFill);
}

void test_copyClassSlot_should_able_to_copy_1_class_to_another(){

	Class testClass;
	
	testClass = copyClassSlot(classList[0]);

	TEST_ASSERT_EQUAL_PTR( classList[0].course, testClass.course);
	TEST_ASSERT_EQUAL_PTR( classList[0].lecturer, testClass.lecturer);
	TEST_ASSERT_EQUAL_PTR( classList[0].group[0], testClass.group[0]);
	TEST_ASSERT_EQUAL_PTR( classList[0].group[1], testClass.group[1]);
	TEST_ASSERT_EQUAL_PTR( classList[0].group[2], testClass.group[2]);
	TEST_ASSERT_EQUAL_PTR( classList[0].group[3], testClass.group[3]);
	TEST_ASSERT_EQUAL_PTR( classList[0].group[4], testClass.group[4]);
	TEST_ASSERT_EQUAL( classList[0].typeOfClass, testClass.typeOfClass);
	
}

void test_copyClass_should_able_to_copy_entire_class(){
	fillInTheChromosome(classList, sizeof(classList)/sizeof(Class));
	copyClass(class,populationOfClasses[0].class);
	
	TEST_ASSERT_EQUAL_PTR(class[0][0][0].course, populationOfClasses[0].class[0][0][0].course);
	TEST_ASSERT_EQUAL_PTR(class[0][0][0].lecturer, populationOfClasses[0].class[0][0][0].lecturer);
	TEST_ASSERT_EQUAL(class[0][0][0].typeOfClass, populationOfClasses[0].class[0][0][0].typeOfClass);	
	TEST_ASSERT_EQUAL_PTR(class[1][2][3].course, populationOfClasses[0].class[1][2][3].course);
	TEST_ASSERT_EQUAL_PTR(class[1][2][3].lecturer, populationOfClasses[0].class[1][2][3].lecturer);
	TEST_ASSERT_EQUAL(class[1][2][3].typeOfClass, populationOfClasses[0].class[1][2][3].typeOfClass);
}

void test_clearClassSlot_should_able_to_remove_elements(){

	Class testClass;
	
	testClass = copyClassSlot(classList[0]);
	testClass = clearClassSlot(testClass);
	TEST_ASSERT_EQUAL_PTR( NULL, testClass.course);
	TEST_ASSERT_EQUAL_PTR( NULL, testClass.lecturer);
	TEST_ASSERT_EQUAL_PTR( NULL, testClass.group[0]);
	TEST_ASSERT_EQUAL_PTR( NULL, testClass.group[1]);
	TEST_ASSERT_EQUAL_PTR( NULL, testClass.group[2]);
	TEST_ASSERT_EQUAL_PTR( NULL, testClass.group[3]);
	TEST_ASSERT_EQUAL_PTR( NULL, testClass.group[4]);
	TEST_ASSERT_EQUAL( 0, testClass.typeOfClass);
	
}

void test_clearClass_should_able_to_remove_elements(){
	fillInTheChromosome(classList, sizeof(classList)/sizeof(Class));
	clearClass(class);
	
	TEST_ASSERT_EQUAL_PTR( NULL, class[0][0][0].course);
	TEST_ASSERT_EQUAL_PTR( NULL, class[0][0][0].lecturer);
	TEST_ASSERT_EQUAL_PTR( NULL, class[0][0][0].group[0]);
	TEST_ASSERT_EQUAL_PTR( NULL, class[0][0][0].group[1]);
	TEST_ASSERT_EQUAL_PTR( NULL, class[0][0][0].group[2]);
	TEST_ASSERT_EQUAL_PTR( NULL, class[0][0][0].group[3]);
	TEST_ASSERT_EQUAL_PTR( NULL, class[0][0][0].group[4]);
	TEST_ASSERT_EQUAL( 0, class[0][0][0].typeOfClass);
	
}


void test_randomizeClassList_can_create_newList(){
 Class testList[52];
 clearClassList(sizeof(testList)/sizeof(Class) , &testList);
 randomizeClassList(sizeof(testList)/sizeof(Class),&testList);

TEST_ASSERT_NOT_NULL(testList[0].course );
 

}

void test_createPopulationOfChromosome(){

	createPopulationsOfChromosome(sizeof(classList)/sizeof(Class));
	int venue = 0, day = 0, time = 0, i;
	
	TEST_ASSERT_NOT_NULL(populationOfClasses[0].class[0][0][0].course);
	TEST_ASSERT_NOT_NULL(populationOfClasses[99].class[0][0][0].course);
	TEST_ASSERT_NOT_NULL(populationOfClasses[199].class[0][0][0].course);
	TEST_ASSERT_NOT_NULL(populationOfClasses[299].class[0][0][0].course);
	TEST_ASSERT_NOT_NULL(populationOfClasses[399].class[0][0][0].course);
	TEST_ASSERT_NOT_NULL(populationOfClasses[499].class[0][0][0].course);
}

void test_compareClass_should_return_1_if_all_elements_are_same(){
	Class test = classList[0];
	Class test1 = classList[0];

	TEST_ASSERT_EQUAL(1, compareClass(test,test1));
}

void test_compareClass_should_return_0_if_one_elements_not_same(){
	Class test = classList[0];
	Class test1 = classList[0];
	test1.lecturer = &lecturer[2];

	TEST_ASSERT_EQUAL(0, compareClass(test,test1));
}


