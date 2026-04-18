#include "noi_thua_lo.h"
#include "../Model/Exception.h"
#include <fstream>
#include <sstream>
#include "../Model/LongOrder.h"
#include "../Model/ShortOrder.h"
#include <random>
#include <thread>
#include <chrono>
#include "../View/giaodien.h"
#include <iostream>
#include <iomanip>

// Constructor dùng Server
noi_thua_lo::noi_thua_lo(Server* s) : sv(s) {}

noi_thua_lo::~noi_thua_lo() {}

void noi_thua_lo::napDuLieu(std::string duongDanFile) {
    std::ifstream file(duongDanFile);
    if (!file.is_open()) return;
    long long timestamp;
    double gia;
    while (file >> timestamp >> gia) {
        duLieuThiTruong[timestamp] = gia;
    }
    file.close();
}

void noi_thua_lo::themLenhMoi(Trade* t) {
    if (t != nullptr) {
        sv->registerTrade(t); // Đẩy vào Server
    }
}

void noi_thua_lo::thucThiGiaoDich() {
}

void noi_thua_lo::batDaubieudien() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-1500.0, 1500.0); // Biến động giá

    Vidientu* vi = sv->getWallet("User");
    if (!vi) {
        giaodien::thongBao("Loi: Khong tim thay vi nguoi dung!");
        return;
    }

    while (true) {
        giaodien::inSaoKe(vi->laySoDu("USDT"), vi->laySoDu("BTC"), vi->laySoDu("ETH"));

        int menu = giaodien::layLuaChonMenu();
        if (menu == 2) break;

        double tienCuoc = giaodien::nhapSoTien("Nhap so USDT muon cuoc");

        if (!vi->coDuKhaNang(tienCuoc)) {
            giaodien::thongBao("So du khong du de thuc hien lenh!");
            continue;
        }

        int loaiLenh = giaodien::chonLoaiViThe();

        double giaVao = 70396.0;
        double giaHienTai = giaVao;

        Trade* lenhHienTai = new LenhGioiHan(giaVao, tienCuoc, (loaiLenh == 1));
        int idLenh = sv->registerTrade(lenhHienTai);

        while (true) {
            giaHienTai += dis(gen);
            double loiLo = lenhHienTai->tinhPnL(giaHienTai);

            giaodien::hienThiBangDienTu(giaHienTai, loiLo);

            if (loiLo >= tienCuoc * 1.2 || loiLo <= -tienCuoc * 0.6) {
                vi->capNhat("USDT", loiLo);

                Order* o = (loaiLenh == 1) ?
                    (Order*)new LongOrder("BTC", giaHienTai, tienCuoc) :
                    (Order*)new ShortOrder("BTC", giaHienTai, tienCuoc);

                vi->luuLenh(o);

                std::cout << std::endl;
                giaodien::thongBao(loiLo > 0 ? "CHOT LAI THANH CONG!" : "DA CAT LO!");
                break;
            }

            // Tốc độ nhảy giá (100ms)
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        sv->removeTrade(idLenh);
    }
}