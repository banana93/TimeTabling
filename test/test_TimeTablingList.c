#include "unity.h"
#include <stdio.h>
#include "TimeTabling.h"
#include "ErrorCode.h"
#include "CException.h"

void setUp(void){
	int venue = 0;
  int day = 0, time = 0;
	int i;
  
  for(venue = 0; venue < MAX_VENUE; venue++) {
    for(day = 0; day < MAX_DAY; day++) {
      for(time = 0; time < MAX_TIME_SLOTS; time++) {
				class[venue][day][time].lecturer = NULL;
				class[venue][day][time].course = NULL;
				class[venue][day][time].typeOfClass = 0;
				for(i = 0 ; i < 5 ; i++){
					class[venue][day][time].group[i] = NULL;
				}
			}
		}
	}
}

void tearDown(void){}

void test_fillInTheChromosome_should_throw_when_list_oversized(){

	Class list[100];
	CEXCEPTION_T e;
	
	Try{
	fillInTheChromosome(list, sizeof(list)/sizeof(Class));}
	Catch(e){
		TEST_ASSERT_EQUAL(ERR_EXCEEDED_INDEX,e);
	}
	
}

void test_fillInTheChromosomeWithReducingViolation_should_less_violation_than_normal_fillInTheChromosome(){
	int normalFill, reducedViolationFill;
	int compare;
	
	fillInTheChromosome(classList, sizeof(classList)/sizeof(Class));
	normalFill = calculateFitnessScore(class);
	
	setUp();
	
	fillInTheChromosomeWithReducingViolation(classList, sizeof(classList)/sizeof(Class));
	reducedViolationFill = calculateFitnessScore(class);
	
	// proofed that fillInTheChromosomeWithReducingViolation is better
	if( normalFill > reducedViolationFill)
		compare = 1;
	else
		compare = 0;
	 
	TEST_ASSERT_EQUAL(1 , compare);
}

void test_fillInTheChromosomeWithReducingViolation_should_throw_when_list_oversized(){
	Class list[100];
	CEXCEPTION_T e;
	
	Try{
	fillInTheChromosomeWithReducingViolation(list, sizeof(list)/sizeof(Class));}
	Catch(e){
		TEST_ASSERT_EQUAL(ERR_EXCEEDED_INDEX,e);
	}
	
}

void test_copyClassSlot_should_able_to_copy_1_class_to_another(){

	Class testClass;
	
	testClass = copyClassSlot(classList[0]);

	TEST_ASSERT_EQUAL_PTR( classList[0].course, testClass.course);
	TEST_ASSERT_EQUAL_PTR( classList[0].lecturer, testClass.lecturer);
	TEST_ASSERT_EQUAL_PTR( classList[0].group[0], testClass.group[0]);
	TEST_ASSERT_EQUAL_PTR( classList[0].group[1], testClass.group[1]);
	TEST_ASSERT_EQUAL_PTR( classList[0].group[2], testClass.group[2]);
	TEST_ASSERT_EQUAL_PTR( classList[0].group[3], testClass.group[3]);
	TEST_ASSERT_EQUAL_PTR( classList[0].group[4], testClass.group[4]);
	TEST_ASSERT_EQUAL( classList[0].typeOfClass, testClass.typeOfClass);
	
}

void test_copyClass_should_able_to_copy_entire_class(){
	fillInTheChromosome(classList, sizeof(classList)/sizeof(Class));
	copyClass(class,populationOfClasses[0].class);
	
	TEST_ASSERT_EQUAL_PTR(class[0][0][0].course, populationOfClasses[0].class[0][0][0].course);
	TEST_ASSERT_EQUAL_PTR(class[0][0][0].lecturer, populationOfClasses[0].class[0][0][0].lecturer);
	TEST_ASSERT_EQUAL(class[0][0][0].typeOfClass, populationOfClasses[0].class[0][0][0].typeOfClass);	
	TEST_ASSERT_EQUAL_PTR(class[1][2][3].course, populationOfClasses[0].class[1][2][3].course);
	TEST_ASSERT_EQUAL_PTR(class[1][2][3].lecturer, populationOfClasses[0].class[1][2][3].lecturer);
	TEST_ASSERT_EQUAL(class[1][2][3].typeOfClass, populationOfClasses[0].class[1][2][3].typeOfClass);
}

