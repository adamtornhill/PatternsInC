#include "DigitalStopWatch.h"
#include "error.h"
#include "TimeSource.h"
#include "Display.h"

typedef enum
{
  stopped,
  started
} State;

struct DigitalStopWatch 
{
  /* Let a variable hold the state of our object. */
  State state;
  TimeSource source;
  Display watchDisplay;
};

typedef enum
{
  stopEvent,
  startEvent
} Event;

#define NO_OF_STATES 2
#define NO_OF_EVENTS 2

static State TransitionTable[NO_OF_STATES][NO_OF_EVENTS] =
{
    { stopped, started },
    { stopped, started }
};

void startWatch(DigitalStopWatchPtr instance) 
{
  const State currentState = instance->state;
  
  instance->state = TransitionTable[currentState][startEvent];
}

void stopWatch(DigitalStopWatchPtr instance) 
{
  const State currentState = instance->state;
  
  instance->state = TransitionTable[currentState][stopEvent];
}
