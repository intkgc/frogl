#include "builder.h"
#include "fvm.h"
#include "instruction.h"

void frogl::builder::push_i32(unsigned int value) {
    bytecode.push_back(PUSH_32);
    pushValue(value);
}

void frogl::builder::push_i16(short value) {
    push_i32(value);
}

void frogl::builder::push_i8(frogl::byte value) {
    push_i32(value);
}

void frogl::builder::plus_i32() {
    bytecode.push_back(PLUS_I32);
}

void frogl::builder::minus_i32() {
    bytecode.push_back(MINUS_I32);
}

void frogl::builder::mul_i32() {
    bytecode.push_back(MUL_I32);
}

void frogl::builder::div_i32() {
    bytecode.push_back(DIV_I32);
}

void frogl::builder::plus_f32() {
    bytecode.push_back(PLUS_F32);
}

void frogl::builder::minus_f32() {
    bytecode.push_back(MINUS_F32);
}

void frogl::builder::mul_f32() {
    bytecode.push_back(MUL_F32);
}

void frogl::builder::div_f32() {
    bytecode.push_back(DIV_F32);
}

void frogl::builder::compare(flags flag) {
    bytecode.push_back(CLESS_I32);
    if (flag == flags::BIGGER)
        bytecode.push_back(INVERT);
}

void frogl::builder::gotoIf() {
    bytecode.push_back(GOTOIF);
}

void frogl::builder::gotoIf(unsigned int address) {
    bytecode.push_back(PUSH_32);
    pushValue(address);
    gotoIf();
}

unsigned int frogl::builder::getAddress() {
    return bytecode.size();
}

void frogl::builder::print_i32() {
    bytecode.push_back(PRINT_I32);
}

void frogl::builder::print() {
    bytecode.push_back(PRINT);
}

void frogl::builder::double_32() {
    bytecode.push_back(DOUBLE_32);
}

void frogl::builder::frame() {
    bytecode.push_back(FRAME);
}


void frogl::builder::load_frame() {
    bytecode.push_back(LOAD_FRAME);
}

void frogl::builder::return_32() {
    bytecode.push_back(RETURN_32);
}

void frogl::builder::story_32(unsigned int address) {
    push_i32(address);
    bytecode.push_back(STORY_32);
}

void frogl::builder::load_32(unsigned int address) {
    push_i32(address);
    bytecode.push_back(LOAD_32);
}

void frogl::builder::gotoIf(frogl::label address) {
    push_i32(0);
    labels.emplace_back(bytecode.size() - 4, address);
    gotoIf();
}

void frogl::builder::build() {
    for (auto &i: labels) {
        *reinterpret_cast<unsigned int *>(&bytecode[i.first]) = *i.second.ptr;
        delete i.second.ptr;
    }
    labels.clear();
}

frogl::label frogl::builder::newLabel() {
    struct label label;
    label.ptr = new unsigned int();
    return label;
}

void frogl::builder::initLabel(frogl::label label) {
    *label.ptr = bytecode.size();
}

frogl::label frogl::builder::setLabel() {
    auto value = newLabel();
    initLabel(value);
    return value;
}

