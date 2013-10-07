#include "StartedState.h"
#include "WatchStateInternal.h"

/* Possible transition to the following state: */
#include "StoppedState.h"

static void stopWatch(WatchStatePtr state) 
{
    transitionToStopped(state);
}

void transitionToStarted(WatchStatePtr state) 
{
   /* Initialize with the default implementation before
      specifying the events to be handled in the started
      state. */
   defaultImplementation(state);
   state->stop = stopWatch;
}

