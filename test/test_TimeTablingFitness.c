#include "unity.h"
#include <stdio.h>
#include "TimeTabling.h"
                    
void setUp(void){
	int venue = 0;
  int day = 0, time = 0;
  
  for(venue = 0 ; venue < MAX_VENUE; venue++) {
    for(day = 0; day < MAX_DAY; day++) {
      for(time = 0; time < MAX_TIME_SLOTS; time++) {
				class[venue][day][time].lecturer = NULL;
				class[venue][day][time].course = NULL;
				class[venue][day][time].typeOfClass = 0;
			}
		}
	}
}

void tearDown(void){}

void test_calculateFitnessScore_should_return_0_when_empty_class(){
	TEST_ASSERT_EQUAL(0,calculateFitnessScore(class));
}

void test_calculateFitnessScore_should_return_1_when_only_violating_lecturerNotInCharge(){
	
  lecturer[0].courseCodeInCharge[0] = "ABCD1234";
  addDetailsIntoChromosome(class, &course[0], &lecturer[0], 'l');

  TEST_ASSERT_EQUAL(1,calculateFitnessScore(class));
}

void test_calculateFitnessScore_should_return_2_when_only_violating_TutionOverloadedInSingleDay(){
  lecturer[0].courseCodeInCharge[0] = "AAMP2041";
  lecturer[0].courseCodeInCharge[1] = NULL;

  addDetailsIntoChromosome(class, &course[0], &lecturer[0], 'l');
  addDetailsIntoChromosome(class, &course[0], &lecturer[0], 'l');

  // extra 2 to violate twice, returns 2  
  addDetailsIntoChromosome(class, &course[0], &lecturer[0], 'l');
  addDetailsIntoChromosome(class, &course[0], &lecturer[0], 'l');

  TEST_ASSERT_EQUAL(2,calculateFitnessScore(class));
}

void test_calculateFitnessScore_should_return_1_when_lecturerAppearInTwoVenue(){
  lecturer[0].courseCodeInCharge[0] = "AAMP2041";
  lecturer[0].courseCodeInCharge[1] = "AAMB2034";
  lecturer[0].courseCodeInCharge[2] = NULL;

  addDetailsIntoChromosome(class, &course[0], &lecturer[0], 'l');
  class[3][0][0].course = &course[1];
  class[3][0][0].lecturer = &lecturer[0];
  class[3][0][0].typeOfClass = 'l';

  TEST_ASSERT_EQUAL(1,calculateFitnessScore(class));
}

void test_calculateFitnessScore_should_return_1_when_studentAppearInTwoVenue(){
  lecturer[0].courseCodeInCharge[0] = "AAMP2041";
  lecturer[0].courseCodeInCharge[1] = NULL;
  lecturer[1].courseCodeInCharge[0] = "AAMP2041";
  lecturer[1].courseCodeInCharge[1] = NULL;

  addDetailsIntoChromosome(class, &course[0], &lecturer[0], 'l');
  class[3][0][0].course = &course[0];
  class[3][0][0].lecturer = &lecturer[1];
  class[3][0][0].typeOfClass = 'l';

  TEST_ASSERT_EQUAL(1,calculateFitnessScore(class));
}

void test_calculateFitnessScore_should_return_1_when_determineViolationForCourseVenueSize_violates(){
  lecturer[3].courseCodeInCharge[0] = "ABCD1234";
  lecturer[3].courseCodeInCharge[1] = NULL;
	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');

  TEST_ASSERT_EQUAL(1,calculateFitnessScore(class));
}

void test_calculateFitnessScore_should_return_8_when_violates_all_but_TuitionOverload(){
  lecturer[0].courseCodeInCharge[0] = NULL; // to remove value declared on top
  lecturer[1].courseCodeInCharge[0] = NULL; // to remove value declared on top
  lecturer[2].courseCodeInCharge[0] = NULL; // to remove value declared on top
  lecturer[3].courseCodeInCharge[0] = NULL; // to remove value declared on top
	
//checkIfTutionOverloadedInSingleDay = 0
//checkLecturerNotInchargeOfCourse = 4
//checkIfLecturerAppearInTwoVenue = 1
//checkStudentViolation = 1
//determineViolationForCourseVenueSize = 2
//total should be 8
	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');
	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');
	addDetailsIntoChromosome(class, &course[2], &lecturer[3], 'l');
	
	class[3][0][2].course = &course[2];
  class[3][0][2].lecturer = &lecturer[3];
  class[3][0][2].typeOfClass = 'l';
	

  TEST_ASSERT_EQUAL(8,calculateFitnessScore(class));
}

