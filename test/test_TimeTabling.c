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
  
  for(venue; venue < 4; venue++) {
    for(day; day < MAX_DAY; day++) {
      for(time; time < MAX_TIME_SLOTS; time++) {
				class[venue][day][time].lecturer = NULL;
				class[venue][day][time].course = NULL;
				class[venue][day][time].typeOfClass = 0;
			}
		}
	}
}

void tearDown(void){}

/**************************************************
 *  getCourseName() and getCourseCode() Functions *                                   
 **************************************************/
// void test_getCourseName_should_able_to_get_wat(){

	// Course newCourse[] = { {.courseCode = "MUET123",
                          // .courseName = "English"}
                       // };

	// char *toCheckAnswer = getCourseName(newCourse[0]);
	
	// TEST_ASSERT_EQUAL_STRING(newCourse[0].courseName, toCheckAnswer);

// }

// void test_getCourseName_should_able_to_get_lolno(){

	// Course newCourse[] = { {.courseCode = "MUET123", 
                          // .courseName = "Electronics"},
                         // {.courseCode = "MATH456", 
                          // .courseName = "TDD"}
                       // };
	
  // char *toCheckAnswer = getCourseName(newCourse[1]);
	// TEST_ASSERT_EQUAL_STRING(newCourse[1].courseName, toCheckAnswer);

// }

// void test_getCourseCode_should_able_to_get_MUET123(){

	// Course newCourse[] = {{.courseCode = "MUET123",
                         // .courseName = "DLP"},
                        // {.courseCode = "MATH123", 
                         // .courseName = "Physics"}
                       // };
	
  // char *toCheckAnswer = getCourseCode(newCourse[0]);
	// TEST_ASSERT_EQUAL_STRING(newCourse[0].courseCode, toCheckAnswer);

// }

// void test_getCourseCode_should_able_to_get_MATH(){

	// Course newCourse[] = {{.courseCode = "MUET123", 
                         // .courseName = "Moral"},
                        // {.courseCode = "MATH321", 
                         // .courseName = "Islamic Studies"}
                       // };
	
  // char *toCheckAnswer = getCourseCode(newCourse[1]);
	// TEST_ASSERT_EQUAL_STRING(newCourse[1].courseCode, toCheckAnswer);
// }

/***********************************************************************************
 *  getTotalStudentsInCourse() and getTotalStudentsInCourseofProgramme() functions *
 ***********************************************************************************/
// void test_getTotalStudentsInCourse_given_the_groupSize_should_return_the_number_of_students(void) {
  // int numberOfStudents;
  // Group group = {.groupName = "RMB2",
                 // .groupSize = 30
                // };
               
  // Class newClass = {.group = &group};
  
  // numberOfStudents = getTotalStudentsInCourse(&newClass);
  // TEST_ASSERT_EQUAL(group.groupSize, numberOfStudents);
// }

// void test_getVenueSize_given_the_size_of_venue_should_be_able_to_return_the_size_of_venue(void) {
  // int venueSize;
  // Venue venue = {.sizeOfVenue = 40};
  // Class newClass = {.venue = &venue};
  
  // venueSize = getVenueSize(&newClass);
  // TEST_ASSERT_EQUAL(venue.sizeOfVenue, venueSize);
// }
  
// void test_checkChromosomeIsEmpty_given_an_empty_chromosome_should_return_class000(void) {
 // class[0][0][0].course = NULL;
 // class[0][0][0].lecturer = NULL;
  
  // Class *result;

  // result = checkChromosomeIsEmpty(class);
  // TEST_ASSERT_EQUAL_PTR(&class[0][0][0],result);
// }

// void test_checkChromosomeIsEmpty_given_a_chromosome_that_is_not_empty_should_return_class001(void) {
 // class[0][0][0].course = &course[0];
 // class[0][0][0].lecturer = &lecturer[0];

  // Class *result;

  // result = checkChromosomeIsEmpty(class);
  // TEST_ASSERT_EQUAL_PTR(&class[0][0][1],result);
// }

// void test_checkChromosomeIsEmpty_given_a_chromosome_that_is_not_empty_should_return_class002(void) {
	// class[0][0][0].course = &course[0];
	// class[0][0][0].lecturer = &lecturer[0];
	// class[0][0][1].course = &course[1];
	// class[0][0][1].lecturer = &lecturer[1];
	
  // Class *result;
  // result = checkChromosomeIsEmpty(class);
  // TEST_ASSERT_EQUAL_PTR(&class[0][0][2],result);
