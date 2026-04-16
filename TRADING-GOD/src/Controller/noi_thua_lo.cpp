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
    // Hàm này Đạt giữ để xử lý khớp lệnh từ file nếu cần
    // Hiện tại tập trung vào luồng Simulator ở dưới
}

void noi_thua_lo::batDaubieudien() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-1500.0, 1500.0);

    // Lấy ví từ Server
    Vidientu* vi = sv->getWallet("User");
    if (!vi) return;

    while (true) {
        // In sao kê từ ví trong Server
        giaodien::inSaoKe(vi->laySoDu("USDT"), vi->laySoDu("BTC"), vi->laySoDu("ETH"));

        int menu;
        std::cout << "\n1. Vao lenh\n2. Thoat\nChon (1-2): ";
        std::cin >> menu;
        if (menu == 2) break;

        double tienCuoc;
        std::cout << ">>> Nhap so USDT muon cuoc: ";
        std::cin >> tienCuoc;

        if (!vi->coDuKhaNang(tienCuoc)) {
            giaodien::thongBao("So du khong du!");
            continue;
        }

        int loaiLenh;
        std::cout << "Chon vi the (1: LONG | 2: SHORT): ";
        std::cin >> loaiLenh;

        double giaVao = 68396.0;
        double giaHienTai = giaVao;

        // Khởi tạo Trade và đăng ký vào Server (Đa hình)
        Trade* lenhHienTai = new LenhGioiHan(giaVao, tienCuoc, (loaiLenh == 1));
        int idLenh = sv->registerTrade(lenhHienTai); // Server quản lý ID

        while (true) {
            giaHienTai += dis(gen);
            double loiLo = lenhHienTai->tinhPnL(giaHienTai);

            std::cout << "Gia BTC: " << std::fixed << std::setprecision(2) << giaHienTai
                      << " | PnL: " << (loiLo >= 0 ? "+" : "") << loiLo << " USDT" << std::endl;

            // Chốt lời 20% hoặc cắt lỗ 40% (Giữ nguyên logic cũ của Đạt)
            if (loiLo >= tienCuoc * 1.2 || loiLo <= -tienCuoc * 0.6) {
                vi->capNhat("USDT", loiLo);

                Order* o = (loaiLenh == 1) ?
                    (Order*)new LongOrder("BTC", giaHienTai, tienCuoc) :
                    (Order*)new ShortOrder("BTC", giaHienTai, tienCuoc);
                vi->luuLenh(o);

                giaodien::thongBao(loiLo > 0 ? "CHOT LAI THANH CONG!" : "DA CAT LO!");
                break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        // Sau khi xong lệnh thì xóa khỏi Server để dọn bộ nhớ
        sv->removeTrade(idLenh);
    }
}