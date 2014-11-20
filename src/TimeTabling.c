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
  if(group.groupSize != 0) 
    return group.groupSize;
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
int checkCourseHoursClash( Course *course){
if( course->hoursOfLecture != 0 && (course->hoursOfTutorial + course->hoursOfPractical) == 0){
	if( course->hoursOfLecture >= 0 && course->hoursOfLecture <= 4)
		return 0;
	else
		return 1;
}
else if( course->hoursOfTutorial != 0 && (course->hoursOfLecture + course->hoursOfPractical) == 0){
	if( course->hoursOfTutorial >= 0 && course->hoursOfTutorial <=2 )
		return 0;
	else
		return 1;
}
else if( course->hoursOfPractical != 0 && (course->hoursOfLecture + course->hoursOfTutorial) == 0)
		return 0;
else if((course->hoursOfLecture + course->hoursOfTutorial + course->hoursOfPractical) == 0)
		return 0;
	return 1;
	
}