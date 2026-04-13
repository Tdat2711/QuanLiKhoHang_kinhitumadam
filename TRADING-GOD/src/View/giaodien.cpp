//
// Created by Khac Lam 's Laptop on 09/04/2026.
//

#include "giaodien.h"
#include <iostream>
#include <iomanip>


void giaodien::veLoiChao() {
    std::cout << "==========================================\n";
    std::cout << "      CHIEN THAN GIAO DICH v1.0 BY DAT     \n";
    std::cout << "==========================================\n";
}

void giaodien::thongBao(std::string msg) {
    std::cout << ">>> " << msg << "\n";
}

void giaodien::inSaoKe(double usdt, double btc) {
    std::cout << "\n[ TAI SAN ] USDT: " << usdt;
}
