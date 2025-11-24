/*
 File: PicoMCAsmInfo.h
 Author: Gulshan Nanda
 Date: 2025-11-24
 Course: Compiler Design - Week 4 (TableGen)
 Note: Simple starter code for my fictional PicoISA backend. I kept it minimal and readable.
*/
#ifndef LLVM_LIB_TARGET_PICOISA_TARGETDESC_PICOMCASMINFO_H
#define LLVM_LIB_TARGET_PICOISA_TARGETDESC_PICOMCASMINFO_H

#include "llvm/MC/MCAsmInfo.h"

namespace llvm {

class PicoMCAsmInfo : public MCAsmInfo {
public:
  PicoMCAsmInfo() {
    // I keep it 32 bit and little endian to keep it simple for now.
    CodePointerSize = 4;
    CalleeSaveStackSlotSize = 4;
    IsLittleEndian = true;
  }
};

} // end namespace llvm

#endif
