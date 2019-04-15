cmake_minimum_required(VERSION 3.13)
project(Project7___C___CRM)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Project7___C___CRM
        Customer.h
        CustomerDB.cpp
        CustomerDB.h
        main.cpp
        Project7.cpp
        String.h)
