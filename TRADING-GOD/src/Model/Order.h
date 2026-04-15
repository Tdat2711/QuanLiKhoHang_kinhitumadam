#ifndef TRADING_GOD_ORDER_H
#define TRADING_GOD_ORDER_H

#include <string>

class Order {
private:
    std::string maCoin;
    double gia;
    double soLuong;
    bool maLenhMua;

public:
    Order(std::string ma, double g, double sl);
    virtual ~Order();

    // dùng thêm tham số
    void getMaLenhMua(bool mua);

    //getter
    std::string getMaCoin() const;
    double getGia() const;
    double getSoLuong() const;
    bool checkMaLenh() const;

    virtual std::string loaiLenh() const = 0;
    virtual std::string xuattin() const;
};

#endif