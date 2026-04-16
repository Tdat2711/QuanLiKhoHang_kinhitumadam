#include <iostream>
#include <fstream>
#include "../src/Model/server.h"
#include "../data/DataTaiSan.h"
#include "Model/Vidientu.h"
#include "Controller/noi_thua_lo.h"
#include "View/giaodien.h"
#include "Model/Exception.h"

int main() {
    // Khởi tạo các con trỏ bằng nullptr để quản lý bộ nhớ an toàn
    Vidientu* vi = nullptr;
    Server* sv = nullptr;           // Thêm Server quản lý tập trung
    noi_thua_lo* controller = nullptr;

    try {
        // 1. Khởi tạo các thành phần cốt lõi
        vi = new Vidientu(0.0);
        sv = new Server();

        // Đăng ký ví vào hệ thống quản lý của Server
        sv->registerWallet("User", vi);

        // 2. Sử dụng lớp DataTaiSan để nạp dữ liệu (Thay cho việc đọc file thủ công)
        DataTaiSan fileManager("data.csv");
        if (!fileManager.loadData(vi)) {
            // Có thể quăng exception nếu file quan trọng không mở được
            // throw LoiFile("Khong the nap du lieu tu data.csv");
        }

        // 3. Khởi tạo Controller (Giao Server thay vì chỉ giao mỗi Ví)
        controller = new noi_thua_lo(sv);

        giaodien::veLoiChao();

        // 4. Chạy luồng xử lý chính
        controller->batDaubieudien();
        giaodien::inLichSu(vi->layLichSu());

        // 5. Sử dụng DataTaiSan để ghi dữ liệu (Thay cho phần ofstream thủ công)
        if (fileManager.saveData(vi)) {
            std::cout << "\n>>> [HE THONG] Da luu tai san an toan." << std::endl;
        }


        // 6. Giải phóng bộ nhớ đúng trình tự
        delete controller;
        delete sv;
        delete vi;

    } catch (const LoiFile& e) {
        std::cerr << "\n[!] Loi tep tin: " << e.what() << std::endl;
        if (controller) delete controller;
        if (sv) delete sv;
        if (vi) delete vi;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "\n[!] Loi chuong trinh: " << e.what() << std::endl;
        if (controller) delete controller;
        if (sv) delete sv;
        if (vi) delete vi;
        return 1;
    } catch (...) {
        std::cerr << "\n[!] Da xay ra loi he thong khong xac dinh!" << std::endl;
        if (controller) delete controller;
        if (sv) delete sv;
        if (vi) delete vi;
        return 1;
    }

    return 0;
}
