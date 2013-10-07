#include "CustomerCategories.h"

/* In production code, I would definitely validate all input and
   secure the calculations upon entry of each function... */

double bronzePriceStrategy(double amount, double shipping)
{
  return amount * 0.98 + shipping;
}

double silverPriceStrategy(double amount, double shipping)
{
  return amount * 0.95 + shipping;
}

double goldPriceStrategy(double amount, double shipping)
{
  /* Free shipping for gold customers. */
  return amount * 0.90; 
}
