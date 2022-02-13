#include "stack.h"

void frogl::stack::push(unsigned char byte) {
    array[size++] = byte;
}

unsigned char frogl::stack::pop() {
    return array[--size];
}

frogl::stack::~stack() {
    delete[] array;
    array = nullptr;
}


int frogl::stack::allocatedSize() {
    return allocated;
}



int frogl::stack::getSize() {
    return size;
}

unsigned char &frogl::stack::operator[](int index) {
    return array[index];
}

void frogl::stack::init(int size) {
    array = new unsigned char[size];
    allocated = size;
}


