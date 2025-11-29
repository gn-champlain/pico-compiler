#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "lexer.h"
#include "parser.h"
#include "codegen.h"
#include "jit.h"

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/ExecutionEngine/Orc/ThreadSafeModule.h>

// ===== Helper: read entire file into a string =====
static bool readFileToString(const std::string& path, std::string& out) {
    std::ifstream in(path);
    if (!in) {
        std::cerr << "Could not open input file: " << path << "\n";
        return false;
    }
    std::stringstream buffer;
    buffer << in.rdbuf();
    out = buffer.str();
    return true;
}

// ===== Helper: emit IR for an Expr (for JIT mode) =====
//
// This mirrors the logic in CodeGen::Impl::emitExpr, but for
// the JIT path here in main.cpp.
static llvm::Value* emitExprJIT(const Expr* e,
    llvm::IRBuilder<>& builder,
    llvm::LLVMContext& ctx) {
    if (!e) return nullptr;

    using namespace llvm;

    // Number literal
    if (auto num = dynamic_cast<const NumberExpr*>(e)) {
        return ConstantInt::get(Type::getInt32Ty(ctx), num->value, true);
    }

    // Binary expression
    if (auto bin = dynamic_cast<const BinaryExpr*>(e)) {
        Value* lhsV = emitExprJIT(bin->lhs.get(), builder, ctx);
        Value* rhsV = emitExprJIT(bin->rhs.get(), builder, ctx);
        if (!lhsV || !rhsV) return nullptr;

        switch (bin->op) {
        case '+':
            return builder.CreateAdd(lhsV, rhsV, "addtmp");
        case '-':
            return builder.CreateSub(lhsV, rhsV, "subtmp");
        case '*':
            return builder.CreateMul(lhsV, rhsV, "multmp");
        case '/':
            // signed integer division
            return builder.CreateSDiv(lhsV, rhsV, "divtmp");
        default:
            return nullptr;
        }
    }

    return nullptr;
}

int main(int argc, char* argv[]) {
    bool useJIT = false;
    std::string inputPath;
    std::string outputPath;

    // Command line:
    //   pico <input.pico> <output.ll>   -> write IR (old behavior)
    //   pico --jit <input.pico>         -> JIT run (calculator style)
    if (argc == 3 && std::string(argv[1]) == "--jit") {
        useJIT = true;
        inputPath = argv[2];
    }
    else if (argc == 3) {
        inputPath = argv[1];
        outputPath = argv[2];
    }
    else {
        std::cerr << "Usage:\n"
            << "  " << argv[0] << " <input.pico> <output.ll>   (write IR only)\n"
            << "  " << argv[0] << " --jit <input.pico>         (JIT compile and run)\n";
        return 1;
    }

    // Read source file
    std::string source;
    if (!readFileToString(inputPath, source)) {
        return 2;
    }

    // Lex and parse
    Lexer lex(source);
    Parser parser(lex);
    Program prog;
    if (!parser.parseProgram(prog)) {
        std::cerr << "Parsing failed.\n";
        return 3;
    }

    // ----- Mode 1: write IR to file using existing CodeGen (old behavior) -----
    if (!useJIT) {
        CodeGen cg("pico_module");
        auto mod = cg.emit(prog);

        std::error_code ec;
        llvm::raw_fd_ostream os(outputPath, ec, llvm::sys::fs::OF_Text);
        if (ec) {
            std::cerr << "Cannot open output file: " << ec.message() << "\n";
            return 5;
        }
        mod->print(os, nullptr);
        std::cout << "Wrote IR to " << outputPath << "\n";
        return 0;
    }

    // ----- Mode 2: JIT run (calculator mode) -----
    using namespace llvm;

    auto ctx = std::make_unique<LLVMContext>();
    auto mod = std::make_unique<Module>("pico_jit_module", *ctx);
    IRBuilder<> builder(*ctx);

    // Declare printf: int printf(const char *fmt, ...);
    auto* i8PtrTy = Type::getInt8PtrTy(*ctx);
    auto* printfTy = FunctionType::get(
        Type::getInt32Ty(*ctx),
        { i8PtrTy },
        true);
    Function* printfFn = cast<Function>(
        mod->getOrInsertFunction("printf", printfTy).getCallee());

    // int main()
    auto* mainTy = FunctionType::get(
        Type::getInt32Ty(*ctx),
        false);
    Function* mainFn = Function::Create(
        mainTy,
        Function::ExternalLinkage,
        "main",
        mod.get());

    BasicBlock* entry = BasicBlock::Create(*ctx, "entry", mainFn);
    builder.SetInsertPoint(entry);

    // Create a global format string "%d\n"
    Value* fmt = builder.CreateGlobalStringPtr("%d\n", "fmt");

    // For each print statement, emit a call to printf("%d\n", <expr>)
    for (const auto& s : prog.stmts) {
        Value* val = emitExprJIT(s.expr.get(), builder, *ctx);
        if (!val) {
            errs() << "JIT CodeGen error: null expression value\n";
            continue;
        }
        builder.CreateCall(printfFn, { fmt, val });
    }

    // return 0;
    builder.CreateRet(
        ConstantInt::get(Type::getInt32Ty(*ctx), 0));

    // Sanity check
    if (verifyModule(*mod, &errs())) {
        errs() << "JIT IR verification failed\n";
        return 6;
    }

    // Wrap in ThreadSafeModule and run with JIT
    llvm::orc::ThreadSafeModule TSM(std::move(mod), std::move(ctx));

    int exitCode = runJIT(std::move(TSM));
    std::cout << "JIT exit code: " << exitCode << "\n";
    return exitCode;
}
