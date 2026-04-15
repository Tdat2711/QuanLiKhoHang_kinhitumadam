//
// Created by Khac Lam 's Laptop on 15/04/2026.
//

#ifndef SHORTORDER_H
#define SHORTORDER_H
#include "Order.h"

class ShortOrder : public Order {
public:
    ShortOrder(std::string ma, double g, double sl);
    std::string loaiLenh() const override;
};
#endif //TRADING_GOD_SHORTORDER_H