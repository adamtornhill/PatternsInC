typedef enum
{
  bronzeCustomer,
  silverCustomer,
  goldCustomer
} CustomerCategory;

/*
Obviously real-world error handling is more complex than this...
The intent with this function is just to put a compilable comment 
into the code.
*/
static void onError(const char* reason)
{
}

double calculatePrice(
  CustomerCategory category, 
  double totalAmount,
  double shipping)
{
  double price = 0.0;
  /* Calculate the total price depending on customer category. */
  switch(category) {
    case bronzeCustomer:
      price = totalAmount * 0.98 + shipping;
      break;
    case silverCustomer:
      price = totalAmount * 0.95 + shipping;
      break;
    case goldCustomer:
      /* Free shipping for gold customers.*/
      price = totalAmount * 0.90;
      break; 
    default:
      onError("Unsupported category");
  }

  return price; 
}
