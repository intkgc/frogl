#pragma once

#include <vector>
#include "stack.h"

namespace frogl {
    typedef unsigned char byte;

    class vm {
    public:
        bool compareFlag = false;
        static void init();
        void run(std::vector<byte> &bytecode);

        frogl::stack stack;
    };
}


