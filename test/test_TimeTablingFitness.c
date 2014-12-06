#include "unity.h"
#include <stdio.h>
#include "TimeTabling.h"
                    
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

void test_calculateFitnessScore_should_return_0_when_empty_class(){
	

TEST_ASSERT_EQUAL(0,calculateFitnessScore(class));

}

void test_calculateFitnessScore_should_return_1_when_only_violating_lecturerNotInCharge(){
	
lecturer[0].courseCodeInCharge[0] = "ABCD1234";
class[0][0][0].course = &course[0];
class[0][0][0].lecturer = &lecturer[0];

TEST_ASSERT_EQUAL(1,calculateFitnessScore(class));

}

void test_calculateFitnessScore_should_return_2_when_only_violating_TutionOverloadedInSingleDay(){
lecturer[0].courseCodeInCharge[0] = "AAMP2041";
lecturer[0].courseCodeInCharge[1] = NULL;
class[0][0][0].course = &course[0];
class[0][0][0].lecturer = &lecturer[0];
class[0][0][0].typeOfClass = 'l';
class[0][0][1].course = &course[0];
class[0][0][1].lecturer = &lecturer[0];
class[0][0][1].typeOfClass = 'l';
//extra 2 to violate twice, returns 2
class[0][0][2].course = &course[0];
class[0][0][2].lecturer = &lecturer[0];
class[0][0][2].typeOfClass = 'l';
class[0][0][3].course = &course[0];
class[0][0][3].lecturer = &lecturer[0];
class[0][0][3].typeOfClass = 'l';

TEST_ASSERT_EQUAL(2,calculateFitnessScore(class));

}

void test_calculateFitnessScore_should_return_1_when_lecturerAppearInTwoVenue(){
lecturer[0].courseCodeInCharge[0] = "AAMP2041";
lecturer[0].courseCodeInCharge[1] = NULL;
class[0][0][0].course = &course[0];
class[0][0][0].lecturer = &lecturer[0];
class[0][0][0].typeOfClass = 'l';
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
class[0][0][0].course = &course[0];
class[0][0][0].lecturer = &lecturer[0];
class[0][0][0].typeOfClass = 'l';
class[3][0][0].course = &course[0];
class[3][0][0].lecturer = &lecturer[1];
class[3][0][0].typeOfClass = 'l';


TEST_ASSERT_EQUAL(1,calculateFitnessScore(class));
}