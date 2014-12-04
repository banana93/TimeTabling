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

/***********************************************************************************
 *  checkLecturerNotInchargeOfCourse() 
 ***********************************************************************************/
 void test_checkLecturerNotInchargeOfCourse_should_return_0_when_course_incharge(){
	Lecturer newLecturer;
	newLecturer.lecturerName = "Albert";
	newLecturer.courseCodeInCharge[0] = "MPU223";
	newLecturer.courseCodeInCharge[1] = "AAMP2041";
	newLecturer.courseCodeInCharge[2] = NULL;
	class[0][0][0].lecturer = &newLecturer;
	//courseB declared on top
	class[0][0][0].course = &courseB[0]; // course code = "AAMP2041"
	
	TEST_ASSERT_EQUAL(0,checkLecturerNotInchargeOfCourse(class,0,0,0));
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
	class[0][0][0].lecturer = &newLecturer;
	//courseB declared on top
	class[0][0][0].course = &courseB[0];// course code = "AAMP2041"
	
	TEST_ASSERT_EQUAL(1,checkLecturerNotInchargeOfCourse(class,0,0,0));
}

/***********************************************************************************
 *  checkIfTutionOverloadedInSingleDay() 
 ***********************************************************************************/
 void test_checkIfTutionOverloadedInSingleDay_shoud_return_0_for_empty_class(){
		
	TEST_ASSERT_EQUAL(0, checkIfTutionOverloadedInSingleDay(class, 0));
 }

void test_checkIfTutionOverloadedInSingleDay_shoud_return_1_for_exceeding_lecture_on_same_venue(){
		
	addDetailsIntoChromosome(class, &course[1], &lecturer[1], 'l');
	addDetailsIntoChromosome(class, &course[1], &lecturer[1], 'l');
	addDetailsIntoChromosome(class, &course[1], &lecturer[1], 'l');


	TEST_ASSERT_EQUAL(1, checkIfTutionOverloadedInSingleDay(class, 0));
 }
 
void test_checkIfTutionOverloadedInSingleDay_shoud_return_2_for_exceeding_lecture_in_different_venue(){
		
	addDetailsIntoChromosome(class, &course[0], &lecturer[0], 'l');
	addDetailsIntoChromosome(class, &course[0], &lecturer[0], 'l');
	
	//manually insert because wanted to skip in between slots for test purpose
	class[1][0][0].course = &course[0];
	class[1][0][0].lecturer = &lecturer[0];
	class[1][0][0].typeOfClass = 'l';	
	class[1][0][1].course = &course[0];
	class[1][0][1].lecturer = &lecturer[0];
	class[1][0][1].typeOfClass = 'l';


	TEST_ASSERT_EQUAL(2, checkIfTutionOverloadedInSingleDay(class, 0));
}
 
void test_checkIfTutionOverloadedInSingleDay_shoud_return_0_for_not_exceeding_tutorial_hours(){
		
	addDetailsIntoChromosome(class, &course[0], &lecturer[0], 't');
	addDetailsIntoChromosome(class, &course[1], &lecturer[1], 't');
	addDetailsIntoChromosome(class, &course[2], &lecturer[2], 't');
	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 't');


	TEST_ASSERT_EQUAL(0, checkIfTutionOverloadedInSingleDay(class, 0));
 }
 
void test_checkIfTutionOverloadedInSingleDay_shoud_return_1_for_exceeding_tutorial_hours_different_venue(){
		
	addDetailsIntoChromosome(class, &course[0], &lecturer[0], 't');
	
	class[1][0][0].course = &course[0];
	class[1][0][0].lecturer = &lecturer[0];
	class[1][0][0].typeOfClass = 't';	

	TEST_ASSERT_EQUAL(1, checkIfTutionOverloadedInSingleDay(class, 0));
 }
 
 void test_checkIfTutionOverloadedInSingleDay_shoud_return_0_for_not_exceeding_practical_hours(){
		
	addDetailsIntoChromosome(class, &course[0], &lecturer[0], 'p');
	addDetailsIntoChromosome(class, &course[0], &lecturer[0], 'p');


	TEST_ASSERT_EQUAL(0, checkIfTutionOverloadedInSingleDay(class, 0));
 }
 
