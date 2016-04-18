#ifndef DIGITAL_STOP_WATCH_H
#define DIGITAL_STOP_WATCH_H

/* 
A pointer to an incomplete type (hides the implementation details). 
*/
typedef struct DigitalStopWatch* DigitalStopWatchPtr;

/*
A watch is implemented using the First-Class ADT pattern.
*/

DigitalStopWatchPtr createWatch(void);

void destroyWatch(DigitalStopWatchPtr instance);

void startWatch(DigitalStopWatchPtr instance);

void stopWatch(DigitalStopWatchPtr instance);

#endif
