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
	
	int leftStop = 0;
	Class targetClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS];
	clearClass(targetClass);
	
	crossoverToOffspring((&classList)[0], &targetClass, 0, 0, 0, &leftStop);
	
	TEST_ASSERT_EQUAL(1, compareClass(classList[0], targetClass[0][0][0]));
	TEST_ASSERT_EQUAL(0, leftStop);
}

void test_crossoverToOffspring_should_not_copy_and_update_leftStop(){
	int leftStop = 0;
	Class targetClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS];
	clearClass(targetClass);
	
	targetClass[0][0][0] = copyClassSlot(classList[0]);
	targetClass[0][0][1] = copyClassSlot(classList[0]);
	
	crossoverToOffspring((&classList)[0], &targetClass, 0, 0, 2, &leftStop);
	
	TEST_ASSERT_EQUAL(1, compareClass(classList[0], targetClass[0][0][0]));
	TEST_ASSERT_EQUAL(1, compareClass(classList[0], targetClass[0][0][1]));
	TEST_ASSERT_EQUAL(0, compareClass(classList[0], targetClass[0][0][2]));
	TEST_ASSERT_EQUAL(1, leftStop);
}



void test_performCrossover_should_fill_in_offSpring(){
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
	
	
	// int i,retLoopVenue = 0, retLoopDay = 0, retLoopTime = 0;
	// for( i = 0 ; i < (MAX_VENUE*MAX_DAY*MAX_TIME_SLOTS) ; i++){
			// printf("%d : ",i+1);
		// if(offSpring[retLoopVenue][retLoopDay][retLoopTime].course != NULL){
			// printf("%s\n",offSpring[retLoopVenue][retLoopDay][retLoopTime].course ->courseName);
		// }
		// else
			// printf("no class, whahha\n");
		// indexForward(&retLoopVenue,&retLoopDay,&retLoopTime);	
	// }
}
