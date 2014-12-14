#ifndef TimeTabling_H
#define TimeTabling_H
#include <stdio.h>
#include "Node.h"
#include "RedBlackTree.h"
#include "ErrorCode.h"
#include "CustomAssertions.h"
#include "Rotations.h"
#include "InitNode.h"

#define MAX_DAY 3
#define MAX_TIME_SLOTS 5
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
  char venueType;
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
  Group *group[5];
};

struct Course
{
	char *courseCode;
	char *courseName;
  int hoursOfLecture;
  int hoursOfTutorial;
  int hoursOfPractical;
  Programme *programme[20];
  int sizeOfProgramme;
};

struct Class 
{
  Course *course;
  Lecturer *lecturer;
	char typeOfClass;
	Group *group[20];
  Node *classNode;
  int markOfViolation;
};

struct Counter
{
	int lectureHours;
	int tutorialHours;
	int practicalHours;
};

extern	Class class[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS];
extern	Group group[];
extern	Venue venue[];
extern	Lecturer lecturer[];
extern	Programme programme[];
extern	Course course[];
extern	Class classList[52];



char *getCourseName(Course newCourse);
char *getCourseCode(Course newCourse);
int getTotalStudentsInCourse(Class *newClass);
int getVenueSize(Class *newClass);
void addDetailsIntoChromosome(Class newClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS], Course course[], Lecturer lecturer[], Group group[], char typeOfClass);
Class *checkChromosomeIsEmpty(Class newClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS]);
int calculateFitnessScore(Class newClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS]);
void fillInTheChromosomeWithReducingViolation(Class classList[], int sizeOfClassList);
int performMutation(Class newClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS]);

//constraints
// int checkLecturerNotInchargeOfCourse(Class newClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS], int venue, int day, int time);
int checkIfTutionOverloadedInSingleDay(Class newClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS], int day);
int checkIfLecturerAppearInTwoVenue(Class newClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS], int day, int time);
int determineViolationForCourseVenueSize(Class newClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS], int VenueNumber, int day, int time);
int checkStudentViolation(Class newClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS], int day, int time);
void clearClassSlot(Class *newClass);
#endif // TimeTabling_H
