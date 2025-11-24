#include "codegen.h"

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;

struct CodeGen::Impl {
    LLVMContext ctx;
    std::unique_ptr<Module> mod;
    std::unique_ptr<IRBuilder<>> builder;
    Function* printfFn = nullptr;

    explicit Impl(std::string name) {
        mod = std::make_unique<Module>(name, ctx);
        builder = std::make_unique<IRBuilder<>>(ctx);
    }

    void declarePrintf() {
        auto* i8PtrTy = Type::getInt8PtrTy(ctx);
        auto* printfTy = FunctionType::get(Type::getInt32Ty(ctx), { i8PtrTy }, true);
        printfFn = cast<Function>(mod->getOrInsertFunction("printf", printfTy).getCallee());
    }

    Value* makeFormatString() {
        // Creates a global string "%d\n" and returns i8* pointer to it.
        return builder->CreateGlobalStringPtr("%d\n", "fmt");
    }
};

CodeGen::CodeGen(std::string moduleName)
    : impl(std::make_unique<Impl>(std::move(moduleName))) {}

CodeGen::~CodeGen() = default;

std::unique_ptr<Module> CodeGen::emit(const Program& P) {
    impl->declarePrintf();

    // int main()
    FunctionType* mainTy =
        FunctionType::get(Type::getInt32Ty(impl->ctx), false);
    Function* mainFn =
        Function::Create(mainTy,
                         Function::ExternalLinkage,
                         "main",
                         impl->mod.get());

    BasicBlock* entry =
        BasicBlock::Create(impl->ctx, "entry", mainFn);
    impl->builder->SetInsertPoint(entry);

    Value* fmt = impl->makeFormatString();

    // For each print statement, emit a call to printf("%d\n", value)
    for (const auto& s : P.stmts) {
        Value* num =
            ConstantInt::get(Type::getInt32Ty(impl->ctx), s.value, true);
        impl->builder->CreateCall(impl->printfFn, { fmt, num });
    }

    // return 0;
    impl->builder->CreateRet(
        ConstantInt::get(Type::getInt32Ty(impl->ctx), 0));

    // Sanity check
    if (verifyModule(*impl->mod, &errs())) {
        errs() << "IR verification failed\n";
    }

    return std::move(impl->mod);
}
