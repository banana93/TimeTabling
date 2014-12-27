#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "TimeTabling.h"
#include "TimeTablingClassList.h"
#include "ErrorCode.h"
#include "CException.h"



Class class[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS];
Population populationOfClasses[6];

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

 void indexForward(int *venue, int *day, int *time){
	if(*venue < 0 || *day < 0 || *time < 0)
		Throw(ERR_EXCEEDED_INDEX);
	if(*venue >= MAX_VENUE || *day >= MAX_DAY || *time >= MAX_TIME_SLOTS)
		Throw(ERR_EXCEEDED_INDEX);
	
	(*time)++;
	if(*time >= MAX_TIME_SLOTS){
		*time = 0;
		(*day)++;
		if(*day >= MAX_DAY){
			(*day) = 0;
			(*venue)++;
			if(*venue >= MAX_VENUE)
			*venue = 0;	
		}
	}
 
 }
 
 void indexBackward(int *venue, int *day, int *time){
		if(*venue < 0 || *day < 0 || *time < 0)
		Throw(ERR_EXCEEDED_INDEX);
		if(*venue >= MAX_VENUE || *day >= MAX_DAY || *time >= MAX_TIME_SLOTS)
		Throw(ERR_EXCEEDED_INDEX);
	
	(*time)--;
	if(*time < 0){
		*time = MAX_TIME_SLOTS-1;
		(*day)--;
		if(*day < 0) {
			(*day) = MAX_DAY-1;
			(*venue)--;
			if(*venue < 0)
			*venue = MAX_VENUE-1;	
		}
	}
 
 }

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
          newClass[venue][day][time].markOfViolation = 0;
					if(newClass[venue][day][time].group[i] != NULL && newClass[venue][day][time].group[i] == &group[j]){
						counter[j]++;
					}
        }
      }
    }	
  }

  for( i = 0; i < (sizeof(group)/ sizeof(Group)) ; i++){
    if(counter[i] > 4)
      violationCounter += counter[i] - 4;
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
	
		if(sizeOfClassList > (MAX_VENUE*MAX_DAY*MAX_TIME_SLOTS))
			Throw(ERR_EXCEEDED_INDEX);
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
	if(sizeOfClassList > (MAX_VENUE*MAX_DAY*MAX_TIME_SLOTS))
		Throw(ERR_EXCEEDED_INDEX);
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
void clearClassList(int sizeOfClass , Class newClass[sizeOfClass]){
	int i, j;
	
for(i = 0; i < sizeOfClass; i++) {
	newClass[i].lecturer = NULL;
	newClass[i].course = NULL;
	newClass[i].typeOfClass = 0;
	newClass[i].markOfViolation = 0;
		for(j = 0 ; j < 5 ; j++){
			newClass[i].group[j] = NULL;
		}
}
}

void clearPopulation(Population *population){
	int i;
	for( i = 0 ; i < sizeof(populationOfClasses)/sizeof(Population) ; i++){
		clearClass(population[i].class);
	}
}

/**
 *  The purpose of this function is randomize the classList before creating populations of chromosome
 */
void randomizeClassList(int sizeOfClassList, Class targetClassList[sizeOfClassList]){
	int i, j;
	int r;

	for(i = 0 ; i < sizeOfClassList; ){
		j = rand()%sizeOfClassList;
			if(targetClassList[j].course == NULL){
				targetClassList[j] = copyClassSlot(classList[i]);
				i++;
			}
	}
}

/**
 *  The purpose of this function is randomize the classList before creating populations of chromosome
 */
void createPopulationsOfChromosome(int sizeOfClassList){
	Class randomList[sizeOfClassList];
	clearPopulation(populationOfClasses);
	int i;
	
	for( i = 0 ; i < sizeof(populationOfClasses)/sizeof(Population) ; i ++){
		clearClassList(sizeOfClassList, randomList);
		randomizeClassList(sizeOfClassList, randomList);
		clearClass(class);
		fillInTheChromosomeWithReducingViolation(randomList, sizeOfClassList);
		copyClass(class, populationOfClasses[i].class);
		populationOfClasses[i].violation = calculateFitnessScore(populationOfClasses[i].class);
	}
	
}

void createPopulationsOfChromosomeNotRandomize(int sizeOfClassList) {
  int i;
  
  for( i = 0 ; i < sizeof(populationOfClasses)/sizeof(Population) ; i ++){
		clearClass(class);
		fillInTheChromosome(classList, sizeOfClassList);
		copyClass(class, populationOfClasses[i].class);
	}
	for( i = 0 ; i < sizeof(populationOfClasses)/sizeof(Population) ; i ++){
		populationOfClasses[i].violation = calculateFitnessScore(populationOfClasses[i].class);
	}
	
}
  
void sortPopulationsAccordingToFitness(){

}

/**
 *  The purpose of this function is compare 2 class
 */
int compareClass(Class newClass, Class newClass2){
	int i;
	if(newClass.course == NULL && newClass2.course == NULL)
		return 1;
	
	if(newClass.course == newClass2.course){
		if(newClass.lecturer == newClass2.lecturer){
			if(newClass.typeOfClass == newClass2.typeOfClass){
				for(i = 0 ; i < 5 ; i++){
					if(newClass.group[i] == newClass2.group[i]);
					else
						return 0;
				}
			}
			else
				return 0;
		}
		else
			return 0;
	}
	else
		return 0;
		
	return 1;
}

int crossoverToOffspring(Class newClass, Class returnClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS], 
												 int venueIndex, int dayIndex, int timeIndex, int *leftStop){
	int counter = 1;
	int retLoopVenue = 0,	retLoopDay = 0, retLoopTime = 0;
		
	while(retLoopVenue != venueIndex || retLoopDay != dayIndex || retLoopTime != timeIndex){
		if(compareClass(newClass,returnClass[retLoopVenue][retLoopDay][retLoopTime]))
			counter+=1;
		indexForward(&retLoopVenue, &retLoopDay, &retLoopTime);
	}
	
	if(newClass.course == NULL){
		if(counter <= (MAX_VENUE*MAX_DAY*MAX_TIME_SLOTS) - (sizeof(classList)/sizeof(Class))){
			returnClass[retLoopVenue][retLoopDay][retLoopTime] = copyClassSlot(newClass);
			return 1;
		}
		else
			*leftStop = 1;
	}
	else if(newClass.typeOfClass == 'l'){
		if(counter <= newClass.course->hoursOfLecture){
			returnClass[retLoopVenue][retLoopDay][retLoopTime] = copyClassSlot(newClass);
			return 1;
		}
		else
			*leftStop = 1;
	}
	else if(newClass.typeOfClass == 't'){
		if(counter <= newClass.course->hoursOfTutorial){
			returnClass[retLoopVenue][retLoopDay][retLoopTime] = copyClassSlot(newClass);
			return 1;
		}
		else
			*leftStop = 1;
	}
	else if(newClass.typeOfClass == 'p'){
		if(counter <= newClass.course->hoursOfPractical){
			returnClass[retLoopVenue][retLoopDay][retLoopTime] = copyClassSlot(newClass);
			return 1;
		}
		else
			*leftStop = 1;
	}
	return 0;
}
 
