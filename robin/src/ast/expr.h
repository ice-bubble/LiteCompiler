/**
 * @file expr.h
 * @brief Token类及相关函数的声明。
 * @date 24-5-15
 */

#ifndef ROBIN_EXPR_H
#define ROBIN_EXPR_H

#include <utility>

#include "../common.h"
#include "../token/token.h"
#include "type.h"

namespace ast{
    /**
 * @brief 所有表达式的基类。
 */
    class Expr {
    public:
        virtual ~Expr() = default;
    };

/**
 * @brief 表示表达式中的字面量值。
 */
    class Literal : Expr {
    public:
        size_t line;                   ///< line 表达式行号
        const Object val;              ///< val 存储字面量
        SharedPtr<Type> literalType;   ///< 字面量的类型

        Literal(size_t line, Object val, SharedPtr<Type> literalType)
                : line(line), val(std::move(val)), literalType(std::move(literalType)) {}
    };

/**
 * @brief 表示表达式中的变量。
 */
    class Variable : Expr {
    public:
        size_t line;                   ///< line 表达式行号
        token::Token name;             ///< name 存储一个 identifier token
        SharedPtr<Type> varType;       ///< 变量的类型

        Variable(size_t line, token::Token name, SharedPtr<Type> varType)
                : line(line), name(std::move(name)), varType(std::move(varType)) {}
    };

/**
 * @brief 表示表达式中的二元操作。
 */
    class Binary : public Expr {
    public:
        size_t line;                   ///< 表达式所在行号
        SharedPtr<Expr> left;          ///< 左操作数
        token::Token op;               ///< 操作符token
        SharedPtr<Expr> right;         ///< 右操作数

        Binary(size_t line, SharedPtr<Expr> left, token::Token op, SharedPtr<Expr> right)
                : line(line), left(std::move(left)), op(std::move(op)), right(std::move(right)) {}
    };

/**
 * @brief 表示表达式中的一元操作。
 */
    class Unary : Expr {
    public:
        size_t line;                   ///< 表达式所在行号
        token::Token op;               ///< 操作符token
        SharedPtr<Expr> expression;    ///< 右操作数

        Unary(size_t line, token::Token op, SharedPtr<Expr> expression)
                : line(line), op(std::move(op)), expression(std::move(expression)) {}
    };

/**
 * @brief 表示表达式中的函数调用。
 */
    class Call : Expr {
    public:
        size_t line;                     ///< 表达式所在行号
        SharedPtr<Expr> callee;          ///< 被调用的函数
        token::Token left_paren;         ///< 左括号token
        List<SharedPtr<Expr>> paramList; ///< 函数参数列表

        Call(size_t line, const SharedPtr<Expr> &callee, token::Token leftParen, List<SharedPtr<Expr>> paramList)
                : line(line), callee(callee), left_paren(std::move(leftParen)), paramList(std::move(paramList)) {}
    };


/**
 * @brief 表示表达式中的赋值操作。
 */
    class Assign : Expr {
    public:
        size_t line;                    ///< 表达式所在行号
        SharedPtr<Expr> var;            ///< 被赋值的变量
        SharedPtr<Expr> value;          ///< 赋值的值

        Assign(size_t line, SharedPtr<Expr> var, SharedPtr<Expr> value)
                : line(line), var(std::move(var)), value(std::move(value)) {}
    };

/**
 * @brief 表示表达式中的分组表达式，即括号内的表达式。
 */
    class Group : Expr {
    public:
        size_t line;                    ///< 表达式所在行号
        SharedPtr<Expr> expression;     ///< 分组的表达式

        Group(size_t line, SharedPtr<Expr> expression) : line(line), expression(std::move(expression)) {}
    };
}

#endif //ROBIN_EXPR_H
