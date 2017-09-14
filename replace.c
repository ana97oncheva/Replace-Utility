// replace.c: Implementation of replace utility
////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// replace command line based on Boyer Moore's Algorithm                      //
//                                                                            //
// Authors: Islam Abdeen                                                      //
//                                                                            //
// E-mail:  engehassan@gmail.com                                              //
//																			  //
// DT	8/9/2017 1:00: AM                                                     //
// -------------------------------------------------------------------------- //
//                                                                            //
// Permission to use, copy, modify, and distribute this software for any      //
// purpose and without fee is hereby granted. This is no guarantee about the  //
// use of this software. For any comments, bugs or thanks, please email us.   //
//                                                                            //
// -------------------------------------------------------------------------- //
//                                                                            //
// Targeted Platform: UNIX-LIKE and Windos systems    			              //
// Programming Language: ANSI C99                                             //
// Compiled with:     gcc version 4.9.2                                       //
//                                                                            //
// Last modification: September 2017                                          //
//                                                                            //
// History:                                                                   //
//                                                                            //
// 1- First release of this file.                                             //
//																			  //
// Notes: 1- This project needs some optimization and modularity              //
//        2- Debugging techniques hasn't imp lamented yet 					  //
//		  3- print to user number of match                                    //
//        4- Please read the ReadMe file          	                          //
////////////////////////////////////////////////////////////////////////////////

/* Include Files */
#include "replace.h"

/* Global Data */
char optionsArr[4] = {0};  // first index--> -b   second index--> -f   third index--> -l    fourth index--> -i

/*! PrintUsageMsg()
\fn Print usages for replace command
\param none
\return none
\pre none
\post none
\author Islam Abdeen
\DT	8/9/2017 1:00: AM
*/
void PrintUsageMsg()
{
    fprintf (stderr, "Usage:\n");
    fprintf (stderr, "        replace OPT <from> <to> -- <filename> [<filename>]*\n\n");

    fprintf (stderr, "Options:\n");
    fprintf (stderr, "        -b    Creates a backup copy of each file before modifying\n");
    fprintf (stderr, "        -f    Replaces only the first occurrence of string in each file\n");
    fprintf (stderr, "        -l    Replaces only the last occurrence of string in each file\n");
    fprintf (stderr, "        -i    Search for string from in a case insensitive way\n");

}

/*! PrintInvalidOptionMsg()
\fn Show to user that option(s) which entered are invalid
\param none
\return none
\pre none
\post none
\author Islam Abdeen
\DT	8/9/2017 1:00: AM
*/
int PrintInvalidOptionMsg()
{
    fprintf (stderr, "Invalid Option:\n");
    fprintf (stderr, "Try 'replace --help' for more information.\n");
    fprintf (stderr, "        replace OPT <from> <to> -- <filename> [<filename>]*\n\n");

    return 1;
}

/*! Create_Bad_Match_Table()
\fn The preprocessing function for Boyer Moore's which create bad match table
\param none
\return none
\pre none
\post none
\author Islam Abdeen
\DT	8/9/2017 1:00: AM
*/
void Create_Bad_Match_Table(char *pPattern, int iSize, char iBadMatchArr[NO_OF_CHARS])
{
    int iIndex;

    // Initialize all Values as -1
    for (iIndex = 0; iIndex < NO_OF_CHARS; iIndex++)
        iBadMatchArr[iIndex] = -1;

	if(optionsArr[3] == 0) // case sensetive
	{
		// Fill the value for each character based on formula: Value = Length - Index - 1
		for (iIndex = 0; iIndex < iSize; iIndex++)
			iBadMatchArr[(int)pPattern[iIndex]] = iSize - iIndex - 1;

		iBadMatchArr[(int)pPattern[iSize - 1]] = iSize -1; // set last element in bad match tbale always to the length of pattern
	}	
	else // not case sensetive
	{
		// Fill the value for each character based on formula: Value = Length - Index - 1
		for (iIndex = 0; iIndex < iSize; iIndex++)
		{
			iBadMatchArr[(int)pPattern[iIndex]] = iSize - iIndex - 1;
			
			if(pPattern[iIndex] >= 97 && pPattern[iIndex] <= 122)  // a~z
			{
				iBadMatchArr[(int)pPattern[iIndex] - 32] = iSize - iIndex - 1;				
			}
			else if(pPattern[iIndex] >= 65 && pPattern[iIndex] <= 90)
			{
				iBadMatchArr[(int)pPattern[iIndex] + 32] = iSize - iIndex - 1;
			}
			
		}

		iBadMatchArr[(int)pPattern[iSize - 1]] = iSize -1; // set last element in bad match tbale always to the length of pattern	
		
		if(pPattern[iIndex] >= 97 && pPattern[iIndex] <= 122)			
			iBadMatchArr[(int)pPattern[iSize - 1] - 32] = iSize -1; // set last element in bad match tbale always to the length of pattern	
		
		else if(pPattern[iIndex] >= 65 && pPattern[iIndex] <= 90)		
			iBadMatchArr[(int)pPattern[iSize - 1] + 32] = iSize -1; // set last element in bad match tbale always to the length of pattern	
		
	}
}

