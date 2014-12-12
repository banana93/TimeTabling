#ifndef TimeTablingClassList_H
#define TimeTablingClassList_H
#include <stdio.h>
#include "Node.h"
#include "RedBlackTree.h"
#include "ErrorCode.h"
#include "CustomAssertions.h"
#include "Rotations.h"
#include "InitNode.h"
#include "TimeTabling.h"


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
                     .groupSize = 16},
                     
                    {.groupName = "F2",
                     .groupSize = 17},
                    
                    {.groupName = "F3",
                     .groupSize = 26},
                    
                    {.groupName = "G2",
                     .groupSize = 22},
                    
                    {.groupName = "G3",
                     .groupSize = 12},
                     
                    {.groupName = "H2",
                     .groupSize = 10},
                    
                    {.groupName = "H3",
                     .groupSize = 11},
                    
                    {.groupName = "I2",
                     .groupSize = 19},
                    
                    {.groupName = "I3",
                     .groupSize = 20},
                    
                    {.groupName = "J2",
                     .groupSize = 27},
                    
                    {.groupName = "J3",
                     .groupSize = 30}  
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
                             .group[0] = &group[0],
                             .group[1] = &group[1],
                             .group[2] = NULL},
                            
                            {.programmeName = "RMB3",
                             .group[2] = &group[2],
                             .group[3] = &group[3],
                             .group[4] = NULL},
                             
                            {.programmeName = "RMM2",
                             .group[4] = &group[4],
                             .group[5] = &group[5],
                             .group[6] = NULL},
                             
                            {.programmeName = "RMM3",
                             .group[6] = &group[6],
                             .group[7] = &group[7],
                             .group[8] = NULL},
                            
                            {.programmeName = "RMS2",
                             .group[8] = &group[8],
                             .group[9] = &group[9],
                             .group[10] = NULL},
                            
                            {.programmeName = "RMS3",
                             .group[10] = &group[10],
                             .group[11] = &group[11],
                             .group[12] = NULL},
                            
                            {.programmeName = "RMT2",
                             .group[12] = &group[12],
                             .group[13] = &group[13],
                             .group[14] = NULL},
                            
                            {.programmeName = "RMT3",
                             .group[14] = &group[14],
                             .group[15] = &group [15],
                             .group[16] = NULL},
                            
                            {.programmeName = "RMA2",
                             .group[16] = &group[16],
                             .group[17] = &group[17],
                             .group[18] = NULL},
                            
                            {.programmeName = "RMA3",
                             .group[18] = &group[18],
                             .group[19] = &group[19],
                             .group[20] = NULL}
                          };
                      
  Course course[] = { {.courseCode = "AAMP2041",
                       .courseName = "Mathematics",
                       .hoursOfLecture = 2,
                       .hoursOfTutorial = 1,
                       .hoursOfPractical = 2,
                       .programme[0] = &programme[0],
                       .programme[1] = &programme[1],
                       .sizeOfProgramme = 20},
                       
                      {.courseCode = "AAMB2034",
                       .courseName = "English",
                       .hoursOfLecture = 2,
                       .hoursOfTutorial = 1,
                       .hoursOfPractical = 0,
                       .programme[2] = &programme[2],
                       .programme[3] = &programme[3],
                       .sizeOfProgramme = 30},
                       
                      {.courseCode = "ABMC1045",
                       .courseName = "History",
                       .hoursOfLecture = 2,
                       .hoursOfTutorial = 1,
                       .hoursOfPractical = 0,
                       .programme[4] = &programme[4],
                       .programme[5] = &programme[5],
                       .sizeOfProgramme = 15},
                      
                      {.courseCode = "ABCD1234",
                       .courseName = "Add Maths",
                       .hoursOfLecture = 2,
                       .hoursOfTutorial = 1,
                       .hoursOfPractical = 0,
                       .programme[6] = &programme[6],
                       .programme[7] = &programme[7],
                       .sizeOfProgramme = 30},
                       
                      {.courseCode = "AAMP1034",
                       .courseName = "Test Driven Development",
                       .hoursOfLecture = 2,
                       .hoursOfTutorial = 2,
                       .hoursOfPractical = 2,
                       .programme[8] = &programme[8],
                       .programme[9] = &programme[9],
                       .sizeOfProgramme = 10},
                       
                      {.courseCode = "EFGH5656",
                       .courseName = "Electromagnetics",
                       .hoursOfLecture = 2,
                       .hoursOfTutorial = 1,
                       .hoursOfPractical = 2,
                       .programme[10] = &programme[10],
                       .programme[11] = &programme[11],
                       .sizeOfProgramme = 20},
                       
                      {.courseCode = "JDHS5839",
                       .courseName = "FPGA and ASIC Design",
                       .hoursOfLecture = 2,
                       .hoursOfTutorial = 1,
                       .hoursOfPractical = 2,
                       .programme[12] = &programme[12],
                       .programme[13] = &programme[13],
                       .sizeOfProgramme = 24},
                       
                      {.courseCode = "UWQI8912",
                       .courseName = "Engineering Mathematics I",
                       .hoursOfLecture = 2,
                       .hoursOfTutorial = 1,
                       .hoursOfPractical = 0,
                       .programme[14] = &programme[14],
                       .programme[15] = &programme[15],
                       .sizeOfProgramme = 15},
                       
                      {.courseCode = "IQJD1875",
                       .courseName = "Tamadun Islam",
                       .hoursOfLecture = 2,
                       .hoursOfTutorial = 1,
                       .hoursOfPractical = 0,
                       .programme[16] = &programme[16],
                       .programme[17] = &programme[17],
                       .sizeOfProgramme = 33},
                       
                      {.courseCode = "ZXCV8787",
                       .courseName = "Pendidikan Moral",
                       .hoursOfLecture = 2,
                       .hoursOfTutorial = 1,
                       .hoursOfPractical = 0,
                       .programme[18] = &programme[18],
                       .programme[19] = &programme[19],
                       .sizeOfProgramme = 32}
                    };
										
	
#endif // TimeTablingClassList_H
