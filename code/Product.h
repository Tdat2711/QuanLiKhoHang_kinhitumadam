#ifndef CODE_PRODUCT_H
#define CODE_PRODUCT_H
#include <string>

class Product {
private:
    std::string sku;
    int supplierId; // Đổi ID thành Id cho đồng bộ
    int stockLevel;

public:
    // Constructor mặc định (cần thiết khi dùng với std::unordered_map)
    Product() {
        sku = "";
        supplierId = 0;
        stockLevel = 0;
    }

    Product(std::string sk, int sup, int sto) {
        this->sku = sk;
        this->supplierId = sup;
        this->stockLevel = sto;
    }

    void addStock(int qty) {
        stockLevel += qty;
    }

    bool removeStock(int qty) {
        if (qty > stockLevel) {
            return false;
        } else {
            stockLevel -= qty;
            return true;
        }
    }

    int getStock() const {
        return stockLevel;
    }

    std::string getSku() const {
        return sku;
    }

    int getSupplierId() const {
        return supplierId;
    }

    void setSupplierId(int newId) {
        this->supplierId = newId;
    }
};

#endif //CODE_PRODUCT_H