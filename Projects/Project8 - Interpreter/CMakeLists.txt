cmake_minimum_required(VERSION 3.13)
project(Project8___Interpreter)

set(CMAKE_CXX_STANDARD 14)

include_directories(../)

add_executable(Project8___Interpreter
        Input.cpp
        Parse.h main.cpp run.h DataStructure.cpp DataStructure.h)
