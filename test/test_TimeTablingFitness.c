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

void test_calculateFitnessScore_should_return_2_when_only_violating_TutionOverloadedInSingleDay(){
  addDetailsIntoChromosome(class, &course[0], &lecturer[0], 'l');
  addDetailsIntoChromosome(class, &course[0], &lecturer[0], 'l');

  // extra 2 to violate twice, returns 2  
  addDetailsIntoChromosome(class, &course[0], &lecturer[0], 'l');
  addDetailsIntoChromosome(class, &course[0], &lecturer[0], 'l');

  TEST_ASSERT_EQUAL(2,calculateFitnessScore(class));
}

void test_calculateFitnessScore_should_return_1_when_lecturerAppearInTwoVenue(){
  addDetailsIntoChromosome(class, &course[0], &lecturer[0], 'l');
  class[3][0][0].course = &course[1];
  class[3][0][0].lecturer = &lecturer[0];
  class[3][0][0].typeOfClass = 'l';

  TEST_ASSERT_EQUAL(1,calculateFitnessScore(class));
}

void test_calculateFitnessScore_should_return_1_when_studentAppearInTwoVenue(){
  addDetailsIntoChromosome(class, &course[0], &lecturer[0], 'l');
  class[3][0][0].course = &course[0];
  class[3][0][0].lecturer = &lecturer[1];
  class[3][0][0].typeOfClass = 'l';

  TEST_ASSERT_EQUAL(1,calculateFitnessScore(class));
}

void test_calculateFitnessScore_should_return_1_when_determineViolationForCourseVenueSize_violates(){
	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');

  TEST_ASSERT_EQUAL(1,calculateFitnessScore(class));
}

void test_calculateFitnessScore_should_return_4_when_violates_all_but_TuitionOverload(){	
//checkIfTutionOverloadedInSingleDay = 0
//checkIfLecturerAppearInTwoVenue = 1
//checkStudentViolation = 1
//determineViolationForCourseVenueSize = 2
//total should be 4
	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');
	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');
	addDetailsIntoChromosome(class, &course[2], &lecturer[3], 'l');
	
	class[3][0][2].course = &course[2];
  class[3][0][2].lecturer = &lecturer[3];
  class[3][0][2].typeOfClass = 'l';
	

  TEST_ASSERT_EQUAL(4,calculateFitnessScore(class));
}

void test_calculateFitnessScore_should_return_7_when_violates_all_but_checkIfLecturerAppearInTwoVenue(){
//checkIfTutionOverloadedInSingleDay = 2
//checkIfLecturerAppearInTwoVenue = 0
//checkStudentViolation = 1
//determineViolationForCourseVenueSize = 4
//total should be 7
	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');
	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');
	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');
	
	class[3][0][0].course = &course[3];
  class[3][0][0].lecturer = &lecturer[2];
  class[3][0][0].typeOfClass = 'l';
	

  TEST_ASSERT_EQUAL(7,calculateFitnessScore(class));
}

void test_calculateFitnessScore_should_return_5_when_violates_all_but_checkStudentViolation(){
//checkIfTutionOverloadedInSingleDay = 1
//checkIfLecturerAppearInTwoVenue = 1
//checkStudentViolation = 0
//determineViolationForCourseVenueSize = 3
//total should be 5
	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');
	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');
	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');
	
	class[3][0][0].course = &course[2];
  class[3][0][0].lecturer = &lecturer[3];
  class[3][0][0].typeOfClass = 'l';
	

  TEST_ASSERT_EQUAL(5,calculateFitnessScore(class));
}

void test_calculateFitnessScore_should_return_4_when_violates_all_but_determineViolationForCourseVenueSize(){
//checkIfTutionOverloadedInSingleDay = 2
//checkIfLecturerAppearInTwoVenue = 1
//checkStudentViolation = 1
//determineViolationForCourseVenueSize = 0
//total should be 4
	addDetailsIntoChromosome(class, &course[2], &lecturer[3], 'l');
	addDetailsIntoChromosome(class, &course[2], &lecturer[3], 'l');
	addDetailsIntoChromosome(class, &course[2], &lecturer[3], 'l');
	
	class[3][0][0].course = &course[2];
  class[3][0][0].lecturer = &lecturer[3];
  class[3][0][0].typeOfClass = 'l';
	

  TEST_ASSERT_EQUAL(4,calculateFitnessScore(class));
}

void test_calculateFitnessScore_should_return_8_when_violates_all(){
//checkIfTutionOverloadedInSingleDay = 2
//checkIfLecturerAppearInTwoVenue = 1
//checkStudentViolation = 1
//determineViolationForCourseVenueSize = 4
//total should be 8
	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');
	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');
	addDetailsIntoChromosome(class, &course[3], &lecturer[3], 'l');
	
	class[3][0][0].course = &course[3];
  class[3][0][0].lecturer = &lecturer[3];
  class[3][0][0].typeOfClass = 'l';
	

  TEST_ASSERT_EQUAL(8,calculateFitnessScore(class));
}


