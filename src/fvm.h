#pragma once

#include <vector>
#include "stack.h"

#define FVM_INSTRUCTION(name, index) static constexpr frogl::byte name = index

namespace frogl {
    typedef unsigned char byte;

    class vm {


    public:
        bool compareFlag = false;
        static void init();
        void run(std::vector<byte> &bytecode);

        FVM_INSTRUCTION(PUSH_8, 0);
        FVM_INSTRUCTION(PUSH_16, PUSH_8 + 1);
        FVM_INSTRUCTION(PUSH_32, PUSH_16 + 1);
        FVM_INSTRUCTION(DOUBLE_32, PUSH_32 + 1);

        FVM_INSTRUCTION(PLUS_I32, DOUBLE_32 + 1);
        FVM_INSTRUCTION(MINUS_I32, PLUS_I32 + 1);
        FVM_INSTRUCTION(MUL_I32, MINUS_I32 + 1);
        FVM_INSTRUCTION(DIV_I32, MUL_I32 + 1);

        FVM_INSTRUCTION(PRINT, DIV_I32 + 1);
        FVM_INSTRUCTION(PRINT_I32, PRINT + 1);

        FVM_INSTRUCTION(INVERT, PRINT_I32 + 1);
        FVM_INSTRUCTION(PUSH_FLAG, INVERT + 1);
        FVM_INSTRUCTION(CLESS_I32, PUSH_FLAG + 1);

        FVM_INSTRUCTION(GOTOIF, CLESS_I32 + 1);

        frogl::stack stack;


    };
}


