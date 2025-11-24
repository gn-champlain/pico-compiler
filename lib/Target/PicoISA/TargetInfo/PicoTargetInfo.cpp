// PicoTargetInfo.cpp — minimal target info registration
// Author: Gulshan Nanda
// Note: Uses MC/TargetRegistry and UnknownArch like other sample backends.

#include <llvm/MC/TargetRegistry.h>
#include <llvm/TargetParser/Triple.h>

using namespace llvm;

namespace llvm {

    // Provide a single, owned Target instance for Pico.
    Target& getThePicoTarget() {
        static Target ThePicoTarget;
        return ThePicoTarget;
    }

    extern "C" void LLVMInitializePicoISATargetInfo() {
        // Minimal registration; UnknownArch is fine for a toy backend.
        RegisterTarget<Triple::UnknownArch, /*HasJIT=*/false> X(
            getThePicoTarget(),
            /*Name*/ "pico",
            /*Desc*/ "Pico ISA",
            /*ShortName*/ "Pico");
    }

} // namespace llvm

extern "C" void LLVMInitializePicoISATarget() {
    // no-op stub for sanity test; real init can be wired later
}
