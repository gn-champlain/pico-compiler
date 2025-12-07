// M88kInstrFormats.cpp
// Week 6 - small helpers for my M88k instruction formats.
// Here I only implement a few "toString" helpers so I can
// print sample instructions in the report and screenshots.

#include "M88kInstrFormats.h"
#include <sstream>

namespace pico {

    static std::string opcodeToString(M88kOpcode op) {
        switch (op) {
        case M88kOpcode::ADD:  return "add";
        case M88kOpcode::ADDI: return "addi";
        case M88kOpcode::LD:   return "ld";
        case M88kOpcode::ST:   return "st";
        case M88kOpcode::BEQ:  return "beq";
        case M88kOpcode::JMP:  return "jmp";
        }
        return "unknown";
    }

    // Just a tiny helper so that registers print as r0, r1, ...
    static std::string regName(int r) {
        std::ostringstream os;
        os << "r" << r;
        return os.str();
    }

    std::string toString(const M88kRType& inst) {
        std::ostringstream os;
        os << opcodeToString(inst.op) << " "
            << regName(inst.rd) << ", "
            << regName(inst.rs) << ", "
            << regName(inst.rt);
        return os.str();
    }

    std::string toString(const M88kIType& inst) {
        std::ostringstream os;
        os << opcodeToString(inst.op) << " "
            << regName(inst.rd) << ", "
            << regName(inst.rs) << ", "
            << inst.imm16;
        return os.str();
    }

    std::string toString(const M88kMType& inst) {
        std::ostringstream os;
        os << opcodeToString(inst.op) << " "
            << regName(inst.rd) << ", "
            << inst.offset << "(" << regName(inst.rs) << ")";
        return os.str();
    }

    std::string toString(const M88kBType& inst) {
        std::ostringstream os;
        os << opcodeToString(inst.op) << " "
            << regName(inst.rs) << ", "
            << regName(inst.rt) << ", "
            << inst.label;
        return os.str();
    }

} // namespace pico
