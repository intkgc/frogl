#include "fvm.h"

int main() {
    frogl::vm::init();
    using frogl::vm;
    std::vector<frogl::byte> ir {
            vm::PUSH_8, 1,
            vm::PUSH_8, 0,
            vm::MUL_I32,
            vm::PUSH_32, '\0', 'd', 'l', 'r',
            vm::PUSH_32, 'o', 'w', ' ', ',',
            vm::PUSH_32, 'o', 'l', 'l', 'e',
            vm::PUSH_32, 'H', 1, 1, 1,
            vm::PRINT
            //vm::DIV_I32
    };
    frogl::vm vm;

    vm.stack.init(16);
    vm.run(ir);
    return 0;
}
