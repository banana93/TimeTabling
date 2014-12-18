#include <stdio.h>
#include <stdlib.h>
#include "TimeTabling.h"
#include "Node.h"
#include "TimeTablingClassList.h"
#include "RedBlackTree.h"
#include "ErrorCode.h"
#include "CustomAssertions.h"
#include "Rotations.h"
#include "InitNode.h"

Class class[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS];
Population populationOfClasses[500];
Node node1, node2, node3, node4, node5, node6, node7, node8, node9, node10, node11, node12, node13, node15, node17, node18, node20, node30;
Node *root = NULL;

/**
char *getCourseName(Course newCourse){
	if(newCourse.courseName != NULL)
    return newCourse.courseName;
}

char *getCourseCode(Course newCourse){

	if(newCourse.courseCode != NULL)
    return newCourse.courseCode;
}

int getTotalStudentsInCourse(Class *newClass) {
  if(newClass->group->groupSize != 0)
      return newClass->group->groupSize;  
}

int getVenueSize(Class *newClass) {
  if(newClass->venue->sizeOfVenue != 0)
    return newClass->venue->sizeOfVenue;
}
**/

/**
 *  The purpose of this function is to check whether the number of 
 *  hours of a particular group exceed 4 hours
 *  
 *  return number of exceeded (the size of student in the class exceeded)
 *  return 0 (the size did not exceed)
 */
int checkIfTutionOverloadedInSingleDay(Class newClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS], int day){
	
	int time, venue, i, j, violationCounter = 0;
	int counter[(sizeof(group)/sizeof(Group))] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};

  for(venue = 0 ; venue < MAX_VENUE ; venue++){
    for(time = 0 ; time < MAX_TIME_SLOTS ; time++){
      for(i = 0 ; newClass[venue][day][time].group[i] != NULL ; i++){
				for(j = 0 ; j < (sizeof(group)/sizeof(Group)) ; j++){
					if(newClass[venue][day][time].group[i] != NULL && newClass[venue][day][time].group[i] == &group[j]){
						counter[j]++;
					}
        }
      }
    }	
  }

  for( i = 0; i < (sizeof(group)/ sizeof(Group)) ; i++){
    if(counter[i] > 4)
      violationCounter+= counter[i] - 4;
  }
  
  return violationCounter;
}

/**
 *  The purpose of this function is to check whether the number of 
 *  students in the class exceed the venue size or not
 *  
 *  return number of exceeded (the size of student in the class exceeded)
 *  return 0 (the size did not exceed)
 */
int determineViolationForCourseVenueSize(Class newClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS], int VenueNumber, int day, int time) {
  int i = 0;
	int violationCounter = 0;

	for(i = 0 ; newClass[VenueNumber][day][time].group[i] != NULL ; i++){
		violationCounter += newClass[VenueNumber][day][time].group[i]->groupSize;
	}
	if(violationCounter > venue[VenueNumber].sizeOfVenue) {
    newClass[VenueNumber][day][time].markOfViolation = 1;
    violationCounter = violationCounter - venue[VenueNumber].sizeOfVenue;
	} else
      violationCounter = 0;
	
  return violationCounter;
}

/**
 *  This function is to check whether the same lecturer appear at 
 *  different venue or not
 *  
 *  return number of exceeded (got violation)
 *  return 0 (no violation)
 */
int checkIfLecturerAppearInTwoVenue(Class newClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS], int day, int time){
	int venue, i;
	int counter[(sizeof(lecturer)/sizeof(Lecturer))] = { 0,0,0,0 };
	int returnCounter = 0;
	
	for(venue = 0 ; venue < MAX_VENUE ; venue++){
		for(i = 0; i < MAX_VENUE; i++){
			if(newClass[venue][day][time].lecturer){
				if(newClass[venue][day][time].lecturer == &lecturer[i]) {
          newClass[venue][day][time].markOfViolation = 1;
					counter[i]++;
        }
			}
		}
	}
  for(i = 0 ; i < (sizeof(lecturer)/sizeof(Lecturer)) ; i++){
		if(counter[i] > 1)
			returnCounter = counter[i] - 1;
	}
  return returnCounter;
}

/**
 *  This function is to check whether the same programme and same group 
 *  appears at different venue or not
 * 
 *  return value of exceeding (got violation)
 *  return 0 (no violation)
 */
int checkStudentViolation(Class newClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS], int day, int time) {
  int venue, i , j;
	int counter[(sizeof(group)/sizeof(Group))] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int returnCounter = 0;
	
  for(venue = 0; venue < MAX_VENUE; venue++){
		for(i = 0; newClass[venue][day][time].group[i] != NULL ; i++){
			for(j = 0; j < (sizeof(group)/sizeof(Group)); j++){
				if(newClass[venue][day][time].group[i] == &group[j]) {
          newClass[venue][day][time].markOfViolation = 1;
					counter[j]++;
        }
			}
		}
  }

  for(i = 0 ; i < (sizeof(group)/sizeof(Group)) ; i++){
		if(counter[i] > 1)
			returnCounter = counter[i] - 1;
	}
  return returnCounter;
}



