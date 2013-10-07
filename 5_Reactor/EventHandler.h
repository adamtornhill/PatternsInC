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

#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "Handle.h"

/* All interaction from Reactor to an event handler goes 
through function pointers with the following signatures: */
typedef Handle (*getHandleFunc)(void* instance);
typedef void (*handleEventFunc)(void* instance);

typedef struct
{
  void* instance;
  getHandleFunc getHandle;
  handleEventFunc handleEvent;
} EventHandler;

#endif
