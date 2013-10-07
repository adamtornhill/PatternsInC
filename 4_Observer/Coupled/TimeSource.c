#include "DigitalStopWatch.h"
#include "SystemTime.h"

static DigitalStopWatchPtr digitalWatch; 
static SystemTime currentTime;

/*
 Dummy stubs for the invoked functions:
*/
static SystemTime calculateNewTime(void)
{
  /* Time will pass slowly in this watch... */
  SystemTime newTime = { 42 };

  return newTime;
}

static void notifyChangedTime(DigitalStopWatchPtr watchToNotify, 
			      const SystemTime* newTime)
{
}

/* Invoked once by the application at start-up. */
void startTimeSource()
{
  digitalWatch = createWatch();
  /* Code for setting up handlers for interrupts, or
     the like, in order to get notified each millisecond
     from the operating system. */
}

/* This function is invoked each millisecond through an
   interaction with the operating system. */
static void msTick() {
  /* Invoke a function encapsulating the knowledge about
     time representation. */
  currentTime = calculateNewTime();
  
  /* Inform the watch that another millisecond passed. */
  notifyChangedTime(digitalWatch, &currentTime);
}
