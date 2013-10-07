#include "TimeSubject.h"
#include <assert.h>
#include <stddef.h>

struct ListNode 
{
  TimeObserver item;
  struct ListNode* next; 
};

static struct ListNode observers; 
static SystemTime currentTime;

/* Local helper functions for managing the linked-list
  (implementation omitted). */
static void appendToList(const TimeObserver* observer)
{
  /* Append a copy of the observer to the linked-list. */
}

static void removeFromList(const TimeObserver* observer)
{
  /* Identify the observer in the linked-list and
     remove that node. */
}

/*
 Dummy stubs for the invoked functions:
*/
static SystemTime calculateNewTime(void)
{
  /* Time will pass slowly in this watch... */
  SystemTime newTime = { 42 };

  return newTime;
}

/* See Listing 8 and the related discussion:
   Checking Subject constraints with assertions.
*/
static int isNotifying = 0;

/* Implementation of the TimeSubject interface. */
void attach(const TimeObserver* observer)
{
  assert(0 == isNotifying);
  assert(NULL != observer);
  appendToList(observer);
}

void detach(const TimeObserver* observer) 
{
  assert(0 == isNotifying);
  assert(NULL != observer);
  removeFromList(observer);
}

/* Implementation of the original responsibility of the
   TimeSource (code for initialization, etc omitted). */
static void msTick() 
{
  struct ListNode* node = observers.next;
  /* Invoke a function encapsulating the knowledge
     about time representation. */
  currentTime = calculateNewTime();
  
  /* Ensure that no changes are done to the
     subject during notification. */
  isNotifying = 1;

  /* Walk through the linked-list and notify every 
     observer that another millisecond passed.\
   */
  while(NULL != node) {
    TimeObserver* observer = &node->item;
    observer->notification(observer->instance, &currentTime);
    node = node->next;
  }

  /* All observers notified, allow changes again. */
  isNotifying = 0;
 }
