//
// Created by icelake on 24-5-18.
//

#ifndef ROBIN_PRODUCTION_H
#define ROBIN_PRODUCTION_H

#include <utility>

#include "../common.h"
#include "../token/token.h"

namespace production {

    class Expr;

    class Expression;

    class Term;

    class Term_prime;

    class Factor;

    class Factor_prime;

    class Unary;

    class Primary;

    class Number;

    class Minus;

    class Plus;

    class Div;

    class Star;

    class Mod;

    class LeftParen;

    class RightParen;

    class Int;

    class Float;


    class Production {
    public:
        virtual ~Production() = default;
    };

    class Expr : Production {
    public:
        size_t line;
        SharedPtr<Expression> expression;

        Expr(size_t line, SharedPtr<Expression> expression) : line(line), expression(std::move(expression)) {}

        static String toString() { return String{"Expr"}; }
    };

    class Expression : Production {
    public:
        virtual ~Expression() = default;

        static String toString() { return String{"expression"}; }
    };

    class Expression1 : Expression {
    public:
        size_t line;
        SharedPtr<Term> term;

        Expression1(size_t line, SharedPtr<Term> term) : line(line), term(std::move(term)) {}
    };

    class Expression2 : Expression {
    };

    class Term : Production {
    public:
        size_t line;
        SharedPtr<Factor> factor;
        SharedPtr<Term_prime> term_Prime;

        Term(size_t line, SharedPtr<Factor> factor, SharedPtr<Term_prime> termPrime)
                : line(line), factor(std::move(factor)), term_Prime(std::move(termPrime)) {}

        static String toString() { return String{"term"}; }
    };

    class Term_prime : Production {
    public:
        virtual ~Term_prime() = default;

        static String toString() { return String{"term_prime"}; }
    };

    class Term_prime1 : Term_prime {
    public:
        size_t line;
        SharedPtr<Minus> minus;
        SharedPtr<Factor> factor;
        SharedPtr<Term_prime> term_Prime;

        Term_prime1(size_t line, SharedPtr<Minus> plus, SharedPtr<Factor> factor, SharedPtr<Term_prime> termPrime)
                : line(line), minus(std::move(plus)), factor(std::move(factor)), term_Prime(std::move(termPrime)) {}
    };

    class Term_prime2 : Term_prime {
    public:
        size_t line;
        SharedPtr<Plus> plus;
        SharedPtr<Factor> factor;
        SharedPtr<Term_prime> term_Prime;

        Term_prime2(size_t line, SharedPtr<Plus> plus, SharedPtr<Factor> factor, SharedPtr<Term_prime> termPrime)
                : line(line), plus(std::move(plus)), factor(std::move(factor)), term_Prime(std::move(termPrime)) {}
    };

    class Term_prime3 : Term_prime {
    };

    class Factor : Production {
    public:
        size_t line;
        SharedPtr<Unary> unary;
        SharedPtr<Factor_prime> factor_prime;

        Factor(size_t line, SharedPtr<Unary> unary, SharedPtr<Factor_prime> factorPrime)
                : line(line), unary(std::move(unary)), factor_prime(std::move(factorPrime)) {}

        static String toString() { return String{"factor"}; }
    };

    class Factor_prime : Production {
    public:
        virtual ~Factor_prime() = default;

        static String toString() { return String{"factor_prime"}; }
    };

    class Factor_prime1 : Factor_prime {
    public:
        size_t line;
        SharedPtr<Div> div;
        SharedPtr<Unary> unary;
        SharedPtr<Factor_prime> factor_prime;

        Factor_prime1(size_t line, SharedPtr<Div> div, SharedPtr<Unary> unary, SharedPtr<Factor_prime> factorPrime)
                : line(line), div(std::move(div)), unary(std::move(unary)), factor_prime(std::move(factorPrime)) {}
    };

    class Factor_prime2 : Factor_prime {
    public:
        size_t line;
        SharedPtr<Star> star;
        SharedPtr<Unary> unary;
        SharedPtr<Factor_prime> factor_prime;

        Factor_prime2(size_t line, SharedPtr<Star> star, SharedPtr<Unary> unary, SharedPtr<Factor_prime> factorPrime)
                : line(line), star(std::move(star)), unary(std::move(unary)), factor_prime(std::move(factorPrime)) {}
    };

    class Factor_prime3 : Factor_prime {
    public:
        size_t line;
        SharedPtr<Mod> mod;
        SharedPtr<Unary> unary;
        SharedPtr<Factor_prime> factor_prime;

