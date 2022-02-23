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
    vm.stack.push(bytecode[0]);
    vm.stack.push(bytecode[1]);
    vm.stack.push(bytecode[2]);
    vm.stack.push(bytecode[3]);
}


void double_32(vm &vm, byte *bytecode, int &index) {
    int stackSize = vm.stack.getSize();
    vm.stack.push(vm.stack[stackSize - 4]);
    vm.stack.push(vm.stack[stackSize - 3]);
    vm.stack.push(vm.stack[stackSize - 2]);
    vm.stack.push(vm.stack[stackSize - 1]);
}

void plus_i32(vm &vm, byte *bytecode, int &index) {
    int a, b, stackSize = vm.stack.getSize();
    a = *reinterpret_cast<int *>(&vm.stack[stackSize - 4]);
    b = *reinterpret_cast<int *>(&vm.stack[stackSize = stackSize - 8]);
    a += b;
    vm.stack.erase(4);
    std::memcpy(&vm.stack[stackSize], &a, 4);
}

void minus_i32(vm &vm, byte *bytecode, int &index) {
    int a, b, stackSize = vm.stack.getSize();
    a = *reinterpret_cast<int *>(&vm.stack[stackSize - 4]);
    b = *reinterpret_cast<int *>(&vm.stack[stackSize = stackSize - 8]);
    a = b - a;
    vm.stack.erase(4);
    std::memcpy(&vm.stack[stackSize], &a, 4);
}

void mul_i32(vm &vm, byte *bytecode, int &index) {
    int a, b, stackSize = vm.stack.getSize();
    a = *reinterpret_cast<int *>(&vm.stack[stackSize - 4]);
    b = *reinterpret_cast<int *>(&vm.stack[stackSize = stackSize - 8]);
    a *= b;
    vm.stack.erase(4);
    std::memcpy(&vm.stack[stackSize], &a, 4);
}

void div_i32(vm &vm, byte *bytecode, int &index) {
    int a, b, stackSize = vm.stack.getSize();
    a = *reinterpret_cast<int *>(&vm.stack[stackSize - 4]);
    b = *reinterpret_cast<int *>(&vm.stack[stackSize = stackSize - 8]);
    a = b / a;
    vm.stack.erase(4);
    std::memcpy(&vm.stack[stackSize], &a, 4);
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

    instructions[PLUS_I32] = &plus_i32;
    instructions[MINUS_I32] = &minus_i32;
    instructions[MUL_I32] = &mul_i32;
    instructions[DIV_I32] = &div_i32;

    instructions[PRINT] = &print;
    instructions[PRINT_I32] = &print_i32;

    instructions[INVERT] = &invert;
    instructions[PUSH_FLAG] = &push_flag;
    instructions[CLESS_I32] = &cless_i32;

    instructions[GOTOIF] = &goto_if;

}

void vm::run(std::vector<byte> &bytecode) {
    int index = 0;
    while (bytecode.size() > index) {
        instructions[bytecode[index++]](*this, &bytecode[index], index);
    }
}
