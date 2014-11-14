#include "unity.h"
#include "TimeTabling.h"

void setUp(void){}

void tearDown(void){}

void test_getCourseName_should_able_to_get_wat(){

	Course newCourse[] = { {.courseCode = "MUET123",
                          .courseName = "wat"}
                       };

	char *toCheckAnswer = getCourseName(newCourse[0]);
	
	TEST_ASSERT_EQUAL_STRING(newCourse[0].courseName, toCheckAnswer);

}

void test_getCourseName_should_able_to_get_lolno(){

	Course newCourse[] = { {.courseCode = "MUET123", 
                          .courseName = "wat"},
                         {.courseCode = "MATH", 
                          .courseName = "lolno"}
                       };
	
  char *toCheckAnswer = getCourseName(newCourse[1]);
	TEST_ASSERT_EQUAL_STRING(newCourse[1].courseName, toCheckAnswer);

}

void test_getCourseCode_should_able_to_get_MUET123(){

	Course newCourse[] = {{.courseCode = "MUET123",
                         .courseName = "wat"},
                        {.courseCode = "MATH", 
                         .courseName = "lolno"}
                       };
	
  char *toCheckAnswer = getCourseCode(newCourse[0]);
	TEST_ASSERT_EQUAL_STRING(newCourse[0].courseCode, toCheckAnswer);

}

void test_getCourseCode_should_able_to_get_MATH(){

	Course newCourse[] = {{.courseCode = "MUET123", 
                         .courseName = "wat"},
                        {.courseCode = "MATH", 
                         .courseName = "lolno"}
                       };
	
  char *toCheckAnswer = getCourseCode(newCourse[1]);
	TEST_ASSERT_EQUAL_STRING(newCourse[1].courseCode, toCheckAnswer);
}