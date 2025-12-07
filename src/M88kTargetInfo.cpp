// M88kTargetInfo.cpp
// Week 6 - basic M88k target info implementation.
// This is NOT the full LLVM backend, just a small helper
// that matches my Week 6 design notes.

#include "M88kTargetInfo.h"
#include <iostream>

namespace pico {

    std::string getM88kTriple() {
        // Later, when I wire this into LLVM, I plan to use this triple.
        return "m88k-unknown-elf";
    }

    std::string getM88kDataLayout() {
        // Simple 32-bit little-endian layout for now.
        // I can tweak this string if I need to later.
        return "e-m:e-p:32:32-i64:64-n32";
    }

    void printM88kSummary() {
        std::cout << "M88k backend summary (Week 6 design)\n";
        std::cout << "------------------------------------\n";
        std::cout << "Word size : 32-bit, two's complement ints\n";
        std::cout << "Endian    : little endian\n\n";

        std::cout << "Registers:\n";
        std::cout << "  r0  - hard-wired zero\n";
        std::cout << "  r1  - return value / first argument\n";
        std::cout << "  r2–r4 - extra argument registers\n";
        std::cout << "  r14 - frame pointer (fp)\n";
        std::cout << "  r15 - stack pointer (sp)\n";
        std::cout << "  others - general purpose\n\n";

        std::cout << "Default triple : " << getM88kTriple() << "\n";
        std::cout << "Data layout    : " << getM88kDataLayout() << "\n\n";
    }

} // namespace pico
