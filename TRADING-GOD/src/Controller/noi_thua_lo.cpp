#include "noi_thua_lo.h"
#include "../Model/Exception.h"
#include <fstream>
#include <sstream>
#include "../Model/LongOrder.h"
#include "../Model/ShortOrder.h"

noi_thua_lo::noi_thua_lo(Vidientu* v) {
    this->vi = v;
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