#include "lexer.h"
#include <cctype>
#include <climits>

Lexer::Lexer(std::string text)
    : src(std::move(text)) {}

char Lexer::peek() const {
    if (i < src.size()) {
        return src[i];
    }
    return '\0';
}

char Lexer::get() {
    char c = peek();
    if (c == '\0') {
        return c;
    }
    ++i;
    if (c == '\n') {
        ++line;
        col = 1;
    } else {
        ++col;
    }
    return c;
}

void Lexer::skipSpacesAndComments() {
    while (true) {
        // skip whitespace
        while (std::isspace(static_cast<unsigned char>(peek()))) {
            get();
        }

        // skip line comments: // ...
        if (peek() == '/' && i + 1 < src.size() && src[i + 1] == '/') {
            while (peek() != '\n' && peek() != '\0') {
                get();
            }
        } else {
            break;
        }
    }
}

Token Lexer::next() {
    skipSpacesAndComments();

    std::size_t tokLine = line;
    std::size_t tokCol = col;
    char c = peek();
    // single-character operators and punctuation
    if (c == '+') {
        get();
        return Token{ TokKind::PLUS, 0, tokLine, tokCol };
    }
    if (c == '-') {
        get();
        return Token{ TokKind::MINUS, 0, tokLine, tokCol };
    }
    if (c == '*') {
        get();
        return Token{ TokKind::STAR, 0, tokLine, tokCol };
    }
    if (c == '/') {
        get();
        return Token{ TokKind::SLASH, 0, tokLine, tokCol };
    }
    if (c == '(') {
        get();
        return Token{ TokKind::LPAREN, 0, tokLine, tokCol };
    }
    if (c == ')') {
        get();
        return Token{ TokKind::RPAREN, 0, tokLine, tokCol };
    }


    if (c == '\0') {
        return Token{TokKind::END, 0, tokLine, tokCol};
    }

    if (c == ';') {
        get();
        return Token{TokKind::SEMI, 0, tokLine, tokCol};
    }

    // keyword: print
    if (std::isalpha(static_cast<unsigned char>(c))) {
        std::string word;
        while (std::isalnum(static_cast<unsigned char>(peek()))) {
            word.push_back(get());
        }
        if (word == "print") {
            return Token{TokKind::PRINT, 0, tokLine, tokCol};
        }
        // no other identifiers in Pico, so treat as invalid
        return Token{TokKind::INVALID, 0, tokLine, tokCol};
    }

    // number literal
    if (std::isdigit(static_cast<unsigned char>(c))) {
        long long val = 0;
        while (std::isdigit(static_cast<unsigned char>(peek()))) {
            int digit = get() - '0';
            val = val * 10 + digit;
        }
        if (val < INT32_MIN || val > INT32_MAX) {
            return Token{TokKind::INVALID, 0, tokLine, tokCol};
        }
        return Token{TokKind::NUMBER, static_cast<int>(val), tokLine, tokCol};
    }

    // any other character is invalid for this tiny language
    get();
    return Token{TokKind::INVALID, 0, tokLine, tokCol};
}
