//
// Created by Khac Lam 's Laptop on 15/04/2026.
//

#include "ShortOrder.h"

ShortOrder::ShortOrder(std::string ma, double g, double sl) : Order(ma, g, sl) {
    this->getMaLenhMua(false); // Đảm bảo luôn là false
}

std::string ShortOrder::loaiLenh() const {
    return "SHORT";
}