#ifndef TIME_SUBJECT_H
#define TIME_SUBJECT_H

#include "TimeObserver.h"

void attach(const TimeObserver* observer); 

void detach(const TimeObserver* observer);

#endif
