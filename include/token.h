#ifndef PICO_TOKEN_H
#define PICO_TOKEN_H

#include <cstddef>

enum class TokKind {
    PRINT,
    NUMBER,
    SEMI,
    END,
    INVALID
};

struct Token {
    TokKind kind;
    int value;        // used only for NUMBER
    std::size_t line; // 1-based line number
    std::size_t col;  // 1-based column number
};

#endif // PICO_TOKEN_H
