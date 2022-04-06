cmake_minimum_required(VERSION 3.10)
project(lab_09 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -pedantic")

include_directories(include/)

add_executable(lab_09 include/Figure.hpp src/Figure.cpp include/Scheme.hpp src/Scheme.cpp include/Rectangle.hpp src/Rectangle.cpp include/Circle.hpp src/Circle.cpp src/main.cpp)
