#pragma once
#include "ast.h"
#include <vector>
#include <string>
#include <memory>

class SemanticAnalyzer {
    std::vector<std::string> errors;

public:
    void analyze(const ASTNode& root) {
        if (root.type != "PROGRAM") {
            errors.push_back("Root node is not a PROGRAM");
        }
        for (auto& child : root.children) {
            if (child->type == "PRINT" && child->children.empty()) {
                errors.push_back("PRINT statement missing argument");
            }
        }
    }

    const std::vector<std::string>& getErrors() const { return errors; }
};
