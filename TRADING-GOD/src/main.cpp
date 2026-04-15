#include <iostream>
#include <fstream>
#include "Model/Vidientu.h"
#include "Controller/noi_thua_lo.h"
#include "View/giaodien.h"
#include "Model/Exception.h"

int main() {
    // Khởi tạo con trỏ ở ngoài để đảm bảo có thể delete trong catch nếu lỗi
    Vidientu* vi = nullptr;
    noi_thua_lo* controller = nullptr;

    try {
        // 1. Khởi tạo Model với số dư 0 (Controller sẽ nạp số dư thực từ file sau)
        vi = new Vidientu(0.0);

        // 2. Khởi tạo Controller
        // Trong Constructor của noi_thua_lo, bạn nên thực hiện việc đọc data.csv
        controller = new noi_thua_lo(vi);

        // 3. Hiển thị giao diện chào mừng
        giaodien::veLoiChao();

        // 4. Chạy vòng lặp điều khiển chính (Nhạc trưởng điều phối M và V)
        controller->batDaubieudien();

        // 5. Ghi lại dữ liệu cuối cùng vào file trước khi kết thúc chương trình
        std::ofstream fileGhi("data.csv");
        if (fileGhi.is_open()) {
            fileGhi << vi->laySoDu("USDT");
            fileGhi.close();
            std::cout << "\n>>> [HE THONG] Da luu tai san an toan." << std::endl;
        }

        // Giải phóng bộ nhớ
        delete controller;
        delete vi;

    } catch (const LoiFile& e) {
        // Xử lý riêng lỗi liên quan đến file dữ liệu
        std::cerr << "\n[!] Loi tep tin: " << e.what() << std::endl;
        if (controller) delete controller;
        if (vi) delete vi;
        return 1;
    } catch (const std::exception& e) {
        // Xử lý các lỗi tiêu chuẩn khác
        std::cerr << "\n[!] Loi chuong trinh: " << e.what() << std::endl;
        if (controller) delete controller;
        if (vi) delete vi;
        return 1;
    } catch (...) {
        // Phòng hờ các lỗi không xác định
        std::cerr << "\n[!] Da xay ra loi he thong khong xac dinh!" << std::endl;
        if (controller) delete controller;
        if (vi) delete vi;
        return 1;
    }

    return 0;
}