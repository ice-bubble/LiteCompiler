//
// Created by icelake on 24-5-19.
//

#ifndef ROBIN_SYMBOL_H
#define ROBIN_SYMBOL_H
namespace symbol {
    enum Symbol {
        base,
        minus,
        plus,
        div,
        star,
        mod,
        int_,
        real_,
        left_paren,
        right_paren,
        dollar,
        Expr,
        expression,
        term,
        term_prime,
        factor,
        factor_prime,
        unary,
        primary,
        number
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
