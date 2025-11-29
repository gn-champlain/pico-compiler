#include "jit.h"

#include <iostream>
#include <string>

#include <llvm/ExecutionEngine/Orc/LLJIT.h>
#include <llvm/ExecutionEngine/Orc/ThreadSafeModule.h>
#include <llvm/ExecutionEngine/Orc/Shared/ExecutorAddress.h>
#include <llvm/Support/Error.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;
using namespace llvm::orc;

// Small helper to print LLVM Error nicely to std::cerr
static void logError(Error Err, const char* where) {
    if (!Err)
        return;

    std::string msg;
    raw_string_ostream os(msg);
    logAllUnhandledErrors(std::move(Err), os, "");
    os.flush();

    std::cerr << "[JIT error in " << where << "]: " << msg << "\n";
}

// Runs the "main" function from the given module using LLJIT.
int runJIT(ThreadSafeModule TSM) {
    // Make sure native target is initialized (safe to call many times).
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();

    // Create an LLJIT instance
    auto jitExpected = LLJITBuilder().create();
    if (!jitExpected) {
        logError(jitExpected.takeError(), "LLJITBuilder::create");
        return 1;
    }
    std::unique_ptr<LLJIT> jit = std::move(*jitExpected);

    // Add our module to the JIT
    if (auto err = jit->addIRModule(std::move(TSM))) {
        logError(std::move(err), "addIRModule");
        return 1;
    }

    // Look up the "main" symbol
    auto addrExpected = jit->lookup("main");
    if (!addrExpected) {
        logError(addrExpected.takeError(), "lookup(main)");
        return 1;
    }

    ExecutorAddr addr = *addrExpected;

    using MainFn = int (*)();
    MainFn mainFn = addr.toPtr<MainFn>();
    if (!mainFn) {
        std::cerr << "[JIT] Could not cast main() function pointer.\n";
        return 1;
    }

    // Call JIT-compiled main() and return its result
    int result = mainFn();
    return result;
}
