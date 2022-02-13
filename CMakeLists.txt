cmake_minimum_required(VERSION 3.21)
project(frogl)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(frogl main.cpp src/fvm.cpp src/fvm.h src/stack.cpp src/stack.h)
