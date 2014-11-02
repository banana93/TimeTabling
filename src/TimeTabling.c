#include <stdio.h>
#include "TimeTabling.h"

void checkPerspective(Perspective *perspective1, Perspective *perspective2)
{
  if((perspective1->time == perspective2->time) && (perspective1->nameOfLecturer != perspective2->nameOfLecturer)) {
    printf("Error, different lecturer at the same time\n");
  }
}