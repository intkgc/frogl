#pragma once

#include <vector>

#define FVM_INSTRUCTION(name, index) static constexpr frogl::byte name = index

namespace frogl {
    typedef unsigned char byte;

    class vm {


    public:
        static void init();
        void run(std::vector<byte> &bytecode);
        FVM_INSTRUCTION(PUSH_8I, 0);
        FVM_INSTRUCTION(PLUS, 1);
        FVM_INSTRUCTION(EXIT, 2);

        std::vector<byte> stack;

    };
}


