/**
 * @file stmt.h
 * @brief Stmt类及相关函数的声明。
 * @date 24-5-16
 */

#ifndef ROBIN_STMT_H
#define ROBIN_STMT_H

#include <utility>

#include "../common.h"
#include "../token/token.h"
#include "type.h"
#include "expr.h"

namespace ast {
    /**
 * @brief 所有语句的基类。
 */
    class Stmt {
    public:
        virtual ~Stmt() = default;
    };

    class Block : Stmt {
    public:
        size_t line;
        List<SharedPtr<Stmt>> statements;

        Block(size_t line, List<SharedPtr<Stmt>> statements) : line(line), statements(std::move(statements)) {}
    };

    class Expression : Stmt {
    public:
        size_t line;
        SharedPtr<Expr> expression;

        Expression(size_t line, SharedPtr<Expr> expression) : line(line), expression(std::move(expression)) {}
    };

    class Function : Stmt {
    public:
        size_t line;
        token::Token name;
        List<token::Token> parmList;
        List<SharedPtr<Stmt>> body;
        SharedPtr<Type> returnType;

        Function(size_t line, token::Token name, List<token::Token> parmList, List<SharedPtr<Stmt>> body,
                 SharedPtr<Type> returnType)
                : line(line), name(std::move(name)), parmList(std::move(parmList)), body(std::move(body)),
                  returnType(std::move(returnType)) {}
    };

    class If : Stmt {
    public:
        size_t line;
        SharedPtr<Expr> condition;
        SharedPtr<Stmt> thenBranch;
        SharedPtr<Stmt> elseBranch;

        If(size_t line, SharedPtr<Expr> condition, SharedPtr<Stmt> thenBranch, SharedPtr<Stmt> elseBranch)
                : line(line), condition(std::move(condition)), thenBranch(std::move(thenBranch)),
                  elseBranch(std::move(elseBranch)) {}
    };

    class While : Stmt {
    public:
        size_t line;
        SharedPtr<Expr> condition;
        SharedPtr<Stmt> body;

        While(size_t line, SharedPtr<Expr> condition, SharedPtr<Stmt> body)
                : line(line), condition(std::move(condition)), body(std::move(body)) {}
    };

    class Repeat : Stmt {
    public:
        size_t line;
        SharedPtr<Stmt> body;
        SharedPtr<Expr> condition;

        Repeat(size_t line, SharedPtr<Stmt> body, SharedPtr<Expr> condition)
                : line(line), body(std::move(body)), condition(std::move(condition)) {}
    };

    class Break : Stmt {
    public:
        size_t line;
        token::Token keyword;

        Break(size_t line, token::Token keyword) : line(line), keyword(std::move(keyword)) {}
    };

    class Continue : Stmt {
    public:
        size_t line;
        token::Token keyword;

        Continue(size_t line, token::Token keyword) : line(line), keyword(std::move(keyword)) {}
    };

    class Return : Stmt {
    public:
        size_t line;
        SharedPtr<Expr> value;

        Return(size_t line, SharedPtr<Expr> value) : line(line), value(std::move(value)) {}
    };

    class Var : Stmt {
    public:
        size_t line;
        List<token::Token> nameList;
        List<SharedPtr<Expr>> initializerList;
        List<Type> typeList;

        Var(size_t line, List<token::Token> nameList, List<SharedPtr<Expr>> initializerList, List<Type> typeList)
                : line(line), nameList(std::move(nameList)), initializerList(std::move(initializerList)),
                  typeList(std::move(typeList)) {}
    };
}

#endif //ROBIN_STMT_H
