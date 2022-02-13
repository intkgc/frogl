#include <cstring>
#include "fvm.h"

using namespace frogl;

void (*instructions[255])(vm &vm, byte* bytecode, int &index);

void push_8i(vm &vm, byte* bytecode, int &index){
    index++;
    vm.stack.push(bytecode[0]);
    vm.stack.push(0);
    vm.stack.push(0);
    vm.stack.push(0);
}
void plus_i32(vm &vm, byte* bytecode, int &index){
    int a, b, stackSize = vm.stack.getSize();
    a = *reinterpret_cast<int*>(&vm.stack[stackSize-4]);
    b = *reinterpret_cast<int*>(&vm.stack[stackSize = stackSize-8]);
    a+=b;
    vm.stack.erase(4);
    std::memcpy(&vm.stack[stackSize], &a, 4);
}

void frogl::vm::init() {
    instructions[PUSH_8I] = &push_8i;
    instructions[PLUS] = &plus_i32;
}

void vm::run(std::vector<byte> &bytecode) {
    int index = 0;
    while (bytecode.size() > index){
        instructions[bytecode[index++]](*this, &bytecode[index], index);
    }
}
