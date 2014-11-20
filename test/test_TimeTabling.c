#include "unity.h"
#include <stdio.h>
#include "TimeTabling.h"

void setUp(void){}

void tearDown(void){}

/**************************************************
 *  getCourseName() and getCourseCode() Functions *                                   
 **************************************************/
void test_getCourseName_should_able_to_get_wat(){

	Course newCourse[] = { {.courseCode = "MUET123",
                          .courseName = "English"}
                       };

	char *toCheckAnswer = getCourseName(newCourse[0]);
	
	TEST_ASSERT_EQUAL_STRING(newCourse[0].courseName, toCheckAnswer);

}

void test_getCourseName_should_able_to_get_lolno(){

	Course newCourse[] = { {.courseCode = "MUET123", 
                          .courseName = "Electronics"},
                         {.courseCode = "MATH456", 
                          .courseName = "TDD"}
                       };
	
  char *toCheckAnswer = getCourseName(newCourse[1]);
	TEST_ASSERT_EQUAL_STRING(newCourse[1].courseName, toCheckAnswer);

}

void test_getCourseCode_should_able_to_get_MUET123(){

	Course newCourse[] = {{.courseCode = "MUET123",
                         .courseName = "DLP"},
                        {.courseCode = "MATH123", 
                         .courseName = "Physics"}
                       };
	
  char *toCheckAnswer = getCourseCode(newCourse[0]);
	TEST_ASSERT_EQUAL_STRING(newCourse[0].courseCode, toCheckAnswer);

}

void test_getCourseCode_should_able_to_get_MATH(){

	Course newCourse[] = {{.courseCode = "MUET123", 
                         .courseName = "Moral"},
                        {.courseCode = "MATH321", 
                         .courseName = "Islamic Studies"}
                       };
	
  char *toCheckAnswer = getCourseCode(newCourse[1]);
	TEST_ASSERT_EQUAL_STRING(newCourse[1].courseCode, toCheckAnswer);
}

/***********************************************************************************
 *  getTotalStudentsInCourse() and getTotalStudentsInCourseofProgramme() functions *
 ***********************************************************************************/
void test_getTotalStudentsInCourse_given_the_groupSize_should_return_the_number_of_students(void) {
  int numberOfStudents;
  Group group = {.groupName = "RMB2",
                 .groupSize = 40
                };
  
  numberOfStudents = getTotalStudentsInCourse(group);
  TEST_ASSERT_EQUAL(group.groupSize, numberOfStudents);
}

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

void test_addDetailsIntoChromosome_given_a_set_of_Class_details_should_be_able_to_add_things_into_the_chromosome(void) {
  Group group = {.groupName = "K2",
                 .groupSize = 40};
                 
  Programme programme = {.programmeName = "RMB2",
                          &group};
                        
  Course course = {.courseCode = "AAMP2042",
                   .courseName = "Test Driven Development",
                   .hoursOfLecture = 2,
                   .hoursOfTutorial = 1,
                   .hoursOfPractical = 2,
                   &programme,
                   .sizeOfProgramme = 40};
  
  Lecturer lecturer = {.lecturerName = "Poh TV",
                       .department = "FASC"};
                      
  Venue venue = {.nameOfVenue = "D203",
                 .sizeOfVenue = 40};
  
  Class class = {&programme,
                 &course,
                 &lecturer,
                 &group,
                 &venue};
              
  
}