void performCrossover(Class newClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS], Class newClass2[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS], Class offSpring[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS]){

	int randomNumberLeft, randomNumberRight;
	int venueToLeft = MAX_VENUE-1, dayToLeft = MAX_DAY-1, timeToLeft = MAX_TIME_SLOTS-1;
	int venueToRight = 0, dayToRight = 0, timeToRight = 0;
	int	 retLoopVenue = 0,	retLoopDay = 0, retLoopTime = 0;
	int i, counter = 1, leftStop = 0;
	// CEXCEPTION_T e;
	
	clearClass(offSpring);
	randomNumberLeft = rand()%(sizeof(classList)/sizeof(Class));
	randomNumberRight = rand()%(sizeof(classList)/sizeof(Class));
	
	for( i = 0 ; i < (MAX_VENUE*MAX_DAY*MAX_TIME_SLOTS) ; i++){
		if(compareClass(newClass[venueToLeft][dayToLeft][timeToLeft],classList[randomNumberLeft]) == 1)
			break;
		indexBackward(&venueToLeft,&dayToLeft,&timeToLeft);	
	}
	for( i = 0 ; i < (MAX_VENUE*MAX_DAY*MAX_TIME_SLOTS) ; i++){
		if(compareClass(newClass2[venueToRight][dayToRight][timeToRight],classList[randomNumberRight]) == 1)
			break;
		indexForward(&venueToRight,&dayToRight,&timeToRight);
	}
	
	
	for( i = 0 ; i < (MAX_VENUE*MAX_DAY*MAX_TIME_SLOTS) ; i++){
		if(leftStop != 1){
			if(crossoverToOffspring(newClass[venueToLeft][dayToLeft][timeToLeft],offSpring, \
															retLoopVenue, retLoopDay, retLoopTime, &leftStop))
				indexForward(&retLoopVenue,&retLoopDay,&retLoopTime);			
			indexBackward(&venueToLeft,&dayToLeft,&timeToLeft);	
		}
		
		if(crossoverToOffspring(newClass[venueToRight][dayToRight][timeToRight],offSpring, \
													  retLoopVenue, retLoopDay, retLoopTime, &leftStop))
				indexForward(&retLoopVenue,&retLoopDay,&retLoopTime);	
		indexForward(&venueToRight,&dayToRight,&timeToRight);			
	}
}


