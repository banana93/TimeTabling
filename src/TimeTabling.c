#include <stdio.h>
#include "TimeTabling.h"

void checkPerspective(Perspective *perspective1, Perspective *perspective2)
{
  if((perspective1->time == perspective2->time) && 
    (perspective1->nameOfLecturer != perspective2->nameOfLecturer)) {
    
    printf("Error, different lecturer at the same time\n");
  
  } else if((perspective1->time == perspective2->time) &&
           (perspective1->nameOfLecturer == perspective2->nameOfLecturer) &&
           (perspective1->subjectType != perspective2->subjectType)) {
      
      printf("Error, same lecturer but different subject type at the same time\n");
      
    } else if((perspective1->time == perspective2->time) &&
             (perspective1->group == perspective2->group) &&
             (perspective1->subjectCode != perspective2->subjectCode)) {
        
        printf("Error, same group but different subject at the same time\n");
      
      } else if((perspective1->time == perspective2->time) &&
               (perspective1->group != perspective2->group) &&
               (perspective1->subjectCode != perspective2->subjectCode)) {
         
          printf("Error, different group and different subjectCode at the same time\n");
        
        }
}

char *getCourseName(Course newCourse){

	if(newCourse.courseName != NULL)
	return newCourse.courseName;
}

char *getCourseCode(Course newCourse){

	if(newCourse.courseCode != NULL)
	return newCourse.courseCode;
}