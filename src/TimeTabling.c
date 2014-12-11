#include <stdio.h>
#include "TimeTabling.h"
#include "Node.h"
#include "RedBlackTree.h"
#include "ErrorCode.h"
#include "CustomAssertions.h"
#include "Rotations.h"
#include "InitNode.h"

Class class[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS];
	
  Group group[] = { {.groupName = "A2",
                     .groupSize = 10},
                     
                    {.groupName = "A3",
                     .groupSize = 13},
                     
                    {.groupName = "K2",
                     .groupSize = 20},
                     
                    {.groupName = "K3",
                     .groupSize = 50},
                    
                    {.groupName = "B2",
                     .groupSize = 34},
                     
                    {.groupName = "B3",
                     .groupSize = 25},
                     
                    {.groupName = "C2",
                     .groupSize = 14},
                    
                    {.groupName = "D2",
                     .groupSize = 20},
                     
                    {.groupName = "E2",
                     .groupSize = 13},
                     
                    {.groupName = "E3",
                     .groupSize = 16}
                    
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
                           
                          {.lecturerName = "Jackson TKS",
                           .department = "HSSchool"},
                          
                          {.lecturerName = "Cheah SL",
                           .department = "FABS"},
                          
                          {.lecturerName = "Wong YY",
                           .department = "FBUS"},
                          
                          {.lecturerName = "Wong KH",
                           .department = "Char Kuey Teow"},
                           
                          {.lecturerName = "VT Chiu",
                           .department = "Gay School"},
                           
                          {.lecturerName = "Low TH",
                           .department = "SH"},
                           
                          {.lecturerName = "Lai JY",
                           .department = "FHGU"}
                        };
                        
  Programme programme[] = { {.programmeName = "RMB2",
                             &group[0]},
                            
                            {.programmeName = "RMB3",
                             &group[1]},
                             
                            {.programmeName = "RMM2",
                             &group[2]},
                             
                            {.programmeName = "RMM3",
                             &group[3]},
                            
                            {.programmeName = "RMS2",
                             &group[4]},
                            
                            {.programmeName = "RMS3",
                             &group[5]},
                            
                            {.programmeName = "RMT2",
                             &group[6]},
                            
                            {.programmeName = "RMT3",
                             &group[7]},
                            
                            {.programmeName = "RMA2",
                             &group[8]},
                            
                            {.programmeName = "RMA3",
                             &group[9]}
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
                       &programme[3],
                       .sizeOfProgramme = 30},
                       
                      {.courseCode = "AAMP1034",
                       .courseName = "Test Driven Development",
                       .hoursOfLecture = 2,
                       .hoursOfTutorial = 2,
                       .hoursOfPractical = 2,
                       &programme[4],
                       .sizeOfProgramme = 10},
                       
                      {.courseCode = "EFGH5656",
                       .courseName = "Electromagnetics",
                       .hoursOfLecture = 2,
                       .hoursOfTutorial = 1,
                       .hoursOfPractical = 2,
                       &programme[5],
                       .sizeOfProgramme = 20},
                       
                      {.courseCode = "JDHS5839",
                       .courseName = "FPGA and ASIC Design",
                       .hoursOfLecture = 2,
                       .hoursOfTutorial = 1,
                       .hoursOfPractical = 2,
                       &programme[6],
                       .sizeOfProgramme = 24},
                       
                      {.courseCode = "UWQI8912",
                       .courseName = "Engineering Mathematics I",
                       .hoursOfLecture = 2,
                       .hoursOfTutorial = 1,
                       .hoursOfPractical = 0,
                       &programme[7],
                       .sizeOfProgramme = 15},
                       
                      {.courseCode = "IQJD1875",
                       .courseName = "Tamadun Islam",
                       .hoursOfLecture = 2,
                       .hoursOfTutorial = 1,
                       .hoursOfPractical = 0,
                       &programme[8],
                       .sizeOfProgramme = 33},
                       
                      {.courseCode = "ZXCV8787",
                       .courseName = "Pendidikan Moral",
                       .hoursOfLecture = 2,
                       .hoursOfTutorial = 1,
                       .hoursOfPractical = 0,
                       &programme[9],
                       .sizeOfProgramme = 32}
                    };
										
									
