#include <stdio.h>
#include "TimeTabling.h"

Class class[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS];
	
Group group[] = { {.groupName = "A2",
                     .groupSize = 10},
                     
                    {.groupName = "A3",
                     .groupSize = 13},
                     
                    {.groupName = "K2",
                     .groupSize = 20},
                     
                    {.groupName = "K3",
                     .groupSize = 50}
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
	for(j=0 ; newClass[venue][day][time].lecturer->courseCodeInCharge[j] != NULL ; j++){
		if(newClass[venue][day][time].lecturer->courseCodeInCharge[j] == newClass[venue][day][time].course->courseCode)
			return 0;
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
int checkStudentAndVenueSize(Class newClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS], Venue usedVenue[]) {
  int venue = 0, day = 0, time = 0;
  
  for(venue; venue < MAX_VENUE; venue++) {
    for(day; day < MAX_DAY; day++) {
      for(time; time < MAX_TIME_SLOTS; time++) {
        if(usedVenue[venue].sizeOfVenue < newClass[venue][day][time].course->programme->group->groupSize)
          return 1;
        else 
          return 0;
      }
    }
  }
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
				if(newClass[venue][day][time].lecturer == newClass[i][day][time].lecturer)
					return 1;
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
        if(newClass[venue][day][time].course->programme == newClass[i][day][time].course->programme)
          return 1;
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

int calculateFitnessScore(Class newClass[4][MAX_DAY][MAX_TIME_SLOTS]){
	int venue = 0;
  int day = 0, time = 0;
	
  for(venue; venue < MAX_VENUE; venue++) {
    for(day; day < MAX_DAY; day++) {
			checkIfTutionOverloadedInSingleDay(newClass, day);
      for(time; time < MAX_TIME_SLOTS; time++) {
        checkLecturerNotInchargeOfCourse(newClass, venue, day, time);
				if(venue == 0)
					checkIfLecturerAppearInTwoVenue(newClass, day, time);
      }
    }
  }

}
