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
                 .groupSize = 30
                };
               
  Class newClass = {.group = &group};
  
  numberOfStudents = getTotalStudentsInCourse(&newClass);
  TEST_ASSERT_EQUAL(group.groupSize, numberOfStudents);
}

void test_getVenueSize_given_the_size_of_venue_should_be_able_to_return_the_size_of_venue(void) {
  int venueSize;
  Venue venue = {.sizeOfVenue = 40};
  Class newClass = {.venue = &venue};
  
  venueSize = getVenueSize(&newClass);
  TEST_ASSERT_EQUAL(venue.sizeOfVenue, venueSize);
}
  
  
  

// void test_addDetailsIntoChromosome_given_a_set_of_Class_details_should_be_able_to_add_things_into_the_chromosome(void) {
  // Group group = {.groupName = "K2",
                 // .groupSize = 40};
                 
  // Programme programme = {.programmeName = "RMB2",
                          // &group};
                        
  // Course course = {.courseCode = "AAMP2042",
                   // .courseName = "Test Driven Development",
                   // .hoursOfLecture = 2,
                   // .hoursOfTutorial = 1,
                   // .hoursOfPractical = 2,
                   // &programme,
                   // .sizeOfProgramme = 40};
  
  // Lecturer lecturer = {.lecturerName = "Poh TV",
                       // .department = "FASC"};
                      
  // Venue venue = {.nameOfVenue = "D203",
                 // .sizeOfVenue = 40};
  
  // Class class = {&programme,
                 // &course,
                 // &lecturer,
                 // &group,
                 // &venue};
              
  // Class Chromosome[2][7][8] = 
// }
