//
// Created by Khac Lam 's Laptop on 09/04/2026.
//

#ifndef TRADING_GOD_TRADE_H
#define TRADING_GOD_TRADE_H

class Trade {
public:
    virtual ~Trade() {}
    // Trả về: 1 (Khớp mua), -1 (Khớp bán), 0 (Không khớp)
    virtual int kiemTraKhop(double giaThiTruong) = 0;
};

class LenhGioiHan : public Trade {
private:
    double giaCho;
    bool maLenhMua;
public:
    LenhGioiHan(double g, bool mua);

    int kiemTraKhop(double giaThiTruong) override;
};


#endif //TRADING_GOD_TRADE_H