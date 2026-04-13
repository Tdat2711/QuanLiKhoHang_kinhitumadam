#include "noi_thua_lo.h"
#include "../Model/Exception.h"
#include <fstream>
#include <sstream>

noi_thua_lo::noi_thua_lo(Vidientu* v) {
    this->vi = v;
}

noi_thua_lo::~noi_thua_lo() {
    // Giải phóng các lệnh chưa khớp để tránh rò rỉ bộ nhớ
    for (auto t : this->danhSachLenhCho) {
        delete t;
    }
    this->danhSachLenhCho.clear();
}

void noi_thua_lo::napDuLieu(std::string duongDanFile) {
    std::ifstream f(duongDanFile);
    if (!f.is_open()) throw LoiFile(duongDanFile);

    std::string dong, thoiGian, gia;
    std::getline(f, dong); // Bỏ qua tiêu đề CSV

    while (std::getline(f, dong)) {
        std::stringstream ss(dong);
        if (std::getline(ss, thoiGian, ',') && std::getline(ss, gia, ',')) {
            this->duLieuThiTruong[std::stoll(thoiGian)] = std::stod(gia);
        }
    }
}

void noi_thua_lo::themLenhMoi(Trade* t) {
    this->danhSachLenhCho.push_back(t);
}

void noi_thua_lo::thucThiGiaoDich() {
    for (auto const& [ts, giaHienTai] : this->duLieuThiTruong) {
        for (auto it = this->danhSachLenhCho.begin(); it != this->danhSachLenhCho.end(); ) {
            int ketQua = (*it)->kiemTraKhop(giaHienTai);
            if (ketQua == 1 && this->vi->laySoDu("USDT") >= giaHienTai) {
                // Khớp lệnh MUA
                this->vi->capNhat("USDT", -giaHienTai);
                this->vi->capNhat("BTC", 1.0);

                Order* o = new Order("BTC", giaHienTai, 1.0);
                o->setMaLenhMua(true); // Gán là lệnh mua
                this->vi->luuLenh(o);

                delete *it;
                it = this->danhSachLenhCho.erase(it);
            }
            else if (ketQua == -1 && this->vi->laySoDu("BTC") >= 1.0) {
                // Khớp lệnh BÁN
                this->vi->capNhat("BTC", -1.0);
                this->vi->capNhat("USDT", giaHienTai);

                this->vi->luuLenh(new Order("BTC", giaHienTai, 1.0));

                delete *it;
                it = this->danhSachLenhCho.erase(it);
            }
            else {
                ++it;
            }
        }
    }
}