// }

// void test_addDetailsIntoChromosome_given_the_details_should_be_able_to_add_into_the_class000(void) {
                                            
  // addDetailsIntoChromosome(class, &course[0], &lecturer[0], 'l');
  
  // TEST_ASSERT_EQUAL_STRING("AAMP2041", class[0][0][0].course->courseCode);
  // TEST_ASSERT_EQUAL_STRING("Mathematics", class[0][0][0].course->courseName);
  // TEST_ASSERT_EQUAL_STRING("RMB2", class[0][0][0].course->programme->programmeName);
  // TEST_ASSERT_EQUAL_STRING("A2", class[0][0][0].course->programme->group->groupName);
  // TEST_ASSERT_EQUAL(2, class[0][0][0].course->hoursOfLecture);
  // TEST_ASSERT_EQUAL(2, class[0][0][0].course->hoursOfPractical);
  // TEST_ASSERT_EQUAL(1, class[0][0][0].course->hoursOfTutorial);
  // TEST_ASSERT_EQUAL(10, class[0][0][0].course->programme->group->groupSize);
  // TEST_ASSERT_EQUAL(20, class[0][0][0].course->sizeOfProgramme);
  // TEST_ASSERT_EQUAL_STRING("Poh TV", class[0][0][0].lecturer->lecturerName);
  // TEST_ASSERT_EQUAL_STRING("FASC", class[0][0][0].lecturer->department);
  // TEST_ASSERT_EQUAL('l', class[0][0][0].typeOfClass);
// }

// void test_addDetailsIntoChromosome_given_the_details_should_be_able_to_add_into_the_class001(void) {

                                            
  // addDetailsIntoChromosome(class, &course[0], &lecturer[0], 'l');
  // addDetailsIntoChromosome(class, &course[1], &lecturer[1], 't');
  
  // TEST_ASSERT_EQUAL_STRING("AAMP2041", class[0][0][0].course->courseCode);
  // TEST_ASSERT_EQUAL_STRING("Mathematics", class[0][0][0].course->courseName);
  // TEST_ASSERT_EQUAL_STRING("RMB2", class[0][0][0].course->programme->programmeName);
  // TEST_ASSERT_EQUAL_STRING("A2", class[0][0][0].course->programme->group->groupName);
  // TEST_ASSERT_EQUAL(2, class[0][0][0].course->hoursOfLecture);
  // TEST_ASSERT_EQUAL(2, class[0][0][0].course->hoursOfPractical);
  // TEST_ASSERT_EQUAL(1, class[0][0][0].course->hoursOfTutorial);
  // TEST_ASSERT_EQUAL(10, class[0][0][0].course->programme->group->groupSize);
  // TEST_ASSERT_EQUAL(20, class[0][0][0].course->sizeOfProgramme);
  // TEST_ASSERT_EQUAL_STRING("Poh TV", class[0][0][0].lecturer->lecturerName);
  // TEST_ASSERT_EQUAL_STRING("FASC", class[0][0][0].lecturer->department);
	// TEST_ASSERT_EQUAL('l', class[0][0][0].typeOfClass);
  
  // TEST_ASSERT_EQUAL_STRING("AAMB2034", class[0][0][1].course->courseCode);
  // TEST_ASSERT_EQUAL_STRING("English", class[0][0][1].course->courseName);
  // TEST_ASSERT_EQUAL_STRING("RMB3", class[0][0][1].course->programme->programmeName);
  // TEST_ASSERT_EQUAL_STRING("A3", class[0][0][1].course->programme->group->groupName);
  // TEST_ASSERT_EQUAL(2, class[0][0][1].course->hoursOfLecture);
  // TEST_ASSERT_EQUAL(1, class[0][0][1].course->hoursOfTutorial);
  // TEST_ASSERT_EQUAL(0, class[0][0][1].course->hoursOfPractical);
  // TEST_ASSERT_EQUAL(13, class[0][0][1].course->programme->group->groupSize);
  // TEST_ASSERT_EQUAL(30, class[0][0][1].course->sizeOfProgramme);
  // TEST_ASSERT_EQUAL_STRING("Chan CK", class[0][0][1].lecturer->lecturerName);
  // TEST_ASSERT_EQUAL_STRING("FASC", class[0][0][1].lecturer->department);
	// TEST_ASSERT_EQUAL('t', class[0][0][1].typeOfClass);
// }

// Perform Mutation Test Codes //
// void test_performMutation_it_should_be_able_to_find_where_is_the_conflict(void) {

// }