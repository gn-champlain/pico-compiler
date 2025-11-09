#ifndef PICO_PP_LEXER_H
#define PICO_PP_LEXER_H

#include "token.h"
#include <string>
#include <vector>

class Lexer {
public:
    explicit Lexer(const std::string &source);

    std::vector<Token> tokenize();

private:
    const std::string &src;
    size_t pos;
    int line;
    int column;

    char peek() const;
    char advance();
    bool isAtEnd() const;

    void skipWhitespaceAndComments();
    Token identifier();
    Token number();
    Token makeToken(TokenKind kind, const std::string &lexeme);

    bool match(char expected);
};

#endif
