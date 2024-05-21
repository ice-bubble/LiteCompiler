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
        Action() : type(symbol::Type::Error), state(0) {}
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

        token::Token peekNext();

        bool callReduceFunctionByIndex(size_t index);

        /////以下是reduce函数


        void reduceByS();

        void reduceByProgram();

        void reduceByDeclarations1();

        void reduceByDeclarations2();

        void reduceByDeclaration1();

        void reduceByDeclaration2();

        void reduceByDeclaration3();

        void reduceByStatement1();

        void reduceByStatement2();

        void reduceByStatement3();

        void reduceByStatement4();

        void reduceByStatement5();

        void reduceByStatement6();

        void reduceByStatement7();

        void reduceByStatement8();

        void reduceByBreakStmt();

        void reduceByContinueStmt();

        void reduceByReturnStmt();

        void reduceByFunDecl();

        void reduceByVarDecl();

        void reduceByVarDef();

        void reduceByVarDefs1();

        void reduceByVarDefs2();

        void reduceByVarInit1();

        void reduceByVarInit2();

        void reduceByType1();

        void reduceByType2();

        void reduceByType3();

        void reduceByType4();

        void reduceByType5();

        void reduceByType6();

        void reduceByExprStmt1();

        void reduceByExprStmt2();

        void reduceByIfStmt();

        void reduceByElseBranch1();

        void reduceByElseBranch2();

        void reduceByWhileStmt();

        void reduceByBlock();

        void reduceByRepeatStmt();

        void reduceByParamList1();

        void reduceByParamList2();

        void reduceByParameters1();

        void reduceByParameters2();

        void reduceByParameter();

        void reduceByExpression();

        void reduceByAssignment1();

        void reduceByAssignment2();

        void reduceByLogic_or();

        void reduceByLogic_or_prime1();

        void reduceByLogic_or_prime2();

        void reduceByLogic_and();

        void reduceByLogic_and_prime1();

        void reduceByLogic_and_prime2();

        void reduceByEquality();

        void reduceByEquality_prime1();

        void reduceByEquality_prime2();

        void reduceByEquality_prime3();

        void reduceByComparison();

        void reduceByComparison_prime1();

        void reduceByComparison_prime2();

        void reduceByComparison_prime3();

        void reduceByComparison_prime4();

        void reduceByComparison_prime5();

        void reduceByTerm();

        void reduceByTerm_prime1();

        void reduceByTerm_prime2();

        void reduceByTerm_prime3();

        void reduceByFactor();

        void reduceByFactor_prime1();

        void reduceByFactor_prime2();

        void reduceByFactor_prime3();

        void reduceByFactor_prime4();

        void reduceByIncr_exp();

        void reduceByIncr_op1();

        void reduceByIncr_op2();

        void reduceByIncr_op3();

        void reduceByUnary1();

        void reduceByUnary2();

        void reduceByUnary3();

        void reduceByCall();

        void reduceByCall_suffix1();

        void reduceByCall_suffix2();

        void reduceByArgList1();

        void reduceByArgList2();

        void reduceByArguments1();

        void reduceByArguments2();

        void reduceByPrimary1();

        void reduceByPrimary2();

        void reduceByPrimary3();

        void reduceByConstVal1();

        void reduceByConstVal2();

        void reduceByConstVal3();

        void reduceByConstVal4();

        void reduceByConstVal5();

        void reduceByConstVal6();

        void reduceByVar();

        void reduceByVarSuffix1();

        void reduceByVarSuffix2();



    };


}


#endif //ROBIN_PARSER_H
