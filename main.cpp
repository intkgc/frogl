#include "fvm.h"
#include "bytecode/instruction.h"
#include "bytecode/builder.h"

using namespace frogl;

int main() {
    frogl::vm::init();
    frogl::vm vm;


    std::vector<frogl::byte> ir {
            PUSH_8, 0,
            PUSH_8, 1,
            PLUS_I32,
            DOUBLE_32,
            PUSH_32, 6, 0, 0, 0,
            CLESS_I32,
            DOUBLE_32,
            PRINT_I32,
            PUSH_32, '\0', '\n', ' ', ' ',
            PRINT,
            PUSH_8, 2,
            GOTOIF
    };

    frogl::builder builder;

    builder.push_i32(1);

    auto address = builder.label();

    builder.push_i8(2);
    builder.mul_i32();
    builder.double_32();
    builder.push_i32(1001);
    builder.compare(flags::LESS);
    builder.double_32();
    builder.print_i32();
    builder.gotoIf(address);


    vm.stack.init(128);
    vm.run(builder.bytecode);


    return 0;
}
