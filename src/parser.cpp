#include "parser.h"
#include <iostream>

Parser::Parser(Lexer& L)
    : lex(L) {
    advance();
}

void Parser::advance() {
    cur = lex.next();
}

bool Parser::expect(TokKind k, const char* msg) {
    if (cur.kind != k) {
        std::cerr << "Parse error at line " << cur.line
                  << ", col " << cur.col
                  << ": " << msg << "\n";
        return false;
    }
    return true;
}

bool Parser::parseProgram(Program& P) {
    while (cur.kind != TokKind::END) {
        if (!expect(TokKind::PRINT, "expected 'print'")) {
            return false;
        }
        advance();

        if (!expect(TokKind::NUMBER, "expected number after 'print'")) {
            return false;
        }
        int n = cur.value;
        advance();

        if (!expect(TokKind::SEMI, "expected ';' after number")) {
            return false;
        }
        advance();

        P.stmts.push_back(PrintStmt{n});
    }
    return true;
}
