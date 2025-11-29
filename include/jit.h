#ifndef PICO_JIT_H
#define PICO_JIT_H

#include <llvm/ExecutionEngine/Orc/ThreadSafeModule.h>

// Run the given LLVM module with LLJIT.
// The ThreadSafeModule owns both the Module and its LLVMContext.
// Returns the exit code from main(), or non-zero on error.
int runJIT(llvm::orc::ThreadSafeModule TSM);

#endif // PICO_JIT_H
