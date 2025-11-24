#ifndef PICO_AST_H
#define PICO_AST_H

#include <vector>

// Pico language has only one kind of statement: print NUMBER;
struct PrintStmt {
    int value;
};

// A whole program is just a list of print statements.
struct Program {
    std::vector<PrintStmt> stmts;
};

#endif // PICO_AST_H
