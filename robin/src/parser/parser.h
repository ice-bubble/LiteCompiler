//
// Created by icelake on 24-5-16.
//

#ifndef ROBIN_PARSER_H
#define ROBIN_PARSER_H

#include "../common.h"
#include "../ast/type.h"
#include "../ast/expr.h"
#include "../ast/stmt.h"

namespace parser {


    // 定义状态和符号
    typedef int State;
    enum Symbol{
        minus,
        plus,
        div,
        star,
        mod,
        number,
        left_paren,
        right_paren,
        dollar,
        expression,
        term,
        term_prime,
        factor,
        factor_prime,
        unary,
        primary
    };

    enum Type {
        Shift,
        Reduce,
        Accept,
        Goto,
        Error
    };

    // SLR分析表：state, symbol -> action
    struct Action {
         Type type;
        State state;  ///< 对于Shift操作，表示下一个状态；对于Reduce操作，表示规约的产生式编号;对于Goto操作，表示Goto的状态
        Action(Type type, State state) : type(type), state(state) {}
    };

    class Parser {
    private:
        List<token::Token> tokens;                         ///< 从源代码生成的token列表。
        List<SharedPtr<ast::Stmt>> stmts;
        size_t current;
        static Map<Pair<State, Symbol>, Action> slrTable;

    public:
        Parser(List<token::Token> tokens, List<SharedPtr<ast::Stmt>> stmts, size_t current);

        List<SharedPtr<ast::Stmt>> parserAst();

    };


}


#endif //ROBIN_PARSER_H
