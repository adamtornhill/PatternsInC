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

CustomerPtr createCustomer(
  const char* name,
  const Address* address) 
{
  CustomerPtr customer = malloc(sizeof *customer);

  if(customer) {
    /* Initialize each field in the customer... */
  }

  return customer; 
}

void destroyCustomer(
  CustomerPtr customer) 
{
  /* Perform clean-up of the customer internals, if necessary. */
  free(customer);
}
