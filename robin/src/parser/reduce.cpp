//
// Created by icelake on 24-5-19.
//
#define REDUCE(P, index)           SharedPtr<production::P> P##Instance##_##index =          \
                                        std::dynamic_pointer_cast<production::P>(            \
                                  productions.back());                                       \
                                  productions.pop_back();                                    \
                                  stateStack.pop();                                          \


#include "parser.h"

namespace parser {

    void Parser::reduceByExpr() {
        //std::cout<<"reduceByExpr";
        REDUCE(Expression, 0)

        SharedPtr<production::Production> ExprInstance = std::make_shared<production::Expr>(
                ExpressionInstance_0->line, ExpressionInstance_0);
        productions.push_back(ExprInstance);
    }

    void Parser::reduceByExpression1() {
        //std::cout<<"reduceByExpression1";
        REDUCE(Term, 0)

        SharedPtr<production::Production> Expression1Instance = std::make_shared<production::Expression1>(
                TermInstance_0->line, TermInstance_0);
        productions.push_back(Expression1Instance);
    }

    void Parser::reduceByExpression2() {
        //std::cout<<"reduceByExpression2";
        SharedPtr<production::Production> Expression2Instance = std::make_shared<production::Expression2>(-1);
        productions.push_back(Expression2Instance);
    }

    void Parser::reduceByTerm() {
        //std::cout<<"reduceByTerm";
        REDUCE(Term_prime, 0)

        REDUCE(Factor, 0)

        SharedPtr<production::Production> TermInstance = std::make_shared<production::Term>(
                FactorInstance_0->line, FactorInstance_0, Term_primeInstance_0);
        productions.push_back(TermInstance);
    }

    void Parser::reduceByTerm_prime1() {
        REDUCE(Term_prime, 0)

        REDUCE(Factor, 0)

        REDUCE(Token, 0)

        SharedPtr<production::Production> Term_prime1Instance = std::make_shared<production::Term_prime1>(
                TokenInstance_0->line, TokenInstance_0, FactorInstance_0, Term_primeInstance_0);
        productions.push_back(Term_prime1Instance);
    }

    void Parser::reduceByTerm_prime2() {
        REDUCE(Term_prime, 0)

        REDUCE(Factor, 0)

        REDUCE(Token, 0)

        SharedPtr<production::Production> Term_prime2Instance = std::make_shared<production::Term_prime2>(
                TokenInstance_0->line, TokenInstance_0, FactorInstance_0, Term_primeInstance_0);
        productions.push_back(Term_prime2Instance);
    }

    void Parser::reduceByTerm_prime3() {
        SharedPtr<production::Production> term_prime3 = std::make_shared<production::Term_prime3>(-1);
        productions.push_back(term_prime3);
    }

    void Parser::reduceByFactor() {
        REDUCE(Factor_prime, 0)

        REDUCE(Unary, 0)

        SharedPtr<production::Production> FactorInstance = std::make_shared<production::Factor>(
                UnaryInstance_0->line, UnaryInstance_0, Factor_primeInstance_0);
        productions.push_back(FactorInstance);
    }

    void Parser::reduceByFactor_prime1() {
        REDUCE(Factor_prime, 0)

        REDUCE(Unary, 0)

        REDUCE(Token, 0)

        SharedPtr<production::Production> Factor_prime1Instance = std::make_shared<production::Factor_prime1>(
                TokenInstance_0->line, TokenInstance_0, UnaryInstance_0, Factor_primeInstance_0);
        productions.push_back(Factor_prime1Instance);
    }

    void Parser::reduceByFactor_prime2() {
        REDUCE(Factor_prime, 0)

        REDUCE(Unary, 0)

        REDUCE(Token, 0)

        SharedPtr<production::Production> Factor_prime2Instance = std::make_shared<production::Factor_prime2>(
                TokenInstance_0->line, TokenInstance_0, UnaryInstance_0, Factor_primeInstance_0);
        productions.push_back(Factor_prime2Instance);
    }

    void Parser::reduceByFactor_prime3() {
        REDUCE(Factor_prime, 0)

        REDUCE(Unary, 0)

        REDUCE(Token, 0)

        SharedPtr<production::Production> Factor_prime3Instance = std::make_shared<production::Factor_prime3>(
                TokenInstance_0->line, TokenInstance_0, UnaryInstance_0, Factor_primeInstance_0);
        productions.push_back(Factor_prime3Instance);
    }

    void Parser::reduceByFactor_prime4() {
        SharedPtr<production::Production> term_prime4 = std::make_shared<production::Factor_prime4>(-1);
        productions.push_back(term_prime4);
    }

    void Parser::reduceByUnary1() {
        REDUCE(Unary, 0)

        REDUCE(Token, 0)

        SharedPtr<production::Production> Unary1Instance = std::make_shared<production::Unary1>(
                TokenInstance_0->line, TokenInstance_0, UnaryInstance_0);
        productions.push_back(Unary1Instance);
    }

    void Parser::reduceByUnary2() {
        REDUCE(Primary, 0)

        SharedPtr<production::Production> Unary2Instance = std::make_shared<production::Unary2>(
                PrimaryInstance_0->line, PrimaryInstance_0);
        productions.push_back(Unary2Instance);
    }

    void Parser::reduceByPrimary1() {
        REDUCE(Number, 0)
        SharedPtr<production::Production> Primary1Instance = std::make_shared<production::Primary1>(
                NumberInstance_0->line, NumberInstance_0);
        productions.push_back(Primary1Instance);
    }

    void Parser::reduceByPrimary2() {
        REDUCE(Token, 1)
        REDUCE(Expression, 0)
        REDUCE(Token, 0)

        SharedPtr<production::Production> Primary2Instance = std::make_shared<production::Primary2>(
                TokenInstance_0->line, TokenInstance_0, ExpressionInstance_0, TokenInstance_1);
        productions.push_back(Primary2Instance);

    }

    void Parser::reduceByNumber1() {
        REDUCE(Token, 0)

        SharedPtr<production::Production> Number1Instance = std::make_shared<production::Number1>(
                TokenInstance_0->line, TokenInstance_0);
        productions.push_back(Number1Instance);
    }

    void Parser::reduceByNumber2() {
        REDUCE(Token, 0)

        SharedPtr<production::Production> Number1Instance = std::make_shared<production::Number1>(
                TokenInstance_0->line, TokenInstance_0);
        productions.push_back(Number1Instance);
    }

    List<Parser::VoidFuncPtr> Parser::ReduceFunctions = {
            &Parser::reduceByExpr,
            &Parser::reduceByExpression1,
            &Parser::reduceByExpression2,
            &Parser::reduceByTerm,
            &Parser::reduceByTerm_prime1,
            &Parser::reduceByTerm_prime2,
            &Parser::reduceByTerm_prime3,
            &Parser::reduceByFactor,
            &Parser::reduceByFactor_prime1,
            &Parser::reduceByFactor_prime2,
            &Parser::reduceByFactor_prime3,
            &Parser::reduceByFactor_prime4,
            &Parser::reduceByUnary1,
            &Parser::reduceByUnary2,
            &Parser::reduceByPrimary1,
            &Parser::reduceByPrimary2,
            &Parser::reduceByNumber1,
            &Parser::reduceByNumber2
    };

}

#undef REDUCE//(P, index)