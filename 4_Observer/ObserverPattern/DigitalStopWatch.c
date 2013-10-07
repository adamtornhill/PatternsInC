#include "DigitalStopWatch.h"
#include "TimeObserver.h"
#include "TimeSubject.h"
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

/*
I never really dive into the details of this type.
Let's just create a dummy placeholder for the information.
*/
typedef struct 
{
  int someDisplayAttributes;
} Display;

struct DigitalStopWatch 
{
  Display watchDisplay;
  /* Other attributes of the watch. */
};

/* Dummy stub for the responsibility of updating the 
   display on the watch. */
static void updateDisplay(DigitalStopWatchPtr watch,
                          const SystemTime* newTime)
{
  Display* display = &watch->watchDisplay;
  /* Do the update...*/
}

/* Implementation of the function required by the
   TimeObserver interface. */
static void changedTime(void* instance, const SystemTime* newTime) 
{
  DigitalStopWatchPtr digitalWatch = instance;
  assert(NULL != digitalWatch);

  updateDisplay(digitalWatch, newTime);
}

DigitalStopWatchPtr createDigitalWatch(void) 
{
  DigitalStopWatchPtr watch = malloc(sizeof *watch);

  if(NULL != watch) {
    /* Successfully created -> attach to the subject. */
    TimeObserver observer = {0};
    observer.instance = watch;
    observer.notification = changedTime;
    attach(&observer);
  }

  return watch; 
}

void destroyDigitalWatch(DigitalStopWatchPtr watch)
{
  /* Before deleting the instance we have to detach
     from the subject. */
  TimeObserver observer = {0};
  observer.instance = watch;
  observer.notification = changedTime;
  detach(&observer);
  free(watch);
}


