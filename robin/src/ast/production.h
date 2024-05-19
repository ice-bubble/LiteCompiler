//
// Created by icelake on 24-5-18.
//

#ifndef ROBIN_PRODUCTION_H
#define ROBIN_PRODUCTION_H

#include <utility>

#include "../common.h"
#include "../token/token.h"
#include "../ast/symbol.h"

namespace production {

    class Expr;

    class Expression;

    class Term;

    class Term_prime;

    class Factor;

    class Factor_prime;

    class Unary;

    class Primary;

    class Token;

    class Number;


    class Production {
    public:
        static Map<token::TokenType,symbol::Symbol> tokenToSym;

        symbol::Symbol thisSymbol = symbol::Symbol::base;

        virtual String toString() = 0;

        virtual ~Production() = default;
    };


    class Expr : public Production {
    public:
        size_t line;
        SharedPtr<Expression> expression;

        Expr(size_t line, SharedPtr<Expression> expression)
                : line(line), expression(std::move(expression)) { thisSymbol = symbol::Symbol::Expr; }

        String toString() override { return String{"Expr"}; }
    };

    class Expression : public Production {
    public:
        size_t line;

        virtual ~Expression() = default;

        explicit Expression(size_t line) : line(line) { thisSymbol = symbol::Symbol::expression; }

        String toString() override { return String{"expression"}; }
    };

    class Expression1 : public Expression {
    public:
        SharedPtr<Term> term;

        Expression1(size_t line, SharedPtr<Term> term) : Expression(line), term(std::move(term)) {}
    };

    class Expression2 : public Expression {
    public:
        explicit Expression2(size_t line) : Expression(line) {}
    };

    class Term : public Production {
    public:
        size_t line;
        SharedPtr<Factor> factor;
        SharedPtr<Term_prime> term_Prime;

        Term(size_t line, SharedPtr<Factor> factor, SharedPtr<Term_prime> termPrime)
                : line(line), factor(std::move(factor)),
                  term_Prime(std::move(termPrime)) { thisSymbol = symbol::Symbol::term; }

        String toString() override { return String{"term"}; }
    };

    class Term_prime : public Production {
    public:
        size_t line;

        explicit Term_prime(size_t line) : line(line) { thisSymbol = symbol::Symbol::term_prime; }

        virtual ~Term_prime() = default;

        String toString() override { return String{"term_prime"}; }
    };

    class Term_prime1 : public Term_prime {
    public:
        SharedPtr<Token> minus;
        SharedPtr<Factor> factor;
        SharedPtr<Term_prime> term_Prime;

        Term_prime1(size_t line, SharedPtr<Token> plus, SharedPtr<Factor> factor, SharedPtr<Term_prime> termPrime)
                : Term_prime(line), minus(std::move(plus)), factor(std::move(factor)),
                  term_Prime(std::move(termPrime)) {}
    };

    class Term_prime2 : public Term_prime {
    public:
        SharedPtr<Token> plus;
        SharedPtr<Factor> factor;
        SharedPtr<Term_prime> term_Prime;

        Term_prime2(size_t line, SharedPtr<Token> plus, SharedPtr<Factor> factor, SharedPtr<Term_prime> termPrime)
                : Term_prime(line), plus(std::move(plus)), factor(std::move(factor)),
                  term_Prime(std::move(termPrime)) {}
    };

    class Term_prime3 : public Term_prime {
    public:
        explicit Term_prime3(size_t line) : Term_prime(line) {}
    };

    class Factor : public Production {
    public:
        size_t line;
        SharedPtr<Unary> unary;
        SharedPtr<Factor_prime> factor_prime;

        Factor(size_t line, SharedPtr<Unary> unary, SharedPtr<Factor_prime> factorPrime)
                : line(line), unary(std::move(unary)),
                  factor_prime(std::move(factorPrime)) { thisSymbol = symbol::Symbol::factor; }

        String toString() override { return String{"factor"}; }
    };

    class Factor_prime : public Production {
    public:
        size_t line;

        explicit Factor_prime(size_t line) : line(line) { thisSymbol = symbol::Symbol::factor_prime; }

        virtual ~Factor_prime() = default;

        String toString() override { return String{"factor_prime"}; }
    };

    class Factor_prime1 : public Factor_prime {
    public:
        SharedPtr<Token> div;
        SharedPtr<Unary> unary;
        SharedPtr<Factor_prime> factor_prime;

