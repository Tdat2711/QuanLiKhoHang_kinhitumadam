#include "Order.h"

Order::Order(std::string ma, double g, double sl) {
    this->maCoin = ma;
    this->gia = g;
    this->soLuong = sl;
    this->maLenhMua = false;
}

Order::~Order() {}

void Order::getMaLenhMua(bool mua) {
    this->maLenhMua = mua;
}

std::string Order::getMaCoin() const {
    return this->maCoin;
}
double Order::getGia() const {
    return this->gia;
}
double Order::getSoLuong() const {
    return this->soLuong;
}
bool Order::checkMaLenh() const {
    return this->maLenhMua;
}

std::string Order::xuattin() const {
    return (this->maLenhMua ? "MUA," : "BAN,") + this->maCoin + "," + std::to_string(this->gia) + "," + std::to_string(this->soLuong);
}