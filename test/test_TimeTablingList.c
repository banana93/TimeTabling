#include "unity.h"
#include <stdio.h>
#include "TimeTabling.h"
#include "Node.h"
#include "RedBlackTree.h"
#include "ErrorCode.h"
#include "CustomAssertions.h"
#include "Rotations.h"
#include "InitNode.h"

Node node1, node2, node3, node4, node5, node6, node7, node8, node9, node10, node11, node12, node13, node15, node17, node18, node20, node30;

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
				class[venue][day][time].classNode = NULL;
				for(i = 0 ; i < 5 ; i++){
					class[venue][day][time].group[i] = NULL;
				}
			}
		}
	}
}

void tearDown(void){}

void test_fillInTheChromosomeWithReducingViolation_should_less_violation_than_normal_fillInTheChromosome(){
	int normalFill, reducedViolationFill;
	
	fillInTheChromosome(classList, sizeof(classList)/sizeof(Class));
	normalFill = calculateFitnessScore(class);
	
	setUp();
	
	fillInTheChromosomeWithReducingViolation(classList, sizeof(classList)/sizeof(Class));
	reducedViolationFill = calculateFitnessScore(class);
	
	//proofed that fillInTheChromosomeWithReducingViolation is better
	TEST_ASSERT_EQUAL(309 , normalFill);
	TEST_ASSERT_EQUAL(171, reducedViolationFill);
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
 clearClassList(sizeof(testList)/sizeof(Class) , &testList);
 randomizeClassList(sizeof(testList)/sizeof(Class),&testList);

TEST_ASSERT_NOT_NULL(testList[0].course );
 

}

void test_createPopulationOfChromosome(){

	createPopulationsOfChromosome(sizeof(classList)/sizeof(Class));
	int venue = 0, day = 0, time = 0, i;
	
	for(venue = 0; venue < MAX_VENUE; venue++){
		for(day = 0; day < MAX_DAY; day++) {
			for(time = 0; time < MAX_TIME_SLOTS; time++) {
				printf("lecturer name: %c\n", populationOfClasses[0].class[venue][day][time].typeOfClass);
			}
		}
	}
}
