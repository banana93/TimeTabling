#ifndef TimeTabling_H
#define TimeTabling_H
#include <stdio.h>

#define MAX_VENUE 4
#define MAX_DAY 3
#define MAX_TIME_SLOTS 5

/************************************************************************
 *	The enum used to indicates the DAY int the timetable
 ************************************************************************/
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

/************************************************************************
 *	The enum used to indicates the TIME_SLOTS in the timetable
 ************************************************************************/
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

/************************************************************************
 *	type define for each structure of the elements of timetable
 ************************************************************************/
typedef struct Course Course;
typedef struct Lecturer Lecturer;
typedef struct Group Group;
typedef struct Programme Programme;
typedef struct Venue Venue;
typedef struct Class Class;
typedef struct Population Population;

/************************************************************************
 *	Struct of Venue
 ************************************************************************/
struct Venue
{
  char *nameOfVenue;
  int sizeOfVenue;
  char venueType;
};

/************************************************************************
 *	Struct of Lecturer
 ************************************************************************/
struct Lecturer
{
	char *lecturerName;
  char *department;
};

/************************************************************************
 *	Struct of Group
 ************************************************************************/
struct Group
{
  char *groupName;
	int groupSize;
};

/************************************************************************
 *	Struct of Programme
 ************************************************************************/
struct Programme
{
  char *programmeName;
  Group *group[5];
};

/************************************************************************
 *	Struct of Course
 ************************************************************************/
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

/************************************************************************
 *	Struct of Class
 ************************************************************************/
struct Class 
{
  Course *course;
  Lecturer *lecturer;
	char typeOfClass;
	Group *group[5];
  int markOfViolation;
};

/************************************************************************
 *	Struct of Population
 ************************************************************************/
struct Population 
{
  Class class[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS];
	int violation;
};

/************************************************************************
 *	extern all the elements to share among the functions
 ************************************************************************/
extern	Class class[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS];
extern	Population populationOfClasses[50];
extern	Group group[];
extern	Venue venue[];
extern	Lecturer lecturer[];
extern	Programme programme[];
extern	Course course[];
extern	Class classList[52];

/************************************************************************
 *	Function prototype
 ************************************************************************/
/***********************************************************************************
 *  Index increment and decrement of 3D array of [venue][day][time]
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
 *  Edit functions for chromosome and Populations
 ***********************************************************************************/
void addDetailsIntoChromosome(Class newClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS], Course course[], Lecturer lecturer[], Group group[], char typeOfClass);
Class *checkChromosomeIsEmpty(Class newClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS]);
void fillInTheChromosomeWithReducingViolation(Class classList[], int sizeOfClassList);
void createPopulationsOfChromosome(int sizeOfClassList);
void sortPopulationsAccordingToFitness(Population *population, int sizeOfPopulation);
Population copyPopulation(Population sourcePopulation);
void clearPopulation(Population *population);

/***********************************************************************************
 *  Edit functions for Class
 ***********************************************************************************/
Class copyClassSlot(Class sourceClass);
void copyClass(Class sourceClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS], Class targetClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS]);
Class clearClassSlot(Class sourceClass);
void clearClass(Class sourceClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS]);
void clearClassList(int sizeOfClass , Class newClass[sizeOfClass]);
int compareClass(Class newClass, Class newClass2);
void randomizeClassList(int sizeOfClassList, Class targetClassList[sizeOfClassList]);

/************************************************************************************
 *   Mutation Functions
 ************************************************************************************/
void swapClasses(Class *newClassA, Class *newClassB);
int checkViolationWhenSwapClasses(Class newClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS]);
void performMutation(Population populationOfClasses[50]);

/************************************************************************************
 *   Crossover Functions
 ************************************************************************************/
int crossoverToOffspring(Class newClass, Class returnClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS], 
												 int venueIndex, int dayIndex, int timeIndex, int *leftStop);
void performCrossover(Class newClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS], Class newClass2[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS], Class offSpring[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS]);


/************************************************************************************
 *      Final Function 
 ************************************************************************************/
 void solveTimeTabling();

#endif // TimeTabling_H
