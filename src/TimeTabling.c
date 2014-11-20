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
*	
*	Descriptions:
*	This function is to check the clashes and maximum hours of the class.
*	In the chromosome, only one Course, and type of class available at times.
*	Besides that, each type of class have a limit of hours

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

int programmeSizeOverloadsVenue(Class *newClass){



}

void addDetailsIntoChromosome(Class (*chromosome)[][MAX_DAY][MAX_TIME_SLOTS]) {
  int venue, day, time;
  
  // for(venue = 0; venue < 2; venue++) {
    // for(day = 0; day < 5; day++) {
      // for(time = 0; time < 8; time ++) {
        //  newClass[venue][day][time];
      // }
    // }
  // }
  
   printf("programme name: %d\n", (*chromosome)[0][0][0].group->groupSize);
}