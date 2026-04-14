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
        if (!fileDoc.is_open()) throw LoiFile("data.csv");

        fileDoc >> vonTuFile;
        fileDoc.close();
        vi = new Vidientu(vonTuFile);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(-1500.0, 1500.0);

        while (true) {
            giaodien::inSaoKe(vi->laySoDu("USDT"), vi->laySoDu("BTC"), vi->laySoDu("ETH"));
            std::cout<<"\n";


            int menu;
            std::cout << "1. Vao lenh\n2. Thoat\nChon (1-2): ";
            std::cin >> menu;
            if (menu == 2) break;

            double tienCuoc;
            std::cout << ">>> Nhap so USDT muon cuoc: ";
            std::cin >> tienCuoc;
            if (tienCuoc > vi->laySoDu("USDT")) tienCuoc = vi->laySoDu("USDT");

            int loaiLenh;
            std::cout << "Chon vi the (1: LONG | 2: SHORT): ";
            std::cin >> loaiLenh;

            double giaVao = 68396.0;
            double giaHienTai = giaVao;
            double mucChotLai = tienCuoc * 1.2;
            double mucCatLo = -tienCuoc * 0.6;

            Order lenhTam("BTC", giaVao, tienCuoc);
            lenhTam.setMaLenhMua(loaiLenh == 1);
            std::cout << "\n>>> KHOI TAO: " << lenhTam.xuattin() << std::endl;

            while (true) {
                giaHienTai += dis(gen);
                double phanTram = (giaHienTai - giaVao) / giaVao;
                // Leverage x10
                double loiLo = (loaiLenh == 1) ? (tienCuoc * phanTram * 10) : (tienCuoc * (-phanTram) * 10);

                std::cout << "Gia BTC: " << std::fixed << std::setprecision(2) << giaHienTai
                          << " | PnL: " << (loiLo >= 0 ? "+" : "") << loiLo << " USDT" << std::endl;

                if (loiLo >= mucChotLai || loiLo <= mucCatLo) {
                    bool thắng = (loiLo >= mucChotLai);
                    std::cout << (thắng ? "\n>>> [THANH CONG] CHOT LAI!" : "\n>>> [THAT BAI] CAT LO!") << std::endl;

                    vi->capNhat("USDT", loiLo);

                    // KHI KHỞI TẠO ORDER, TRUYỀN THÊM BIẾN loiLo VÀO CUỐI
                    // Cấu trúc: Order(mã, giá_đóng, số_lượng, tiền_lãi_lỗ)
                    Order* o = new Order("BTC", giaHienTai, tienCuoc);
                    o->setMaLenhMua(loaiLenh == 1);

                    // Bây giờ gọi xuattin() sẽ hiện đầy đủ thông tin
                    std::cout << ">>> DONG LENH: " << o->xuattin() << std::endl;

                    vi->luuLenh(o);
                    break;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }

        }
        giaodien::inLichSu(vi->layLichSu());

        std::ofstream fileGhi("data.csv");
        if (fileGhi.is_open()) {
            fileGhi << vi->laySoDu("USDT");
            fileGhi.close();
        }

        delete vi;

    } catch (const LoiFile& e) {
        std::cerr << "\n[!] Loi he thong: " << e.what() << std::endl;
        if (vi) delete vi;
        return 1;
    } catch (...) {
        std::cerr << "\n[!] Xay ra loi khong xac dinh!" << std::endl;
        if (vi) delete vi;
        return 1;
    }
    return 0;
}