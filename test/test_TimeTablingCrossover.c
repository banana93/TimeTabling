#include "unity.h"
#include <stdio.h>
#include "TimeTabling.h"
#include "Node.h"
#include "RedBlackTree.h"
#include "ErrorCode.h"
#include "CustomAssertions.h"
#include "Rotations.h"
#include "InitNode.h"
#include "CException.h"

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

void test_crossoverToOffspring_should_copy_to_target_class(){
	fillInTheChromosome(classList, sizeof(classList)/sizeof(Class));
	
	int leftStop = 0;
	Class targetClass[sizeof(classList)/sizeof(Class)];
	clearClassList(sizeof(classList)/sizeof(Class), &targetClass);
	crossoverToOffspring((&class)[0][0][0], &targetClass, &leftStop);
	
	TEST_ASSERT_EQUAL(1, compareClass(class[0][0][0], targetClass[0]));
	TEST_ASSERT_EQUAL(0, leftStop);
}

void test_crossoverToOffspring_should_update_leftStop(){
	fillInTheChromosome(classList, sizeof(classList)/sizeof(Class));
	int leftStop = 0;
	Class targetClass[sizeof(classList)/sizeof(Class)];
	clearClassList(sizeof(classList)/sizeof(Class), &targetClass);
	targetClass[0] = copyClassSlot(class[0][0][0]);
	targetClass[1] = copyClassSlot(class[0][0][0]);
	
	crossoverToOffspring(&class[0][0][0], &targetClass,&leftStop);
	
	TEST_ASSERT_EQUAL(1, leftStop);
}


void test_performCrossover(){
	//declaration fixture of topFitness population, and randomize ClassList
	Class topFitness[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS];
	Class topFitness2[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS];
	Class testList[52];
	int topFitnessScore, topFitnessScore2;
	clearClassList(sizeof(testList)/sizeof(Class) , &testList);
	
	//randomizeClassList (assume this is top 1 fitness among the population)
	randomizeClassList(sizeof(testList)/sizeof(Class),&testList);
	clearClass(topFitness);
	fillInTheChromosomeWithReducingViolation(testList, sizeof(testList)/sizeof(Class));
	copyClass(class, topFitness);
 
	clearClass(class);
 
 	//randomizeClassList (assume this is top 2 fitness among the population)
	clearClassList(sizeof(testList)/sizeof(Class) , &testList);
	randomizeClassList(sizeof(testList)/sizeof(Class),&testList);
	clearClass(topFitness2);
	fillInTheChromosomeWithReducingViolation(testList, sizeof(testList)/sizeof(Class));
	copyClass(class, topFitness2);
	
	//record down fitness score of each
	topFitnessScore = calculateFitnessScore(topFitness);
	topFitnessScore2 = calculateFitnessScore(topFitness2);
	
	//offSpring result (class[][][])
	Class offSpring[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS];
	
	performCrossover(topFitness,topFitness2,&offSpring);
	TEST_ASSERT_EQUAL(sizeof(topFitness)/sizeof(Class), sizeof(offSpring)/sizeof(Class));
}

