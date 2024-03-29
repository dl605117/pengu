/*
Start Jan. 2024:
Developer: dl605117 (Darren)

Generator (Back-end):
Code generator of Pengu compiler. Ingests AST tree to generate IR to be used in LLVM IR.
Currently only generates x86 ASM for testing purposes.
*/

#pragma once
#include "parser.hpp"
#include <sstream>

class Generator {
public:
    Generator (NodeReturn root) : root_(std::move(root)) {}

    std::string generate() const {
        std::stringstream output;
        output << "global _start\n_start:\n";
        output << "\tmov rax, 60\n";
        output << "\tmov rdi, " << root_.expr.int_lit.value.value() << "\n";
        output << "\tsyscall";
        return output.str();
    }
private:
    const NodeReturn root_;
};