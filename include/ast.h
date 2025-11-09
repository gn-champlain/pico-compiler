#ifndef PICO_PP_AST_H
#define PICO_PP_AST_H

#include <memory>
#include <string>
#include <vector>

enum class NodeKind {
    Expr,
    Stmt,

    BinaryExpr,
    LiteralExpr,
    VarExpr,

    BlockStmt,
    VarDeclStmt,
    AssignStmt,
    IfStmt,
    WhileStmt,
    PrintStmt
};

class ASTNode {
public:
    explicit ASTNode(NodeKind kind) : kind(kind) {}
    virtual ~ASTNode() = default;

    NodeKind getKind() const { return kind; }

private:
    NodeKind kind;
};

// LLVM-style helpers
template <typename T>
bool isa(ASTNode *node) {
    return node && T::classof(node);
}

template <typename T>
T *cast(ASTNode *node) {
    return static_cast<T *>(node);
}

template <typename T>
T *dyn_cast(ASTNode *node) {
    return isa<T>(node) ? static_cast<T *>(node) : nullptr;
}

class Expr : public ASTNode {
public:
    explicit Expr(NodeKind kind) : ASTNode(kind) {}
    static bool classof(ASTNode *node) {
        NodeKind k = node->getKind();
        return k == NodeKind::BinaryExpr
            || k == NodeKind::LiteralExpr
            || k == NodeKind::VarExpr;
    }
};

class Stmt : public ASTNode {
public:
    explicit Stmt(NodeKind kind) : ASTNode(kind) {}
    static bool classof(ASTNode *node) {
        NodeKind k = node->getKind();
        return k == NodeKind::BlockStmt
            || k == NodeKind::VarDeclStmt
            || k == NodeKind::AssignStmt
            || k == NodeKind::IfStmt
            || k == NodeKind::WhileStmt
            || k == NodeKind::PrintStmt;
    }
};

// Expressions

class BinaryExpr : public Expr {
public:
    std::string op;
    std::unique_ptr<Expr> left;
    std::unique_ptr<Expr> right;

    BinaryExpr(const std::string &op,
               std::unique_ptr<Expr> left,
               std::unique_ptr<Expr> right)
        : Expr(NodeKind::BinaryExpr),
          op(op),
          left(std::move(left)),
          right(std::move(right)) {}

    static bool classof(ASTNode *node) {
        return node->getKind() == NodeKind::BinaryExpr;
    }
};

class LiteralExpr : public Expr {
public:
    int value;

    explicit LiteralExpr(int value)
        : Expr(NodeKind::LiteralExpr), value(value) {}

    static bool classof(ASTNode *node) {
        return node->getKind() == NodeKind::LiteralExpr;
    }
};

class VarExpr : public Expr {
public:
    std::string name;

    explicit VarExpr(const std::string &name)
        : Expr(NodeKind::VarExpr), name(name) {}

    static bool classof(ASTNode *node) {
        return node->getKind() == NodeKind::VarExpr;
    }
};

// Statements

class BlockStmt : public Stmt {
public:
    std::vector<std::unique_ptr<Stmt>> statements;

    BlockStmt()
        : Stmt(NodeKind::BlockStmt) {}

    static bool classof(ASTNode *node) {
        return node->getKind() == NodeKind::BlockStmt;
    }
};

class VarDeclStmt : public Stmt {
public:
    std::string name;
    std::unique_ptr<Expr> initExpr;

    VarDeclStmt(const std::string &name,
                std::unique_ptr<Expr> initExpr)
        : Stmt(NodeKind::VarDeclStmt),
          name(name),
          initExpr(std::move(initExpr)) {}

    static bool classof(ASTNode *node) {
        return node->getKind() == NodeKind::VarDeclStmt;
    }
};

class AssignStmt : public Stmt {
public:
    std::string name;
    std::unique_ptr<Expr> value;

    AssignStmt(const std::string &name,
               std::unique_ptr<Expr> value)
        : Stmt(NodeKind::AssignStmt),
          name(name),
          value(std::move(value)) {}

    static bool classof(ASTNode *node) {
        return node->getKind() == NodeKind::AssignStmt;
    }
};

class IfStmt : public Stmt {
public:
    std::unique_ptr<Expr> condition;
    std::unique_ptr<Stmt> thenBranch;
    std::unique_ptr<Stmt> elseBranch; // may be null

    IfStmt(std::unique_ptr<Expr> condition,
           std::unique_ptr<Stmt> thenBranch,
           std::unique_ptr<Stmt> elseBranch)
        : Stmt(NodeKind::IfStmt),
          condition(std::move(condition)),
          thenBranch(std::move(thenBranch)),
          elseBranch(std::move(elseBranch)) {}

    static bool classof(ASTNode *node) {
        return node->getKind() == NodeKind::IfStmt;
    }
};

class WhileStmt : public Stmt {
public:
    std::unique_ptr<Expr> condition;
    std::unique_ptr<Stmt> body;

    WhileStmt(std::unique_ptr<Expr> condition,
              std::unique_ptr<Stmt> body)
        : Stmt(NodeKind::WhileStmt),
          condition(std::move(condition)),
          body(std::move(body)) {}

    static bool classof(ASTNode *node) {
        return node->getKind() == NodeKind::WhileStmt;
    }
};

class PrintStmt : public Stmt {
public:
    std::unique_ptr<Expr> expr;

    explicit PrintStmt(std::unique_ptr<Expr> expr)
        : Stmt(NodeKind::PrintStmt),
          expr(std::move(expr)) {}

    static bool classof(ASTNode *node) {
        return node->getKind() == NodeKind::PrintStmt;
    }
};

class Program {
public:
    std::vector<std::unique_ptr<Stmt>> statements;
};

#endif
