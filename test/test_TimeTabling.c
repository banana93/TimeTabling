#include "unity.h"
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

