cmake_minimum_required(VERSION 3.10)
project(lab_13 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -pedantic")

include_directories(include/)

add_executable(lab_13 include/my_array.h src/main.cpp)
