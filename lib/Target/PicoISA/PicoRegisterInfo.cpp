#include "TargetInfo/PicoTargetInfo.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/TargetParser/Triple.h"

using namespace llvm;

Target& getThePicoTarget() {
    static Target ThePicoTarget;
    return ThePicoTarget;
}

