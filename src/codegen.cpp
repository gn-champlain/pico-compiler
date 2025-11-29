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

    // helper to emit IR for an expression tree
    Value* emitExpr(const Expr* e) {
        if (!e) return nullptr;

        // number literal
        if (auto num = dynamic_cast<const NumberExpr*>(e)) {
            return ConstantInt::get(Type::getInt32Ty(ctx), num->value, true);
        }

        // binary expression: lhs (op) rhs
        if (auto bin = dynamic_cast<const BinaryExpr*>(e)) {
            Value* lhsV = emitExpr(bin->lhs.get());
            Value* rhsV = emitExpr(bin->rhs.get());
            if (!lhsV || !rhsV) return nullptr;

            switch (bin->op) {
            case '+':
                return builder->CreateAdd(lhsV, rhsV, "addtmp");
            case '-':
                return builder->CreateSub(lhsV, rhsV, "subtmp");
            case '*':
                return builder->CreateMul(lhsV, rhsV, "multmp");
            case '/':
                // signed integer division
                return builder->CreateSDiv(lhsV, rhsV, "divtmp");
            default:
                return nullptr;
            }
        }

        // unknown expression type
        return nullptr;
    }
};

CodeGen::CodeGen(std::string moduleName)
    : impl(std::make_unique<Impl>()) {
    impl->mod = std::make_unique<Module>(moduleName, impl->ctx);
    impl->builder = std::make_unique<IRBuilder<>>(impl->ctx);
}

CodeGen::~CodeGen() = default;

// Build LLVM IR for the program and return the Module
std::unique_ptr<Module> CodeGen::emit(const Program& P) {
    // Declare printf: int printf(const char *fmt, ...);
    auto* i8PtrTy = Type::getInt8PtrTy(impl->ctx);
    auto* printfTy = FunctionType::get(
        Type::getInt32Ty(impl->ctx),
        { i8PtrTy },
        true);
    impl->printfFn = cast<Function>(
        impl->mod->getOrInsertFunction("printf", printfTy).getCallee());

    // int main()
    auto* mainTy = FunctionType::get(
        Type::getInt32Ty(impl->ctx),
        false);
    Function* mainFn = Function::Create(
        mainTy,
        Function::ExternalLinkage,
        "main",
        impl->mod.get());

    BasicBlock* entry = BasicBlock::Create(impl->ctx, "entry", mainFn);
    impl->builder->SetInsertPoint(entry);

    // Create a global format string "%d\n"
    Value* fmt = impl->builder->CreateGlobalStringPtr("%d\n", "fmt");

    // For each print statement, emit a call to printf("%d\n", <expr>)
    for (const auto& s : P.stmts) {
        Value* val = impl->emitExpr(s.expr.get());
        if (!val) {
            errs() << "CodeGen error: null expression value\n";
            continue;
        }
        impl->builder->CreateCall(impl->printfFn, { fmt, val });
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
