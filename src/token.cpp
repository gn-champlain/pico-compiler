#include "token.h"

std::string tokenKindToString(TokenKind kind) {
    switch (kind) {
    case TokenKind::EndOfFile:    return "EOF";
    case TokenKind::Identifier:   return "Identifier";
    case TokenKind::Number:       return "Number";
    case TokenKind::KwLet:        return "let";
    case TokenKind::KwIf:         return "if";
    case TokenKind::KwElse:       return "else";
    case TokenKind::KwWhile:      return "while";
    case TokenKind::KwPrint:      return "print";
    case TokenKind::LParen:       return "(";
    case TokenKind::RParen:       return ")";
    case TokenKind::LBrace:       return "{";
    case TokenKind::RBrace:       return "}";
    case TokenKind::Semicolon:    return ";";
    case TokenKind::Equal:        return "=";
    case TokenKind::Plus:         return "+";
    case TokenKind::Minus:        return "-";
    case TokenKind::Star:         return "*";
    case TokenKind::Slash:        return "/";
    case TokenKind::Percent:      return "%";
    case TokenKind::Less:         return "<";
    case TokenKind::Greater:      return ">";
    case TokenKind::LessEqual:    return "<=";
    case TokenKind::GreaterEqual: return ">=";
    case TokenKind::EqualEqual:   return "==";
    case TokenKind::BangEqual:    return "!=";
    default:                      return "Unknown";
    }
}
