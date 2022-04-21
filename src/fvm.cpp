#include <cstring>
#include "fvm.h"
#include "bytecode/instruction.h"
#include <iostream>

using namespace frogl;

void (*instructions[255])(vm &vm, byte *bytecode, int &index);

void push_8(vm &vm, byte *bytecode, int &index) {
    index++;
    vm.stack.push(bytecode[0]);
    vm.stack.push(0);
    vm.stack.push(0);
    vm.stack.push(0);
}

void push_16(vm &vm, byte *bytecode, int &index) {
    index += 2;
    vm.stack.push(bytecode[0]);
    vm.stack.push(bytecode[1]);
    vm.stack.push(0);
    vm.stack.push(0);
}

void push_32(vm &vm, byte *bytecode, int &index) {
    index += 4;
    for (int i = 0; i < 4; ++i)
        vm.stack.push(bytecode[i]);
}

void load_32(vm &vm, byte *bytecode, int &index) {
    auto valueAddress = reinterpret_cast<unsigned int*>(&vm.stack[vm.stack.getSize() - 4]);
    *valueAddress = *reinterpret_cast<unsigned int*>(&vm.stack[vm.stackFrame + *valueAddress]);
}

void frame(vm &vm, byte *bytecode, int &index) {
    vm.stackFrame = vm.stack.getSize();
}

void load_frame(vm &vm, byte *bytecode, int &index) {
    vm.stackFrame = *reinterpret_cast<int *>(&vm.stack[vm.stack.getSize() - 4]);
    vm.stack.erase(4);
}


void load_32(vm &vm, byte *bytecode, int &index) {
    auto valueAddress = reinterpret_cast<unsigned int*>(&vm.stack[vm.stack.getSize() - 4]);
    *valueAddress = *reinterpret_cast<unsigned int*>(&vm.stack[vm.stackFrame + *valueAddress]);
}

void story_32(vm &vm, byte *bytecode, int &index) {
    auto valueAddress = *reinterpret_cast<unsigned int*>(&vm.stack[vm.stack.getSize() - 4]);
    auto value = *reinterpret_cast<unsigned int*>(&vm.stack[vm.stack.getSize() - 8]);
    *reinterpret_cast<unsigned int*>(&vm.stack[vm.stackFrame + valueAddress]) = value;
    vm.stack.erase(4);
}

void return_32(vm &vm, byte *bytecode, int &index) {
    frogl::byte *value = &vm.stack[vm.stack.getSize() - 4];
    vm.stack.setSize(vm.stackFrame);
    for (int i = 0; i < 4; ++i)
        vm.stack.push(value[i]);
}

void double_32(vm &vm, byte *bytecode, int &index) {
    int stackSize = vm.stack.getSize();
    vm.stack.push(vm.stack[stackSize - 4]);
    vm.stack.push(vm.stack[stackSize - 3]);
    vm.stack.push(vm.stack[stackSize - 2]);
    vm.stack.push(vm.stack[stackSize - 1]);
}

template<typename T>
void plus(vm &vm, byte *bytecode, int &index) {
    T a, b;
    int stackSize = vm.stack.getSize();
    a = *reinterpret_cast<T *>(&vm.stack[stackSize - sizeof(T)]);
    b = *reinterpret_cast<T *>(&vm.stack[stackSize = stackSize - sizeof(T)*2]);
    a += b;
    vm.stack.erase(sizeof(T));
    std::memcpy(&vm.stack[stackSize], &a, sizeof(T));
}

template<typename T>
void minus(vm &vm, byte *bytecode, int &index) {
    T a, b;
    int stackSize = vm.stack.getSize();
    a = *reinterpret_cast<T *>(&vm.stack[stackSize - sizeof(T)]);
    b = *reinterpret_cast<T *>(&vm.stack[stackSize = stackSize - sizeof(T)*2]);
    a = b - a;
    vm.stack.erase(sizeof(T));
    std::memcpy(&vm.stack[stackSize], &a, sizeof(T));
}

