//
// Created by Khac Lam 's Laptop on 15/04/2026.
//

#include "DataTaiSan.h"

DataTaiSan::DataTaiSan(std::string path) : filePath(path) {}

bool DataTaiSan::loadData(Vidientu* vi) {
    if (vi == nullptr) return false;

    std::ifstream file(filePath);
    if (!file.is_open()) return false;

    double soDu;
    if (file >> soDu) {
        // Nạp số dư vào ví. Giả định ví dùng đơn vị USDT làm mặc định
        vi->capNhat("USDT", soDu);
    }

    file.close();
    return true;
}

bool DataTaiSan::saveData(Vidientu* vi) {
    if (vi == nullptr) return false;

    std::ofstream file(filePath);
    if (!file.is_open()) return false;

    // Ghi lại số dư USDT hiện có vào file
    file << vi->laySoDu("USDT");

    file.close();
    return true;
}