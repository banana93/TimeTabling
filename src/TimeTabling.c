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

int getTotalStudentsInCourse(Group group) {
  if(group.groupSize != 0) 
    return group.groupSize;
}