/*! SearchPattern_BoyerMooreAlgorithm()
\fn The function search matche pattern based on Boyer Moore's
\param [IP]pPatternStr: Pattern to be matched, [IP]ulPatternStrLen: Lenth of pattern, [IP]BadMatchArr: Arry of bad character
\return Shift: How many shift to be make
\pre Bad match table is created
\post none
\author Islam Abdeen
\DT	8/9/2017 1:00: AM
*/
int SearchPattern_BoyerMooreAlgorithm(char *pPatternStr, unsigned long ulPatternStrLen, char *buffer, char BadMatchArr[])
{
    int i = 1;
    int shift;    
	
	while(i <= ulPatternStrLen)
	{
		if(optionsArr[3] == 0) // case sensetive
		{
			if (pPatternStr[ulPatternStrLen - i] != buffer[ulPatternStrLen - i])
			{				
				shift = BadMatchArr[buffer[ulPatternStrLen - i]];
				return shift;
			}

			++i;
		}
		else // non case sensitive
		{
			if (pPatternStr[ulPatternStrLen - i] == buffer[ulPatternStrLen - i] || (pPatternStr[ulPatternStrLen - i] + 32) == buffer[ulPatternStrLen - i] || (pPatternStr[ulPatternStrLen - i] - 32) == buffer[ulPatternStrLen - i])
			{
				++i;
			}
			else
			{
				printf("flagg\n");
				shift = BadMatchArr[buffer[ulPatternStrLen - i]];
				return shift;
			}			
		}

	}		

    return 0;
}

