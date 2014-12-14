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