#include "unity.h"
#include "TimeTabling.h"

void setUp(void){}

void tearDown(void){}

void test_checkPerspective_given_perspective_that_did_not_clash_it_should_print_out_no_clash(void)
{
	Perspective perspective1 = {.time = 9,
                             .venue = "D203",
                             .day = "Monday",
                             .subjectType = 'L',
                             .group = "RMB2",
                             .nameOfLecturer = "Poh TV"};
  
  Perspective perspective2 = {.time = 10,
                             .venue = "D203",
                             .day = "Monday",
                             .subjectType = 'L',
                             .group = "RMB3",
                             .nameOfLecturer = "Chan CK"};
  
  checkPerspective(&perspective1, &perspective2);
}

void test_checkPerspective_given_perspective_that_did_clash_it_should_print_out_error_message(void)
{
	Perspective perspective1 = {.time = 9,
                             .venue = "D203",
                             .day = "Monday",
                             .subjectType = 'L',
                             .group = "RMB2",
                             .nameOfLecturer = "Poh TV",
                             .subjectCode = "AAMP2000"};
  
  Perspective perspective2 = {.time = 9,
                             .venue = "D203",
                             .day = "Monday",
                             .subjectType = 'L',
                             .group = "RMB3",
                             .nameOfLecturer = "Chan CK",
                             .subjectCode = "AAMP2000"};
  
  checkPerspective(&perspective1, &perspective2);
}

void test_checkPerspective_given_different_subjectType_at_the_same_time_clash_it_should_print_out_error_message(void)
{
	Perspective perspective1 = {.time = 9,
                             .venue = "D203",
                             .day = "Monday",
                             .subjectType = 'L',
                             .group = "RMB2",
                             .nameOfLecturer = "Poh TV",
                             .subjectCode = "AAMP2000"};
  
  Perspective perspective2 = {.time = 9,
                             .venue = "D203",
                             .day = "Monday",
                             .subjectType = 'P',
                             .group = "RMB3",
                             .nameOfLecturer = "Poh TV",
                             .subjectCode = "AAMP2000"};
  
  checkPerspective(&perspective1, &perspective2);
}

void test_checkPerspective_given_different_subjectCode_at_the_same_time_and_same_group_clash_it_should_print_out_error_message(void)
{
	Perspective perspective1 = {.time = 9,
                             .venue = "D203",
                             .day = "Monday",
                             .subjectType = 'L',
                             .group = "RMB2",
                             .nameOfLecturer = "Poh TV",
                             .subjectCode = "AAMP2000"};
  
  Perspective perspective2 = {.time = 9,
                             .venue = "D203",
                             .day = "Monday",
                             .subjectType = 'L',
                             .group = "RMB2",
                             .nameOfLecturer = "Poh TV",
                             .subjectCode = "AAMP2001"};
  
  checkPerspective(&perspective1, &perspective2);
}

void test_checkPerspective_given_different_subjectCode_and_different_group_at_the_same_time_clash_it_should_print_out_error_message(void)
{
	Perspective perspective1 = {.time = 9,
                             .venue = "D203",
                             .day = "Monday",
                             .subjectType = 'L',
                             .group = "RMB2",
                             .nameOfLecturer = "Poh TV",
                             .subjectCode = "AAMP2000"};
  
  Perspective perspective2 = {.time = 9,
                             .venue = "D203",
                             .day = "Monday",
                             .subjectType = 'L',
                             .group = "RMB3",
                             .nameOfLecturer = "Poh TV",
                             .subjectCode = "AAMP2001"};
  
  checkPerspective(&perspective1, &perspective2);
}