        Factor_prime3(size_t line, SharedPtr<Mod> mod, SharedPtr<Unary> unary, SharedPtr<Factor_prime> factorPrime)
                : line(line), mod(std::move(mod)), unary(std::move(unary)), factor_prime(std::move(factorPrime)) {}
    };

    class Factor_prime4 : Factor_prime {
    };

    class Unary : Production {
    public:
        virtual ~Unary() = default;

        static String toString() { return String{"unary"}; }
    };

    class Unary1 : Unary {
    public:
        size_t line;
        SharedPtr<Minus> minus;
        SharedPtr<Unary> unary;

        Unary1(size_t line, SharedPtr<Minus> minus, SharedPtr<Unary> unary)
                : line(line), minus(std::move(minus)), unary(std::move(unary)) {}
    };

    class Unary2 : Unary {
    public:
        size_t line;
        SharedPtr<Primary> primary;

        Unary2(size_t line, SharedPtr<Primary> primary) : line(line), primary(std::move(primary)) {}
    };

    class Primary : Production {
    public:
        virtual ~Primary() = default;

        static String toString() { return String{"primary"}; }
    };

    class Primary1 : Primary {
    public:
        size_t line;
        SharedPtr<Number> number;

        Primary1(size_t line, SharedPtr<Number> number) : line(line), number(std::move(number)) {}
    };

    class Primary2 : Primary {
    public:
        size_t line;
        SharedPtr<LeftParen> left_paren;
        SharedPtr<Expression> expression;
        SharedPtr<RightParen> right_paren;

        Primary2(size_t line, SharedPtr<LeftParen> leftParen, SharedPtr<Expression> expression,
                 SharedPtr<RightParen> rightParen)
                : line(line), left_paren(std::move(leftParen)), expression(std::move(expression)),
                  right_paren(std::move(rightParen)) {}
    };

    class Number : Production {
    public:
        virtual ~Number() = default;

        static String toString() { return String{"number"}; }
    };

    class Number1 : Production {
    public:
        size_t line;
        SharedPtr<Int> int_;

        Number1(size_t line, SharedPtr<Int> int_) : line(line), int_(std::move(int_)) {}
    };

    class Number2 : Production {
    public:
        size_t line;
        SharedPtr<Float> float_;

        Number2(size_t line, SharedPtr<Float> float_) : line(line), float_(std::move(float_)) {}
    };


    //////接下来是token对应的production类

    class Minus : Production {
    public:
        size_t line;
        token::Token minus;

        Minus(size_t line, token::Token minus) : line(line), minus(std::move(minus)) {}

        static String toString() { return String{"-"}; }
    };

    class Plus : Production {
    public:
        size_t line;
        token::Token plus;

        Plus(size_t line, token::Token plus) : line(line), plus(std::move(plus)) {}

        static String toString() { return String{"+"}; }
    };

    class Div : Production {
    public:
        size_t line;
        token::Token div;

        Div(size_t line, token::Token div) : line(line), div(std::move(div)) {}

        static String toString() { return String{"/"}; }
    };

    class Star : Production {
    public:
        size_t line;
        token::Token star;

        Star(size_t line, token::Token star) : line(line), star(std::move(star)) {}

        static String toString() { return String{"*"}; }
    };

    class Mod : Production {
    public:
        size_t line;
        token::Token mod;

        Mod(size_t line, token::Token mod) : line(line), mod(std::move(mod)) {}

        static String toString() { return String{"%"}; }
    };

    class LeftParen : Production {
    public:
        size_t line;
        token::Token left_paren;

        LeftParen(size_t line, token::Token left_paren) : line(line), left_paren(std::move(left_paren)) {}

        static String toString() { return String{"("}; }
    };

    class RightParen : Production {
    public:
        size_t line;
        token::Token right_paren;

        RightParen(size_t line, token::Token right_paren) : line(line), right_paren(std::move(right_paren)) {}

        static String toString() { return String{")"}; }
    };

    class Int : Production {
    public:
        size_t line;
        token::Token int_;

        Int(size_t line, token::Token int_) : line(line), int_(std::move(int_)) {}

        String toString() { return int_.getLiteralString(); }
    };

    class Float : Production {
    public:
        size_t line;
        token::Token float_;

        Float(size_t line, token::Token float_) : line(line), float_(std::move(float_)) {}

        String toString() { return float_.getLiteralString(); }
    };

}

#endif //ROBIN_PRODUCTION_H
