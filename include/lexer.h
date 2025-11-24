#ifndef PICO_LEXER_H
#define PICO_LEXER_H

#include <string>
#include "token.h"

// The Lexer takes the full source text and produces tokens one by one.
// It hides all details like whitespace and comments.
class Lexer {
public:
    explicit Lexer(std::string text);

    // Get next token from input stream.
    Token next();

private:
    std::string src;
    std::size_t i = 0;
    std::size_t line = 1;
    std::size_t col = 1;

    char peek() const;
    char get();
    void skipSpacesAndComments();
};

#endif // PICO_LEXER_H
