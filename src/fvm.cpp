#include <cstring>
#include "fvm.h"

using namespace frogl;

void (*instructions[255])(vm &vm, byte* bytecode, int &index);

void push_8(vm &vm, byte* bytecode, int &index){
    index++;
    vm.stack.push(bytecode[0]);
    vm.stack.push(0);
    vm.stack.push(0);
    vm.stack.push(0);
}

void push_16(vm &vm, byte* bytecode, int &index){
    index+=2;
    vm.stack.push(bytecode[0]);
    vm.stack.push(bytecode[1]);
    vm.stack.push(0);
    vm.stack.push(0);
}

void push_32(vm &vm, byte* bytecode, int &index){
    index+=4;
    vm.stack.push(bytecode[0]);
    vm.stack.push(bytecode[1]);
    vm.stack.push(bytecode[2]);
    vm.stack.push(bytecode[3]);
}

void plus_i32(vm &vm, byte* bytecode, int &index){
    int a, b, stackSize = vm.stack.getSize();
    a = *reinterpret_cast<int*>(&vm.stack[stackSize-4]);
    b = *reinterpret_cast<int*>(&vm.stack[stackSize = stackSize-8]);
    a+=b;
    vm.stack.erase(4);
    std::memcpy(&vm.stack[stackSize], &a, 4);
}

void minus_i32(vm &vm, byte* bytecode, int &index){
    int a, b, stackSize = vm.stack.getSize();
    a = *reinterpret_cast<int*>(&vm.stack[stackSize-4]);
    b = *reinterpret_cast<int*>(&vm.stack[stackSize = stackSize-8]);
    a = b - a;
    vm.stack.erase(4);
    std::memcpy(&vm.stack[stackSize], &a, 4);
}

void mul_i32(vm &vm, byte* bytecode, int &index){
    int a, b, stackSize = vm.stack.getSize();
    a = *reinterpret_cast<int*>(&vm.stack[stackSize-4]);
    b = *reinterpret_cast<int*>(&vm.stack[stackSize = stackSize-8]);
    a*=b;
    vm.stack.erase(4);
    std::memcpy(&vm.stack[stackSize], &a, 4);
}

void div_i32(vm &vm, byte* bytecode, int &index){
    int a, b, stackSize = vm.stack.getSize();
    a = *reinterpret_cast<int*>(&vm.stack[stackSize-4]);
    b = *reinterpret_cast<int*>(&vm.stack[stackSize = stackSize-8]);
    a = b / a;
    vm.stack.erase(4);
    std::memcpy(&vm.stack[stackSize], &a, 4);
}

void frogl::vm::init() {
    instructions[PUSH_8] = &push_8;
    instructions[PUSH_16] = &push_16;
    instructions[PUSH_32] = &push_32;

    instructions[PLUS_I32] = &plus_i32;
    instructions[MINUS_I32] = &minus_i32;
    instructions[MUL_I32] = &mul_i32;
    instructions[DIV_I32] = &div_i32;
}

void vm::run(std::vector<byte> &bytecode) {
    int index = 0;
    while (bytecode.size() > index){
        instructions[bytecode[index++]](*this, &bytecode[index], index);
    }
}
