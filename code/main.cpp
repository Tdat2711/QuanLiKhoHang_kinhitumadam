#include <iostream>
#include <iomanip>
#include "FulfillmentCenter.h"

using namespace std;

int main() {
    FulfillmentCenter fc;

    // 1. Đăng ký Nhà cung cấp và Sản phẩm
    fc.registerSupplier(101, "Vinamilk");
    fc.registerSupplier(102, "TH True Milk");

    fc.registerProduct("MILK-01", 101);
    fc.registerProduct("MILK-02", 102);

    // 2. Nhập hàng (Inbound)
    cout << "--- Nhap hang vao kho ---" << endl;
    fc.receiveInboundShipment("MILK-01", 100, true); // Giao dung han
    fc.receiveInboundShipment("MILK-02", 50, false); // Giao tre han

    cout << "Ton kho MILK-01: " << fc.getProductStock("MILK-01") << endl;
    cout << "Do tin cay Vinamilk: " << fc.getSupplierReliability(101) << "%" << endl;
    cout << "Do tin cay TH True Milk: " << fc.getSupplierReliability(102) << "%" << endl;
    cout << "-------------------------" << endl << endl;

    // 3. Đăng ký và cho Nhân viên đi làm
    fc.registerEmployee(1, "Khac Lam");
    fc.registerEmployee(2, "Tuan Dat");

    // Phai dung ham tu lop Employee de ClockIn (Gia su ban lay doi tuong tu map hoac bo sung ham vao FC)
    // De don gian, toi gia su ban da co ham clockIn trong Employee.h
    // Nhung vi map trong FC la private, ban nen bo sung public method vao FC de clockIn:
    /* void clockInEmployee(int id) {
           auto it = employee.find(id);
           if (it != employee.end()) it->second.clockIn();
       }
    */

    // Test Assign Pick Task (Se tra ve -1 vi chua co ai Clock In)
    cout << "--- Phan cong lay hang (Chua ai di lam) ---" << endl;
    int empId = fc.assignPickTask("MILK-01", 10);
    cout << "Ket qua phan cong: " << empId << " (Ky vong: -1)" << endl;
    cout << "------------------------------------------" << endl << endl;

    // Lưu ý: Để code này chạy được hoàn hảo, bạn cần đảm bảo các hàm
    // getID(), getisclockedIn(), getitemsPickedToday()
    // đều viết đúng chữ hoa/thường trong FulfillmentCenter.h như lỗi ban nãy.
    // 4. Cho nhân viên đi làm và phân công thực tế
    cout << "--- Phan cong lay hang (Sau khi di lam) ---" << endl;
    fc.clockInEmployee(1); // Cho Khac Lam đi làm
    fc.clockInEmployee(2); // Cho Tuan Dat đi làm

    int assignedId = fc.assignPickTask("MILK-01", 20);
    cout << "Nhan vien nhan viec ID: " << assignedId << " (Ky vong: 1)" << endl;
    cout << "Ton kho MILK-01 con lai: " << fc.getProductStock("MILK-01") << endl;
    cout << "------------------------------------------" << endl;
    return 0;
}