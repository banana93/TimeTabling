#include "unity.h"
#include <stdio.h>
#include "TimeTabling.h"

void setUp(void){}
void tearDown(void){}

/***********************************************************************************
 *  checkCourseHoursClash() 
 ***********************************************************************************/
void test_checkCourseHoursClash_should_return_1_with_exceeding_hours_of_lecture(){
	Class newClass;
	Course courseA;
	courseA.hoursOfLecture = 5;
	courseA.hoursOfTutorial = 0;
	courseA.hoursOfPractical = 0;
	newClass.course = &courseA;
	
	int returnValue = 0;
	returnValue = checkCourseHoursClash(&newClass);
	TEST_ASSERT_EQUAL( 1 , returnValue);
 }
 
void test_checkCourseHoursClash_should_return_1_with_exceeding_hours_of_tutorial(){
	Class newClass;
	Course courseA;
	courseA.hoursOfLecture = 0;
	courseA.hoursOfTutorial = 3;
	courseA.hoursOfPractical = 0;
	newClass.course = &courseA;
	
	int returnValue = 0;
	returnValue = checkCourseHoursClash(&newClass);
	TEST_ASSERT_EQUAL( 1 , returnValue);
 }
 
 void test_checkCourseHoursClash_should_return_1_with_more_than_1_type_of_class(){
	Class newClass;
	Course courseA;
	courseA.hoursOfLecture = 0;
	courseA.hoursOfTutorial = 1;
	courseA.hoursOfPractical = 1;
	newClass.course = &courseA;
	
	int returnValue = 0;
	returnValue = checkCourseHoursClash(&newClass);
	TEST_ASSERT_EQUAL( 1 , returnValue);
}
