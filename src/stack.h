#pragma once

namespace frogl {
    class stack {
    private:
        unsigned char *array = nullptr;
        int allocated = 0;
        unsigned short size = 0;
    public:
        stack() = default;
        void init(int size);
        ~stack();
        void push(unsigned char byte);
        unsigned char pop();
        int allocatedSize();
        int getSize();
        unsigned char& operator [](int index);
        inline void erase(int count){
            size-=count;
        }
    };
}


