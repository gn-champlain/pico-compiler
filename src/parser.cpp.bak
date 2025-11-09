#include "parser.h"

Parser::Parser(const std::vector<Token> &tokens)
    : tokens(tokens), current(0) {}

std::unique_ptr<Program> Parser::parseProgram() {
    auto program = std::make_unique<Program>();
    // We will fill proper parsing later.
    // For now, accept empty program and collect no errors.
    return program;
}

const Token &Parser::peek() const {
    return tokens[current];
}

const Token &Parser::previous() const {
    return tokens[current - 1];
}

bool Parser::isAtEnd() const {
    return peek().kind == TokenKind::EndOfFile;
}

const Token &Parser::advance() {
    if (!isAtEnd()) current++;
    return previous();
}

bool Parser::check(TokenKind kind) const {
    if (isAtEnd()) return false;
    return peek().kind == kind;
}

bool Parser::match(TokenKind kind) {
    if (check(kind)) {
        advance();
        return true;
    }
    return false;
}

bool Parser::match(TokenKind kind1, TokenKind kind2) {
    if (check(kind1) || check(kind2)) {
        advance();
        return true;
    }
    return false;
}

void Parser::error(const Token &tok, const std::string &message) {
    errors.push_back("Parse error at line " + std::to_string(tok.line) +
                     ": " + message);
}

// Stub parse functions for now
std::unique_ptr<Stmt> Parser::parseStatement() { return nullptr; }
std::unique_ptr<Stmt> Parser::parseVarDecl() { return nullptr; }
std::unique_ptr<Stmt> Parser::parseAssignOrExprStmt() { return nullptr; }
std::unique_ptr<Stmt> Parser::parseIfStmt() { return nullptr; }
std::unique_ptr<Stmt> Parser::parseWhileStmt() { return nullptr; }
std::unique_ptr<Stmt> Parser::parsePrintStmt() { return nullptr; }
std::unique_ptr<BlockStmt> Parser::parseBlock() { return nullptr; }

std::unique_ptr<Expr> Parser::parseExpression() { return nullptr; }
std::unique_ptr<Expr> Parser::parseEquality() { return nullptr; }
std::unique_ptr<Expr> Parser::parseRelational() { return nullptr; }
std::unique_ptr<Expr> Parser::parseAddExpr() { return nullptr; }
std::unique_ptr<Expr> Parser::parseTerm() { return nullptr; }
std::unique_ptr<Expr> Parser::parseFactor() { return nullptr; }
std::unique_ptr<Expr> Parser::parsePrimary() { return nullptr; }
