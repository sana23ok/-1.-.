cmake_minimum_required(VERSION 3.24)
project(Labaratorna_N1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Labaratorna_N1 main.cpp stream_handler.cpp stream_handler.h pointer_handler.cpp pointer_handler.h)
add_executable(test1 test1.cpp)