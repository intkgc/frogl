#FVM (frogl virtual machine)

---

FVM is a register virtual machine developed for executing frogl bytecode.
It has 4 registers, namely A, B, C, D. All of these registers are 64 bit variables,
but using the postfixes 32, 16, 8 after an instruction, 
they can be used as 32, 16, 8 bit variables, respectively

Also, FVM has a fixed stack that used for local variables and intermediate results of computing.
The stack size can be set before the program is executed.

Each of fvm instruction is one byte number, but it can have several bytes as operands.