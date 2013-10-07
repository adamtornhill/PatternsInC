#include "WatchState.h"
#include "WatchStateInternal.h"

/*
Provide the default implementations:
*/

static void defaultStop(WatchStatePtr state) 
{
  /* We'll get here if the stop event isn't supported
     in the concrete state. */
}

static void defaultStart(WatchStatePtr state) 
{
    /* We'll get here if the start event isn't supported
       in the concrete state. */
}

void defaultImplementation(WatchStatePtr state) {
    state->start = defaultStart;
    state->stop = defaultStop;
}
