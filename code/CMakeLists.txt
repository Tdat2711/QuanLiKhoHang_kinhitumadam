cmake_minimum_required(VERSION 4.1)
project(code)

set(CMAKE_CXX_STANDARD 20)

add_executable(code main.cpp
        Employee.cpp
        Employee.h
        Supplier.cpp
        Supplier.h
        Product.cpp
        Product.h
        FulfillmentCenter.cpp
        FulfillmentCenter.h
        Service.cpp
        Service.h)
