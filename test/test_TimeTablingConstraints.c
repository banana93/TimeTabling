#include "unity.h"
#include <stdio.h>
#include "TimeTabling.h"
  Class class[4][MAX_DAY][MAX_TIME_SLOTS];
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
 *  checkCourseHoursClash() 
 ***********************************************************************************/
void test_checkCourseHoursClash_should_return_1_with_exceeding_hours_of_lecture(){
	Class newClass;
	Course courseA;
	courseA.hoursOfLecture = 5;
	courseA.hoursOfTutorial = 0;
	courseA.hoursOfPractical = 0;
	newClass.course = &courseA;
	
	int returnValue = 0;
	returnValue = checkCourseHoursClash(&newClass);
	TEST_ASSERT_EQUAL( 1 , returnValue);
 }
 
void test_checkCourseHoursClash_should_return_1_with_exceeding_hours_of_tutorial(){
	Class newClass;
	Course courseA;
	courseA.hoursOfLecture = 0;
	courseA.hoursOfTutorial = 3;
	courseA.hoursOfPractical = 0;
	newClass.course = &courseA;
	
	int returnValue = 0;
	returnValue = checkCourseHoursClash(&newClass);
	TEST_ASSERT_EQUAL( 1 , returnValue);
 }
 
 void test_checkCourseHoursClash_should_return_1_with_more_than_1_type_of_class(){
	Class newClass;
	Course courseA;
	courseA.hoursOfLecture = 0;
	courseA.hoursOfTutorial = 1;
	courseA.hoursOfPractical = 1;
	newClass.course = &courseA;
	
	int returnValue = 0;
	returnValue = checkCourseHoursClash(&newClass);
	TEST_ASSERT_EQUAL( 1 , returnValue);
}
/***********************************************************************************
 *  checkLecturerNotInchargeOfCourse() 
 ***********************************************************************************/
 void test_checkLecturerNotInchargeOfCourse_should_return_0_when_course_incharge(){
	Class newClass;
	Lecturer newLecturer;
	newLecturer.lecturerName = "Albert";
	newLecturer.courseCodeInCharge[0] = "MPU223";
	newLecturer.courseCodeInCharge[1] = "AAMP2041";
	newLecturer.courseCodeInCharge[2] = NULL;
	newClass.lecturer = &newLecturer;
	//courseB declared on top
	newClass.course = &courseB[0]; // course code = "AAMP2041"
	
	TEST_ASSERT_EQUAL(0,checkLecturerNotInchargeOfCourse(&newClass));
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
	newClass.lecturer = &newLecturer;
	//courseB declared on top
	newClass.course = &courseB[0];// course code = "AAMP2041"
	
	TEST_ASSERT_EQUAL(1,checkLecturerNotInchargeOfCourse(&newClass));
}

/***********************************************************************************
 *  checkIfLecturesOverloaded() 
 ***********************************************************************************/
 void test_checkIfLecturesOverloaded_(){
		
	addDetailsIntoChromosome(class, &course[0], &lecturer[0], 'l');
	addDetailsIntoChromosome(class, &course[1], &lecturer[1], 'l');
	addDetailsIntoChromosome(class, &course[1], &lecturer[1], 'l');

	TEST_ASSERT_EQUAL(0, checkIfLecturesOverloaded(class));
 }