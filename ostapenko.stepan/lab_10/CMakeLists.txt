cmake_minimum_required(VERSION 3.10)
project(lab_10 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -pedantic")

include_directories(include/)

add_executable(lab_10 include/employees.h src/employees.cpp src/main.cpp)
