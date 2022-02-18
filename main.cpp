#include <iostream>
#include "fvm.h"
#include "climits"

int main() {
    frogl::vm::init();
    using frogl::vm;
    std::vector<frogl::byte> ir {
            vm::PUSH_8, 1,
            vm::PUSH_8, 2,
            vm::PLUS_I32,
            vm::DOUBLE_32,
            vm::PUSH_16, 255, 255,
            vm::CLESS_I32,
            vm::DOUBLE_32,
            vm::PRINT_I32,
            vm::PUSH_32, '\0', '\n', ' ', ' ',
            vm::PRINT,
            vm::GOTOIF, 16, 0
    };
    frogl::vm vm;

    vm.stack.init(128);
    vm.run(ir);


    return 0;
}
