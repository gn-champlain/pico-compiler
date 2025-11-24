#ifndef PICO_PARSER_H
#define PICO_PARSER_H

#include "lexer.h"
#include "ast.h"

// The Parser consumes tokens from the Lexer and builds a Program AST.
// Grammar:
//   program := { "print" NUMBER ";" } EOF
class Parser {
public:
    explicit Parser(Lexer& L);

    bool parseProgram(Program& P);

private:
    Lexer& lex;
    Token cur;

    void advance();
    bool expect(TokKind k, const char* msg);
};

#endif // PICO_PARSER_H
