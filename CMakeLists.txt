cmake_minimum_required(VERSION 3.21)
project(frogl)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(frogl main.cpp src/fvm.cpp src/fvm.h src/stack.cpp src/stack.h src/bytecode/builder.cpp src/bytecode/builder.h src/bytecode/instruction.h src/froglm/compiler.h src/froglm/node.h src/froglm/type.h src/froglm/compiler.cpp)
