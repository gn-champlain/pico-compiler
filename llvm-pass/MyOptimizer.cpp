// MyOptimizer.cpp — LLVM 17 minimal function pass that registers as "my-optimizer"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/IR/PassManager.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Metadata.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

// Simple function pass: add a harmless metadata tag on the Function.
// This keeps things minimal but proves the pass ran.
struct MyOptimizerPass : PassInfoMixin<MyOptimizerPass> {
    PreservedAnalyses run(Function& F, FunctionAnalysisManager&) {
        LLVMContext& Ctx = F.getContext();
        MDNode* Tag = MDNode::get(Ctx, MDString::get(Ctx, "myopt"));
        F.setMetadata("myoptimizer.tag", Tag);
        return PreservedAnalyses::all();
    }
};

// Plugin registration for the new PM.
static PassPluginLibraryInfo getMyPluginInfo() {
    return {
        LLVM_PLUGIN_API_VERSION,
        "MyOptimizer",                 // Plugin name (any string)
        LLVM_VERSION_STRING,           // LLVM version
        [](PassBuilder& PB) {
          PB.registerPipelineParsingCallback(
              [](StringRef Name, FunctionPassManager& FPM,
                 ArrayRef<PassBuilder::PipelineElement>) {
                if (Name == "my-optimizer") {
                  FPM.addPass(MyOptimizerPass());
                  return true;
                }
                return false;
              });
        } };
}

// This must be at global scope, with this exact signature and C linkage.
extern "C" LLVM_ATTRIBUTE_WEAK PassPluginLibraryInfo llvmGetPassPluginInfo() {
    return getMyPluginInfo();
}
