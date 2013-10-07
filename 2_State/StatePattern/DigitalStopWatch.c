#include "DigitalStopWatch.h"

/* We need to know about or initial state: */
#include "StoppedState.h"

#include "WatchStateInternal.h"
#include "error.h"
#include "TimeSource.h"
#include "Display.h"
#include <stdlib.h>

struct DigitalStopWatch 
{
  struct WatchState state; 
  TimeSource source; 
  Display watchDisplay;
};

DigitalStopWatchPtr createWatch(void) 
{
  DigitalStopWatchPtr instance = malloc(sizeof *instance);

  if(NULL != instance) {
    /* Specify the initial state. */
    transitionToStopped(&instance->state);
    /* Initialize the other attributes here.*/
  }

  return instance; 
}

void destroyWatch(DigitalStopWatchPtr instance) 
{
  free(instance);
}

void startWatch(DigitalStopWatchPtr instance) 
{
  instance->state.start(&instance->state);
}

void stopWatch(DigitalStopWatchPtr instance) 
{
  instance->state.stop(&instance->state);
}

