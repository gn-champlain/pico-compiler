#ifndef PICO_PP_TOKEN_H
#define PICO_PP_TOKEN_H

#include <string>

enum class TokenKind {
    EndOfFile,
    Identifier,
    Number,

    // Keywords
    KwLet,
    KwIf,
    KwElse,
    KwWhile,
    KwPrint,

    // Symbols
    LParen,     // (
    RParen,     // )
    LBrace,     // {
    RBrace,     // }
    Semicolon,  // ;
    Equal,      // =

    Plus,
    Minus,
    Star,
    Slash,
    Percent,

    Less,
    Greater,
    LessEqual,
    GreaterEqual,
    EqualEqual,
    BangEqual,
};

struct Token {
    TokenKind kind;
    std::string lexeme;
    int line;
    int column;
};

std::string tokenKindToString(TokenKind kind);

#endif
