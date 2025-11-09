#ifndef PICO_PP_SEMANTIC_H
#define PICO_PP_SEMANTIC_H

#include "ast.h"
#include "symbol_table.h"
#include <vector>
#include <string>

class SemanticAnalyzer {
public:
    SemanticAnalyzer();

    void analyze(Program &program);

    const std::vector<std::string> &getErrors() const { return errors; }

private:
    SymbolTable symbols;
    std::vector<std::string> errors;

    void analyzeStmt(Stmt *stmt);
    void analyzeExpr(Expr *expr);

    void addError(const std::string &msg);
};

#endif
