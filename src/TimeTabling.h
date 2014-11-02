#ifndef TimeTabling_H
#define TimeTabling_H

typedef struct Perspective Perspective;

struct Perspective
{
  int time;
  char *venue;
  char *day;
  char subjectType;
  char *group;
  char *nameOfLecturer;
};

void checkPerspective(Perspective *perspective1, Perspective *perspective2);

#endif // TimeTabling_H
