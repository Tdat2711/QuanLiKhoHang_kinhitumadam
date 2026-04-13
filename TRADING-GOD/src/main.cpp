#include <iostream>
#include <iomanip>
#include <random>
#include <thread>
#include <chrono>
#include <fstream>
#include "Model/Vidientu.h"
#include "Model/Order.h"
#include "View/giaodien.h"
#include "Model/Exception.h"

int main() {
    Vidientu* vi = nullptr;

    try {
        giaodien::veLoiChao();

        double vonTuFile = 0.0;
        std::ifstream fileDoc("data.csv");

        if (!fileDoc.is_open()) {
            throw LoiFile("data.csv");
        }

        fileDoc >> vonTuFile;
        fileDoc.close();
        // Khởi tạo ví với số vốn vừa đọc
        vi = new Vidientu(vonTuFile);

        bool tiepTuc = true;
        while (tiepTuc) {
            std::cout << "[ TAI SAN HIEN TAI ] " << vi->laySoDu("USDT") << " USDT" << std::endl;
            int menu;
            std::cout << "1. vao lenh" << std::endl;
            std::cout << "2. exit" << std::endl;
            std::cout << "Chon (1-2): ";
            std::cin >> menu;

            if (menu == 2) {
                tiepTuc = false;
                break;
            }

            double tienCuoc;
            std::cout << ">>> Nhap so USDT muon cuoc: ";
            std::cin >> tienCuoc;
            if (tienCuoc > vi->laySoDu("USDT")) tienCuoc = vi->laySoDu("USDT");

            int loaiLenh; // 1: Long, 2: Short
            std::cout << "Chon vi the (1: LONG | 2: SHORT): ";
            std::cin >> loaiLenh;

            double giaVao = 50000.0;
            double giaHienTai = giaVao;
            double mucChotLai = tienCuoc * 1.2;
            double mucCatLo = tienCuoc * 0.6;

            std::cout << "\n>>> DANG CHAY LENH " << (loaiLenh == 1 ? "LONG" : "SHORT") << "..." << std::endl;

            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<> dis(-1000.0, 1000.0);

            while (true) {
                giaHienTai += dis(gen);
                double phanTram = (giaHienTai - giaVao) / giaVao;
                double loiLo = (loaiLenh == 1) ? (tienCuoc * phanTram * 10) : (tienCuoc * (-phanTram) * 10);

                std::cout << "Gia BTC: " << giaHienTai
                          << " | PnL: " << (loiLo >= 0 ? "+" : "") << loiLo << " USDT" << std::endl;

                if (loiLo >= mucChotLai) {
                    std::cout << "\n>>> [THANH CONG] CHOT LAI +120%!" << std::endl;
                    vi->capNhat("USDT", loiLo);
                    Order* o = new Order("BTC", giaHienTai, 0.0);
                    o->setMaLenhMua(loaiLenh == 1);
                    vi->luuLenh(o);
                    break;
                }

                if (loiLo <= -mucCatLo) {
                    std::cout << "\n>>> [THAT BAI] CAT LO -60%!" << std::endl;
                    vi->capNhat("USDT", loiLo);
                    Order* o = new Order("BTC", giaHienTai, 0.0);
                    o->setMaLenhMua(loaiLenh == 1);
                    vi->luuLenh(o);
                    break;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
        }


        std::cout << "\n--- tong ket thua lo---" << std::endl;
        giaodien::inSaoKe(vi->laySoDu("USDT"), vi->laySoDu("BTC"));

        // Ghi lại số dư cuối cùng vào data.csv
        std::ofstream fileGhi("data.csv");
        if (fileGhi.is_open()) {
            fileGhi << vi->laySoDu("USDT");
            fileGhi.close();
        }

        delete vi;

    } catch (const LoiFile& e) {
        std::cerr << "\n[!] loi he thong: " << e.what() << std::endl;
        if (vi) delete vi;
        return 1;
    } catch (...) {
        std::cerr << "\n[!]xay ra loi deo xac dinh dc!" << std::endl;
        if (vi) delete vi;
        return 1;
    }

    return 0;
}