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

noi_thua_lo::noi_thua_lo(Vidientu* v) {
    this->vi = v;

    // Tự động nạp dữ liệu từ file khi khởi tạo Controller
    double vonTuFile = 0.0;
    std::ifstream fileDoc("data.csv");
    if (fileDoc.is_open()) {
        fileDoc >> vonTuFile;
        fileDoc.close();

        // Dùng hàm capNhat có sẵn để đưa tiền vào ví
        this->vi->capNhat("USDT", vonTuFile);
    }
}
noi_thua_lo::~noi_thua_lo() {
    for (auto t : this->danhSachLenhCho) {
        delete t;
    }
    this->danhSachLenhCho.clear();
}

// ... các hàm napDuLieu, themLenhMoi giữ nguyên ...

void noi_thua_lo::thucThiGiaoDich() {
    for (auto const& [ts, giaHienTai] : this->duLieuThiTruong) {
        for (auto it = this->danhSachLenhCho.begin(); it != this->danhSachLenhCho.end(); ) {

            int ketQua = (*it)->kiemTraKhop(giaHienTai);

            // Lấy loại lệnh cực kỳ đơn giản qua hàm ảo
            bool kiemTraLong = (*it)->laLenhMua();

            if (ketQua == 1 && this->vi->laySoDu("USDT") >= giaHienTai) {
                // --- KHỚP MUA ---
                this->vi->capNhat("USDT", -giaHienTai);
                this->vi->capNhat("BTC", 1.0);

                Order* o = nullptr;
                if (kiemTraLong == true) {
                    o = new LongOrder("BTC", giaHienTai, 1.0);
                } else {
                    o = new ShortOrder("BTC", giaHienTai, 1.0);
                }
                this->vi->luuLenh(o);

                delete *it;
                it = this->danhSachLenhCho.erase(it);
            }
            else if (ketQua == -1 && this->vi->laySoDu("BTC") >= 1.0) {
                // --- KHỚP BÁN ---
                this->vi->capNhat("BTC", -1.0);
                this->vi->capNhat("USDT", giaHienTai);

                Order* o = nullptr;
                if (kiemTraLong == true) {
                    o = new LongOrder("BTC", giaHienTai, 1.0);
                } else {
                    o = new ShortOrder("BTC", giaHienTai, 1.0);
                }
                this->vi->luuLenh(o);

                delete *it;
                it = this->danhSachLenhCho.erase(it);
            }
            else {
                ++it;
            }
        }
    }
}

void noi_thua_lo::batDaubieudien() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-1500.0, 1500.0);

    while (true) {
        // Gọi View để in sao kê
        giaodien::inSaoKe(vi->laySoDu("USDT"), vi->laySoDu("BTC"), vi->laySoDu("ETH"));

        int menu;
        std::cout << "\n1. Vao lenh\n2. Thoat\nChon (1-2): ";
        std::cin >> menu;
        if (menu == 2) break;

        double tienCuoc;
        std::cout << ">>> Nhap so USDT muon cuoc: ";
        std::cin >> tienCuoc;

        // Gọi Model (Vidientu) để kiểm tra dữ liệu (Encapsulation)
        if (!vi->coDuKhaNang(tienCuoc)) {
            giaodien::thongBao("So du khong du!");
            continue;
        }

        int loaiLenh;
        std::cout << "Chon vi the (1: LONG | 2: SHORT): ";
        std::cin >> loaiLenh;

        double giaVao = 68396.0;
        double giaHienTai = giaVao;

        // Khởi tạo Trade (Đa hình)
        Trade* lenhHienTai = new LenhGioiHan(giaVao, tienCuoc, (loaiLenh == 1));

        while (true) {
            giaHienTai += dis(gen);
            double loiLo = lenhHienTai->tinhPnL(giaHienTai);

            // Gọi View để in giá và PnL
            std::cout << "Gia BTC: " << std::fixed << std::setprecision(2) << giaHienTai
                      << " | PnL: " << (loiLo >= 0 ? "+" : "") << loiLo << " USDT" << std::endl;

            if (loiLo >= tienCuoc * 1.2 || loiLo <= -tienCuoc * 0.6) {
                vi->capNhat("USDT", loiLo);

                // Tạo lịch sử Order (Polymorphism)
                Order* o = (loaiLenh == 1) ?
                    (Order*)new LongOrder("BTC", giaHienTai, tienCuoc) :
                    (Order*)new ShortOrder("BTC", giaHienTai, tienCuoc);
                vi->luuLenh(o);

                giaodien::thongBao(loiLo > 0 ? "CHOT LAI THANH CONG!" : "DA CAT LO!");
                break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        delete lenhHienTai;
    }
}