template<typename T>
void mul(vm &vm, byte *bytecode, int &index) {
    T a, b;
    int stackSize = vm.stack.getSize();
    a = *reinterpret_cast<T *>(&vm.stack[stackSize - sizeof(T)]);
    b = *reinterpret_cast<T *>(&vm.stack[stackSize = stackSize - sizeof(T)*2]);
    a *= b;
    vm.stack.erase(sizeof(T));
    std::memcpy(&vm.stack[stackSize], &a, sizeof(T));
}

template<typename T>
void div(vm &vm, byte *bytecode, int &index) {
    T a, b;
    int stackSize = vm.stack.getSize();
    a = *reinterpret_cast<T *>(&vm.stack[stackSize - sizeof(T)]);
    b = *reinterpret_cast<T *>(&vm.stack[stackSize = stackSize - sizeof(T)*2]);
    a = b / a;
    vm.stack.erase(sizeof(T));
    std::memcpy(&vm.stack[stackSize], &a, sizeof(T));
}

void print(vm &vm, byte *bytecode, int &index) {
    unsigned char character;
    while ((character = vm.stack.pop()) != '\0') {
        std::cout << character;
    }
}

void print_i32(vm &vm, byte *bytecode, int &index) {
    int value = *reinterpret_cast<int *>(&vm.stack[vm.stack.getSize() - 4]);
    vm.stack.erase(4);
    std::cout << value << '\n';
}


void invert(vm &vm, byte *bytecode, int &index) {
    vm.compareFlag = !vm.compareFlag;
}

void push_flag(vm &vm, byte *bytecode, int &index) {
    vm.stack.push((unsigned char) vm.compareFlag);
    vm.stack.push(0);
    vm.stack.push(0);
    vm.stack.push(0);
}


void cless_i32(vm &vm, byte *bytecode, int &index) {
    int a, b, stackSize = vm.stack.getSize();
    a = *reinterpret_cast<int *>(&vm.stack[stackSize - 4]);
    b = *reinterpret_cast<int *>(&vm.stack[stackSize = stackSize - 8]);
    vm.compareFlag = a > b;
    vm.stack.erase(8);
}

void goto_if(vm &vm, byte *bytecode, int &index) {
    if (vm.compareFlag) {
        int address = *reinterpret_cast<int *>(&vm.stack[vm.stack.getSize() - 4]);
        index = address;
    }
    vm.stack.erase(4);
}

void frogl::vm::init() {
    instructions[PUSH_8] = &push_8;
    instructions[PUSH_16] = &push_16;
    instructions[PUSH_32] = &push_32;
    instructions[DOUBLE_32] = &double_32;

    instructions[PLUS_I32] = &plus<int>;
    instructions[MINUS_I32] = &minus<int>;
    instructions[MUL_I32] = &mul<int>;
    instructions[DIV_I32] = &div<int>;
    instructions[PLUS_F32] = &plus<float>;
    instructions[MINUS_F32] = &minus<float>;
    instructions[MUL_F32] = &mul<float>;
    instructions[DIV_F32] = &div<float>;

    instructions[PRINT] = &print;
    instructions[PRINT_I32] = &print_i32;

    instructions[INVERT] = &invert;
    instructions[PUSH_FLAG] = &push_flag;
    instructions[CLESS_I32] = &cless_i32;

    instructions[GOTOIF] = &goto_if;

    instructions[FRAME] = &frame;
    instructions[LOAD_FRAME] = &load_frame;
    instructions[RETURN_32] = &return_32;
    instructions[LOAD_32] = &load_32;
    instructions[STORY_32] = &story_32;
}



void vm::run(std::vector<byte> &bytecode) {
    int index = 0;
    while (bytecode.size() > index) {
        instructions[bytecode[index++]](*this, &bytecode[index], index);
    }
}
