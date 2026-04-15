//
// Created by Khac Lam 's Laptop on 15/04/2026.
//

#ifndef LONGORDER_H
#define LONGORDER_H
#include "Order.h"
#include <string>

class LongOrder : public Order {
public:
    LongOrder(std::string ma, double g, double sl);
    std::string loaiLenh() const override;
};
#endif //TRADING_GOD_LONGORDER_H