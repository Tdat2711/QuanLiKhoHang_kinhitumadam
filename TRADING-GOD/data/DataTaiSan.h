//
// Created by Khac Lam 's Laptop on 15/04/2026.
//

#ifndef TRADING_GOD_DATATAISAN_H
#define TRADING_GOD_DATATAISAN_H

#include <string>
#include <fstream>
#include "../src/Model/Vidientu.h"

class DataTaiSan {
private:
    std::string filePath;

public:
    // Constructor nhận đường dẫn file, mặc định là data.csv
    DataTaiSan(std::string path = "data.csv");

    // Đọc số dư từ file và nạp vào đối tượng Ví (Sử dụng hàm capNhat của Vidientu)
    bool loadData(Vidientu* vi);

    // Lấy số dư hiện tại từ Ví và ghi đè vào file
    bool saveData(Vidientu* vi);
};

#endif //TRADING_GOD_DATATAISAN_H