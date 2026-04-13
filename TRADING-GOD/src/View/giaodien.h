//
// Created by Khac Lam 's Laptop on 09/04/2026.
//

#ifndef TRADING_GOD_GIAODIEN_H
#define TRADING_GOD_GIAODIEN_H
#include <vector>
#include <string>
#include "../Model/Order.h"

class giaodien {
public:
    static void veLoiChao();
    static void thongBao(std::string msg);
    static void inSaoKe(double usdt, double btc);
};

#endif //TRADING_GOD_GIAODIEN_H