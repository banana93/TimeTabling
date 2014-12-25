#ifndef TimeTabling_H
#define TimeTabling_H
#include <stdio.h>
// #include "Node.h"
// #include "RedBlackTree.h"
// #include "ErrorCode.h"
// #include "CustomAssertions.h"
// #include "Rotations.h"
// #include "InitNode.h"

#define MAX_VENUE 4
#define MAX_DAY 3
#define MAX_TIME_SLOTS 5

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
typedef struct Population Population;

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
  Programme *programme[5];
  int sizeOfProgramme;
};

struct Class 
{
  Course *course;
  Lecturer *lecturer;
	char typeOfClass;
	Group *group[5];
  int markOfViolation;
};

struct Population 
{
  Class class[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS];
	int violation;
};

extern	Class class[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS];
extern	Population populationOfClasses[20];
extern	Group group[];
extern	Venue venue[];
extern	Lecturer lecturer[];
extern	Programme programme[];
extern	Course course[];
extern	Class classList[52];


/***********************************************************************************
 *  get information from class
 ***********************************************************************************
char *getCourseName(Course newCourse);
char *getCourseCode(Course newCourse);
int getTotalStudentsInCourse(Class *newClass);
int getVenueSize(Class *newClass);
// did not use
**/

/***********************************************************************************
 *  Constraint functions & fitness score calculator
 ***********************************************************************************/
 void indexForward(int *venue, int *day, int *time);
 void indexBackward(int *venue, int *day, int *time);
 
/***********************************************************************************
 *  Constraint functions & fitness score calculator
 ***********************************************************************************/
int checkIfTutionOverloadedInSingleDay(Class newClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS], int day);
int checkIfLecturerAppearInTwoVenue(Class newClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS], int day, int time);
int determineViolationForCourseVenueSize(Class newClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS], int VenueNumber, int day, int time);
int checkStudentViolation(Class newClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS], int day, int time);
int calculateFitnessScore(Class newClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS]);

/***********************************************************************************
 *  fill in the chromosome, populations and mutation/crossover functions
 ***********************************************************************************/
void addDetailsIntoChromosome(Class newClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS], Course course[], Lecturer lecturer[], Group group[], char typeOfClass);
Class *checkChromosomeIsEmpty(Class newClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS]);
void fillInTheChromosomeWithReducingViolation(Class classList[], int sizeOfClassList);
int performMutation(Class newClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS]);
void createPopulationsOfChromosome(int sizeOfClassList);
void sortPopulationsAccordingToFitness();

/***********************************************************************************
 *  Clear and copy class functions
 ***********************************************************************************/
Class copyClassSlot(Class sourceClass);
void copyClass(Class sourceClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS], Class targetClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS]);
Class clearClassSlot(Class sourceClass);
void clearClass(Class sourceClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS]);
void clearClassList(int sizeOfClass , Class (*newClass)[sizeOfClass]);
int compareClass(Class newClass, Class newClass2);
void randomizeClassList(int sizeOfClassList, Class (*targetClassList)[sizeOfClassList]);

/************************************************************************************
 *   Mutation Functions
 ************************************************************************************/
void swapClasses(Class *newClassA, Class *newClassB);

/************************************************************************************
 *   Crossover Functions
 ************************************************************************************/
int crossoverToOffspring(Class *newClass, Class (*returnClass)[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS], 
												 int venueIndex, int dayIndex, int timeIndex, int *leftStop);
void performCrossover(Class newClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS], Class newClass2[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS], Class (*offSpring)[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS]);


/************************************************************************************
 *      Final Function 
 ************************************************************************************/
 void solveTimeTabling();

#endif // TimeTabling_H
