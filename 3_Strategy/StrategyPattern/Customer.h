#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "CustomerStrategy.h"
#include "Address.h"

/* 
A pointer to an incomplete type (hides the implementation details). 
*/
typedef struct Customer* CustomerPtr;

CustomerPtr createCustomer(
  const char* name, 
  const Address* address,
  CustomerPriceStrategy priceStrategy);

void changePriceCategory(
  CustomerPtr customer, 
  CustomerPriceStrategy newPriceStrategy);

#endif
