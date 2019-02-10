cmake_minimum_required(VERSION 3.13)
project(CLion)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES "letters.c")
add_executable(Lectures ${SOURCE_FILES})
