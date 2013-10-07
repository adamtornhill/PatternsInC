/********************************************************************
* (C) Adam Petersen 2005
*
* This code accompanies the article "Patterns in C, part 5: REACTOR".
* The article is available as PDF from www.adampetersen.se
*
* The code is intended as a illustration of the Reactor at work and 
* is not suitable for use in production code (in order to keep this 
* example as short as possible, the error handling has been strongly 
* simplified).
*
********************************************************************/

#ifndef ERROR_H
#define ERROR_H

/**
* This function defines the error handling strategy.
* In this sample code, it simply prints the given error string and 
* terminates the program.
*/
void error(const char* reason);

#endif