void test_clearClassSlot_should_able_to_remove_elements(){

	Class testClass;
	
	testClass = copyClassSlot(classList[0]);
	testClass = clearClassSlot(testClass);
	TEST_ASSERT_EQUAL_PTR( NULL, testClass.course);
	TEST_ASSERT_EQUAL_PTR( NULL, testClass.lecturer);
	TEST_ASSERT_EQUAL_PTR( NULL, testClass.group[0]);
	TEST_ASSERT_EQUAL_PTR( NULL, testClass.group[1]);
	TEST_ASSERT_EQUAL_PTR( NULL, testClass.group[2]);
	TEST_ASSERT_EQUAL_PTR( NULL, testClass.group[3]);
	TEST_ASSERT_EQUAL_PTR( NULL, testClass.group[4]);
	TEST_ASSERT_EQUAL( 0, testClass.typeOfClass);
	
}

void test_clearClass_should_able_to_remove_elements(){
	fillInTheChromosome(classList, sizeof(classList)/sizeof(Class));
	clearClass(class);
	
	TEST_ASSERT_EQUAL_PTR( NULL, class[0][0][0].course);
	TEST_ASSERT_EQUAL_PTR( NULL, class[0][0][0].lecturer);
	TEST_ASSERT_EQUAL_PTR( NULL, class[0][0][0].group[0]);
	TEST_ASSERT_EQUAL_PTR( NULL, class[0][0][0].group[1]);
	TEST_ASSERT_EQUAL_PTR( NULL, class[0][0][0].group[2]);
	TEST_ASSERT_EQUAL_PTR( NULL, class[0][0][0].group[3]);
	TEST_ASSERT_EQUAL_PTR( NULL, class[0][0][0].group[4]);
	TEST_ASSERT_EQUAL( 0, class[0][0][0].typeOfClass);
	
}


void test_randomizeClassList_can_create_newList(){
 Class testList[52];
 clearClassList(sizeof(testList)/sizeof(Class) , testList);
 randomizeClassList(sizeof(testList)/sizeof(Class),testList);

TEST_ASSERT_NOT_NULL(testList[0].course );
 

}

void test_createPopulationOfChromosome(){
	int i;
	
	clearPopulation(populationOfClasses);
	createPopulationsOfChromosome(sizeof(classList)/sizeof(Class));

	TEST_ASSERT_NOT_NULL(populationOfClasses[0].class[0][0][0].course);

	TEST_ASSERT_EQUAL(populationOfClasses[0].violation , calculateFitnessScore(populationOfClasses[0].class));
}

void test_copyPopulation_should_copy_population_over(){
	int i;
	clearPopulation(populationOfClasses);
	createPopulationsOfChromosome(sizeof(classList)/sizeof(Class));
	
	Population resultPop = copyPopulation(populationOfClasses[0]);
	
	TEST_ASSERT_EQUAL(populationOfClasses[0].violation, resultPop.violation);
	
}

void test_sortPopulationsAccordingToFitness_should_swap_population_fitness_in_ascending_order(){
	clearPopulation(populationOfClasses);
	int pop0Violation, pop1Violation;
	Population pop[2];
	
	fillInTheChromosome(classList, sizeof(classList)/sizeof(Class));
	copyClass(class, pop[0].class);
	pop[0].violation = calculateFitnessScore(pop[0].class);
	pop0Violation = pop[0].violation;
	
	clearClass(class);
	
	fillInTheChromosomeWithReducingViolation(classList, sizeof(classList)/sizeof(Class));
	copyClass(class, pop[1].class);
	pop[1].violation = calculateFitnessScore(pop[1].class);
	pop1Violation = pop[1].violation;
	clearClass(class);
	
	sortPopulationsAccordingToFitness(pop, sizeof(pop)/sizeof(Population));
	
	TEST_ASSERT_EQUAL(pop1Violation, pop[0].violation);
	TEST_ASSERT_EQUAL(pop0Violation, pop[1].violation);
	
}


void test_sortPopulationsAccordingToFitness_should_sort_fitness_in_ascending_order(){
	int i, compareResult;
	clearPopulation(populationOfClasses);
	createPopulationsOfChromosome(sizeof(classList)/sizeof(Class));
	
	sortPopulationsAccordingToFitness(populationOfClasses, sizeof(populationOfClasses)/sizeof(Population));
	
	for(i= 0 ; i+1 < sizeof(populationOfClasses)/sizeof(Population) ; i++){
		if(populationOfClasses[i].violation <= populationOfClasses[i+1].violation)
			compareResult = 1;
		else
			compareResult = 0;
			
			TEST_ASSERT_EQUAL(1, compareResult);
	}
}
	
void test_compareClass_should_return_1_if_all_elements_are_same(){
	Class test = classList[0];
	Class test1 = classList[0];

	TEST_ASSERT_EQUAL(1, compareClass(test,test1));
}

void test_compareClass_should_return_0_if_one_elements_not_same(){
	Class test = classList[0];
	Class test1 = classList[0];
	test1.lecturer = &lecturer[2];

	TEST_ASSERT_EQUAL(0, compareClass(test,test1));
}


