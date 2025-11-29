#ifndef PICO_PARSER_H
#define PICO_PARSER_H

#include <memory>
#include "lexer.h"
#include "ast.h"

// Very small recursive-descent parser for:
//
//   program := { "print" expr ";" } EOF
//   expr    := term { ("+" | "-") term }
//   term    := factor { ("*" | "/") factor }
//   factor  := NUMBER | "(" expr ")"
//
class Parser {
public:
    explicit Parser(Lexer& lex);

    // Parse the whole program into 'prog'.
    // Returns true on success, false on error.
    bool parseProgram(Program& prog);

private:
    Lexer& lex;
    Token curTok;

    void advance();
    bool expect(TokKind kind);

    // expression helpers
    std::unique_ptr<Expr> parseExpr();
    std::unique_ptr<Expr> parseTerm();
    std::unique_ptr<Expr> parseFactor();
};

#endif // PICO_PARSER_H
