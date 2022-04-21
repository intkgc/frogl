#include <iostream>
#include "src/fvm.h"
#include "src/bytecode/instruction.h"
#include "src/bytecode/builder.h"
#include "src/froglm/compiler.h"
#include "src/froglm/node.h"

using namespace frogl;

int main() {
    frogl::vm::init();
    frogl::vm vm;

    froglm::compiler compiler;

    std::vector<frogl::byte> ir{
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

    std::cout << "1: " << froglm::compiler::is_function("f(x) = 123 * x - xxD") << "\n";
    std::cout << "2: " << froglm::compiler::is_variable("f = 123 * x - xxD") << "\n";


    auto address = builder.newLabel();

    builder.frame();
    builder.push_i32(1000);
    builder.initLabel(address);
    builder.load_32(0);
    builder.push_i32(7);
    builder.minus_i32();
    builder.double_32();
    builder.double_32();
    builder.story_32(0);
    builder.print_i32();
    builder.push_i32(0);
    builder.compare(frogl::flags::BIGGER);
    builder.gotoIf(address);
    builder.build();




    vm.stack.init(128);
    vm.run(builder.bytecode);


    return 0;
}
