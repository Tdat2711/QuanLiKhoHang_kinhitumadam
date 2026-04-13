#ifndef NOI_THUA_LO_H
#define NOI_THUA_LO_H

#include <unordered_map>
#include <vector>
#include <string>
#include "../Model/Vidientu.h"
#include "../Model/Trade.h"

class noi_thua_lo {
private:
    std::unordered_map<long long, double> duLieuThiTruong;
    Vidientu* vi;
    std::vector<Trade*> danhSachLenhCho;
public:
    noi_thua_lo(Vidientu* v);
    ~noi_thua_lo();

    void napDuLieu(std::string duongDanFile);
    void themLenhMoi(Trade* t);
    void thucThiGiaoDich();
};

#endif