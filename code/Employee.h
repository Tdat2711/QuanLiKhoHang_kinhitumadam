#ifndef CODE_EMPLOYEE_H
#define CODE_EMPLOYEE_H
#include <string>

class Employee {
private:
    int employeeId;
    std::string name;
    bool isClockedIn;
    int itemsPickedToday;

public:
    Employee();
    Employee(int id, std::string n, bool clocked, int IPT) {
        employeeId = id;
        name = n;
        isClockedIn = clocked;
        itemsPickedToday = IPT;
    }

    void clockIn() {
        isClockedIn = true;
    }

    void clockOut() {
        isClockedIn = false;
    }

    bool assignPick(int qty) {
        if (isClockedIn == false) {
            return false;
        } else {
            itemsPickedToday += qty;
            return true;
        }
    }

    int getID() const {
        return employeeId;
    }
    void setName(std::string n) {
        name = n;
    }

    std::string getName() const {
        return name;
    }

    bool getisclockedIn() const {
        return isClockedIn;
    }

    int getitemsPickedToday() const {
        return itemsPickedToday;
    }
};

#endif //CODE_EMPLOYEE_H