int performMutation(Class newClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS]) {
  int fitnessScoreBeforeMutation = 0, fitnessScoreAfterMutation = 0;
  int venue = 0, day = 0, time = 0;
  int tempVenue = 0, tempDay = 0, tempTime = 0;
  int randomVenue, randomDay, randomTime;
  int counter = 0;
	
  fitnessScoreBeforeMutation = calculateFitnessScore(newClass);
  printf("fitnessScoreBeforeMutation: %d\n", fitnessScoreBeforeMutation);

  // randomVenue = random(MAX_VENUE);
  // randomDay = random(MAX_DAY);
  // randomTime = random(MAX_TIME_SLOTS);
  
  for(venue; venue < MAX_VENUE; venue++) {
    for(day; day < MAX_DAY; day++) {
      for(time; time < MAX_TIME_SLOTS; time++) {
        if(newClass[venue][day][time].course != NULL) {
          if(newClass[venue][day][time].markOfViolation == 1) {
            if(counter == 0) {
              tempVenue = venue;
              tempDay = day;
              tempTime = time;
              counter++;
            }
            
            // randomVenue = rand()%4;
            // randomDay = rand()%3;
            // randomTime = rand()%5;
            swapClasses(&newClass[tempVenue][tempDay][tempTime], &newClass[randomVenue][randomDay][randomTime]);
            fitnessScoreAfterMutation = calculateFitnessScore(newClass);

            if(fitnessScoreAfterMutation < fitnessScoreBeforeMutation) {
                break;
            }
          } 
        } 
      }
    }
  }
  return fitnessScoreAfterMutation;
}

void swapClasses(Class *newClassA, Class *newClassB) {
  Class tempClass;
  
  tempClass = copyClassSlot(*newClassA);
  *newClassA = copyClassSlot(*newClassB);
  *newClassB = tempClass;
}

/*
    The purpose of this function is to check after the specific inside the
    class slot is swapped whether it will violates or not, if it violates it
    will return 1, else it will return 0.
  */
int checkViolationWhenSwapClasses(Class newClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS]) {
	int venue = 0;
  int day = 0, time = 0;
	int violation = 0;
	
		
  for(venue = 0; venue < MAX_VENUE; venue++) {
    for(day = 0; day < MAX_DAY; day++) {
			if(venue == 0) {
				violation += checkIfTutionOverloadedInSingleDay(newClass, day);
        if(violation > 0)
          return 1;
      }
      for(time = 0; time < MAX_TIME_SLOTS; time++) {
				violation += determineViolationForCourseVenueSize(newClass,venue,day,time);
				if(violation > 0) 
          return 1;
          
        if(venue == 0){
					violation += checkIfLecturerAppearInTwoVenue(newClass, day, time);
					violation += checkStudentViolation(newClass, day, time);
          if(violation > 0) 
            return 1;
           
        }
      }
    }
  }
   
	return 0;
}

int calculateHeightOfTree(double numberOfNodes) {
  int heightOfTree = 0;
  double logBase2Result = 0;
  double logBase2 = 2;
  
  logBase2Result = log10(numberOfNodes) / log10(logBase2);
  heightOfTree = 2 * logBase2Result;
  
  return heightOfTree;
  
}
void solveTimeTabling() {
  int fitnessScoreBeforeMutation = 0, fitnessScoreAfterMutation = 0;
  
  // createPopulationsOfChromosome(sizeof(classList)/sizeof(Class));
  
  // crossover..
  // fitnessScoreAfterMutation = performMutation();
}