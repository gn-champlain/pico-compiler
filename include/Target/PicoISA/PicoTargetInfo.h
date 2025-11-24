/*
 File: PicoTargetInfo.h
 Author: Gulshan Nanda
 Date: 2025-11-24
 Course: Compiler Design - Week 4 (TableGen)
 Note: Simple starter code for my fictional PicoISA backend. I kept it minimal and readable.
*/
#ifndef LLVM_LIB_TARGET_PICOISA_TARGETINFO_PICOTARGETINFO_H
#define LLVM_LIB_TARGET_PICOISA_TARGETINFO_PICOTARGETINFO_H

namespace llvm {
	class Target;
	Target& getThePicoTarget();
} // namespace llvm

#endif
