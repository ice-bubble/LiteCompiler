#ifndef AST_H
#define AST_H

#include <memory>
#include <vector>

class ASTNode
{
public:
    virtual ~ASTNode() = default;
};

class ASTBinaryOp : public ASTNode
{
public:
    ASTBinaryOp(std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right, const std::string &op)
        : left(std::move(left)), right(std::move(right)), op(op) {}

    std::unique_ptr<ASTNode> left, right;
    std::string op;
};

class ASTIdentifier : public ASTNode
{
public:
    ASTIdentifier(const std::string &name) : name(name) {}

    std::string name;
};

class ASTParentheses : public ASTNode
{
public:
    ASTParentheses(std::unique_ptr<ASTNode> expr) : expr(std::move(expr)) {}

    std::unique_ptr<ASTNode> expr;
};


#endif //AST_H
