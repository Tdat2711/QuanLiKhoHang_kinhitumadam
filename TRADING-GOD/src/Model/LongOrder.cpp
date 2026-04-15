//
// Created by Khac Lam 's Laptop on 15/04/2026.
//

#include "LongOrder.h"

LongOrder::LongOrder(std::string ma, double g, double sl) : Order(ma, g, sl) {
    this->getMaLenhMua(true); // Đè giá trị mặc định của cha thành true
}

std::string LongOrder::loaiLenh() const {
    return "LONG";
}