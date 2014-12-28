#include "unity.h"
#include <stdio.h>
#include "TimeTabling.h"
#include "ErrorCode.h"

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
