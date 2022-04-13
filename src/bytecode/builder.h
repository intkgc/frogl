#pragma once

#include <cstring>
#include "fvm.h"

namespace frogl {

    struct label {
        unsigned int *ptr = nullptr;
    };

    enum class flags {
        LESS = 0,
        BIGGER,
    };

    class builder {
    private:
        std::vector<std::pair<int, label>> labels;

        template<typename T>
        inline void pushValue(T value){
            byte array[sizeof(T)];
            memcpy(&array, &value, sizeof(T));
            for (int i = 0; i < sizeof(T); ++i) {
                bytecode.push_back(array[i]);
            }
        }

    public:
        std::vector<byte> bytecode;
        void push_i32(unsigned int value);
        void push_i16(short value);
        void push_i8(byte value);
        void double_32();

        void plus_i32();
        void minus_i32();
        void mul_i32();
        void div_i32();
        void plus_f32();
        void minus_f32();
        void mul_f32();
        void div_f32();

        void compare(flags flag);
        void gotoIf();
        void gotoIf(unsigned int address);
        void gotoIf(label address);
        unsigned int getAddress();
        label newLabel();
        label setLabel();
        void initLabel(label label);

        void print_i32();
        void print();

        void frame();
        void load_32(unsigned int address);
        void load_frame();
        void return_32();
        void story_32(unsigned int address);

        void build();
    };
}


