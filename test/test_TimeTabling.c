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

void test_checkChromosomeIsEmpty_given_a_chromosome_that_is_not_empty_should_return_class001(void) {
 class[0][0][0].course = &course[0];
 class[0][0][0].lecturer = &lecturer[0];

  Class *result;

  result = checkChromosomeIsEmpty(class);
  TEST_ASSERT_EQUAL_PTR(&class[0][0][1],result);
}

void test_checkChromosomeIsEmpty_given_a_chromosome_that_is_not_empty_should_return_class002(void) {
	class[0][0][0].course = &course[0];
	class[0][0][0].lecturer = &lecturer[0];
	class[0][0][1].course = &course[1];
	class[0][0][1].lecturer = &lecturer[1];
	
  Class *result;
  result = checkChromosomeIsEmpty(class);
  TEST_ASSERT_EQUAL_PTR(&class[0][0][2],result);
}

void test_addDetailsIntoChromosome_given_the_details_should_be_able_to_add_into_the_class000(void) {
                                            
  addDetailsIntoChromosome(class, &course[0], &lecturer[0], &group[0], 'l');
  
  TEST_ASSERT_EQUAL_STRING("AAMP2041", class[0][0][0].course->courseCode);
  TEST_ASSERT_EQUAL_STRING("Mathematics", class[0][0][0].course->courseName);
  TEST_ASSERT_EQUAL_STRING("RMB2", class[0][0][0].course->programme[0]->programmeName);
  TEST_ASSERT_EQUAL_STRING("A1", class[0][0][0].course->programme[0]->group[0]->groupName);
  TEST_ASSERT_EQUAL_STRING("A2", class[0][0][0].course->programme[0]->group[1]->groupName);
  TEST_ASSERT_EQUAL(2, class[0][0][0].course->hoursOfLecture);
  TEST_ASSERT_EQUAL(2, class[0][0][0].course->hoursOfPractical);
  TEST_ASSERT_EQUAL(1, class[0][0][0].course->hoursOfTutorial);
  TEST_ASSERT_EQUAL(12, class[0][0][0].group[0]->groupSize);
  TEST_ASSERT_EQUAL(20, class[0][0][0].course->sizeOfProgramme);
  TEST_ASSERT_EQUAL_STRING("Poh TV", class[0][0][0].lecturer->lecturerName);
  TEST_ASSERT_EQUAL_STRING("FASC", class[0][0][0].lecturer->department);
  TEST_ASSERT_EQUAL('l', class[0][0][0].typeOfClass);
}

void test_addDetailsIntoChromosome_given_the_details_should_be_able_to_add_into_the_class001(void) {

                                            
  addDetailsIntoChromosome(class, &course[0], &lecturer[0], &group[0], 'l');
  addDetailsIntoChromosome(class, &course[1], &lecturer[1], &group[1], 't');
  
  TEST_ASSERT_EQUAL_STRING("AAMP2041", class[0][0][0].course->courseCode);
  TEST_ASSERT_EQUAL_STRING("Mathematics", class[0][0][0].course->courseName);
  TEST_ASSERT_EQUAL_STRING("RMB2", class[0][0][0].course->programme[0]->programmeName);
  TEST_ASSERT_EQUAL_STRING("A1", class[0][0][0].course->programme[0]->group[0]->groupName);
  TEST_ASSERT_EQUAL_STRING("A2", class[0][0][0].course->programme[0]->group[1]->groupName);
  TEST_ASSERT_EQUAL(2, class[0][0][0].course->hoursOfLecture);
  TEST_ASSERT_EQUAL(2, class[0][0][0].course->hoursOfPractical);
  TEST_ASSERT_EQUAL(1, class[0][0][0].course->hoursOfTutorial);
  TEST_ASSERT_EQUAL(12, class[0][0][0].course->programme[0]->group[0]->groupSize);
  TEST_ASSERT_EQUAL(20, class[0][0][0].course->sizeOfProgramme);
  TEST_ASSERT_EQUAL_STRING("Poh TV", class[0][0][0].lecturer->lecturerName);
  TEST_ASSERT_EQUAL_STRING("FASC", class[0][0][0].lecturer->department);
	TEST_ASSERT_EQUAL('l', class[0][0][0].typeOfClass);
  
  TEST_ASSERT_EQUAL_STRING("AAMB2034", class[0][0][1].course->courseCode);
  TEST_ASSERT_EQUAL_STRING("English", class[0][0][1].course->courseName);
  TEST_ASSERT_EQUAL_STRING("RMB3", class[0][0][1].course->programme[0]->programmeName);
  TEST_ASSERT_EQUAL_STRING("B1", class[0][0][1].course->programme[0]->group[0]->groupName);
  TEST_ASSERT_EQUAL_STRING("B2", class[0][0][1].course->programme[0]->group[1]->groupName);
  TEST_ASSERT_EQUAL(2, class[0][0][1].course->hoursOfLecture);
  TEST_ASSERT_EQUAL(1, class[0][0][1].course->hoursOfTutorial);
  TEST_ASSERT_EQUAL(0, class[0][0][1].course->hoursOfPractical);
  TEST_ASSERT_EQUAL(15, class[0][0][1].course->programme[0]->group[0]->groupSize);
  TEST_ASSERT_EQUAL(30, class[0][0][1].course->sizeOfProgramme);
  TEST_ASSERT_EQUAL_STRING("Chan CK", class[0][0][1].lecturer->lecturerName);
  TEST_ASSERT_EQUAL_STRING("FASC", class[0][0][1].lecturer->department);
	TEST_ASSERT_EQUAL('t', class[0][0][1].typeOfClass);
}

void xtest_performMutation_it_should_be_able_to_find_empty_slots(void) {

}

void xtest_performMutation_it_should_be_able_to_calculateFitnessScore_and_genericRedBlackTreeAdd_into_the_redBlackTree(void) {

}

