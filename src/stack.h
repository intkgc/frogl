#pragma once

namespace frogl {
    class stack {
    private:
        unsigned char *array = nullptr;
        int allocated = 0;
        unsigned short size = 0;
    public:
        stack() = default;
        ~stack();
        void init(int size);
        void push(unsigned char byte);
        unsigned char pop();
        int allocatedSize();
        unsigned char& operator [](int index);

        inline void erase(int count){
            size-=count;
        }

        inline int getSize() const{
            return size;
        }
    };
}


