//
// Created by Khac Lam 's Laptop on 09/04/2026.
//

#include "giaodien.h"
#include <iostream>
#include <iomanip>
#include "../Model/ShortOrder.h"


void giaodien::veLoiChao() {
    std::cout << "==========================================\n";
    std::cout << "      CHIEN THAN GIAO DICH v1.0 BY DAT     \n";
    std::cout << "==========================================\n";
}

void giaodien::thongBao(std::string msg) {
    std::cout << ">>> " << msg << "\n";
}

void giaodien::inSaoKe(double usdt,double btc,double eth) {
    std::cout << "\n[ TAI SAN ] USDT: " << usdt;
    std::cout << "\n[ TAI SAN ] BTC: " << btc;
    std::cout << "\n[ TAI SAN ] ETH: " << eth;
}
void giaodien::inLichSu(const std::vector<Order*>& lichSu) {
    std::cout << "\n--- LICH SU GIAO DICH ---\n";
    for (Order* o : lichSu) {
        std::cout << o->loaiLenh() << " | " << o->getMaCoin() << " | " << o->getGia() << " | " << o->getSoLuong() << std::endl;
    }
}