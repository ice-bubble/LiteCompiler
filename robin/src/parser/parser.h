//
// Created by icelake on 24-5-16.
//

#ifndef ROBIN_PARSER_H
#define ROBIN_PARSER_H

#include "../common.h"
#include "../ast/production.h"
#include "../ast/symbol.h"

namespace parser {


    // 定义状态和符号
    typedef int State;


    // SLR分析表：state, symbol -> action
    struct Action {
        symbol::Type type;
        State state;  ///< 对于Shift操作，表示下一个状态；对于Reduce操作，表示规约的产生式编号;对于Goto操作，表示Goto的状态
        Action(symbol::Type type, State state) : type(type), state(state) {}
    };

    class Parser {
        typedef void (Parser::*VoidFuncPtr)();

    private:
        List<token::Token> tokens;                         ///< 从源代码生成的token列表。
        List<SharedPtr<production::Production>> productions;
        Stack<State> stateStack;
        size_t currentToken = 0;
        static Map<Pair<State, symbol::Symbol>, Action> slrTable;
        static List<VoidFuncPtr> ReduceFunctions;


    public:
        bool hasError = false;

        Parser(List<token::Token> tokens);

        List<SharedPtr<production::Production>> parserAst();

    private:

        void printProductionStack();

        void printStateStack();

        void printInfo(const String &message);

        bool isAtTokenListEnd();

        token::Token advance();

        token::Token peek();

        bool callReduceFunctionByIndex(size_t index);

        /////以下是reduce函数


        void reduceByExpr();

        void reduceByExpression1();

        void reduceByExpression2();

        void reduceByTerm();

        void reduceByTerm_prime1();

        void reduceByTerm_prime2();

        void reduceByTerm_prime3();

        void reduceByFactor();

        void reduceByFactor_prime1();

        void reduceByFactor_prime2();

        void reduceByFactor_prime3();

        void reduceByFactor_prime4();

        void reduceByUnary1();

        void reduceByUnary2();

        void reduceByPrimary1();

        void reduceByPrimary2();

        void reduceByNumber1();

        void reduceByNumber2();

    };


}


#endif //ROBIN_PARSER_H
