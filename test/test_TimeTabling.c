#include "unity.h"
#include <stdio.h>
#include "TimeTabling.h"

  Group group[] = { {.groupName = "A2",
                     .groupSize = 10},
                     
                    {.groupName = "A3",
                     .groupSize = 13},
                     
                    {.groupName = "K2",
                     .groupSize = 20},
                     
                    {.groupName = "K3",
                     .groupSize = 19}
                  };
                 
  Venue venue[] = { {.nameOfVenue = "D203",
                     .sizeOfVenue = 40},
                     
                    {.nameOfVenue = "D300",
                     .sizeOfVenue = 25},
                     
                    {.nameOfVenue = "D204",
                     .sizeOfVenue = 30},
                     
                    {.nameOfVenue = "D301",
                     .sizeOfVenue = 25}
                  };
                  
  Lecturer lecturer[] = { {.lecturerName = "Poh TV",
                           .department = "FASC"},
                           
                          {.lecturerName = "Chan CK",
                           .department = "FASC"},
                          
                          {.lecturerName = "Chiu VT",
                           .department = "TR"},
                           
                          {.lecturerName = "Jackson Teh",
                           .department = "HSSchool"}
                        };
                        
  Programme programme[] = { {.programmeName = "RMB2",
                             &group[0]},
                            
                            {.programmeName = "RMB3",
                             &group[1]},
                             
                            {.programmeName = "RMM2",
                             &group[2]},
                             
                            {.programmeName = "RMM3",
                             &group[3]}
                          };
                      
  Course course[] = { {.courseCode = "AAMP2041",
                       .courseName = "Mathematics",
                       .hoursOfLecture = 2,
                       .hoursOfTutorial = 1,
                       .hoursOfPractical = 2,
                       &programme[0],
                       .sizeOfProgramme = 20},
                       
                      {.courseCode = "AAMB2034",
                       .courseName = "English",
                       .hoursOfLecture = 2,
                       .hoursOfTutorial = 1,
                       .hoursOfPractical = 0,
                       &programme[1],
                       .sizeOfProgramme = 30},
                       
                      {.courseCode = "ABMC1045",
                       .courseName = "History",
                       .hoursOfLecture = 2,
                       .hoursOfTutorial = 1,
                       .hoursOfPractical = 0,
                       &programme[2],
                       .sizeOfProgramme = 15},
                      
                      {.courseCode = "ABCD1234",
                       .courseName = "Add Maths",
                       .hoursOfLecture = 2,
                       .hoursOfTutorial = 1,
                       .hoursOfPractical = 0,
                       &programme[4],
                       .sizeOfProgramme = 30}
                    };
                    
void setUp(void){}

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
  
void test_checkChromosomeIsEmpty_given_an_empty_chromosome_should_return_class000(void) {
  Class class[4][MAX_DAY][MAX_TIME_SLOTS] = {NULL, NULL};
  
  Class *result;

  result = checkChromosomeIsEmpty(class);
  TEST_ASSERT_EQUAL_PTR(&class[0][0][0],result);
}

void test_checkChromosomeIsEmpty_given_a_chromosome_that_is_not_empty_should_return_class001(void) {
  Class class[4][MAX_DAY][MAX_TIME_SLOTS] = {&course[0], 
                                             &lecturer[0]};
  Class *result;

  result = checkChromosomeIsEmpty(class);
  TEST_ASSERT_EQUAL_PTR(&class[0][0][1],result);
}

void test_checkChromosomeIsEmpty_given_a_chromosome_that_is_not_empty_should_return_class002(void) {
  Class class[4][MAX_DAY][MAX_TIME_SLOTS] = {&course[0], &lecturer[0]};

  //help help directly declare top, i did, but dont know why cannot, lol
	class[0][0][1].course = &course[1];
	class[0][0][1].lecturer = &lecturer[1];
	
  Class *result;
  result = checkChromosomeIsEmpty(class);
  TEST_ASSERT_EQUAL_PTR(&class[0][0][2],result);
}

// void test_addDetailsIntoChromosome_given_the_details_should_be_able_to_add_into_the_chromosome(void) {
  // Class class[4][MAX_DAY][MAX_TIME_SLOTS];
                                            
  // addDetailsIntoChromosome(class, &programme[0], &group[0], &course[0], &lecturer[0], &venue[0]);
  
  // TEST_ASSERT_EQUAL_STRING("AAMP2041", class[0][0][0].course[0].courseCode);
  // TEST_ASSERT_EQUAL_STRING("Mathematics", class[0][0][0].course[0].courseName);
  // TEST_ASSERT_EQUAL(2, class[0][0][0].course[0].hoursOfLecture);
  // TEST_ASSERT_EQUAL(2, class[0][0][0].course[0].hoursOfPractical);
  // TEST_ASSERT_EQUAL(1, class[0][0][0].course[0].hoursOfTutorial);
  // TEST_ASSERT_EQUAL_STRING("RMB2", class[0][0][0].course[0].programme[0].programmeName);
  // TEST_ASSERT_EQUAL_STRING("A2", class[0][0][0].course[0].programme[0].group[0].groupName);
  // TEST_ASSERT_EQUAL(10, class[0][0][0].course[0].programme[0].group[0].groupSize);
  // TEST_ASSERT_EQUAL(20, class[0][0][0].course[0].sizeOfProgramme);
  // TEST_ASSERT_EQUAL_STRING("Poh TV", class[0][0][0].lecturer[0].lecturerName);
  // TEST_ASSERT_EQUAL_STRING("FASC", class[0][0][0].lecturer[0].department);
// }