#include <iostream>
#include "fvm.h"

int main() {
    frogl::vm::init();
    using frogl::vm;
    std::vector<frogl::byte> ir {
            vm::PUSH_16, 12, 13,
            vm::PUSH_8, 1,
            vm::PLUS_I32,
            vm::PUSH_8, 100,
            vm::MUL_I32,
            vm::PUSH_8, 100,
            //vm::DIV_I32
    };
    frogl::vm vm;

    vm.stack.init(16);
    vm.run(ir);
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
