#ifndef PICO_CODEGEN_H
#define PICO_CODEGEN_H

#include <memory>
#include <string>
#include "ast.h"

namespace llvm {
    class Module;
}

// CodeGen turns a Program AST into an LLVM Module containing main()
class CodeGen {
public:
    explicit CodeGen(std::string moduleName);
    ~CodeGen();

    // Build LLVM IR for the program and return the Module
    std::unique_ptr<llvm::Module> emit(const Program& P);

private:
    struct Impl;
    std::unique_ptr<Impl> impl;
};

#endif // PICO_CODEGEN_H
