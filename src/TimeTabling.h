#ifndef TimeTabling_H
#define TimeTabling_H
#include <stdio.h>
typedef enum
{
  SUNDAY,
  MONDAY,
  TUESDAY,
  WEDNESDAY,
  THURSDAY,
  FRIDAY,
  SATURDAY
} TotalDays;

typedef enum
{
  _8_to_9,
  _9_to_10,
  _10_to_11,
  _11_to_12,
  _12_to_1,
  _1_to_2,
  _2_to_3,
  _3_to_4,
  _4_to_5
} TotalTimeSlot;
       
typedef struct Class Class;
typedef struct Course Course;
typedef struct Lecturer Lecturer;
typedef struct Group Group;
typedef struct Programme Programme;
typedef struct Venue Venue;

struct Venue
{
  char *nameOfVenue;
  int sizeOfVenue;
};

struct Lecturer
{
	char *lecturerName;
  char *department;
};

struct Group
{
  char *groupName;
	int groupSize;
};

struct Programme
{
  char *programmeName;
  Group group;
};

struct Course
{
	char *courseCode;
	char *courseName;
  int hoursOfLecture;
  int hoursOfTutorial;
  int hoursOfPractical;
  Programme programme;
  int sizeOfProgramme;
};

struct Class 
{
  Programme *programme;
  Course *course;
  Lecturer *lecturer;
  Group *group;
  Venue *venue;
};

char *getCourseName(Course newCourse);
char *getCourseCode(Course newCourse);
int getTotalStudentsInCourse(Group group);
int getTotalStudentsInCourseofProgramme();

//constraints
int checkCourseHoursClash( Class *newClass);
#endif // TimeTabling_H
