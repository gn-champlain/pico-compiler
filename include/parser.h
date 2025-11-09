#ifndef PICO_PP_PARSER_H
#define PICO_PP_PARSER_H

#include "token.h"
#include "ast.h"
#include <vector>
#include <memory>
#include <string>

class Parser {
public:
    explicit Parser(const std::vector<Token> &tokens);

    std::unique_ptr<Program> parseProgram();

    const std::vector<std::string> &getErrors() const { return errors; }

private:
    const std::vector<Token> &tokens;
    size_t current;
    std::vector<std::string> errors;

    const Token &peek() const;
    const Token &previous() const;
    bool isAtEnd() const;
    const Token &advance();
    bool check(TokenKind kind) const;
    bool match(TokenKind kind);
    bool match(TokenKind kind1, TokenKind kind2);
    void error(const Token &tok, const std::string &message);

    // Parsing helpers (to be filled in later)
    std::unique_ptr<Stmt> parseStatement();
    std::unique_ptr<Stmt> parseVarDecl();
    std::unique_ptr<Stmt> parseAssignOrExprStmt();
    std::unique_ptr<Stmt> parseIfStmt();
    std::unique_ptr<Stmt> parseWhileStmt();
    std::unique_ptr<Stmt> parsePrintStmt();
    std::unique_ptr<BlockStmt> parseBlock();

    std::unique_ptr<Expr> parseExpression();
    std::unique_ptr<Expr> parseEquality();
    std::unique_ptr<Expr> parseRelational();
    std::unique_ptr<Expr> parseAddExpr();
    std::unique_ptr<Expr> parseTerm();
    std::unique_ptr<Expr> parseFactor();
    std::unique_ptr<Expr> parsePrimary();
};

#endif
