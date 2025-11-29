#include "parser.h"
#include <iostream>

Parser::Parser(Lexer& L)
    : lex(L) {
    advance();
}

void Parser::advance() {
    curTok = lex.next();
}

bool Parser::expect(TokKind kind) {
    if (curTok.kind != kind) {
        std::cerr << "Parse error at line " << curTok.line
            << ", col " << curTok.col
            << ": unexpected token.\n";
        return false;
    }
    return true;
}

// program := { "print" expr ";" } EOF
bool Parser::parseProgram(Program& prog) {
    while (curTok.kind != TokKind::END) {
        // expect 'print'
        if (curTok.kind != TokKind::PRINT) {
            std::cerr << "Parse error: expected 'print' at line "
                << curTok.line << ", col " << curTok.col << "\n";
            return false;
        }
        advance(); // consume 'print'

        // parse expression
        auto expr = parseExpr();
        if (!expr) {
            return false;
        }

        // expect ';'
        if (!expect(TokKind::SEMI)) {
            return false;
        }
        advance(); // consume ';'

        PrintStmt stmt;
        stmt.expr = std::move(expr);
        prog.stmts.push_back(std::move(stmt));
    }
    return true;
}

// expr := term { ("+" | "-") term }
std::unique_ptr<Expr> Parser::parseExpr() {
    auto lhs = parseTerm();
    if (!lhs) return nullptr;

    while (curTok.kind == TokKind::PLUS ||
        curTok.kind == TokKind::MINUS) {
        char op = (curTok.kind == TokKind::PLUS) ? '+' : '-';
        advance(); // consume + or -

        auto rhs = parseTerm();
        if (!rhs) return nullptr;

        lhs = std::make_unique<BinaryExpr>(op, std::move(lhs), std::move(rhs));
    }

    return lhs;
}

// term := factor { ("*" | "/") factor }
std::unique_ptr<Expr> Parser::parseTerm() {
    auto lhs = parseFactor();
    if (!lhs) return nullptr;

    while (curTok.kind == TokKind::STAR ||
        curTok.kind == TokKind::SLASH) {
        char op = (curTok.kind == TokKind::STAR) ? '*' : '/';
        advance(); // consume * or /

        auto rhs = parseFactor();
        if (!rhs) return nullptr;

        lhs = std::make_unique<BinaryExpr>(op, std::move(lhs), std::move(rhs));
    }

    return lhs;
}

// factor := NUMBER | "(" expr ")"
std::unique_ptr<Expr> Parser::parseFactor() {
    if (curTok.kind == TokKind::NUMBER) {
        int val = curTok.value;
        advance(); // consume number
        return std::make_unique<NumberExpr>(val);
    }

    if (curTok.kind == TokKind::LPAREN) {
        advance(); // consume '('
        auto inside = parseExpr();
        if (!inside) return nullptr;

        if (!expect(TokKind::RPAREN)) {
            return nullptr;
        }
        advance(); // consume ')'
        return inside;
    }

    std::cerr << "Parse error at line " << curTok.line
        << ", col " << curTok.col
        << ": expected number or '('.\n";
    return nullptr;
}
