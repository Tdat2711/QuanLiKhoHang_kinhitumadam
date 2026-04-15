//
// Created by Khac Lam 's Laptop on 09/04/2026.
//

#include "Trade.h"

LenhGioiHan::LenhGioiHan(double g,double stc, bool mua) {
    this->giaCho = g;
    this->soTienCuoc= stc;
    this->maLenhMua = mua;
}
double LenhGioiHan::tinhPnL(double giaThiTruong) const {
    double phanTram = (giaThiTruong - this->giaCho) / this->giaCho;
    // Tự động tính theo vị thế Long hoặc Short
    if (this->maLenhMua) {
        return this->soTienCuoc * phanTram * 10; // Đòn bẩy x10
    }
    return this->soTienCuoc * (-phanTram) * 10;
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