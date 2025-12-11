//===- M88kFallthroughPass.cpp - Simple fallthrough branch opt ---*- C++ -*-===//
//
// This file implements a small MachineFunction pass that removes
// redundant unconditional branches to the next layout basic block.
// The goal is to let control flow fall through naturally instead of
// jumping to the block that is already the layout successor.
//
// Project: pico-m88k-machfun (Week 7)
// Author:  Gulshan Nanda
//
//===----------------------------------------------------------------------===//

#include "llvm/CodeGen/MachineBasicBlock.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/CodeGen/TargetInstrInfo.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"
#include "llvm/Pass.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

#define DEBUG_TYPE "m88k-fallthrough"

namespace {

    /// M88kFallthroughPass - MachineFunction pass that removes
    /// unconditional branches to the layout-successor block.
    class M88kFallthroughPass : public MachineFunctionPass {
    public:
        static char ID;

        M88kFallthroughPass() : MachineFunctionPass(ID) {}

        StringRef getPassName() const override {
            return "M88k Fallthrough Branch Optimization (MachineFunction pass)";
        }

        bool runOnMachineFunction(MachineFunction& MF) override;
    };

} // end anonymous namespace

char M88kFallthroughPass::ID = 0;

// Legacy-style registration so this pass has a command-line name if built
// as a plugin in real LLVM.
static RegisterPass<M88kFallthroughPass>
X("m88k-fallthrough",
    "M88k fallthrough branch optimization (MachineFunction pass)",
    false, // Only looks at CFG?
    false  // Is analysis?
);

// Simple factory so our own code can create the pass.
namespace llvm {
    FunctionPass* createM88kFallthroughPass() {
        return new M88kFallthroughPass();
    }
} // namespace llvm

bool M88kFallthroughPass::runOnMachineFunction(MachineFunction& MF) {
    LLVM_DEBUG(dbgs() << "M88kFallthroughPass running on function: "
        << MF.getName() << "\n");

    bool Changed = false;

    // Get TargetInstrInfo so we can use the generic branch helpers.
    const TargetSubtargetInfo& STI = MF.getSubtarget();
    const TargetInstrInfo* TII = STI.getInstrInfo();

    if (!TII) {
        LLVM_DEBUG(dbgs() << "  No TargetInstrInfo available, skipping.\n");
        return false;
    }

    // Walk blocks in layout order.
    for (MachineBasicBlock& MBB : MF) {
        MachineBasicBlock* Succ = MBB.getNextNode();
        if (!Succ)
            continue; // Last block, nothing to fall through into.

        // Analyze the branch at the end of this block.
        MachineBasicBlock* TBB = nullptr;
        MachineBasicBlock* FBB = nullptr;
        SmallVector<MachineOperand, 4> Cond;

        bool CannotAnalyze = TII->analyzeBranch(MBB, TBB, FBB, Cond);
        if (CannotAnalyze)
            continue; // Unknown or complex terminator, do not touch.

        // We only care about the simple case:
        //   - One unconditional branch to TBB.
        //   - No fallthrough or second branch (FBB == nullptr).
        //   - No condition (Cond.empty()).
        if (!TBB || FBB || !Cond.empty())
            continue;

        // Check if the branch target is exactly the layout successor.
        if (TBB != Succ)
            continue;

        // At this point we have:
        //   MBB: ... ; br TBB
        //   Succ == TBB
        // We can safely remove the branch and let control fall through.
        int Removed = TII->removeBranch(MBB);
        if (Removed > 0) {
            Changed = true;
            LLVM_DEBUG(dbgs() << "  Removed " << Removed
                << " branch(es) from block "
                << MBB.getNumber()
                << " that jumped to its layout successor.\n");
        }
    }

    return Changed;
}
