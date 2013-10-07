#ifndef TIME_OBSERVER_H
#define TIME_OBSERVER_H

#include "SystemTime.h"

typedef void (*ChangeTimeNotification)(void* instance,
                                       const SystemTime* newTime);

typedef struct
{
  void* instance;
  ChangeTimeNotification notification;
} TimeObserver;

#endif