/*! replace()
\fn The function replace matche pattern in the whole file based on Boyer Moore's
\param 
\return 
\pre 
\post none
\author Islam Abdeen
\DT	8/9/2017 1:00: AM
*/
char * replace(char *pPatternStr, unsigned long ulPatternStrLen, char *pCompensatedStr, unsigned long ulCompensatedStrLen, char *buffer, unsigned long ulBufferSize, char BadMatchArr[])
{
    int shift;
    unsigned int uiIndex = 0;

	if(optionsArr[1] == 1 ) // first occurance
	{
		unsigned int uiNewSize = ulBufferSize;
		unsigned int uiDiff = ulCompensatedStrLen - ulPatternStrLen;
		
		while(buffer[uiIndex] != '\0' && strlen(&buffer[uiIndex]) >= ulPatternStrLen)
		{					
			shift = SearchPattern_BoyerMooreAlgorithm(pPatternStr, ulPatternStrLen, &buffer[uiIndex], BadMatchArr);
			//printf("shift: %i\n", shift); Used for Debugging
			if(!shift)
			{
				if(ulCompensatedStrLen == ulPatternStrLen)
				{			
					memcpy(&buffer[uiIndex], pCompensatedStr, ulCompensatedStrLen);
					uiIndex += ulCompensatedStrLen;
				}

				else if(ulCompensatedStrLen > ulPatternStrLen)
				{					
					uiNewSize += uiDiff;										
					buffer = realloc(buffer, uiNewSize);
									
					if(buffer[uiIndex + ulPatternStrLen] != '\0')
					{					
						unsigned int uiMemToCopyLen = 1 + strlen(&buffer[uiIndex + ulPatternStrLen]);						
						char *tmp = (char *)malloc(uiMemToCopyLen);
						memcpy(tmp, &buffer[uiIndex + ulPatternStrLen], uiMemToCopyLen);
						memcpy(&buffer[uiIndex + ulPatternStrLen + uiDiff], tmp, uiMemToCopyLen);
						free(tmp);						
						memcpy(&buffer[uiIndex], pCompensatedStr, ulCompensatedStrLen);
						uiIndex += ulCompensatedStrLen;
					}
					else
					{
						memcpy(&buffer[uiIndex], pCompensatedStr, ulCompensatedStrLen);
						uiIndex += ulCompensatedStrLen;
						buffer[uiIndex] = '\0';
					}
				}
				else // lees than
				{				
					unsigned int uiDiff =  ulPatternStrLen - ulCompensatedStrLen;
					uiNewSize -= uiDiff;
					memcpy(&buffer[uiIndex], pCompensatedStr, ulCompensatedStrLen);
					memmove(&buffer[uiIndex + ulPatternStrLen - uiDiff], &buffer[uiIndex + ulPatternStrLen], strlen(&buffer[uiIndex + ulPatternStrLen]) + 1); // shifting
					uiIndex += ulCompensatedStrLen;
				}
				
				//return buffer;
				break;
			}
			else if (shift == -1) // character not in table then sift the whole length
			{				
					uiIndex += ulPatternStrLen;								
			}
			else
			{
				uiIndex += shift;
			}
		} // while
	}
	if(optionsArr[2] == 1 ) // last occurance
	{
		unsigned int uiNewSize = 1 + strlen(buffer); // if -b and -l is applied
				
		unsigned int uiDiff = ulCompensatedStrLen - ulPatternStrLen;
		unsigned int uiLastOccurrence = 0;
		uiIndex = 0;
		
		// get index of last occurrence
		while(buffer[uiIndex] != '\0' && strlen(&buffer[uiIndex]) >= ulPatternStrLen)
		{					
			shift = SearchPattern_BoyerMooreAlgorithm(pPatternStr, ulPatternStrLen, &buffer[uiIndex], BadMatchArr);
			printf("shift: %i\n", shift);
			if(!shift)
			{
				uiLastOccurrence = uiIndex;	
				uiIndex += ulCompensatedStrLen;				
			}
			else if (shift == -1) // character not in table then sift the whole length
			{				
					uiIndex += ulPatternStrLen;								
			}
			else
			{
				uiIndex += shift;
			}
		} // while		
		
		// replacing
		if(ulCompensatedStrLen == ulPatternStrLen)
		{			
			memcpy(&buffer[uiLastOccurrence], pCompensatedStr, ulCompensatedStrLen);			
		}
		else if(ulCompensatedStrLen > ulPatternStrLen)
		{					
			uiNewSize += uiDiff;
								
			buffer = realloc(buffer, uiNewSize);
							
			if(buffer[uiLastOccurrence + ulPatternStrLen] != '\0')
			{					
				unsigned int uiMemToCopyLen = 1 + strlen(&buffer[uiLastOccurrence + ulPatternStrLen]);						
				char *tmp = (char *)malloc(uiMemToCopyLen);
				memcpy(tmp, &buffer[uiLastOccurrence + ulPatternStrLen], uiMemToCopyLen);
				memcpy(&buffer[uiLastOccurrence + ulPatternStrLen + uiDiff], tmp, uiMemToCopyLen);
				free(tmp);						
				memcpy(&buffer[uiLastOccurrence], pCompensatedStr, ulCompensatedStrLen);				
			}
			else
			{
				memcpy(&buffer[uiLastOccurrence], pCompensatedStr, ulCompensatedStrLen);
				uiLastOccurrence += ulCompensatedStrLen;
				buffer[uiLastOccurrence] = '\0';
			}
		}
		else // lees than
		{				
			unsigned int uiDiff =  ulPatternStrLen - ulCompensatedStrLen;
			uiNewSize -= uiDiff;
			memcpy(&buffer[uiLastOccurrence], pCompensatedStr, ulCompensatedStrLen);
			memmove(&buffer[uiLastOccurrence + ulPatternStrLen - uiDiff], &buffer[uiLastOccurrence + ulPatternStrLen], strlen(&buffer[uiLastOccurrence + ulPatternStrLen]) + 1); // shifting			
		}		
		
	}		
		
	if(optionsArr[1] == 0 && optionsArr[2] == 0) // normal i.e replace all matches
	{
		unsigned int uiNewSize = ulBufferSize;
		unsigned int uiDiff = ulCompensatedStrLen - ulPatternStrLen;
		
		while(buffer[uiIndex] != '\0' && strlen(&buffer[uiIndex]) >= ulPatternStrLen)
		{				
			shift = SearchPattern_BoyerMooreAlgorithm(pPatternStr, ulPatternStrLen, &buffer[uiIndex], BadMatchArr);
			
			if(!shift)
			{
				if(ulCompensatedStrLen == ulPatternStrLen)
				{			
					memcpy(&buffer[uiIndex], pCompensatedStr, ulCompensatedStrLen);
					uiIndex += ulCompensatedStrLen;
				}

				else if(ulCompensatedStrLen > ulPatternStrLen)
				{					
					uiNewSize += uiDiff;										
					buffer = realloc(buffer, uiNewSize);
									
					if(buffer[uiIndex + ulPatternStrLen] != '\0')
					{					
						unsigned int uiMemToCopyLen = 1 + strlen(&buffer[uiIndex + ulPatternStrLen]);						
						char *tmp = (char *)malloc(uiMemToCopyLen);
						memcpy(tmp, &buffer[uiIndex + ulPatternStrLen], uiMemToCopyLen);
						memcpy(&buffer[uiIndex + ulPatternStrLen + uiDiff], tmp, uiMemToCopyLen);
						free(tmp);						
						memcpy(&buffer[uiIndex], pCompensatedStr, ulCompensatedStrLen);
						uiIndex += ulCompensatedStrLen;
					}
					else
					{
						memcpy(&buffer[uiIndex], pCompensatedStr, ulCompensatedStrLen);
						uiIndex += ulCompensatedStrLen;
						buffer[uiIndex] = '\0';
					}
				}
				else // lees than
				{				
					unsigned int uiDiff =  ulPatternStrLen - ulCompensatedStrLen;
					uiNewSize -= uiDiff;
					//unsigned int uiNewSize = ulBufferSize - uiDiff;
					memcpy(&buffer[uiIndex], pCompensatedStr, ulCompensatedStrLen);
					memmove(&buffer[uiIndex + ulPatternStrLen - uiDiff], &buffer[uiIndex + ulPatternStrLen], strlen(&buffer[uiIndex + ulPatternStrLen]) + 1); // shifting
					uiIndex += ulCompensatedStrLen;
				}
			}
			else if (shift == -1) // character not in table then sift the whole length
			{							
					uiIndex += ulPatternStrLen;									
			}
			else
			{
				uiIndex += shift;
			}
		} // while
						
	}
	
	if(strlen(&buffer[uiIndex]) >= ulPatternStrLen)
		buffer[uiIndex] = '\0';	   	
		
	return buffer;
}

