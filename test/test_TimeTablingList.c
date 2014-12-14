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
