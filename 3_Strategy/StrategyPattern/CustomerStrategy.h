#ifndef CUSTOMER_STRATEGY_H
#define CUSTOMER_STRATEGY_H

typedef double (*CustomerPriceStrategy)(double amount,
                                        double shipping);

#endif
