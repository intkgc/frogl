#include <iostream>
#include "fvm.h"

int main() {
    frogl::vm::init();
    std::vector<frogl::byte> ir {
        frogl::vm::PUSH_8I, 12,
        frogl::vm::PUSH_8I, 1,
        frogl::vm::PLUS,
        frogl::vm::PUSH_8I, 10,
        frogl::vm::PLUS,
        frogl::vm::PUSH_8I, 100,
        frogl::vm::PLUS
    };
    frogl::vm vm;

    vm.stack.init(64);
    vm.run(ir);
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