char *getCourseName(Course newCourse){
	if(newCourse.courseName != NULL)
    return newCourse.courseName;
}

char *getCourseCode(Course newCourse){

	if(newCourse.courseCode != NULL)
    return newCourse.courseCode;
}

// int getTotalStudentsInCourse(Class *newClass) {
  // if(newClass->group->groupSize != 0)
      // return newClass->group->groupSize;  
// }

// int getVenueSize(Class *newClass) {
  // if(newClass->venue->sizeOfVenue != 0)
    // return newClass->venue->sizeOfVenue;
// }

// constraints try

/**
*	Name:	checkLecturerNotInchargeOfCourse()
*	Input: 	Class struct pointer, Course *course[]
*	Output: return 1 if there is violation, else 0
*	
*	Descriptions:
*	To check the course on the time slot incharge by the lecturer
*
*/
int checkLecturerNotInchargeOfCourse(Class newClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS], int venue, int day, int time){

	int j;
	for(j=0 ; j < MAX_COURSE_PER_LECTURER ; j++){
		if(!newClass[venue][day][time].course || !newClass[venue][day][time].course->courseCode || !newClass[venue][day][time].lecturer )
			return 0;
		else if(newClass[venue][day][time].lecturer != NULL && newClass[venue][day][time].lecturer->courseCodeInCharge[j] != NULL && class[0][0][0].course->courseCode){
			if(strcmp(newClass[venue][day][time].lecturer->courseCodeInCharge[j], newClass[venue][day][time].course->courseCode) == 0)
				return 0;
		}
	}
	return 1;
}

int checkIfTutionOverloadedInSingleDay(Class newClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS], int day){
	
	int time, venue, i, violationCounter = 0;
	Counter counter[(sizeof(group)/sizeof(Group))] = {{.tutorialHours = 0, .lectureHours = 0},
																										{.tutorialHours = 0, .lectureHours = 0},
																										{.tutorialHours = 0, .lectureHours = 0},
																										{.tutorialHours = 0, .lectureHours = 0}};

  for(venue = 0 ; venue < MAX_VENUE ; venue++){
    for(time = 0 ; time < MAX_TIME_SLOTS ; time++){
      for(i = 0 ; i < MAX_TIME_SLOTS ; i++){
        if(newClass[venue][day][time].course && newClass[venue][day][time].course == &course[i]){
          if(newClass[venue][day][time].typeOfClass == 'l')
            counter[i].lectureHours+=1;
          else if(newClass[venue][day][time].typeOfClass == 't')
            counter[i].tutorialHours+=1;
          else if(newClass[venue][day][time].typeOfClass == 'p')
            counter[i].practicalHours+=1;	
        }
      }
    }	
  }

  for( i = 0; i < (sizeof(group)/ sizeof(Group)) ; i++){
    if(counter[i].lectureHours > course[i].hoursOfLecture)
      violationCounter+= counter[i].lectureHours - course[i].hoursOfLecture;
    if(counter[i].tutorialHours > course[i].hoursOfTutorial)
      violationCounter+= counter[i].tutorialHours - course[i].hoursOfTutorial;
    if(counter[i].practicalHours > course[i].hoursOfPractical)
      violationCounter+= counter[i].practicalHours - course[i].hoursOfPractical;
  }
  
  return violationCounter;
}

/**
 *  The purpose of this function is to check whether the number of 
 *  students in the class exceed the venue size or not
 *  
 *  return 1 (the size of student in the class exceeded)
 *  return 0 (the size did not exceed)
 */
