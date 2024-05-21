//
// Created by icelake on 24-5-19.
//

#ifndef ROBIN_SYMBOL_H
#define ROBIN_SYMBOL_H
namespace symbol {
    enum Symbol {
        BASE,
        EOF_FLAG,
        INT_,
        REAL_,
        STRING_,
        IDENTIFIER,
        INTEGER,
        DOUBLE,
        STRING,
        BOOL,
        CHAR,
        VAR,
        BREAK,
        CONTINUE,
        RETURN,
        NOT,
        MINUS,
        TRUE,
        FALSE,
        NIL,
        LEFT_PAREN,
        IF,
        WHILE,
        REPEAT,
        LEFT_BRACE,
        COMMA,
        EQUAL,
        SEMICOLON,
        ELSE,
        OR,
        AND,
        NOT_EQUAL,
        EQUAL_EQUAL,
        GREATER,
        GREATER_EQUAL,
        LESS,
        LESS_EQUAL,
        PLUS,
        DIV,
        STAR,
        MOD,
        DOUBLE_ADD,
        DOUBLE_MINUS,
        LEFT_BRACKET,
        FUNCTION,
        UNTIL,
        RIGHT_BRACE,
        RIGHT_PAREN,
        RIGHT_BRACKET,
        DOLLAR,

        S,
        program,
        declarations,
        declaration,
        statement,
        breakStmt,
        continueStmt,
        returnStmt,
        funDecl,
        varDecl,
        varDef,
        varDefs,
        varInit,
        type,
        exprStmt,
        ifStmt,
        elseBranch,
        whileStmt,
        block,
        repeatStmt,
        paramList,
        parameters,
        parameter,
        expression,
        assignment,
        logic_or,
        logic_or_prime,
        logic_and,
        logic_and_prime,
        equality,
        equality_prime,
        comparison,
        comparison_prime,
        term,
        term_prime,
        factor,
        factor_prime,
        incr_exp,
        incr_op,
        unary,
        call,
        call_suffix,
        argList,
        arguments,
        primary,
        constVal,
        var,
        varSuffix,
    };

    enum Type {
        Shift,
        Reduce,
        Accept,
        Goto,
        Error
    };


}
#endif //ROBIN_SYMBOL_H
