cmake_minimum_required(VERSION 3.13)
project(Project4___CRM)

set(CMAKE_CXX_STANDARD 14)

include_directories(Project4_starter_files)

add_executable(Project4___CRM
        Project4_starter_files/Invent.h
        Project4_starter_files/main.cpp
        Project4_starter_files/MyString.cpp
        Project4_starter_files/MyString.h
        Project4_starter_files/Project4.cpp)
