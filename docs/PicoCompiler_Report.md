# Pico Compiler: A Minimal LLVM IR Generator

Gulshan  
Champlain College  
CSCI-430: Compilers  
Dr. Kenneth Revett  
November 2025  

## 1. Introduction

This project demonstrates how to build a very small compiler in C++ that
generates LLVM Intermediate Representation (IR). The idea was to focus on the
core compiler stages without getting lost in a large language design. The toy
language is called **Pico** and it supports just one kind of statement:

```text
print NUMBER;
```

The compiler reads a `.pico` source file, checks that each line is valid, and
then emits LLVM IR code that prints the given numbers using `printf`.

## 2. Language Overview

Pico is intentionally minimal. The grammar is:

```text
program := { stmt } EOF
stmt    := "print" NUMBER ";"
NUMBER  := digit { digit }
```

Some example programs:

```text
print 7;
print 21;
print 300;
```

The language also allows whitespace and `//` comments, which are ignored by the
lexer. All values are treated as 32 bit signed integers.

## 3. Compiler Structure

The compiler is split into three simple stages.

### 3.1 Lexer

The lexer takes the full source text and converts it into tokens. The token
kinds for Pico are:

- `PRINT` for the `print` keyword  
- `NUMBER` for integer literals  
- `SEMI` for the `;` character  
- `END` to mark end of file  
- `INVALID` for anything unexpected  

The lexer also skips whitespace and line comments that start with `//`. It keeps
track of line and column numbers so that parse errors can report where
something went wrong.

### 3.2 Parser

The parser reads tokens from the lexer and checks that they follow the Pico
grammar. For each statement it expects:

1. The `PRINT` token  
2. A `NUMBER` token  
3. A semicolon `SEMI` token  

If anything is missing, the parser prints an error message with line and column
information and stops. On success, the parser produces a simple abstract syntax
tree (AST) where the program is just a list of `PrintStmt` nodes.

### 3.3 Code Generator

The code generator takes the AST and creates LLVM IR. Internally it builds:

- An `LLVMContext`  
- A `Module` named `"pico_module"`  
- A single function `i32 @main()`  

In the entry block of `main`, it declares `printf` and creates a global format
string `"%d\n"`. For each print statement, it emits a call:

```llvm
call i32 (i8*, ...) @printf(i8* @.fmt, i32 <value>)
```

Finally, it returns `i32 0`. The generated IR can be run with `lli` or passed to
the rest of the LLVM toolchain.

## 4. Testing

A simple test program is:

```text
print 7;
print 21;
```

After running the compiler:

```bash
pico samples/hello.pico out.ll
```

we can inspect `out.ll` and then run:

```bash
lli out.ll
```

The expected terminal output is:

```text
100
42
7
```

for the default sample, or it will show whatever numbers are in the input file.

Screenshots of the build process, source code, and IR view can be collected and
included if required by the assignment.

## 5. Challenges and Fixes

The main challenges in this project were:

- Setting up LLVM correctly with CMake and Visual Studio  
- Linking against the correct LLVM libraries (`Core` and `Support`)  
- Handling basic error reporting with line and column numbers  

Each of these issues was resolved by carefully following the LLVM "Getting
Started" documentation and by testing the project in small steps: first getting
the lexer working, then the parser, and finally the code generator.

## 6. Conclusion

Even though Pico is a tiny language, working through the full path from source
file to LLVM IR helped solidify the concepts of lexical analysis, parsing, and
code generation. The same structure can be extended in future work to support
variables, expressions, and control flow while still keeping the design clean
and modular.
