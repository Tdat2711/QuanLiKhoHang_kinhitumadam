//
// Created by Khac Lam 's Laptop on 09/04/2026.
//

#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <exception>
#include <string>

class Exception : public std::exception {
private:
    std::string thongBao;

public:

    Exception(const std::string& msg) : thongBao(msg) {}
    virtual const char* what() const noexcept override {
        return thongBao.c_str();
        // c_str() trả về const char* để tương thích với std::exception
        // Ghi đè hàm what() của std::exception
        // noexcept: đảm bảo hàm này không ném thêm exception khác
    }
};
class LoiFile : public std::exception {
private:
    std::string message;
public:
    LoiFile(const std::string& tenFile) {
        message = "Loi:deo mo duoc file" + tenFile;
    }
    const char* what() const noexcept override {
        return message.c_str();
    }
};
#endif