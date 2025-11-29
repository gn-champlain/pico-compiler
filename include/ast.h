#ifndef PICO_AST_H
#define PICO_AST_H

#include <memory>
#include <vector>

// ===== Expression AST =====

// Base class for all expressions
struct Expr {
    virtual ~Expr() = default;
};

// Number literal, like: 10, 20, 42
struct NumberExpr : Expr {
    int value;

    explicit NumberExpr(int v) : value(v) {}
};

// Binary expression, like: a + b, a * b, etc.
struct BinaryExpr : Expr {
    char op; // '+', '-', '*', '/'
    std::unique_ptr<Expr> lhs;
    std::unique_ptr<Expr> rhs;

    BinaryExpr(char op,
        std::unique_ptr<Expr> lhs,
        std::unique_ptr<Expr> rhs)
        : op(op),
        lhs(std::move(lhs)),
        rhs(std::move(rhs)) {
    }
};

// ===== Statement and Program AST =====

// print <expr> ;
struct PrintStmt {
    std::unique_ptr<Expr> expr;
};

// A whole program is just a list of print statements.
struct Program {
    std::vector<PrintStmt> stmts;
};

#endif // PICO_AST_H