void test_checkIfTutionOverloadedInSingleDay_shoud_return_2_for_exceeding_practical_hours(){
		
	addDetailsIntoChromosome(class, &course[0], &lecturer[0], 'p');
	addDetailsIntoChromosome(class, &course[0], &lecturer[0], 'p');
	
	class[1][0][0].course = &course[0];
	class[1][0][0].lecturer = &lecturer[0];
	class[1][0][0].typeOfClass = 'p';	
	class[1][0][1].course = &course[0];
	class[1][0][1].lecturer = &lecturer[0];
	class[1][0][1].typeOfClass = 'p';


	TEST_ASSERT_EQUAL(2, checkIfTutionOverloadedInSingleDay(class, 0));
 }
 
void test_checkStudentAndVenueSize_should_return_1_if_the_group_size_is_larger_than_the_venue_size(void) {
  int result;
  
  addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'p');
  result = checkStudentAndVenueSize(class, &venue[0]);
  
  TEST_ASSERT_EQUAL(1, result);
}

void test_checkStudentAndVenueSize_should_return_0_if_the_group_size_is_smaller_than_the_venue_size(void) {
  int result;
  
  addDetailsIntoChromosome(class, &course[0], &lecturer[0], 't');
  result = checkStudentAndVenueSize(class, &venue[0]);
  
  TEST_ASSERT_EQUAL(0, result);
}

/***********************************************************************************
 *  checkIfTutionOverloadedInSingleDay() 
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

	TEST_ASSERT_EQUAL(1,checkIfLecturerAppearInTwoVenue(class,1,1));
}

void test_checkIfLecturerAppearInTwoVenue_shoud_return_1_with_same_lecturer2(){
		
	class[0][1][1].lecturer = &lecturer[0];
	class[1][1][1].lecturer = &lecturer[2];
	class[2][1][1].lecturer = &lecturer[1];
	class[3][1][1].lecturer = &lecturer[0];

	TEST_ASSERT_EQUAL(1,checkIfLecturerAppearInTwoVenue(class,1,1));
}

void test_checkStudentViolation_should_return_1_if_same_programme_same_group_but_appear_at_different_venue(void) {
  Course course[] = {{.courseCode = "AAMP2013",
                      .courseName = "RMB2",
                      .hoursOfLecture = 2,
                      .hoursOfTutorial = 1,
                      .hoursOfPractical = 2,
                      &programme[0],
                      .sizeOfProgramme = 20
                     },
                     {.courseCode = "AAMP2114",
                      .courseName = "RMB3",
                      .hoursOfLecture = 2,
                      .hoursOfTutorial = 1,
                      .hoursOfPractical = 2,
                      &programme[0],
                      .sizeOfProgramme = 10
                    },
                    {.courseCode = "AAMP2015",
                      .courseName = "RMB4",
                      .hoursOfLecture = 2,
                      .hoursOfTutorial = 1,
                      .hoursOfPractical = 2,
                      &programme[0],
                      .sizeOfProgramme = 22
                    },
                    {.courseCode = "AAMP2113",
                      .courseName = "RMB1",
                      .hoursOfLecture = 2,
                      .hoursOfTutorial = 1,
                      .hoursOfPractical = 2,
                      &programme[0],
                      .sizeOfProgramme = 10
                    }
                    };
                    
  class[0][1][1].course = &course[0];
  class[1][1][1].course = &course[1];
  class[2][1][1].course = &course[2];
  class[3][1][1].course = &course[3];
  
  TEST_ASSERT_EQUAL(1, checkStudentViolation(class, 1, 1));
}

void test_checkStudentViolation_should_return_0_if_different_programme_different_group_but_appear_at_different_venue(void) {
  class[0][1][1].course = &course[0];
  class[1][1][1].course = &course[1];
  class[2][1][1].course = &course[2];
  class[3][1][1].course = &course[3];
  
  TEST_ASSERT_EQUAL(0, checkStudentViolation(class, 1, 1));
}