//
// Created by Khac Lam 's Laptop on 09/04/2026.
//

#include "Order.h"
Order::Order(std::string ma,double g,double sl) {
    this->maCoin = ma;
    this->gia = g;
    this->soLuong = sl;
    this->maLenhMua = false;
}
void Order::setMaLenhMua(bool mua) {
    this->maLenhMua = mua;
}
std::string Order::xuattin() const {
    return (maLenhMua ? "MUA," : "BAN,") + maCoin + "," + std::to_string(gia) + "," + std::to_string(soLuong);
}