//
// Created by Khac Lam 's Laptop on 09/04/2026.
//

#ifndef TRADING_GOD_ORDER_H
#define TRADING_GOD_ORDER_H
#include <string>
class Order {
private:
    std::string maCoin;
    double gia;
    double soLuong;
    bool maLenhMua;
public:
    Order(std::string ma,double g,double sl);
    void setMaLenhMua(bool mua);
    std::string xuattin() const;

    double getGia() const { return gia; }
    bool isMaLenhMua() const { return maLenhMua; }
};


#endif //TRADING_GOD_ORDER_H