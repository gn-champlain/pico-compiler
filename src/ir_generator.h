#ifndef IR_GENERATOR_H
#define IR_GENERATOR_H

#include "ast.h"
#include "symbol_table.h"
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <memory>

class IRGenerator {
public:
    IRGenerator();
    void generate(std::shared_ptr<ASTNode> root);
    llvm::Module* getModule();   // 
    void printIR();              // 

private:
    llvm::LLVMContext context;
    std::unique_ptr<llvm::Module> module;
    llvm::IRBuilder<> builder;
    SymbolTable symTable;
};

#endif
