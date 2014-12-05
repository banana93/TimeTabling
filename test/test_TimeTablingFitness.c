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

void test_calculateFitnessScore(){
	

// calculateFitnessScore(class);
// checkLecturerNotInchargeOfCourse(class, 0, 0, 0);
// checkIfTutionOverloadedInSingleDay(class, 0);
// checkIfLecturerAppearInTwoVenue(class,0,0);
checkStudentViolation(class,0,0);
}