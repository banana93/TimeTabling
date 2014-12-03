#include <stdio.h>
#include "TimeTabling.h"

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
*	Name:	checkCourseHoursClash()
*	Input: Class struct pointer
*	Output: return 1 if there is clash/violation, else 0
*	
*	Descriptions:
*	This function is to check the clashes and maximum hours of the class.
*	In the chromosome, only one Course, and type of class available at times.
*	Besides that, each type of class have a limit of hours
*
*	Constraints included for each Chromosome's slot
*	- Only can have one in each array slot. Tutorial, Practical, Lecture
*	- Lecture cannot more than 4 hours
*	- Tutorial cannot more than 2 hours
*
*/
int checkCourseHoursClash(Class *newClass){
if( newClass->course->hoursOfLecture != 0 && (newClass->course->hoursOfTutorial + newClass->course->hoursOfPractical) == 0){
	if( newClass->course->hoursOfLecture >= 0 && newClass->course->hoursOfLecture <= 4)
		return 0;
	else
		return 1;
}
else if( newClass->course->hoursOfTutorial != 0 && (newClass->course->hoursOfLecture + newClass->course->hoursOfPractical) == 0){
	if( newClass->course->hoursOfTutorial >= 0 && newClass->course->hoursOfTutorial <=2 )
		return 0;
	else
		return 1;
}
else if( newClass->course->hoursOfPractical != 0 && (newClass->course->hoursOfLecture + newClass->course->hoursOfTutorial) == 0)
		return 0;
else if((newClass->course->hoursOfLecture + newClass->course->hoursOfTutorial + newClass->course->hoursOfPractical) == 0)
		return 0;
	return 1;
	
}

/**
*	Name:	checkLecturerNotInchargeOfCourse()
*	Input: 	Class struct pointer, Course *course[]
*	Output: return 1 if there is violation, else 0
*	
*	Descriptions:
*	To check the course on the time slot incharge by the lecturer
*
*/
int checkLecturerNotInchargeOfCourse(Class *newClass){

	int i,j;
	for(j=0 ; newClass->lecturer->courseCodeInCharge[j] != NULL ; j++){
		if(newClass->lecturer->courseCodeInCharge[j] == newClass->course->courseCode)
			return 0;
	}
	return 1;
}

int checkIfTutionOverloadedInSingleDay(Class newClass[4][MAX_DAY][MAX_TIME_SLOTS], int venue, int day){

	int time, i, j;
	int counter[MAX_TIME_SLOTS] = {0,0,0,0,0,0,0,0};
	
	// Add up hours of lecture
	for(time = 0 ; time < MAX_TIME_SLOTS ; time++){
		for(i = 0; i < MAX_TIME_SLOTS; i++){
				if(newClass[venue][day][time].course == newClass[venue][day][i].course
					&& newClass[venue][day][time].typeOfClass == newClass[venue][day][i].typeOfClass)
					counter[time]++;
		}
	}

	for(j = 0 ; j < MAX_TIME_SLOTS && newClass[venue][day][j].course; j++){
		if(newClass[venue][day][j].typeOfClass == 'l'){
			if(counter[j] > newClass[venue][day][j].course->hoursOfLecture)
				return 1;
		}
		else if(newClass[venue][day][j].typeOfClass == 't'){
			if(counter[j] > newClass[venue][day][j].course->hoursOfTutorial)
				return 1;
		}
		else if(newClass[venue][day][j].typeOfClass == 'p'){
			if(counter[j] > newClass[venue][day][j].course->hoursOfPractical)
				return 1;
		}
	}
		return 0;

}

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

//constraints function ends here

Class *checkChromosomeIsEmpty(Class newClass[4][MAX_DAY][MAX_TIME_SLOTS]) {
  int venue = 0;
  int day = 0, time = 0;
  
  for(venue; venue < 4; venue++) {
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

