#ifndef NOI_THUA_LO_H
#define NOI_THUA_LO_H

#include <unordered_map>
#include <vector>
#include <string>
#include "../Model/Vidientu.h"
#include "../Model/Trade.h"
#include "../Model/server.h" // Thêm include này

class noi_thua_lo {
private:
    std::unordered_map<long long, double> duLieuThiTruong;
    Server* sv; // Thay Vidientu* bằng Server* để quản lý tập trung
    // Không cần vector danhSachLenhCho nữa vì Server đã quản lý trong map rồi
public:
    // Constructor nhận Server thay vì Vidientu
    noi_thua_lo(Server* s);
    ~noi_thua_lo();

    void napDuLieu(std::string duongDanFile);
    void themLenhMoi(Trade* t);
    void thucThiGiaoDich();
    void batDaubieudien();
};

#endif