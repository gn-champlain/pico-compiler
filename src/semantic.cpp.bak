#include "semantic.h"
#include <iostream>

SemanticAnalyzer::SemanticAnalyzer() {
    symbols.enterScope();
}

void SemanticAnalyzer::analyze(Program &program) {
    for (auto &stmt : program.statements) {
        analyzeStmt(stmt.get());
    }
}

void SemanticAnalyzer::analyzeStmt(Stmt *stmt) {
    if (!stmt) return;
    // We will add real logic later using isa<VarDeclStmt>() etc.
}

void SemanticAnalyzer::analyzeExpr(Expr *expr) {
    if (!expr) return;
}

void SemanticAnalyzer::addError(const std::string &msg) {
    errors.push_back(msg);
}
