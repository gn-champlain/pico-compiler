/*
 File: PicoInstrInfo.h
 Author: Gulshan Nanda
 Date: 2025-11-24
 Course: Compiler Design - Week 4 (TableGen)
 Note: Minimal header that does NOT depend on generated .inc yet.
*/
#ifndef LLVM_LIB_TARGET_PICOISA_PICOINSTRINFO_H
#define LLVM_LIB_TARGET_PICOISA_PICOINSTRINFO_H

#include <llvm/CodeGen/TargetInstrInfo.h>

namespace llvm {

	class PicoInstrInfo : public TargetInstrInfo {
	public:
		PicoInstrInfo() = default;
		~PicoInstrInfo() override = default;
	};

} // end namespace llvm

#endif
