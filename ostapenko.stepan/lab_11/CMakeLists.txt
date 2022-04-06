cmake_minimum_required(VERSION 3.10)
project(lab_11 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -pedantic")

include_directories(include/)

add_executable(lab_11 include/my_vector.h include/my_vector_impl.h src/main.cpp)
