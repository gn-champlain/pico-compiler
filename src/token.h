#pragma once
#include <string>

// Define all token types
enum class TokenKind {
    Identifier,
    Number,
    LParen, RParen,
    LBrace, RBrace,
    Semicolon,
    Plus, Minus, Star, Slash, Percent,
    Equal, EqualEqual,
    Less, LessEqual, Greater, GreaterEqual,
    Bang, BangEqual,
    KwLet, KwIf, KwElse, KwWhile, KwPrint,
    EndOfFile
};

// Token structure
struct Token {
    TokenKind kind;
    std::string lexeme;
    int line;
    int column;

    Token(TokenKind k, const std::string& l, int ln, int col)
        : kind(k), lexeme(l), line(ln), column(col) {
    }
};

// Declaration only (implemented in token.cpp)
std::string tokenKindToString(TokenKind kind);
