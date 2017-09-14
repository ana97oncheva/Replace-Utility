// replace.h: Interface of replace utility
////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// replace command line                                                       //
//                                                                            //
// Authors: Islam Abdeen                                                      //
//                                                                            //
// E-mail:  engehassan@gmail.com                                              //
//																			  //
// DT	7/9/2017 10:00: PM                                                    //
// -------------------------------------------------------------------------- //
//                                                                            //
// Permission to use, copy, modify, and distribute this software for any      //
// purpose and without fee is hereby granted. This is no guarantee about the  //
// use of this software. For any comments, bugs or thanks, please email us.   //
//                                                                            //
// -------------------------------------------------------------------------- //
//                                                                            //
// Targeted Platform: UNIX-LIKE and Windos systems    			              //
// Programming Language: ANCI C99                                             //
// Compiled with:     gcc version 4.9.2                                       //
//                                                                            //
// Last modification: September 2017                                          //
//                                                                            //
// History:                                                                   //
//                                                                            //
// 1- First release of this file.                                             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#ifndef REPLACE_H
#define REPLACE_H

#define LENTH_OF_FILE 20

/* Include Files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Preprocessor */
#define NO_OF_CHARS 256

/* Functions Prototype */
void PrintUsageMsg();
int PrintInvalidOptionMsg();
void Create_Bad_Match_Table(char *pPattern, int iSize, char iBadMatchArr[NO_OF_CHARS]);
int SearchPattern_BoyerMooreAlgorithm(char *pPatternStr, unsigned long ulPatternStrLen, char *buffer, char BadMatchArr[]);
char * replace(char *pPatternStr, unsigned long ulPatternStrLen, char *pCompensatedStr, unsigned long ulCompensatedStrLen, char *buffer, unsigned long ulBufferSize, char BadMatchArr[]);

#endif // REPLACE_H 

