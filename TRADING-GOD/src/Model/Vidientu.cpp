//
// Created by Khac Lam 's Laptop on 09/04/2026.
//

#include "Vidientu.h"

Vidientu::Vidientu(double usdtBanDau) { taiSan["USDT"] = usdtBanDau; }

Vidientu::~Vidientu() {
    for (auto o : lichSu) delete o;
    lichSu.clear();
}

double Vidientu::laySoDu(std::string ma) const {
    return (taiSan.count(ma)) ? taiSan.at(ma) : 0.0;
}

void Vidientu::capNhat(std::string ma, double luong) {
    taiSan[ma] += luong;
}
void Vidientu::luuLenh(Order* o) {
    lichSu.push_back(o);
}
const std::vector<Order*>& Vidientu::layLichSu() const {
    return lichSu;
}