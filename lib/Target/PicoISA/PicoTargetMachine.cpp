/*
 File: PicoTargetMachine.cpp
 Author: Gulshan Nanda
 Date: 2025-11-24
 Note: Minimal TargetMachine + registration for LLVM 17.
*/

#include "TargetInfo/PicoTargetInfo.h"     // getThePicoTarget()
#include "PicoTargetMachine.h"

#include <llvm/MC/TargetRegistry.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/TargetParser/Triple.h>

using namespace llvm;


// === Tiny TargetMachine that just uses defaults ===
PicoTargetMachine::PicoTargetMachine(const Target& T, const Triple& TT,
    StringRef CPU, StringRef FS,
    const TargetOptions& Options,
    std::optional<Reloc::Model> RM,
    std::optional<CodeModel::Model> CM,
    CodeGenOpt::Level OL, bool /*JIT*/)
    : LLVMTargetMachine(T,
        /*DataLayout*/ "e",     // little-endian default
        TT,
        CPU, FS,
        Options,
        RM.value_or(Reloc::Model::Static),
        CM.value_or(CodeModel::Small),
        OL) {
    initAsmInfo();
}
// === Force TargetMachine registration and make the TU “visible” to the linker ===
#include "llvm/MC/TargetRegistry.h"
namespace llvm {
    // Forward declared in TargetInfo TU
    extern Target& getThePicoTarget();
}

// This is a distinct init symbol (do NOT collide with LLVMInitializePicoISATarget
// or LLVMInitializePicoISATargetMC which live in other TUs).
extern "C" void LLVMInitializePicoISATargetMachine() {
    static llvm::RegisterTargetMachine<llvm::PicoTargetMachine> X(llvm::getThePicoTarget());
}
