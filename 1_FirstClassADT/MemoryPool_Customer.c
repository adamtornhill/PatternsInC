#include "Customer.h"
#include "Order.h"
#include <stdlib.h>

struct Customer 
{
  const char* name;
  Address address; 
  size_t noOfOrders; 
  Order orders[42];
};

#define MAX_NO_OF_CUSTOMERS 42

static struct Customer objectPool[MAX_NO_OF_CUSTOMERS];
static size_t numberOfObjects = 0;

CustomerPtr createCustomer(
  const char* name, 
  const Address* adress)
{
  CustomerPtr customer = NULL;

  if(numberOfObjects < MAX_NO_OF_CUSTOMERS) {
    customer = &objectPool[numberOfObjects++]; 
    /* Initialize the object... */
  }
  return customer; 
}

void destroyCustomer(
  CustomerPtr customer) 
{
/*
  In case de-allocation is needed, an array will still do, but 
  a more sophisticated method for keeping track of “allocated” objects will be needed. 
  However, such an algorithm is outside the scope of this book.
*/
}

