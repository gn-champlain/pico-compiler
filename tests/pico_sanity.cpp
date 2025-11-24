#include <iostream>
#include <memory>
#include <string>

#include <llvm/MC/TargetRegistry.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/TargetParser/Triple.h>

extern "C" void LLVMInitializePicoISATargetInfo();
extern "C" void LLVMInitializePicoISATarget();
extern "C" void LLVMInitializePicoISATargetMC();
// This symbol should be defined in PicoTargetMachine.cpp (empty body is fine)
// to force-link the TU that calls RegisterTargetMachine<...>.
extern "C" void LLVMInitializePicoISATargetMachine();

int main() {
    // Ensure all registrars run for our out-of-tree target.
    LLVMInitializePicoISATargetInfo();
    LLVMInitializePicoISATarget();
    LLVMInitializePicoISATargetMC();
    LLVMInitializePicoISATargetMachine();

    // LLVM 17: use lookupTarget(ArchName, Err)
    std::string Err;
    const llvm::Target* T = llvm::TargetRegistry::lookupTarget("pico", Err);
    if (!T) {
        std::cerr << "lookupTarget failed: " << Err << "\n";
        return 1;
    }
    std::cout << "Found target: " << T->getName() << "\n";

    // Keep triple neutral so we don't depend on core triple parsing a custom arch.
    llvm::Triple TT("unknown-unknown-unknown");
    std::string CPU = "generic";
    std::string FS = "";
    llvm::TargetOptions Opts;

    std::unique_ptr<llvm::TargetMachine> TM(
        T->createTargetMachine(TT.str(), CPU, FS, Opts,
            std::optional<llvm::Reloc::Model>(llvm::Reloc::Static),
            std::optional<llvm::CodeModel::Model>(llvm::CodeModel::Small),
            llvm::CodeGenOpt::Default));

    if (!TM) {
        std::cerr << "createTargetMachine failed\n";
        return 2;
    }

    std::cout << "TargetMachine OK\n";
    return 0;
}
