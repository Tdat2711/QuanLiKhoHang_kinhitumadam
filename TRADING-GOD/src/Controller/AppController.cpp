//
// Created by Khac Lam 's Laptop on 18/04/2026.
//

#include "AppController.h"
#include "noi_thua_lo.h"
#include <iostream>
#include <exception>
#include "../View/giaodien.h"
#include "../Model/Vidientu.h"
#include "../Model/server.h"
#include "../Model/Exception.h"
#include "../../data/DataTaiSan.h"

AppController::AppController() {
    // Khởi tạo các thành phần trong Constructor
    vi = new Vidientu(0.0);
    sv = new Server();
    fileManager = new DataTaiSan("data.csv");
    tradingController = new noi_thua_lo(sv);
}

AppController::~AppController() {
    // Giải phóng bộ nhớ trong Destructor (Tính RAII)
    delete tradingController;
    delete fileManager;
    delete sv;
    delete vi;
}

void AppController::run() {
    try {
        sv->registerWallet("User", vi);
        fileManager->loadData(vi);

        giaodien::veLoiChao();

        tradingController->batDaubieudien();

        giaodien::inLichSu(vi->layLichSu());
        if (fileManager->saveData(vi)) {
            giaodien::thongBao("He thong da luu tai san an toan.");
        }

    } catch (const LoiFile& e) {
        std::cerr << "\n[!] Loi tep tin: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "\n[!] Loi chuong trinh: " << e.what() << std::endl;
    }
}