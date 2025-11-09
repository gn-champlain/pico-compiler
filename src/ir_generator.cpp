#include "ir_generator.h"
#include <iostream>
#include <llvm/Support/raw_ostream.h>

using namespace std;

IRGenerator::IRGenerator()
    : module(std::make_unique<llvm::Module>("pico_module", context)),
      builder(context) {}

void IRGenerator::generate(std::shared_ptr<ASTNode> root) {
    cout << "Generating IR...\n";

    // Create a simple function: int main() { return 0; }
    llvm::FunctionType* funcType =
        llvm::FunctionType::get(builder.getInt32Ty(), false);
    llvm::Function* mainFunc =
        llvm::Function::Create(funcType, llvm::Function::ExternalLinkage,
                               "main", module.get());

    llvm::BasicBlock* entry =
        llvm::BasicBlock::Create(context, "entry", mainFunc);
    builder.SetInsertPoint(entry);

    // Example IR instruction
    llvm::Value* result = builder.CreateAdd(
        llvm::ConstantInt::get(builder.getInt32Ty(), 5),
        llvm::ConstantInt::get(builder.getInt32Ty(), 3),
        "addtmp");

    builder.CreateRet(result);
}

llvm::Module* IRGenerator::getModule() {
    return module.get();
}

void IRGenerator::printIR() {
    module->print(llvm::outs(), nullptr);
}
