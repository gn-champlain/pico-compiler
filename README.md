# Pico++ Frontend (Week 2)

This is a small teaching compiler frontend that extends the Week 1 Pico compiler.

Stages:
1. Lexical analysis (Lexer)
2. Parsing into an AST (Parser + AST)
3. Semantic analysis with simple scope handling (SemanticAnalyzer + SymbolTable)

You can build with CMake and run:

```bash
mkdir build
cd build
cmake ..
cmake --build .
./pico_pp_frontend ../examples/demo1.pico
```
