#include "unity.h"
#include <stdio.h>
#include "TimeTabling.h"

  Course courseB[] = { {.courseCode = "AAMP2041",
                       .courseName = "Mathematics",
                       .hoursOfLecture = 2,
                       .hoursOfTutorial = 1,
                       .hoursOfPractical = 2,
                       // &programme[0],
                       .sizeOfProgramme = 20},
                       
                      {.courseCode = "AAMB2034",
                       .courseName = "English",
                       .hoursOfLecture = 2,
                       .hoursOfTutorial = 1,
                       .hoursOfPractical = 0,
                       // &programme[1],
                       .sizeOfProgramme = 30},
                       
                      {.courseCode = "ABMC1045",
                       .courseName = "History",
                       .hoursOfLecture = 2,
                       .hoursOfTutorial = 1,
                       .hoursOfPractical = 0,
                       // &programme[2],
                       .sizeOfProgramme = 15},
                      
                      {.courseCode = "ABCD1234",
                       .courseName = "Add Maths",
                       .hoursOfLecture = 2,
                       .hoursOfTutorial = 1,
                       .hoursOfPractical = 0,
                       // &programme[3],
                       .sizeOfProgramme = 30}
                    };
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
/***********************************************************************************
 *  checkLecturerNotInchargeOfCourse() 
 ***********************************************************************************/
 void test_checkLecturerNotInchargeOfCourse_should_return_0_when_course_incharge(){
	Class newClass;
	Lecturer newLecturer;
	newLecturer.lecturerName = "Albert";
	newLecturer.courseCodeInCharge[0] = "MPU223";
	newLecturer.courseCodeInCharge[1] = "AAMP2041";
	newLecturer.courseCodeInCharge[2] = NULL;
	newClass.lecturer = &newLecturer;
	//courseB declared on top
	newClass.course = &courseB[0]; // course code = "AAMP2041"
	
	TEST_ASSERT_EQUAL(0,checkLecturerNotInchargeOfCourse(&newClass));
}

 void test_checkLecturerNotInchargeOfCourse_should_return_1_when_course_not_incharge(){
	Class newClass;
	Lecturer newLecturer;
	newLecturer.lecturerName = "Samuel";
	newLecturer.courseCodeInCharge[0] = "MPU223";
	newLecturer.courseCodeInCharge[1] = "ABMC1035";
	newLecturer.courseCodeInCharge[1] = "ABNC1045";
	newLecturer.courseCodeInCharge[1] = "ABXC1045";
	newLecturer.courseCodeInCharge[2] = NULL;
	newClass.lecturer = &newLecturer;
	//courseB declared on top
	newClass.course = &courseB[0];// course code = "AAMP2041"
	
	TEST_ASSERT_EQUAL(1,checkLecturerNotInchargeOfCourse(&newClass));
}

void test_checkLecturerAtDifferentVenue_should_return_1_if_the_lecturer_is_at_different_venue_at_the_same_time(void) {

}