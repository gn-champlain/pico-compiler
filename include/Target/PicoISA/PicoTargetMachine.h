/*
 File: PicoTargetMachine.h
 Author: Gulshan Nanda
 Date: 2025-11-24
 Note: Minimal TargetMachine class for the toy Pico backend (LLVM 17).
*/

#ifndef LLVM_LIB_TARGET_PICOISA_PICOTARGETMACHINE_H
#define LLVM_LIB_TARGET_PICOISA_PICOTARGETMACHINE_H

#include <optional>
#include <string>

#include <llvm/Target/TargetMachine.h>
#include <llvm/TargetParser/Triple.h>

namespace llvm {

    // Forward decl from TargetInfo so both sides share the same Target.
    Target& getThePicoTarget();

    // A tiny TargetMachine that just lets LLVM construct one for "pico".
    class PicoTargetMachine : public LLVMTargetMachine {
    public:
        PicoTargetMachine(const Target& T, const Triple& TT,
            StringRef CPU, StringRef FS,
            const TargetOptions& Options,
            std::optional<Reloc::Model> RM,
            std::optional<CodeModel::Model> CM,
            CodeGenOpt::Level OL, bool JIT);

        ~PicoTargetMachine() override = default;
    };

} // namespace llvm

#endif // LLVM_LIB_TARGET_PICOISA_PICOTARGETMACHINE_H