/**
 *  The purpose of this function is to check whether the chromosome
 *  have empty slots or not, if it has empty slots it will return the address 
 *  of the chromosome
 */
Class *checkChromosomeIsEmpty(Class newClass[4][MAX_DAY][MAX_TIME_SLOTS]) {
  int venue = 0;
  int day = 0, time = 0;
  
  for(venue = 0; venue < MAX_VENUE; venue++) {
    for(day = 0; day < MAX_DAY; day++) {
      for(time = 0; time < MAX_TIME_SLOTS; time++) {
        if(newClass[venue][day][time].course == NULL && newClass[venue][day][time].lecturer == NULL)
          return &newClass[venue][day][time];
      }
    }
  }
}

/**
 *  The purpose of this function is to add
 *	information of class into one particular slot of class
 */
void addDetailsIntoChromosome(Class newClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS], Course course[], Lecturer lecturer[], Group group[], char typeOfClass){
	int i;
	Class *addIntoClass = checkChromosomeIsEmpty(newClass);
	addIntoClass->lecturer = lecturer;
	addIntoClass->course = course;
	addIntoClass->typeOfClass = typeOfClass;
	for( i = 0 ; i < 3 ; i++){
		if(&group[i] != NULL)
      addIntoClass->group[i] = &group[i];
	}
}

/**
 *  This function is to calculate the number / points of violation of the entire class[][][]
 *
 *  return value of exceeding (got violation)
 *  return 0 (no violation)
 */
int calculateFitnessScore(Class newClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS]){
	int venue = 0;
  int day = 0, time = 0;
	int violation = 0;
	
		
  for(venue = 0; venue < MAX_VENUE; venue++) {
    for(day = 0; day < MAX_DAY; day++) {
			if(venue == 0)
				violation += checkIfTutionOverloadedInSingleDay(newClass, day);
      for(time = 0; time < MAX_TIME_SLOTS; time++) {
				violation += determineViolationForCourseVenueSize(newClass,venue,day,time);
				if(venue == 0){
					violation += checkIfLecturerAppearInTwoVenue(newClass, day, time);
					violation += checkStudentViolation(newClass, day, time);
				}
      }
    }
  }
    
	return violation;
}

/**
 *  The purpose of this function is to add
 *	information from classList (entire amount of classes)
 *	into the venue, day and time slot (class[][][])
 */
void fillInTheChromosome(Class classList[], int sizeOfClassList){
	int venue, day, time;
	int i = 0, violation;
	
		for(venue = 0; venue < MAX_VENUE; venue++) {
			for(day = 0; day < MAX_DAY; day++) {
				for(time = 0; i < sizeOfClassList && time < MAX_TIME_SLOTS; time++) {
					if(class[venue][day][time].course == NULL){
						class[venue][day][time] = classList[i];
						i++;
					}
				}
			}
		}
}

/**
 *  The purpose of this function is to add
 *	information from classList (entire amount of classes)
 *	into the venue, day and time slot (class[][][])
 *	with some logic to reduce the violation to reduce the burden of crossover / mutation
 */
void fillInTheChromosomeWithReducingViolation(Class classList[], int sizeOfClassList){
	int venue, day, time;
	int i = 0, violation;
	
	for(violation = 0 ; violation < 1000; violation+=1){
		for(venue = 0; venue < MAX_VENUE; venue++){
			for(day = 0; day < MAX_DAY; day++) {
				for(time = 0; i < sizeOfClassList && time < MAX_TIME_SLOTS; time++) {
					if(class[venue][day][time].course == NULL){
						class[venue][day][time] = classList[i];
						if(calculateFitnessScore(class) > violation)
							class[venue][day][time] = clearClassSlot(class[venue][day][time]);
						else
							i++;
					}
				}
			}
		}
	}
}

/**
 *  The purpose of this function is to copy one  particular slot in class to another
 */
Class copyClassSlot(Class sourceClass){
	int i;
	Class targetClass;
	
	targetClass.course = sourceClass.course;
	targetClass.lecturer = sourceClass.lecturer;
	targetClass.typeOfClass = sourceClass.typeOfClass;
	targetClass.classNode = sourceClass.classNode;
	targetClass.markOfViolation = sourceClass.markOfViolation;
	for(i = 0 ; i < 5 ; i++){
		targetClass.group[i] = sourceClass.group[i];
	}
	return targetClass;
}

/**
 *  The purpose of this function is to copy one class to another
 */
void copyClass(Class sourceClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS], Class targetClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS]){
	int i, j, k;
	
	for( i = 0 ; i < MAX_VENUE ; i++ ){
		for( j = 0 ; j < MAX_DAY ; j++ ){
			for( k = 0 ; k < MAX_TIME_SLOTS ; k++ ){
				targetClass[i][j][k] = copyClassSlot(sourceClass[i][j][k]);
			}
		}
	}
}