        Factor_prime1(size_t line, SharedPtr<Token> div, SharedPtr<Unary> unary, SharedPtr<Factor_prime> factorPrime)
                : Factor_prime(line), div(std::move(div)), unary(std::move(unary)),
                  factor_prime(std::move(factorPrime)) {}
    };

    class Factor_prime2 : public Factor_prime {
    public:
        SharedPtr<Token> star;
        SharedPtr<Unary> unary;
        SharedPtr<Factor_prime> factor_prime;

        Factor_prime2(size_t line, SharedPtr<Token> star, SharedPtr<Unary> unary, SharedPtr<Factor_prime> factorPrime)
                : Factor_prime(line), star(std::move(star)), unary(std::move(unary)),
                  factor_prime(std::move(factorPrime)) {}
    };

    class Factor_prime3 : public Factor_prime {
    public:
        SharedPtr<Token> mod;
        SharedPtr<Unary> unary;
        SharedPtr<Factor_prime> factor_prime;

        Factor_prime3(size_t line, SharedPtr<Token> mod, SharedPtr<Unary> unary, SharedPtr<Factor_prime> factorPrime)
                : Factor_prime(line), mod(std::move(mod)), unary(std::move(unary)),
                  factor_prime(std::move(factorPrime)) {}
    };

    class Factor_prime4 : public Factor_prime {
    public:
        explicit Factor_prime4(size_t line) : Factor_prime(line) {}
    };

    class Unary : public Production {
    public:
        size_t line;

        explicit Unary(size_t line) : line(line) { thisSymbol = symbol::Symbol::unary; }

        virtual ~Unary() = default;

        String toString() override { return String{"unary"}; }
    };

    class Unary1 : public Unary {
    public:
        size_t line;
        SharedPtr<Token> minus;
        SharedPtr<Unary> unary;

        Unary1(size_t line, SharedPtr<Token> minus, SharedPtr<Unary> unary)
                : Unary(line), minus(std::move(minus)), unary(std::move(unary)) {}
    };

    class Unary2 : public Unary {
    public:
        SharedPtr<Primary> primary;

        Unary2(size_t line, SharedPtr<Primary> primary) : Unary(line), primary(std::move(primary)) {}
    };

    class Primary : public Production {
    public:
        size_t line;

        explicit Primary(size_t line) : line(line) {thisSymbol = symbol::Symbol::primary; }

        virtual ~Primary() = default;

        String toString() override { return String{"primary"}; }
    };

    class Primary1 : public Primary {
    public:
        SharedPtr<Number> number;

        Primary1(size_t line, SharedPtr<Number> number) : Primary(line), number(std::move(number)) {}
    };

    class Primary2 : public Primary {
    public:
        SharedPtr<Token> left_paren;
        SharedPtr<Expression> expression;
        SharedPtr<Token> right_paren;

        Primary2(size_t line, SharedPtr<Token> leftParen, SharedPtr<Expression> expression,
                 SharedPtr<Token> rightParen)
                : Primary(line), left_paren(std::move(leftParen)), expression(std::move(expression)),
                  right_paren(std::move(rightParen)) {}
    };

    class Number : public Production {
    public:
        size_t line;

        explicit Number(size_t line) : line(line) {thisSymbol = symbol::Symbol::number; }

        virtual ~Number() = default;

        String toString() override { return String{"number"}; }
    };

    class Number1 : public Number {
    public:
        SharedPtr<Token> int_;

        Number1(size_t line, SharedPtr<Token> int_) : Number(line), int_(std::move(int_)) {}
    };

    class Number2 : public Number {
    public:
        SharedPtr<Token> float_;

        Number2(size_t line, SharedPtr<Token> float_) : Number(line), float_(std::move(float_)) {}
    };


    //////接下来是token对应的production类
    class Token : public Production {
    public:
        size_t line;
        token::Token thisToken;


        Token(size_t line, token::Token thisToken) : line(line), thisToken(std::move(thisToken))
        {thisSymbol = tokenToSym[thisToken.getType()]; }

        String toString() override {
            if (thisToken.getType() == token::TokenType::TOKEN_INT_ ||
                thisToken.getType() == token::TokenType::TOKEN_REAL_)
                return thisToken.getLiteralString();
            return thisToken.getLexeme();
        }
    };

}

#endif //ROBIN_PRODUCTION_H
