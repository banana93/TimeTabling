#include "unity.h"
#include <stdio.h>
#include "LinkedList.h"
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
				for(i = 0 ; i < 5 ; i++){
					class[venue][day][time].group[i] = NULL;
				}
			}
		}
	}
}

void tearDown(void){}

void test_addLinkedList_should_able_to_add_data_into_list(){
	Item data;
	LinkedList *list = create_linkedList();
	
	Population population;
	fillInTheChromosomeWithReducingViolation(classList, sizeof(classList)/sizeof(Class));
	copyClass(class,population.class);
	population.violation = calculateFitnessScore(population.class);
	
	data.next = NULL;
	data.population = &population;
	
	addLinkedList(list, &data);
	
	TEST_ASSERT_NOT_NULL(list->head);
	TEST_ASSERT_NOT_NULL(list->tail);
	TEST_ASSERT_EQUAL_PTR(&population, list->head->population);
	TEST_ASSERT_EQUAL_PTR(&population, list->tail->population);
	TEST_ASSERT_NULL(list->head->next);
}

void test_addLinkedList_should_able_to_add_2data_into_list(){
	Item data, data2;
	LinkedList *list = create_linkedList();
	
	Population population, population2;
	fillInTheChromosome(classList, sizeof(classList)/sizeof(Class));
	copyClass(class,population.class);
	population.violation = calculateFitnessScore(population.class);
	
	data.next = NULL;
	data.population = &population;
	
	addLinkedList(list, &data);
	
	clearClass(class);
	fillInTheChromosomeWithReducingViolation(classList, sizeof(classList)/sizeof(Class));
	copyClass(class,population2.class);
	population2.violation = calculateFitnessScore(population2.class);
	
	data2.next = NULL;
	data2.population = &population2;
	
	addLinkedList(list, &data2);
	
	TEST_ASSERT_NOT_NULL(list->head);
	TEST_ASSERT_NOT_NULL(list->tail);
	TEST_ASSERT_EQUAL_PTR(&population, list->head->population);
	TEST_ASSERT_EQUAL_PTR(&population2, list->head->next->population);
	TEST_ASSERT_EQUAL_PTR(&population2, list->tail->population);

}

void test_addLinkedList_should_able_to_add_3data_into_list(){
	Item data, data2,data3;
	Population population, population2,population3;
	
	LinkedList *list = create_linkedList();
	fillInTheChromosome(classList, sizeof(classList)/sizeof(Class));
	copyClass(class,population.class);
	population.violation = calculateFitnessScore(population.class);
	
	data.next = NULL;
	data.population = &population;
	
	addLinkedList(list, &data);
	
	clearClass(class);
	fillInTheChromosomeWithReducingViolation(classList, sizeof(classList)/sizeof(Class));
	copyClass(class,population2.class);
	population2.violation = calculateFitnessScore(population2.class);
	
	data2.next = NULL;
	data2.population = &population2;
	
	addLinkedList(list, &data2);
	population3.violation = 100;
	
	data3.next = NULL;
	data3.population = &population3;
	
	addLinkedList(list, &data3);
	
	
	TEST_ASSERT_NOT_NULL(list->head);
	TEST_ASSERT_NOT_NULL(list->tail);
	TEST_ASSERT_EQUAL_PTR(&population, list->head->population);
	TEST_ASSERT_EQUAL_PTR(&population2, list->head->next->population);
	TEST_ASSERT_EQUAL_PTR(&population3, list->tail->population);

}

void test_removeFromHeadLinkedList_should_able_to_remove_into_list(){
	Item data, *populationReturn;
	LinkedList *list = create_linkedList();
	
	Population population;
	fillInTheChromosomeWithReducingViolation(classList, sizeof(classList)/sizeof(Class));
	copyClass(class,population.class);
	population.violation = calculateFitnessScore(population.class);
	
	data.next = NULL;
	data.population = &population;
	
	addLinkedList(list, &data);
	
	populationReturn = removeFromHeadLinkedList(list);
	
	TEST_ASSERT_EQUAL_PTR(&population, populationReturn->population);
}

void test_removeFromHeadLinkedList_should_able_to_remove3_into_list(){
	Item data, data2,data3, *populationReturn1, *populationReturn2, *populationReturn3;
	Population population, population2,population3;
	
	LinkedList *list = create_linkedList();
	fillInTheChromosome(classList, sizeof(classList)/sizeof(Class));
	copyClass(class,population.class);
	population.violation = calculateFitnessScore(population.class);
	
	data.next = NULL;
	data.population = &population;
	
	addLinkedList(list, &data);
	
	clearClass(class);
	fillInTheChromosomeWithReducingViolation(classList, sizeof(classList)/sizeof(Class));
	copyClass(class,population2.class);
	population2.violation = calculateFitnessScore(population2.class);
	
	data2.next = NULL;
	data2.population = &population2;
	
	addLinkedList(list, &data2);
	population3.violation = 100;
	
	data3.next = NULL;
	data3.population = &population3;
	
	addLinkedList(list, &data3);
	
	
	populationReturn1 = removeFromHeadLinkedList(list);
	populationReturn2 = removeFromHeadLinkedList(list);
	populationReturn3 = removeFromHeadLinkedList(list);
	
	TEST_ASSERT_EQUAL_PTR(&population, populationReturn1->population);
	TEST_ASSERT_EQUAL_PTR(&population2, populationReturn2->population);
	TEST_ASSERT_EQUAL_PTR(&population3, populationReturn3->population);
}