/*! main()
\fn main function 
\param Number of argument and arr of arguments
\return none
\pre none
\post none
\author Islam Abdeen
\DT	8/9/2017 1:00: AM
*/
int main(int argc, char *argv[])
{
   
   unsigned long ulPatternStrLen = 0, ulCompensatedStrLen = 0;
    char *pPatternStr, *pCompensatedStr;
    char BadMatchArr[NO_OF_CHARS];	
	unsigned short usNumOfFiles = 0;
	int iFilesSeperatorPos = 0; // i.e --

    if(argc < 2)
    {
        PrintUsageMsg();
        return 1;
    }

    if (argc == 2 && !(strcmp(argv[1],"--help")))
    {
        PrintUsageMsg();
        return 1;

    }

    if (argc < 4)
    {
        PrintUsageMsg();
        return 1;
    }

    if(argc >= 4)
    {
        for(int i=1; i<argc; ++i)
        {
            if(!(strcmp(argv[i],"--")))
            {
                iFilesSeperatorPos = i;
                break;
            }
        }

        if(iFilesSeperatorPos < 3)
        {
            PrintUsageMsg();
            return 1;
        }
        else if(iFilesSeperatorPos == 3) // should be no option
        {          
            ulPatternStrLen = strlen(argv[1]);            
            pPatternStr = (char *)malloc(ulPatternStrLen+1);
            memcpy(pPatternStr, &argv[1][0], ulPatternStrLen);
            pPatternStr[ulPatternStrLen] = '\0';
           
            ulCompensatedStrLen = strlen(argv[2]);
            pCompensatedStr = (char *)malloc(ulCompensatedStrLen+1);
            memcpy(pCompensatedStr, &argv[2][0], ulCompensatedStrLen);
            pCompensatedStr[ulCompensatedStrLen] = '\0';

            usNumOfFiles = argc - iFilesSeperatorPos - 1;
            printf("usNumOfFiles = %i\n", usNumOfFiles);

        }
        else if(iFilesSeperatorPos == 4) // should be one option
        {
            if (!(strcmp(argv[1],"-b")))
                optionsArr[0] = 1;
            else if (!(strcmp(argv[1],"-f")))
                optionsArr[1] = 1;
            else if (!(strcmp(argv[1],"-l")))
                optionsArr[2] = 1;
            else if (!(strcmp(argv[1],"-i")))
                optionsArr[3] = 1;
            else
            {
                PrintInvalidOptionMsg();
                return 1;
            }

            ulPatternStrLen = strlen(argv[2]);
            pPatternStr = (char *)malloc(ulPatternStrLen+1);
            memcpy(pPatternStr, &argv[2][0], ulPatternStrLen);
            pPatternStr[ulPatternStrLen] = '\0';

            ulCompensatedStrLen = strlen(argv[3]);
            pCompensatedStr = (char *)malloc(ulCompensatedStrLen+1);
            memcpy(pCompensatedStr, &argv[3][0], ulCompensatedStrLen);
            pCompensatedStr[ulCompensatedStrLen] = '\0';

            usNumOfFiles = argc - iFilesSeperatorPos - 1;
            printf("usNumOfFiles = %i\n", usNumOfFiles);
        }
        else if(iFilesSeperatorPos == 5) // should be 2 option
        {
            for(int i=1; i<=2; ++i)
            {
                if (!(strcmp(argv[i],"-b")))
                    optionsArr[0] = 1;
                else if (!(strcmp(argv[i],"-f")))
                    optionsArr[1] = 1;
                else if (!(strcmp(argv[i],"-l")))
                    optionsArr[2] = 1;
                else if (!(strcmp(argv[i],"-i")))
                    optionsArr[3] = 1;
                else
                {
                    PrintInvalidOptionMsg();
                    return 1;
                }
            }

            ulPatternStrLen = strlen(argv[3]);
            pPatternStr = (char *)malloc(ulPatternStrLen+1);
            memcpy(pPatternStr, &argv[3][0], ulPatternStrLen);
            pPatternStr[ulPatternStrLen] = '\0';

            ulCompensatedStrLen = strlen(argv[4]);
            pCompensatedStr = (char *)malloc(ulCompensatedStrLen+1);
            memcpy(pCompensatedStr, &argv[4][0], ulCompensatedStrLen);
            pCompensatedStr[ulCompensatedStrLen] = '\0';

            usNumOfFiles = argc - iFilesSeperatorPos - 1;
            printf("usNumOfFiles = %i\n", usNumOfFiles);
        }
        else if(iFilesSeperatorPos == 6) // should be 3 option
        {
            for(int i=1; i<=3; ++i)
            {
                if (!(strcmp(argv[i],"-b")))
                    optionsArr[0] = 1;
                else if (!(strcmp(argv[i],"-f")))
                    optionsArr[1] = 1;
                else if (!(strcmp(argv[i],"-l")))
                    optionsArr[2] = 1;
                else if (!(strcmp(argv[i],"-i")))
                    optionsArr[3] = 1;
                else
                {
                    PrintInvalidOptionMsg();
                    return 1;
                }
            }

            ulPatternStrLen = strlen(argv[4]);
            pPatternStr = (char *)malloc(ulPatternStrLen+1);
            memcpy(pPatternStr, &argv[4][0], ulPatternStrLen);
            pPatternStr[ulPatternStrLen] = '\0';

            ulCompensatedStrLen = strlen(argv[5]);
            pCompensatedStr = (char *)malloc(ulCompensatedStrLen+1);
            memcpy(pCompensatedStr, &argv[5][0], ulCompensatedStrLen);
            usNumOfFiles = argc - iFilesSeperatorPos - 1;
            printf("usNumOfFiles = %i\n", usNumOfFiles);
        }
        else if(iFilesSeperatorPos == 7) // should be 4 option
        {
            for(int i=1; i<=4; ++i)
            {
                if (!(strcmp(argv[i],"-b")))
                    optionsArr[0] = 1;
                else if (!(strcmp(argv[i],"-f")))
                    optionsArr[1] = 1;
                else if (!(strcmp(argv[i],"-l")))
                    optionsArr[2] = 1;
                else if (!(strcmp(argv[i],"-i")))
                    optionsArr[3] = 1;
                else
                {
                    PrintInvalidOptionMsg();
                    return 1;
                }
            }

            ulPatternStrLen = strlen(argv[5]);
            pPatternStr = (char *)malloc(ulPatternStrLen+1);
            memcpy(pPatternStr, &argv[5][0], ulPatternStrLen);
            pPatternStr[ulPatternStrLen] = '\0';

            ulCompensatedStrLen = strlen(argv[6]);
            pCompensatedStr = (char *)malloc(ulCompensatedStrLen+1);
            memcpy(pCompensatedStr, &argv[6][0], ulCompensatedStrLen);
            usNumOfFiles = argc - iFilesSeperatorPos - 1;
            printf("usNumOfFiles = %i\n", usNumOfFiles);
        }
        else // error there is no 5 option in this application
        {
            PrintUsageMsg();
            return 1;
        }


    }
    else
    {
        PrintUsageMsg();
        return 1;
    }

    printf("-b = %i\n", optionsArr[0]);
    printf("-f = %i\n", optionsArr[1]);
    printf("-l = %i\n", optionsArr[2]);
    printf("-i = %i\n", optionsArr[3]);

    printf("PatternStr= %s\n", pPatternStr);
    printf("CompensatedStr= %s\n", pCompensatedStr);
    printf("ulPatternStrLen= %i\n", ulPatternStrLen);

    for(int i=0; i<usNumOfFiles; ++i)
    {
        char *buff;
        long lfsize;
		
        printf("file name= %s\n", argv[iFilesSeperatorPos + i + 1]);
		
        FILE *fb = fopen(argv[iFilesSeperatorPos + i + 1], "rb");
        if(!fb)
        {
            printf("err to open file\n");
            return -1;
        }
        fseek(fb, 0, SEEK_END);
        lfsize = ftell(fb);
        fseek(fb, 0, SEEK_SET); 
      	   
        /* allocate memory for entire content */
        buff = (char *)malloc(lfsize + 1);		
        if(buff == NULL)
        {
            printf("Faild to allocate memory\n");
            return -1;
        }

        if(fread(buff, lfsize, 1, fb) != 1)
        {
            fclose(fb);
            free(buff);
            
            return -1;
        }             
		
		buff[lfsize] = '\0';
		
		if(lfsize < ulPatternStrLen)
		{
			printf("pattern is less than text file\n");
			fclose(fb);
            free(buff);
			return -1;
		}		
		fclose(fb);
		
        /* do your work here, buffer is a string contains the whole text */
        Create_Bad_Match_Table(pPatternStr, strlen(pPatternStr),BadMatchArr);
        for(int i=0; i<NO_OF_CHARS; ++i)
        {
            // printf("BadMatchArr[%i] = %i\n", i, BadMatchArr[i]);
        }
		
        char *pOutBuf = replace(pPatternStr, ulPatternStrLen, pCompensatedStr, ulCompensatedStrLen, buff, lfsize+1, BadMatchArr);
		       		
		if(optionsArr[0] == 1) // take backup
		{
			char cpCmd[LENTH_OF_FILE*2+15] ;
			#ifdef UNIX
				sprintf(cpCmd, "cp %s %s.backup", argv[iFilesSeperatorPos + i + 1], argv[iFilesSeperatorPos + i + 1]);
				system(cpCmd);
			#else
				sprintf(cpCmd, "copy %s %s.backup", argv[iFilesSeperatorPos + i + 1], argv[iFilesSeperatorPos + i + 1]);
				system(cpCmd);
			#endif
		}
		
		// saving
		FILE *f = fopen(argv[iFilesSeperatorPos + i + 1], "w");
		if(!f)
		{
			printf("error to open file\n");
			return -1;
		}

		fprintf(f, "%s", pOutBuf);
		
		fclose(f);		
        free(buff);		
		free(pOutBuf);
    }
	
    free(pPatternStr);
    free(pCompensatedStr);

    return 0;
}
