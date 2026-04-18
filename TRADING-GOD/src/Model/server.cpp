//
// Created by Khac Lam 's Laptop on 15/04/2026.
//

#include "server.h"

Server::Server() : nextTradeID(1) {}
Server::~Server() {
    clearAll();
}

void Server::registerWallet(std::string name, Vidientu* v) {
    if (v != nullptr) {
        wallets.emplace(name, v);
    }
}
int Server::registerTrade(Trade* t) {
    int id = nextTradeID++;
    activeTrades.emplace(id, t);
    return id;
}

void Server::removeTrade(int id) {
    auto it = activeTrades.find(id);
    if (it != activeTrades.end()) {
        delete it->second; // Xóa đối tượng Trade*
        activeTrades.erase(it);
    }
}

Vidientu* Server::getWallet(std::string name) {
    auto it = wallets.find(name);
    if (it == wallets.end()) return nullptr;
    return it->second;
}

// Lấy danh sách lệnh để Controller thực hiện vòng lặp tính PnL
std::unordered_map<int, Trade*>& Server::getAllActiveTrades() {
    return activeTrades;
}

// Dọn dẹp bộ nhớ
void Server::clearAll() {
    for (auto& pair : activeTrades) {
        delete pair.second;
    }
    activeTrades.clear();
}