void test_calculateFitnessScore_should_return_8_when_violates_all_but_checkLecturerNotInchargeOfCourse(){
  lecturer[0].courseCodeInCharge[0] = NULL; // to remove value declared on top
  lecturer[1].courseCodeInCharge[0] = NULL; // to remove value declared on top
  lecturer[2].courseCodeInCharge[0] = NULL; // to remove value declared on top
  lecturer[3].courseCodeInCharge[0] = "ABCD1234"; 
  lecturer[3].courseCodeInCharge[1] = NULL; 
	
//checkIfTutionOverloadedInSingleDay = 2
//checkLecturerNotInchargeOfCourse = 0
//checkIfLecturerAppearInTwoVenue = 1
//checkStudentViolation = 1
//determineViolationForCourseVenueSize = 4
//total should be 8
	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');
	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');
	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');
	
	class[3][0][2].course = &course[3];
  class[3][0][2].lecturer = &lecturer[3];
  class[3][0][2].typeOfClass = 'l';
	

  TEST_ASSERT_EQUAL(8,calculateFitnessScore(class));
}

void test_calculateFitnessScore_should_return_11_when_violates_all_but_checkIfLecturerAppearInTwoVenue(){
  lecturer[0].courseCodeInCharge[0] = NULL; // to remove value declared on top
  lecturer[1].courseCodeInCharge[0] = NULL; // to remove value declared on top
  lecturer[2].courseCodeInCharge[0] = NULL; // to remove value declared on top
  lecturer[3].courseCodeInCharge[0] = NULL; // to remove value declared on top
//checkIfTutionOverloadedInSingleDay = 2
//checkLecturerNotInchargeOfCourse = 4
//checkIfLecturerAppearInTwoVenue = 0
//checkStudentViolation = 1
//determineViolationForCourseVenueSize = 4
//total should be 11
	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');
	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');
	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');
	
	class[3][0][0].course = &course[3];
  class[3][0][0].lecturer = &lecturer[2];
  class[3][0][0].typeOfClass = 'l';
	

  TEST_ASSERT_EQUAL(11,calculateFitnessScore(class));
}

void test_calculateFitnessScore_should_return_9_when_violates_all_but_checkStudentViolation(){
  lecturer[0].courseCodeInCharge[0] = NULL; // to remove value declared on top
  lecturer[1].courseCodeInCharge[0] = NULL; // to remove value declared on top
  lecturer[2].courseCodeInCharge[0] = NULL; // to remove value declared on top
  lecturer[3].courseCodeInCharge[0] = NULL; // to remove value declared on top
//checkIfTutionOverloadedInSingleDay = 1
//checkLecturerNotInchargeOfCourse = 4
//checkIfLecturerAppearInTwoVenue = 1
//checkStudentViolation = 0
//determineViolationForCourseVenueSize = 3
//total should be 9
	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');
	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');
	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');
	
	class[3][0][0].course = &course[2];
  class[3][0][0].lecturer = &lecturer[3];
  class[3][0][0].typeOfClass = 'l';
	

  TEST_ASSERT_EQUAL(9,calculateFitnessScore(class));
}

void test_calculateFitnessScore_should_return_8_when_violates_all_but_determineViolationForCourseVenueSize(){
  lecturer[0].courseCodeInCharge[0] = NULL; // to remove value declared on top
  lecturer[1].courseCodeInCharge[0] = NULL; // to remove value declared on top
  lecturer[2].courseCodeInCharge[0] = NULL; // to remove value declared on top
  lecturer[3].courseCodeInCharge[0] = NULL; // to remove value declared on top
//checkIfTutionOverloadedInSingleDay = 2
//checkLecturerNotInchargeOfCourse = 4
//checkIfLecturerAppearInTwoVenue = 1
//checkStudentViolation = 1
//determineViolationForCourseVenueSize = 0
//total should be 8
	addDetailsIntoChromosome(class, &course[2], &lecturer[3], 'l');
	addDetailsIntoChromosome(class, &course[2], &lecturer[3], 'l');
	addDetailsIntoChromosome(class, &course[2], &lecturer[3], 'l');
	
	class[3][0][0].course = &course[2];
  class[3][0][0].lecturer = &lecturer[3];
  class[3][0][0].typeOfClass = 'l';
	

  TEST_ASSERT_EQUAL(8,calculateFitnessScore(class));
}

void test_calculateFitnessScore_should_return_12_when_violates_all(){
  lecturer[0].courseCodeInCharge[0] = NULL; // to remove value declared on top
  lecturer[1].courseCodeInCharge[0] = NULL; // to remove value declared on top
  lecturer[2].courseCodeInCharge[0] = NULL; // to remove value declared on top
  lecturer[3].courseCodeInCharge[0] = NULL; // to remove value declared on top
//checkIfTutionOverloadedInSingleDay = 2
//checkLecturerNotInchargeOfCourse = 4
//checkIfLecturerAppearInTwoVenue = 1
//checkStudentViolation = 1
//determineViolationForCourseVenueSize = 4
//total should be 12
	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');
	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');
	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');
	
	class[3][0][0].course = &course[3];
  class[3][0][0].lecturer = &lecturer[3];
  class[3][0][0].typeOfClass = 'l';
	

  TEST_ASSERT_EQUAL(12,calculateFitnessScore(class));
}


