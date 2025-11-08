# Pico Compiler

Author: Gulshan  
Course: CSCI-430 Compilers  
Instructor: Dr. Kenneth Revett  
Date: November 2025  

## Overview

This project implements a very small compiler for a toy language called **Pico**.  
The compiler is written in C++ and uses LLVM to generate LLVM IR.

Pico supports only one kind of statement:

```text
print NUMBER;
```

Example program:

```text
print 100;
print 42;
// comments are allowed
print 7;
```

The compiler reads a `.pico` source file, parses it, and then generates LLVM IR
that calls `printf("%d\n", NUMBER)` for each statement.

## Build Instructions

1. Install LLVM (version 17 or later) and CMake.
2. Clone this repository.
3. From the project root, configure and build:

```bash
cmake -B build
cmake --build build
```

In Visual Studio, you can open this folder as a CMake project and build using
the CMake targets.

## Usage

Once built, run:

```bash
./build/pico samples/hello.pico out.ll
```

This will read `samples/hello.pico` and write LLVM IR to `out.ll`.

To inspect the IR, open `out.ll` in a text editor.

If you have the LLVM interpreter `lli` installed, you can run:

```bash
lli out.ll
```

You should see the numbers from the input printed, one per line.

## Project Layout

```text
pico-compiler/
 ├── include/    # header files (token, lexer, parser, ast, codegen)
 ├── src/        # C++ source files
 ├── samples/    # sample Pico programs
 ├── docs/       # report and screenshots (if any)
 ├── CMakeLists.txt
 └── README.md
```

## Pico Language Summary

- Statement form: `print NUMBER;`
- NUMBER is a decimal integer (32 bit).
- Lines can contain comments starting with `//`.
- Whitespace is ignored except that it separates tokens.

## Acknowledgements

LLVM documentation and examples were used as a reference for setting up the
LLVM context, module, and IRBuilder.
