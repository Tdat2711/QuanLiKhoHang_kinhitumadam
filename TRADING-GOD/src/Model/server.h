#ifndef SERVER_H
#define SERVER_H

#include <unordered_map>
#include <string>
#include "Vidientu.h"
#include "Trade.h"

class Server {
private:
    std::unordered_map<int, Trade*> activeTrades;
    std::unordered_map<std::string, Vidientu*> wallets;

    int nextTradeID;

public:
    Server();
    ~Server();

    // Các hàm nghiệp vụ
    void registerWallet(std::string name, Vidientu* v);
    int registerTrade(Trade* t);
    void removeTrade(int id);

    // Truy xuất dữ liệu
    Vidientu* getWallet(std::string name);
    std::unordered_map<int, Trade*>& getAllActiveTrades();

    void clearAll();
};

#endif