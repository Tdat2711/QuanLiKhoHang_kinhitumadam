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
    virtual bool laLenhMua() = 0;

    virtual double tinhPnL(double giaThiTruong) const = 0;
    virtual double getTienCuoc() const = 0;
};

class LenhGioiHan : public Trade {
private:
    double giaCho;
    double soTienCuoc;
    bool maLenhMua;
public:
    LenhGioiHan(double g,double stc, bool mua);

    int kiemTraKhop(double giaThiTruong) override;
    bool laLenhMua() override {
        return this->maLenhMua;
    }
    double tinhPnL(double giaThiTruong) const override;
    double getTienCuoc() const override { return this->soTienCuoc; }
};


#endif //TRADING_GOD_TRADE_H