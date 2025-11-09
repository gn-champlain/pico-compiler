#pragma once
#include <string>
#include <vector>
#include <memory>

class ASTNode {
public:
    std::string type;
    std::string value;
    std::vector<std::shared_ptr<ASTNode>> children;

    ASTNode(const std::string &t, const std::string &v)
        : type(t), value(v) {}

    ASTNode(const std::string &t)
        : type(t) {}

    ASTNode() = default;
};
