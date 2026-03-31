#ifndef CODE_FULFILLMENTCENTER_H
#define CODE_FULFILLMENTCENTER_H

#include <unordered_map>
#include <string>

#include "Supplier.h"
#include "Employee.h"
#include "Product.h"

class FulfillmentCenter {
private:
    std::unordered_map<int, Employee> employee;
    std::unordered_map<int, Supplier> supplier;
    std::unordered_map<std::string, Product> inventory;
public:
    void registerEmployee(int id, const std::string& name) {
        employee.emplace(id, Employee(id, name,false,0));
    }

    void registerSupplier(int id, const std::string& name) {
        supplier.emplace(id, Supplier(id, name));
    }

    bool registerProduct(const std::string& sku, int supplierID) {
        if (supplier.find(supplierID) == supplier.end()) {
            return false;
        }
        inventory.emplace(sku, Product(sku, supplierID,0));
        return true;
    }

    std::string getEmployeeName(int id) {
        auto it = employee.find(id);
        if (it == employee.end()) {
            return "";
        }
        return it->second.getName();
    }

    int getProductStock(const std::string& sku) {
        auto it = inventory.find(sku);
        if (it == inventory.end()) {
            return -1;
        }
        return it->second.getStock();
    }

    double getSupplierReliability(int id) {
        auto it = supplier.find(id);
        if (it == supplier.end()) {
            return -1;
        }
        return it->second.getReliabilityScore();
    }

    bool updateEmployeeName(int id, const std::string& newName) {
        auto it = employee.find(id);
        if (it == employee.end()) {
            return false;
        }
        it->second.setName(newName);
        return true;
    }

    bool updateProductSupplier(const std::string& sku, int newSupplierID) {
        auto itProd = inventory.find(sku);
        auto itSupp = supplier.find(newSupplierID);
        if (itProd == inventory.end() || itSupp == supplier.end()) {
            return false;
        }
        itProd->second.setSupplierId(newSupplierID);
        return true;
    }

    bool removeEmployee(int id) {
        auto it = employee.find(id);
        if (it != employee.end()) {
            employee.erase(it);
            return true;
        }
        return false;
    }

    bool removeProduct(const std::string& sku) {
        auto it = inventory.find(sku);
        if (it != inventory.end()) {
            inventory.erase(it);
            return true;
        }
        return false;
    }

    bool removeSupplier(int id) {
        auto it = supplier.find(id);
        if (it == supplier.end()) {
            return false;
        }
        for (const auto& pair : inventory) {
            if (pair.second.getSupplierId() == id) {
                return false;
            }
        }
        supplier.erase(it);
        return true;
    }
    void clockInEmployee(int id) {
        auto it = employee.find(id);
        if (it != employee.end()) {
            it->second.clockIn();
        }
    }
    bool receiveInboundShipment(const std::string& sku, int qty, bool isOnTime) {
        auto it = inventory.find(sku);
        if (it == inventory.end()) {
            return false;
        }
        Product& p = it->second;
        p.addStock(qty);
        auto sIt = supplier.find(p.getSupplierId());
        if (sIt != supplier.end()) {
            sIt->second.recordDelivery(isOnTime);
        }
        return true;
    }

    int assignPickTask(const std::string& sku, int qty) {
        auto it = inventory.find(sku);
        if (it == inventory.end()) return -1;

        Product& p = it->second;
        if (!p.removeStock(qty)) {
            return -1;
        }

        Employee* bestEmp = nullptr;
        for (auto& pair : employee) {
            Employee& emp = pair.second;
            if (emp.getisclockedIn()) {
                if (bestEmp == nullptr || 
                    emp.getitemsPickedToday() < bestEmp->getitemsPickedToday() ||
                    (emp.getitemsPickedToday() == bestEmp->getitemsPickedToday() && emp.getID() < bestEmp->getID())) {
                    bestEmp = &emp;
                }
            }
        }

        if (bestEmp == nullptr) {
            p.addStock(qty);
            return -1;
        }
        bestEmp->assignPick(qty);
        return bestEmp->getID();
    }
};

#endif