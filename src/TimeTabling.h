#ifndef TimeTabling_H
#define TimeTabling_H
#include <stdio.h>

#define MAX_DAY 5
#define MAX_TIME_SLOTS 8
#define MAX_VENUE 4

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
       
typedef struct Course Course;
typedef struct Lecturer Lecturer;
typedef struct Group Group;
typedef struct Programme Programme;
typedef struct Venue Venue;
typedef struct Class Class;
typedef struct Counter Counter;

struct Venue
{
  char *nameOfVenue;
  int sizeOfVenue;
};

struct Lecturer
{
	char *lecturerName;
  char *department;
  char *courseCodeInCharge[5];
};

struct Group
{
  char *groupName;
	int groupSize;
};

struct Programme
{
  char *programmeName;
  Group *group;
};

struct Course
{
	char *courseCode;
	char *courseName;
  int hoursOfLecture;
  int hoursOfTutorial;
  int hoursOfPractical;
  Programme *programme;
  int sizeOfProgramme;
};

struct Class 
{
  Course *course;
  Lecturer *lecturer;
	char typeOfClass;
};

struct Counter
{
	int lectureHours;
	int tutorialHours;
	int practicalHours;
};

extern	Class class[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS];
extern	Group group[4];
extern	Venue venue[4];
extern	Lecturer lecturer[4];
extern	Programme programme[4];
extern	Course course[4];


char *getCourseName(Course newCourse);
char *getCourseCode(Course newCourse);
int getTotalStudentsInCourse(Class *newClass);
int getVenueSize(Class *newClass);
void addDetailsIntoChromosome(Class newClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS], Course course[], Lecturer lecturer[], char typeOfClass);
Class *checkChromosomeIsEmpty(Class newClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS]);


//constraints
int checkCourseHoursClash( Class *newClass);
int checkLecturerNotInchargeOfCourse(Class newClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS], int venue, int day, int time);
int checkIfTutionOverloadedInSingleDay(Class newClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS], int day);
int checkIfLecturerAppearInTwoVenue(Class newClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS], int day, int time);
int checkStudentAndVenueSize(Class newClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS], Venue usedVenue[]);
int checkStudentViolation(Class newClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS], int day, int time);

#endif // TimeTabling_H
