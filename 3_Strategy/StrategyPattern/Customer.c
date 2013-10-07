#include "Customer.h"
#include <stdlib.h>
#include <assert.h>

/*
I never really dive into the details of these types.
Let's just create a dummy placeholder for the information.
*/
typedef struct
{
  unsigned long orderId;
  double amount;
  double shipping;
} Order;

typedef struct
{
  int implementationOfLinkedList;
} List;

struct Customer 
{
  const char* name; 
  Address address; 
  List orders;
   
  /* Bind the strategy to Customer: */
  CustomerPriceStrategy priceStrategy;
};

CustomerPtr createCustomer(
  const char* name, 
  const Address* address,
  CustomerPriceStrategy priceStrategy)
{
  CustomerPtr customer = malloc(sizeof *customer);
  
  if(NULL != customer) {
    /* Bind the initial strategy supplied by the client. */
    customer->priceStrategy = priceStrategy; 

    /* Initialize the other attributes of the customer here. */
  }

  return customer; 
}

void placeOrder(struct Customer* customer, const Order* order)
{
  double totalAmount = customer->priceStrategy(order->amount, order->shipping);

  /* More code to process the order... */
}

void changePriceCategory(CustomerPtr customer, CustomerPriceStrategy newPriceStrategy)
{
  assert(NULL != customer);
  customer->priceStrategy = newPriceStrategy;
}