int determineViolationForCourseVenueSize(Class newClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS]) {
  int VenueNumber = 0, day = 0, time = 0;
	int violationCounter = 0;
  
  for(VenueNumber = 0; VenueNumber < MAX_VENUE; VenueNumber++) {
    for(day = 0; day < MAX_DAY; day++) {
      for(time = 0; time < MAX_TIME_SLOTS; time++) {
				if(newClass[VenueNumber][day][time].course != NULL){
					if(venue[VenueNumber].sizeOfVenue < newClass[VenueNumber][day][time].course->programme->group->groupSize){
						violationCounter++;
					}
				}
      }
    }
  }
  return violationCounter;
}

/**
 *  This function is to check whether the same lecturer appear at 
 *  different venue or not
 *  
 *  return 1 (got violation)
 *  return 0 (no violation)
 */
int checkIfLecturerAppearInTwoVenue(Class newClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS], int day, int time){
	int venue, i;
	
	for(venue = 0 ; venue < MAX_VENUE ; venue++){
		for(i = 0; i < MAX_VENUE; i++){
			if(venue != i){
				if(newClass[venue][day][time].lecturer && newClass[i][day][time].lecturer){
					if(newClass[venue][day][time].lecturer == newClass[i][day][time].lecturer)
						return 1;
				}
			}
		}
	}
	return 0;
}

/**
 *  This function is to check whether the same programme and same group 
 *  appears at different venue or not
 * 
 *  return 1 (got violation)
 *  return 0 (no violation)
 */
int checkStudentViolation(Class newClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS], int day, int time) {
  int venue, i;
  
  for(venue = 0; venue < MAX_VENUE; venue++) {
    for(i = 0; i < MAX_VENUE; i++) {
      if(venue != i) {
        if(newClass[venue][day][time].course && newClass[i][day][time].course){
					if(newClass[venue][day][time].course->programme == newClass[i][day][time].course->programme)
						return 1;
				}
      }
    }
  }
  return 0;
}

//constraints function ends here

/**
 *  The purpose of this function is to check whether the chromosome
 *  have empty slots or not, if it has empty slots it will return the address 
 *  of the chromosome
 */
Class *checkChromosomeIsEmpty(Class newClass[4][MAX_DAY][MAX_TIME_SLOTS]) {
  int venue = 0;
  int day = 0, time = 0;
  
  for(venue; venue < MAX_VENUE; venue++) {
    for(day; day < MAX_DAY; day++) {
      for(time; time < MAX_TIME_SLOTS; time++) {
        if(newClass[venue][day][time].course == NULL && newClass[venue][day][time].lecturer == NULL)
          return &newClass[venue][day][time];
      }
    }
  }
}

void addDetailsIntoChromosome(Class newClass[4][MAX_DAY][MAX_TIME_SLOTS], Course course[], Lecturer lecturer[], char typeOfClass){
	Class *addIntoClass = checkChromosomeIsEmpty(newClass);
	addIntoClass->lecturer = lecturer;
	addIntoClass->course = course;
	addIntoClass->typeOfClass = typeOfClass;
}

int calculateFitnessScore(Class newClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS]){
	int venue = 0;
  int day = 0, time = 0;
	int violation = 0;
	
		
  for(venue = 0; venue < MAX_VENUE; venue++) {
    for(day = 0; day < MAX_DAY; day++) {
			if(venue == 0)
				violation += checkIfTutionOverloadedInSingleDay(newClass, day);
      for(time = 0; time < MAX_TIME_SLOTS; time++) {
				violation +=  checkLecturerNotInchargeOfCourse(newClass, venue, day, time);
				if(venue == 0){
					violation += checkIfLecturerAppearInTwoVenue(newClass, day, time);
					violation += checkStudentViolation(newClass, day, time);
				}
      }
    }
  }
  violation += determineViolationForCourseVenueSize(newClass);
    
	return violation;
}