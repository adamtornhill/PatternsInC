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

#ifndef HANDLE_H
#define HANDLE_H

/* The type of a handle is system specific - this example 
uses UNIX I/O handles, which are plain integer values. */
typedef int Handle;

#endif
