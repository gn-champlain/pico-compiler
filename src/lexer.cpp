#include "lexer.h"
#include <cctype>

Lexer::Lexer(const std::string &source)
    : src(source), pos(0), line(1), column(1) {}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;

    while (!isAtEnd()) {
        skipWhitespaceAndComments();
        if (isAtEnd()) break;

        char c = peek();

        if (std::isalpha(static_cast<unsigned char>(c))) {
            tokens.push_back(identifier());
        } else if (std::isdigit(static_cast<unsigned char>(c))) {
            tokens.push_back(number());
        } else {
            switch (c) {
            case '(': tokens.push_back(makeToken(TokenKind::LParen, "(")); advance(); break;
            case ')': tokens.push_back(makeToken(TokenKind::RParen, ")")); advance(); break;
            case '{': tokens.push_back(makeToken(TokenKind::LBrace, "{")); advance(); break;
            case '}': tokens.push_back(makeToken(TokenKind::RBrace, "}")); advance(); break;
            case ';': tokens.push_back(makeToken(TokenKind::Semicolon, ";")); advance(); break;
            case '+': tokens.push_back(makeToken(TokenKind::Plus, "+")); advance(); break;
            case '-': tokens.push_back(makeToken(TokenKind::Minus, "-")); advance(); break;
            case '*': tokens.push_back(makeToken(TokenKind::Star, "*")); advance(); break;
            case '/':
                advance();
                if (!isAtEnd() && peek() == '/') {
                    while (!isAtEnd() && peek() != '\n') {
                        advance();
                    }
                } else {
                    tokens.push_back(makeToken(TokenKind::Slash, "/"));
                }
                break;
            case '%': tokens.push_back(makeToken(TokenKind::Percent, "%")); advance(); break;
            case '=':
                advance();
                if (!isAtEnd() && peek() == '=') {
                    advance();
                    tokens.push_back(makeToken(TokenKind::EqualEqual, "=="));
                } else {
                    tokens.push_back(makeToken(TokenKind::Equal, "="));
                }
                break;
            case '<':
                advance();
                if (!isAtEnd() && peek() == '=') {
                    advance();
                    tokens.push_back(makeToken(TokenKind::LessEqual, "<="));
                } else {
                    tokens.push_back(makeToken(TokenKind::Less, "<"));
                }
                break;
            case '>':
                advance();
                if (!isAtEnd() && peek() == '=') {
                    advance();
                    tokens.push_back(makeToken(TokenKind::GreaterEqual, ">="));
                } else {
                    tokens.push_back(makeToken(TokenKind::Greater, ">"));
                }
                break;
            case '!':
                advance();
                if (!isAtEnd() && peek() == '=') {
                    advance();
                    tokens.push_back(makeToken(TokenKind::BangEqual, "!="));
                }
                break;
            default:
                // skip unknown characters for now
                advance();
                break;
            }
        }
    }

    tokens.push_back(Token{TokenKind::EndOfFile, "", line, column});
    return tokens;
}

char Lexer::peek() const {
    if (isAtEnd()) return '\0';
    return src[pos];
}

char Lexer::advance() {
    char c = peek();
    if (c == '\n') {
        line++;
        column = 1;
    } else {
        column++;
    }
    pos++;
    return c;
}

bool Lexer::isAtEnd() const {
    return pos >= src.size();
}

void Lexer::skipWhitespaceAndComments() {
    while (!isAtEnd()) {
        char c = peek();
        if (c == ' ' || c == '\t' || c == '\r' || c == '\n') {
            advance();
        } else if (c == '/' && pos + 1 < src.size() && src[pos + 1] == '/') {
            // comment until end of line
            while (!isAtEnd() && peek() != '\n') {
                advance();
            }
        } else {
            break;
        }
    }
}

Token Lexer::identifier() {
    size_t start = pos;
    int startCol = column;
    while (!isAtEnd() && (std::isalnum(static_cast<unsigned char>(peek())))) {
        advance();
    }
    std::string text = src.substr(start, pos - start);

    if (text == "let")   return Token{TokenKind::KwLet, text, line, startCol};
    if (text == "if")    return Token{TokenKind::KwIf, text, line, startCol};
    if (text == "else")  return Token{TokenKind::KwElse, text, line, startCol};
    if (text == "while") return Token{TokenKind::KwWhile, text, line, startCol};
    if (text == "print") return Token{TokenKind::KwPrint, text, line, startCol};

    return Token{TokenKind::Identifier, text, line, startCol};
}

Token Lexer::number() {
    size_t start = pos;
    int startCol = column;
    while (!isAtEnd() && std::isdigit(static_cast<unsigned char>(peek()))) {
        advance();
    }
    std::string text = src.substr(start, pos - start);
    return Token{TokenKind::Number, text, line, startCol};
}

Token Lexer::makeToken(TokenKind kind, const std::string &lexeme) {
    return Token{kind, lexeme, line, column};
}

bool Lexer::match(char expected) {
    if (isAtEnd()) return false;
    if (src[pos] != expected) return false;
    advance();
    return true;
}
