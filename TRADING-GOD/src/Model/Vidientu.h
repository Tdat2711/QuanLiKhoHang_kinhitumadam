//
// Created by Khac Lam 's Laptop on 09/04/2026.
//

#ifndef TRADING_GOD_VIDIENTU_H
#define TRADING_GOD_VIDIENTU_H
#include <unordered_map>
#include <vector>
#include "Order.h"

class Vidientu {
private:
    std::unordered_map<std::string, double> taiSan;
    std::vector<Order*> lichSu;

public:
    Vidientu(double usdtBanDau);
    ~Vidientu();

    bool coDuKhaNang(double soTien) const;
    double laySoDu(std::string ma) const;
    void capNhat(std::string ma, double luong);
    void luuLenh(Order* o);
    const std::vector<Order*>& layLichSu() const;

    Vidientu(const Vidientu&) = delete;
    Vidientu& operator=(const Vidientu&) = delete;
};

#endif //TRADING_GOD_VIDIENTU_H