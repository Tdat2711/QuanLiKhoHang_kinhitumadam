//
// Created by Khac Lam 's Laptop on 18/04/2026.
//

#ifndef TRADING_GOD_APPCONTROLLER_H
#define TRADING_GOD_APPCONTROLLER_H

#include "../Model/server.h"
#include "../Model/Vidientu.h"
#include "../Controller/noi_thua_lo.h"
#include "../../data/DataTaiSan.h"
class AppController {
private:
    Vidientu* vi;
    Server* sv;
    noi_thua_lo* tradingController;
    DataTaiSan* fileManager;
public:
    AppController();
    ~AppController();
    void run();
};

#endif //TRADING_GOD_APPCONTROLLER_H