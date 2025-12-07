// M88kInstrFormats.h
// Week 6 - simple description of my M88k instruction formats.
//
// This is not a full assembler. I just want a clean place
// to write down the formats that I use in the report and
// in my small examples.

#ifndef M88K_INSTR_FORMATS_H
#define M88K_INSTR_FORMATS_H

#include <string>

namespace pico {

    // I keep a tiny list of opcodes that I actually talk about
    // in my report and examples.
    enum class M88kOpcode {
        ADD,    // R-type: add rd, rs, rt        rd = rs + rt
        ADDI,   // I-type: addi rd, rs, imm      rd = rs + imm
        LD,     // M-type:  ld rd, offset(rs)    rd = *(rs + offset)
        ST,     // M-type:  st rd, offset(rs)    *(rs + offset) = rd
        BEQ,    // B-type:  beq rs, rt, label    if (rs == rt) branch
        JMP     // B-type:  jmp label            jump to label
    };

    // R-type: op rd, rs, rt  (3 registers)
    struct M88kRType {
        M88kOpcode op;
        int rd;
        int rs;
        int rt;
    };

    // I-type: op rd, rs, imm16
    struct M88kIType {
        M88kOpcode op;
        int rd;
        int rs;
        int imm16;  // I keep this as plain int in my toy design
    };

    // M-type (memory): op rd, offset(rs)
    struct M88kMType {
        M88kOpcode op;
        int rd;
        int rs;
        int offset; // byte offset from base register
    };

    // B-type (branches): op rs, rt, label
    struct M88kBType {
        M88kOpcode op;
        int rs;
        int rt;
        std::string label; // target label name
    };

    // Small helpers so I can print instructions like:
    //   add r1, r2, r3
    //   ld r3, 8(r15)
    // in my tests and screenshots.
    std::string toString(const M88kRType& inst);
    std::string toString(const M88kIType& inst);
    std::string toString(const M88kMType& inst);
    std::string toString(const M88kBType& inst);

} // namespace pico

#endif // M88K_INSTR_FORMATS_H
