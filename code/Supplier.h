#ifndef CODE_SUPPLIER_H
#define CODE_SUPPLIER_H
#include <string>

class Supplier {
private:
    int supplierID;
    std::string name;
    int totalDeliveries;
    int onTimeDeliveries;

public:
    Supplier();
    Supplier(int su, std::string n) {
        supplierID = su;
        name = n;
        totalDeliveries = 0;
        onTimeDeliveries = 0;
    }

    void recordDelivery(bool isOnTime) {
        totalDeliveries += 1;
        if (isOnTime == true)
            onTimeDeliveries += 1;
    }

    double getReliabilityScore() const {
        if (totalDeliveries == 0) {
            return 100.0;
        } else {
            return ((double)onTimeDeliveries / totalDeliveries) * 100.0;
        }
    }

    int getSupplierID() const {
        return supplierID;
    }

    std::string getName() const {
        return name;
    }

    int getTotalDeliveries() const {
        return totalDeliveries;
    }

    int getOnTimeDeliveries() const {
        return onTimeDeliveries;
    }
};

#endif //CODE_SUPPLIER_H