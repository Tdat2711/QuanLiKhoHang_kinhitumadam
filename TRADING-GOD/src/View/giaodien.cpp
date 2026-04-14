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

void giaodien::inSaoKe(double usdt,double btc,double eth) {
    std::cout << "\n[ TAI SAN ] USDT: " << usdt;
    std::cout << "\n[ TAI SAN ] BTC: " << btc;
    std::cout << "\n[ TAI SAN ] ETH: " << eth;
}
void giaodien::inLichSu(const std::vector<Order*>& lichSu) {
    std::cout << "\n==========================================" << std::endl;
    std::cout << "         LICH SU GIAO DICH CHI TIET       " << std::endl;
    std::cout << "==========================================" << std::endl;

    if (lichSu.empty()) {
        std::cout << " ( Khong co giao dich nao )" << std::endl;
    } else {
        for (size_t i = 0; i < lichSu.size(); ++i) {
            std::cout << i + 1 << ". " << lichSu[i]->xuattin() << std::endl;
        }
    }
    std::cout << "==========================================" << std::endl;
}