#include <cstring>
#include "fvm.h"

using namespace frogl;

void (*instructions[255])(vm &vm, byte* bytecode, int &index);

void push_8i(vm &vm, byte* bytecode, int &index){
    index++;
    vm.stack.push_back(bytecode[0]);
    vm.stack.push_back(0);
    vm.stack.push_back(0);
    vm.stack.push_back(0);
}
void plus_i32(vm &vm, byte* bytecode, int &index){
    int a;
    int b;
    std::memcpy(&a, &vm.stack[vm.stack.size()-4], 4);
    std::memcpy(&b, &vm.stack[vm.stack.size()-8], 4);
    a+=b;
    for (int i = 0; i < 4; ++i)
        vm.stack.pop_back();
    std::memcpy(&vm.stack[vm.stack.size()-4], &a, 4);
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
