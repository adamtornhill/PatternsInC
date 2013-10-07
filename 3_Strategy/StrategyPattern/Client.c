#include "Customer.h"
#include "CustomerCategories.h"

/*
Client code illustrating the binding of a strategy:
*/
static CustomerPtr createBronzeCustomer(
  const char* name,
  const Address* address)
{
  return createCustomer(name, address, bronzePriceStrategy);
}
