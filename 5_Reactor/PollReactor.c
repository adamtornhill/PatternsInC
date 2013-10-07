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

/***************************************************************************
* A sample implementation of a concrete Reactor using the poll() function as 
* a synchronous event demultiplexer.
****************************************************************************/

#include "Reactor.h"
#include "ReactorEventLoop.h"

#include "Error.h"

#include <poll.h>

#include <assert.h>
#include <stddef.h>
#include <stdio.h>

#define MAX_NO_OF_HANDLES 32

/* POSIX requires <poll.h> to define INFTIM. 
   However, in my environment it doesn't -> follow the recommendations by Mr. Stevens.
*/
#ifndef INFTIM
#define INFTIM -1
#endif

/* Bind an event handler to the struct used to interface poll(). */
typedef struct
{
   int isUsed;
   EventHandler handler;
   struct pollfd fd;
} HandlerRegistration;

static HandlerRegistration registeredHandlers[MAX_NO_OF_HANDLES];

/************************************************************
* Function declarations.
************************************************************/

/* Add a copy of the given handler to the first free position in registeredHandlers. */
static int addToRegistry(EventHandler* handler);

/* Identify the event handler in the registeredHandlers and remove it. */
static int removeFromRegistry(EventHandler* handler);

/* Add a copy of all registered handlers to the given array. */
static size_t buildPollArray(struct pollfd* fds);

/* Identify the event handler corresponding to the given descriptor in the registeredHandlers. */
static EventHandler* findHandler(int fd);

/* Detect all signalled handles and invoke their corresponding event handlers. */
static void dispatchSignalledHandles(const struct pollfd* fds, size_t noOfHandles);

/****************************************************************
* Implementation of the Reactor interface used for registrations.
*****************************************************************/

void Register(EventHandler* handler)
{
   assert(NULL != handler);

   if(!addToRegistry(handler)) {
      /* NOTE: In production code, this error should be delegated to the client instead. */
      error("No more registrations possible");
   }
}

void Unregister(EventHandler* handler)
{
   assert(NULL != handler);
   
   if(!removeFromRegistry(handler)) {
      /* NOTE: In production code, this error should be delegated to the client instead. */
      error("Event handler not registered");
   }
}

/****************************************************************
* Implementation of the reactive event loop 
* (interface separated in ReactorEventLoop.h).
*****************************************************************/

void HandleEvents(void)
{
   /* Build the array required to interact with poll().*/
   struct pollfd fds[MAX_NO_OF_HANDLES] = {0};

   const size_t noOfHandles = buildPollArray(fds);

   /* Inoke the synchronous event demultiplexer.*/
   if(0 < poll(fds, noOfHandles, INFTIM)){
      /* Identify all signalled handles and invoke the event handler associated with each one. */
      dispatchSignalledHandles(fds, noOfHandles);
     }
   else{
      error("Poll failure");
   }
}

/************************************************************
* Definition of the local utility functions.
************************************************************/

/**
* Add a copy of the given handler to the first free position in registeredHandlers.
*/
static int addToRegistry(EventHandler* handler)
{
   /* Identify the first free position. */
   int isRegistered = 0;
   int i = 0;
   
   for(i = 0; (i < MAX_NO_OF_HANDLES) && (0 == isRegistered); ++i) {
      
      if(0 == registeredHandlers[i].isUsed) {
         /* A free position found. */
         HandlerRegistration* freeEntry = &registeredHandlers[i];
         
         /* Create a binding between the handle provided by the client and the events of interest. */
         freeEntry->handler = *handler;
         freeEntry->fd.fd = handler->getHandle(handler->instance);
         freeEntry->fd.events = POLLRDNORM;
         
         isRegistered = freeEntry->isUsed = 1;
         
         (void) printf("Reactor: Added handle with ID = %d\n", freeEntry->fd.fd);
      }
   }

   return isRegistered;
}

/**
* Identify the event handler in the registeredHandlers and remove it.
*/
static int removeFromRegistry(EventHandler* handler)
{
   /* Identify the event handler in the registeredHandlers and remove it. */
   int i = 0;
   int nodeRemoved = 0;
   
   for(i = 0; (i < MAX_NO_OF_HANDLES) && (0 == nodeRemoved); ++i) {
      
      if(registeredHandlers[i].isUsed && (registeredHandlers[i].handler.instance == handler->instance)) {
         /* The given event handler is found -> mark it as unused and terminate the loop. */
         registeredHandlers[i].isUsed = 0;
		 nodeRemoved = 1;
         
		 (void) printf("Reactor: Removed event handler with ID = %d\n", registeredHandlers[i].fd.fd);
      }
   }
   
   return nodeRemoved;
}

/**
* Add a copy of all registered handlers to the given array.
*/
static size_t buildPollArray(struct pollfd* fds)
{
   /* Add all registered handlers to the given array. */
   int i = 0;
   size_t noOfCopiedHandles = 0;
   
   for(i = 0; i < MAX_NO_OF_HANDLES; ++i) {
      
      if(registeredHandlers[i].isUsed) {
        
         fds[noOfCopiedHandles] = registeredHandlers[i].fd;
         ++noOfCopiedHandles;
      }
   }
   
   return noOfCopiedHandles;
}

/**
* Identify the event handler corresponding to the given descriptor in the registeredHandlers.
*/
static EventHandler* findHandler(int fd)
{
   EventHandler* matchingHandler = NULL;
   
   /* Identify the corresponding concrete event handler in the registeredHandles. */
   int i = 0;
   
   for(i = 0; (i < MAX_NO_OF_HANDLES) && (NULL == matchingHandler); ++i) {
      
      if(registeredHandlers[i].isUsed && (registeredHandlers[i].fd.fd == fd)) {
         matchingHandler = &registeredHandlers[i].handler;
      }
   }
   
   return matchingHandler;
}

/**
* Loop through all handles. Upon detection of a handle signalled by poll(), its 
* corresponding event handler is fetched and invoked.
*/
static void dispatchSignalledHandles(const struct pollfd* fds, size_t noOfHandles)
{
   size_t i = 0;

   for(i = 0; i < noOfHandles; ++i) {
      /* Detect all signalled handles. */
      if((POLLRDNORM | POLLERR) & fds[i].revents) {
         /* This handle is signalled -> find and invoke its corresponding event handler. */
         EventHandler* signalledHandler = findHandler(fds[i].fd);

         if(NULL != signalledHandler){
            signalledHandler-> handleEvent(signalledHandler->instance);
         }
      }
   }
}

