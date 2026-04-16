#ifndef SERVER_H
#define SERVER_H

#include <unordered_map>
#include <string>
#include "Vidientu.h"
#include "Trade.h"

class Server {
private:
    // Quản lý lệnh đang chạy (ID -> Đối tượng Trade)
    std::unordered_map<int, Trade*> activeTrades;

    // Quản lý ví (Tên người dùng -> Đối tượng Ví)
    std::unordered_map<std::string, Vidientu*> wallets;

    int nextTradeID; // Biến đếm để tự động tạo ID duy nhất cho mỗi lệnh

public:
    Server();
    ~Server();

    // Các hàm nghiệp vụ (Service Methods)
    void registerWallet(std::string name, Vidientu* v);
    int registerTrade(Trade* t);
    void removeTrade(int id);

    // Truy xuất dữ liệu
    Vidientu* getWallet(std::string name);
    std::unordered_map<int, Trade*>& getAllActiveTrades();

    void clearAll(); // Giải phóng toàn bộ bộ nhớ
};

#endif