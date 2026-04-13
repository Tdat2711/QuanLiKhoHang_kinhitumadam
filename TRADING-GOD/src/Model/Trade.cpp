//
// Created by Khac Lam 's Laptop on 09/04/2026.
//

#include "Trade.h"

LenhGioiHan::LenhGioiHan(double g, bool mua) {
    this->giaCho = g;
    this->maLenhMua = mua;
}

int LenhGioiHan::kiemTraKhop(double giaThiTruong) {
    // Nếu là lệnh MUA (maLenhMua == true) và giá thị trường thấp hơn hoặc bằng giá chờ
    if (this->maLenhMua == true && giaThiTruong <= this->giaCho) {
        return 1;
    }
    // Nếu là lệnh BÁN (maLenhMua == false) và giá thị trường cao hơn hoặc bằng giá chờ
    if (this->maLenhMua == false && giaThiTruong >= this->giaCho) {
        return -1;
    }

    return 0;
}