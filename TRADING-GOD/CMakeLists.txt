cmake_minimum_required(VERSION 4.1)
project(TRADING_GOD)

set(CMAKE_CXX_STANDARD 20)

add_executable(TRADING_GOD src/main.cpp
        src/Model/Exception.cpp
        src/Model/Exception.h
        src/Model/Trade.cpp
        src/Model/Trade.h
        src/Model/Order.cpp
        src/Model/Order.h
        src/Model/Vidientu.cpp
        src/Model/Vidientu.h
        src/View/giaodien.cpp
        src/View/giaodien.h
        src/Controller/noi_thua_lo.cpp
        src/Controller/noi_thua_lo.h
        src/Model/LongOrder.cpp
        src/Model/LongOrder.h
        src/Model/ShortOrder.cpp
        src/Model/ShortOrder.h
)