/**
 *  The purpose of this function is to clear particular slot in class[][][]
 */
Class clearClassSlot(Class sourceClass){
	int i;
	
	sourceClass.lecturer = NULL;
	sourceClass.course = NULL;
	sourceClass.typeOfClass = 0;
	sourceClass.classNode = NULL;
	sourceClass.markOfViolation = 0;
	for(i = 0 ; i < 5 ; i++){
		sourceClass.group[i] = NULL;
	}
	
	return sourceClass;
}

/**
 *  The purpose of this function is to clear particular slot in class[][][]
 */
void clearClass(Class sourceClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS]){
	int i, j, k;
	
	for( i = 0 ; i < MAX_VENUE ; i++ ){
		for( j = 0 ; j < MAX_DAY ; j++ ){
			for( k = 0 ; k < MAX_TIME_SLOTS ; k++ ){
				sourceClass[i][j][k] = clearClassSlot(sourceClass[i][j][k]);
			}
		}
	}
}

/**
 *  The purpose of this function is to clear class[] for population purpose
 */
void clearClassList(int sizeOfClass , Class (*newClass)[sizeOfClass]){
	int i, j;
	
for(i = 0; i < sizeOfClass; i++) {
	(*newClass)[i].lecturer = NULL;
	(*newClass)[i].course = NULL;
	(*newClass)[i].typeOfClass = 0;
	(*newClass)[i].classNode = NULL;
	(*newClass)[i].markOfViolation = 0;
		for(j = 0 ; j < 5 ; j++){
			(*newClass)[i].group[j] = NULL;
		}
}
}

/**
 *  The purpose of this function is randomize the classList before creating populations of chromosome
 */
void randomizeClassList(int sizeOfClassList, Class (*targetClassList)[sizeOfClassList]){
	int i, j;
	int r;

	for(i = 0 ; i < sizeOfClassList; ){
		j = rand()%sizeOfClassList;
			if((*targetClassList)[j].course == NULL){
				(*targetClassList)[j] = copyClassSlot(classList[i]);
				i++;
			}
	}
}

/**
 *  The purpose of this function is randomize the classList before creating populations of chromosome
 */
void createPopulationsOfChromosome(int sizeOfClassList){
	Class randomList[sizeOfClassList];
	int i;
	
	for( i = 0 ; i < sizeof(populationOfClasses)/sizeof(Population) ; i ++){
		clearClassList(sizeOfClassList, &randomList);
		randomizeClassList(sizeOfClassList, &randomList);
		clearClass(class);
		fillInTheChromosomeWithReducingViolation(randomList, sizeOfClassList);
		copyClass(class, populationOfClasses[i].class);
	}


}

void performCrossover(Class newClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS], Class newClass2[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS], int sizeOfClassList){
	
}



int performMutation(Class newClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS]) {
  int fitnessScoreBeforeMutation = 0, fitnessScoreAfterMutation = 0;
  int venue = 0, day = 0, time = 0;
  int tempVenue = 0, tempDay = 0, tempTime = 0;
  Class *tempClass;
	
	/*
		not to destroy your code, but this actually shoudn't be here, you just pick the most fit
		among the population and do it, this part will done by create population function, sorry
	
	fillInTheChromosome(classList, sizeof(classList)/sizeof(Class));
  fitnessScoreBeforeMutation = calculateFitnessScore(newClass);
  */
	
  resetNode(&node1, fitnessScoreBeforeMutation);
  
  for(venue; venue < MAX_VENUE; venue++) {
    for(day; day < MAX_DAY; day++) {
      for(time; time < MAX_TIME_SLOTS; time++) {
        if(newClass[venue][day][time].course != NULL) {
          newClass[venue][day][time].classNode = &node1;
        }
      }
    }
  }
  
  setNode(&node1, NULL, NULL, 'b');
  genericRedBlackTreeAdd(&root, &node1, compare);
  removeSmallestValue(&root);

  for(venue; venue < MAX_VENUE; venue++) {
    for(day; day < MAX_DAY; day++) {
      for(time; time < MAX_TIME_SLOTS; time++) {
        if(newClass[venue][day][time].markOfViolation == 1) {
          tempVenue = venue;
          tempDay = day;
          tempTime = time;
          break;
        }
      }
    }
  }  
  
  // tempClass = checkChromosomeIsEmpty(newClass);
  // tempClass->lecturer = newClass[tempVenue][tempDay][tempTime].lecturer;
  // tempClass->course = newClass[tempVenue][tempDay][tempTime].course;
  // tempClass->typeOfClass = newClass[tempVenue][tempDay][tempTime].typeOfClass;
  // tempClass->group = newClass[tempVenue][tempDay][tempTime].group;
  
  return fitnessScoreBeforeMutation;
  
}