//
// Created by icelake on 24-5-16.
//

#include "parser.h"

namespace parser {

    Map<Pair<State, Symbol>, Action> Parser::slrTable = {
            {{0, Symbol::minus},        {Type::Shift,  4}},
            {{0, Symbol::number},       {Type::Shift,  6}},
            {{0, Symbol::left_paren},   {Type::Shift,  7}},
            {{0, Symbol::term},         {Type::Goto,   1}},
            {{0, Symbol::factor},       {Type::Goto,   2}},
            {{0, Symbol::unary},        {Type::Goto,   3}},
            {{0, Symbol::primary},      {Type::Goto,   5}},

            {{1, Symbol::right_parent}, {Type::Accept, 1}},
            {{1, Symbol::dollar},       {Type::Accept, 1}},

            {{2, Symbol::minus},        {Type::Shift,  9}},
            {{2, Symbol::plus},         {Type::Shift,  10}},
            {{2, Symbol::right_parent}, {Type::Reduce, 5}},
            {{2, Symbol::dollar},       {Type::Reduce, 5}},
            {{2, Symbol::term_prime},   {Type::Goto,   8}},

            {{3, Symbol::minus},        {Type::Reduce, 10}},
            {{3, Symbol::plus},         {Type::Reduce, 10}},
            {{3, Symbol::div},          {Type::Shift,  12}},
            {{3, Symbol::star},         {Type::Shift,  13}},
            {{3, Symbol::mod},          {Type::Shift,  14}},
            {{3, Symbol::right_parent}, {Type::Reduce, 10}},
            {{3, Symbol::dollar},       {Type::Reduce, 10}},
            {{3, Symbol::factor_prime}, {Type::Goto,   11}},

            {{4, Symbol::minus},        {Type::Shift,  4}},
            {{4, Symbol::number},       {Type::Shift,  6}},
            {{4, Symbol::left_paren},   {Type::Shift,  7}},
            {{4, Symbol::unary},        {Type::Goto,   15}},
            {{4, Symbol::primary},      {Type::Goto,   5}},


    };

    Parser::Parser(List<token::Token> tokens, List<SharedPtr<ast::Stmt>> stmts, size_t current)
            : tokens(std::move(tokens)), stmts(std::move(stmts)), current(current) {}

    List<SharedPtr<ast::Stmt>> Parser::parserAst() {

        return stmts;
    }
}
