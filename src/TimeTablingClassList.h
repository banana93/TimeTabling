#ifndef TimeTablingClassList_H
#define TimeTablingClassList_H
#include <stdio.h>
#include "Node.h"
#include "RedBlackTree.h"
#include "ErrorCode.h"
#include "CustomAssertions.h"
#include "Rotations.h"
#include "InitNode.h"


  Group group[] = { {.groupName = "A2",
                     .groupSize = 10},
                     
                    {.groupName = "A3",
                     .groupSize = 13},
                     
                    {.groupName = "K2",
                     .groupSize = 20},
                     
                    {.groupName = "K3",
                     .groupSize = 50},
                    
                    {.groupName = "B2",
                     .groupSize = 34},
                     
                    {.groupName = "B3",
                     .groupSize = 25},
                     
                    {.groupName = "C2",
                     .groupSize = 14},
                    
                    {.groupName = "D2",
                     .groupSize = 20},
                     
                    {.groupName = "E2",
                     .groupSize = 13},
                     
                    {.groupName = "E3",
                     .groupSize = 16}
                    
                  };
                 
  Venue venue[] = { {.nameOfVenue = "D203",
                     .sizeOfVenue = 40},
                     
                    {.nameOfVenue = "D300",
                     .sizeOfVenue = 25},
                     
                    {.nameOfVenue = "D204",
                     .sizeOfVenue = 30},
                     
                    {.nameOfVenue = "D301",
                     .sizeOfVenue = 25}
                  };
                  
  Lecturer lecturer[] = { {.lecturerName = "Poh TV",
                           .department = "FASC"},
                           
                          {.lecturerName = "Chan CK",
                           .department = "FASC"},
                          
                          {.lecturerName = "Chiu VT",
                           .department = "TR"},
                           
                          {.lecturerName = "Jackson TKS",
                           .department = "HSSchool"},
                          
                          {.lecturerName = "Cheah SL",
                           .department = "FABS"},
                          
                          {.lecturerName = "Wong YY",
                           .department = "FBUS"},
                          
                          {.lecturerName = "Wong KH",
                           .department = "Char Kuey Teow"},
                           
                          {.lecturerName = "VT Chiu",
                           .department = "Gay School"},
                           
                          {.lecturerName = "Low TH",
                           .department = "SH"},
                           
                          {.lecturerName = "Lai JY",
                           .department = "FHGU"}
                        };
                        
  Programme programme[] = { {.programmeName = "RMB2",
                             &group[0]},
                            
                            {.programmeName = "RMB3",
                             &group[1]},
                             
                            {.programmeName = "RMM2",
                             &group[2]},
                             
                            {.programmeName = "RMM3",
                             &group[3]},
                            
                            {.programmeName = "RMS2",
                             &group[4]},
                            
                            {.programmeName = "RMS3",
                             &group[5]},
                            
                            {.programmeName = "RMT2",
                             &group[6]},
                            
                            {.programmeName = "RMT3",
                             &group[7]},
                            
                            {.programmeName = "RMA2",
                             &group[8]},
                            
                            {.programmeName = "RMA3",
                             &group[9]}
                          };
                      
  Course course[] = { {.courseCode = "AAMP2041",
                       .courseName = "Mathematics",
                       .hoursOfLecture = 2,
                       .hoursOfTutorial = 1,
                       .hoursOfPractical = 2,
                       &programme[0],
                       .sizeOfProgramme = 20},
                       
                      {.courseCode = "AAMB2034",
                       .courseName = "English",
                       .hoursOfLecture = 2,
                       .hoursOfTutorial = 1,
                       .hoursOfPractical = 0,
                       &programme[1],
                       .sizeOfProgramme = 30},
                       
                      {.courseCode = "ABMC1045",
                       .courseName = "History",
                       .hoursOfLecture = 2,
                       .hoursOfTutorial = 1,
                       .hoursOfPractical = 0,
                       &programme[2],
                       .sizeOfProgramme = 15},
                      
                      {.courseCode = "ABCD1234",
                       .courseName = "Add Maths",
                       .hoursOfLecture = 2,
                       .hoursOfTutorial = 1,
                       .hoursOfPractical = 0,
                       &programme[3],
                       .sizeOfProgramme = 30},
                       
                      {.courseCode = "AAMP1034",
                       .courseName = "Test Driven Development",
                       .hoursOfLecture = 2,
                       .hoursOfTutorial = 2,
                       .hoursOfPractical = 2,
                       &programme[4],
                       .sizeOfProgramme = 10},
                       
                      {.courseCode = "EFGH5656",
                       .courseName = "Electromagnetics",
                       .hoursOfLecture = 2,
                       .hoursOfTutorial = 1,
                       .hoursOfPractical = 2,
                       &programme[5],
                       .sizeOfProgramme = 20},
                       
                      {.courseCode = "JDHS5839",
                       .courseName = "FPGA and ASIC Design",
                       .hoursOfLecture = 2,
                       .hoursOfTutorial = 1,
                       .hoursOfPractical = 2,
                       &programme[6],
                       .sizeOfProgramme = 24},
                       
                      {.courseCode = "UWQI8912",
                       .courseName = "Engineering Mathematics I",
                       .hoursOfLecture = 2,
                       .hoursOfTutorial = 1,
                       .hoursOfPractical = 0,
                       &programme[7],
                       .sizeOfProgramme = 15},
                       
                      {.courseCode = "IQJD1875",
                       .courseName = "Tamadun Islam",
                       .hoursOfLecture = 2,
                       .hoursOfTutorial = 1,
                       .hoursOfPractical = 0,
                       &programme[8],
                       .sizeOfProgramme = 33},
                       
                      {.courseCode = "ZXCV8787",
                       .courseName = "Pendidikan Moral",
                       .hoursOfLecture = 2,
                       .hoursOfTutorial = 1,
                       .hoursOfPractical = 0,
                       &programme[9],
                       .sizeOfProgramme = 32}
                    };
										
	
#endif // TimeTablingClassList_H
