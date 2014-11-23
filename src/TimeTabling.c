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

int getTotalStudentsInCourse(Class *newClass) {
  if(newClass->group->groupSize != 0)
      return newClass->group->groupSize;  
}

int getVenueSize(Class *newClass) {
  if(newClass->venue->sizeOfVenue != 0)
    return newClass->venue->sizeOfVenue;
}

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
//constraints function ends here

// int addDetailsIntoChromosome(Programme (*programme)[], Group (*group)[], Course (*course)[], Lecturer (*lecturer)[], Venue (*venues)[]) {
  // int venue = 0, day = 0, time = 0;
  // Class (*chromosome)[venue][day][time];
  
  // for(venue = 0; venue < 1; venue++) {
    // for(day = 0; day < 1; day++) {
      // for(time = 0; time < 1; time ++) {
      
        // if(chromosome[venue][day][time] == NULL) {
        
          // (*chromosome)[venue][day][time] = {  &programme,
                                               // &course,
                                               // &lecturer,
                                               // &group,
                                               // &venues
                                            // };
         // printf("asd\n");
        // } else 
            // return 0;
      // }
    // }
  // }
// }

int checkChromosomeIsEmpty(Class chromosome [1][MAX_DAY][MAX_TIME_SLOTS]) {
  int venue = 0, day = 0, time = 0;
  
  for(venue; venue < 4; venue++) {
    for(day; day < MAX_DAY; day++) {
      for(time; time < MAX_TIME_SLOTS; time++) {
        if(chromosome[venue][day][time] == NULL)
          return 1;
        else 
          return 0;
      }
    }
  }
}