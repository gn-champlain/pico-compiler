#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <memory>
#include <string>
#include "token.h"

// Forward declaration of ASTNode (defined in ast.h)
struct ASTNode;

// Simple stub parser for Pico++ to make IR backend work
class Parser {
public:
    explicit Parser(const std::vector<Token>& tokens)
        : tokens(tokens)
    {
    }

    // Dummy parseProgram: returns empty AST
    std::shared_ptr<ASTNode> parseProgram() {
        return nullptr;
    }

    // Dummy getErrors: return empty list so main.cpp compiles
    const std::vector<std::string>& getErrors() const {
        return errors;
    }

private:
    const std::vector<Token>& tokens;
    std::vector<std::string> errors;
};

#endif // PARSER_H
