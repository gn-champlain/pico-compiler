#ifndef LLVM_LIB_TARGET_PICOISA_TARGETINFO_PICOTARGETINFO_H
#define LLVM_LIB_TARGET_PICOISA_TARGETINFO_PICOTARGETINFO_H

#include "llvm/TargetParser/Triple.h"
#include "llvm/ADT/StringRef.h"

namespace llvm {
class Target;

// This symbol is defined by TargetInfo/PicoTargetInfo.cpp
extern Target ThePicoTarget;

} // namespace llvm

#endif