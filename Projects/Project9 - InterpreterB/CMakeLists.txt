cmake_minimum_required(VERSION 3.13)
project(Project9___InterpreterB)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Project9___InterpreterB
        DataStructure.cpp
        DataStructure.h
        Input.cpp
        Parse.h
        main.cpp run_new.cpp
        Expressions.cpp run.h)
