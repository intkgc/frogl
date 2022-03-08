#include "src/fvm.h"
#include "src/bytecode/instruction.h"
#include "src/bytecode/builder.h"

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


    builder.frame();
    builder.push_i32(1);
    builder.push_i32(0);
    auto label = builder.label();
    builder.load_32(4);
    builder.push_i32(1);
    builder.plus_i32();
    builder.double_32();
    builder.double_32();
    builder.double_32();
    builder.story_32(4);
    builder.print_i32();
    builder.push_i32(6);
    builder.compare(flags::LESS);
    builder.gotoIf(label);



    vm.stack.init(128);
    vm.run(builder.bytecode);


    return 0;
}
