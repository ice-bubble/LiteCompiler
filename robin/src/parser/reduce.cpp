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


    void Parser::reduceByS() {
        REDUCE(Program, 0)
        SharedPtr<production::Production> SInstance =
                std::make_shared<production::S>(ProgramInstance_0->line, ProgramInstance_0);
        productions.push_back(SInstance);
    }

    void Parser::reduceByProgram() {
        REDUCE(Declarations, 0)
        SharedPtr<production::Production> ProgramInstance =
                std::make_shared<production::Program>(DeclarationsInstance_0->line, DeclarationsInstance_0);
        productions.push_back(ProgramInstance);
    }

    void Parser::reduceByDeclarations1() {
        REDUCE(Declarations, 0)
        REDUCE(Declaration, 0)
        SharedPtr<production::Production> Declarations1Instance
                = std::make_shared<production::Declarations1>
                        (DeclarationInstance_0->line, DeclarationInstance_0, DeclarationsInstance_0);
        productions.push_back(Declarations1Instance);
    }

    void Parser::reduceByDeclarations2() {
        SharedPtr<production::Production> Declarations2Instance = std::make_shared<production::Declarations2>(0);
        productions.push_back(Declarations2Instance);
    }

    void Parser::reduceByDeclaration1() {
        REDUCE(FunDecl, 0)
        SharedPtr<production::Production> Declaration1Instance
                = std::make_shared<production::Declaration1>(FunDeclInstance_0->line, FunDeclInstance_0);
        productions.push_back(Declaration1Instance);
    }

    void Parser::reduceByDeclaration2() {
        REDUCE(VarDecl, 0)
        SharedPtr<production::Production> Declaration2Instance
                = std::make_shared<production::Declaration2>(VarDeclInstance_0->line, VarDeclInstance_0);
        productions.push_back(Declaration2Instance);
    }

    void Parser::reduceByDeclaration3() {
        REDUCE(Statement, 0)
        SharedPtr<production::Production> Declaration3Instance
                = std::make_shared<production::Declaration3>(StatementInstance_0->line, StatementInstance_0);
        productions.push_back(Declaration3Instance);
    }

    void Parser::reduceByStatement1() {
        REDUCE(BreakStmt, 0)
        SharedPtr<production::Production> Statement1Instance
                = std::make_shared<production::Statement1>(BreakStmtInstance_0->line, BreakStmtInstance_0);
        productions.push_back(Statement1Instance);
    }

    void Parser::reduceByStatement2() {
        REDUCE(ContinueStmt, 0)
        SharedPtr<production::Production> Statement2Instance
                = std::make_shared<production::Statement2>(ContinueStmtInstance_0->line, ContinueStmtInstance_0);
        productions.push_back(Statement2Instance);
    }

    void Parser::reduceByStatement3() {
        REDUCE(ReturnStmt, 0)
        SharedPtr<production::Production> Statement3Instance
                = std::make_shared<production::Statement3>(ReturnStmtInstance_0->line, ReturnStmtInstance_0);
        productions.push_back(Statement3Instance);
    }

    void Parser::reduceByStatement4() {
        REDUCE(ExprStmt, 0)
        SharedPtr<production::Production> Statement4Instance
                = std::make_shared<production::Statement4>(ExprStmtInstance_0->line, ExprStmtInstance_0);
        productions.push_back(Statement4Instance);
    }

    void Parser::reduceByStatement5() {
        REDUCE(IfStmt, 0)
        SharedPtr<production::Production> Statement5Instance
                = std::make_shared<production::Statement5>(IfStmtInstance_0->line, IfStmtInstance_0);
        productions.push_back(Statement5Instance);
    }

    void Parser::reduceByStatement6() {
        REDUCE(WhileStmt, 0)
        SharedPtr<production::Production> Statement6Instance
                = std::make_shared<production::Statement6>(WhileStmtInstance_0->line, WhileStmtInstance_0);
        productions.push_back(Statement6Instance);
    }

    void Parser::reduceByStatement7() {
        REDUCE(RepeatStmt, 0)
        SharedPtr<production::Production> Statement7Instance
                = std::make_shared<production::Statement7>(RepeatStmtInstance_0->line, RepeatStmtInstance_0);
        productions.push_back(Statement7Instance);
    }

    void Parser::reduceByStatement8() {
        REDUCE(Block, 0)
        SharedPtr<production::Production> Statement8Instance
                = std::make_shared<production::Statement8>(BlockInstance_0->line, BlockInstance_0);
        productions.push_back(Statement8Instance);
    }

    void Parser::reduceByStatement9() {
        REDUCE(ForStmt, 0)
        SharedPtr<production::Production> Statement9Instance
                = std::make_shared<production::Statement9>(ForStmtInstance_0->line, ForStmtInstance_0);
        productions.push_back(Statement9Instance);
    }

    void Parser::reduceByBreakStmt() {
        REDUCE(Token, 1)  ///< ";"
        REDUCE(Token, 0)  ///< "break"
        SharedPtr<production::Production> BreakStmtInstance = std::make_shared<production::BreakStmt>
                (TokenInstance_0->line, TokenInstance_0, TokenInstance_1);
        productions.push_back(BreakStmtInstance);
    }

    void Parser::reduceByContinueStmt() {
        REDUCE(Token, 1)  ///< ";"
        REDUCE(Token, 0)  ///< "continue"
        SharedPtr<production::Production> ContinueStmtInstance = std::make_shared<production::ContinueStmt>
                (TokenInstance_0->line, TokenInstance_0, TokenInstance_1);
        productions.push_back(ContinueStmtInstance);
    }

    void Parser::reduceByReturnStmt() {
        REDUCE(ExprStmt, 0)
        REDUCE(Token, 0)
        SharedPtr<production::Production> ReturnStmtInstance = std::make_shared<production::ReturnStmt>
                (TokenInstance_0->line, TokenInstance_0, ExprStmtInstance_0);
        productions.push_back(ReturnStmtInstance);
    }

    void Parser::reduceByFunDecl() {
        REDUCE(Block, 0)             ///< block
        REDUCE(Token, 4)             ///< ")"
        REDUCE(ParamList, 0)         ///< paramList
        REDUCE(Token, 3)             ///< "("
        REDUCE(Token, 2)             ///< "function"
        REDUCE(Token, 1)             ///< "="
        REDUCE(Token, 0)             ///< identifier
        SharedPtr<production::Production> FunDeclInstance = std::make_shared<production::FunDecl>
                (TokenInstance_0->line, TokenInstance_0, TokenInstance_1,
                 TokenInstance_2, TokenInstance_3, ParamListInstance_0,
                 TokenInstance_4, BlockInstance_0);
        productions.push_back(FunDeclInstance);
    }

    void Parser::reduceByVarDecl() {
        REDUCE(Token, 0)
        REDUCE(VarDefs, 0)
        REDUCE(VarDef, 0)
        REDUCE(Type, 0)
        SharedPtr<production::Production> VarDeclInstance = std::make_shared<production::VarDecl>
                (TypeInstance_0->line, TypeInstance_0, VarDefInstance_0, VarDefsInstance_0,
                 TokenInstance_0);
        productions.push_back(VarDeclInstance);
    }

    void Parser::reduceByVarDef() {
        REDUCE(VarInit, 0)
        REDUCE(Var, 0)
        SharedPtr<production::Production> VarDefInstance = std::make_shared<production::VarDef>
                (VarInstance_0->line, VarInstance_0, VarInitInstance_0);
        productions.push_back(VarDefInstance);
    }

    void Parser::reduceByVarDefs1() {
        REDUCE(VarDefs, 0)
        REDUCE(VarDef, 0)
        REDUCE(Token, 0)
        SharedPtr<production::Production> VarDefs1Instance = std::make_shared<production::VarDefs1>
                (TokenInstance_0->line, TokenInstance_0, VarDefInstance_0, VarDefsInstance_0);
        productions.push_back(VarDefs1Instance);
    }

    void Parser::reduceByVarDefs2() {
        SharedPtr<production::Production> VarDefs2Instance = std::make_shared<production::VarDefs2>(0);
        productions.push_back(VarDefs2Instance);
    }

    void Parser::reduceByVarInit1() {
        REDUCE(Expression, 0)
        REDUCE(Token, 0)
        SharedPtr<production::Production> VarInit1Instance = std::make_shared<production::VarInit1>
                (TokenInstance_0->line, TokenInstance_0, ExpressionInstance_0);
        productions.push_back(VarInit1Instance);
    }

    void Parser::reduceByVarInit2() {
        SharedPtr<production::Production> VarInit2Instance = std::make_shared<production::VarInit2>(0);
        productions.push_back(VarInit2Instance);
    }

    void Parser::reduceByType1() {
        REDUCE(Token, 0)
        SharedPtr<production::Production> Type1Instance = std::make_shared<production::Type1>
                (TokenInstance_0->line, TokenInstance_0);
        productions.push_back(Type1Instance);
    }

    void Parser::reduceByType2() {
        REDUCE(Token, 0)
        SharedPtr<production::Production> Type2Instance = std::make_shared<production::Type2>
                (TokenInstance_0->line, TokenInstance_0);
        productions.push_back(Type2Instance);
    }

    void Parser::reduceByType3() {
        REDUCE(Token, 0)
        SharedPtr<production::Production> Type3Instance = std::make_shared<production::Type3>
                (TokenInstance_0->line, TokenInstance_0);
        productions.push_back(Type3Instance);
    }

    void Parser::reduceByType4() {
        REDUCE(Token, 0)
        SharedPtr<production::Production> Type4Instance = std::make_shared<production::Type4>
                (TokenInstance_0->line, TokenInstance_0);
        productions.push_back(Type4Instance);
    }

    void Parser::reduceByType5() {
        REDUCE(Token, 0)
        SharedPtr<production::Production> Type5Instance = std::make_shared<production::Type5>
                (TokenInstance_0->line, TokenInstance_0);
        productions.push_back(Type5Instance);
    }

    void Parser::reduceByType6() {
        REDUCE(Token, 0)
        SharedPtr<production::Production> Type6Instance = std::make_shared<production::Type6>
                (TokenInstance_0->line, TokenInstance_0);
        productions.push_back(Type6Instance);
    }

    void Parser::reduceByExprStmt1() {
        REDUCE(Token, 0)
        REDUCE(Expression, 0)
        SharedPtr<production::Production> ExprStmt1Instance = std::make_shared<production::ExprStmt1>
                (ExpressionInstance_0->line, ExpressionInstance_0, TokenInstance_0);
        productions.push_back(ExprStmt1Instance);
    }

    void Parser::reduceByExprStmt2() {
        REDUCE(Token, 0)
        SharedPtr<production::Production> ExprStmt2Instance = std::make_shared<production::ExprStmt2>
                (TokenInstance_0->line, TokenInstance_0);
        productions.push_back(ExprStmt2Instance);
    }

    void Parser::reduceByIfStmt() {
        REDUCE(ElseBranch, 0)     ///< elseBranch
        REDUCE(Statement, 0)      ///< statement
        REDUCE(Token, 2)          ///< ")"
        REDUCE(Expression, 0)     ///< expression
        REDUCE(Token, 1)          ///< "("
        REDUCE(Token, 0)          ///< "if"
        SharedPtr<production::Production> IfStmtInstance = std::make_shared<production::IfStmt>
                (TokenInstance_0->line, TokenInstance_0, TokenInstance_1,
                 ExpressionInstance_0, TokenInstance_2, StatementInstance_0,
                 ElseBranchInstance_0);
        productions.push_back(IfStmtInstance);
    }

    void Parser::reduceByElseBranch1() {
        REDUCE(Statement, 0)
        REDUCE(Token, 0)
        SharedPtr<production::Production> ElseBranch1Instance = std::make_shared<production::ElseBranch1>
                (TokenInstance_0->line, TokenInstance_0, StatementInstance_0);
        productions.push_back(ElseBranch1Instance);
    }

    void Parser::reduceByElseBranch2() {
        SharedPtr<production::Production> ElseBranch2Instance = std::make_shared<production::ElseBranch2>(0);
        productions.push_back(ElseBranch2Instance);
    }

    void Parser::reduceByWhileStmt() {
        REDUCE(Statement, 0)     ///< statement
        REDUCE(Token, 2)         ///< ")"
        REDUCE(Expression, 0)    ///< expression
        REDUCE(Token, 1)         ///< "("
        REDUCE(Token, 0)         ///< "if"
        SharedPtr<production::Production> WhileStmtInstance = std::make_shared<production::WhileStmt>
                (TokenInstance_0->line, TokenInstance_0, TokenInstance_1,
                 ExpressionInstance_0, TokenInstance_2, StatementInstance_0);
        productions.push_back(WhileStmtInstance);
    }

    void Parser::reduceByForStmt1() {
        REDUCE(Statement, 0)  ///< statement
        REDUCE(Token, 2)      ///< ")"
        REDUCE(ExprStmt, 0)   ///< exprStmt
        REDUCE(VarDecl, 0)    ///< varDecl
        REDUCE(Token, 1)      ///< "("
        REDUCE(Token, 0)      ///< "for"
        SharedPtr<production::Production> ForStmt1Instance = std::make_shared<production::ForStmt1>
                (TokenInstance_0->line, TokenInstance_0, TokenInstance_1,
                 VarDeclInstance_0, ExprStmtInstance_0, TokenInstance_2,
                 StatementInstance_0);
        productions.push_back(ForStmt1Instance);
    }

    void Parser::reduceByForStmt2() {
        REDUCE(Statement, 0)  ///< statement
        REDUCE(Token, 2)      ///< ")"
        REDUCE(Expression, 0) ///< expression
        REDUCE(ExprStmt, 0)   ///< exprStmt
        REDUCE(VarDecl, 0)    ///< varDecl
        REDUCE(Token, 1)      ///< "("
        REDUCE(Token, 0)      ///< "for"
        SharedPtr<production::Production> ForStmt2Instance = std::make_shared<production::ForStmt2>
                (TokenInstance_0->line, TokenInstance_0, TokenInstance_1,
                 VarDeclInstance_0, ExprStmtInstance_0, ExpressionInstance_0,
                 TokenInstance_2, StatementInstance_0);
        productions.push_back(ForStmt2Instance);
    }

    void Parser::reduceByForStmt3() {
        REDUCE(Statement, 0)  ///< statement
        REDUCE(Token, 2)      ///< ")"
        REDUCE(ExprStmt, 1)   ///< exprStmt
        REDUCE(ExprStmt, 0)   ///< exprStmt
        REDUCE(Token, 1)      ///< "("
        REDUCE(Token, 0)      ///< "for"
        SharedPtr<production::Production> ForStmt3Instance = std::make_shared<production::ForStmt3>
                (TokenInstance_0->line, TokenInstance_0, TokenInstance_1,
                 ExprStmtInstance_0, ExprStmtInstance_1, TokenInstance_2,
                 StatementInstance_0);
        productions.push_back(ForStmt3Instance);
    }

    void Parser::reduceByForStmt4() {
        REDUCE(Statement, 0)  ///< statement
        REDUCE(Token, 2)      ///< ")"
        REDUCE(Expression, 0) ///< expression
        REDUCE(ExprStmt, 1)   ///< exprStmt
        REDUCE(ExprStmt, 0)   ///< exprStmt
        REDUCE(Token, 1)      ///< "("
        REDUCE(Token, 0)      ///< "for"
        SharedPtr<production::Production> ForStmt4Instance = std::make_shared<production::ForStmt4>
                (TokenInstance_0->line, TokenInstance_0, TokenInstance_1,
                 ExprStmtInstance_0, ExprStmtInstance_1, ExpressionInstance_0,
                 TokenInstance_2, StatementInstance_0);
        productions.push_back(ForStmt4Instance);
    }

    void Parser::reduceByBlock() {
        REDUCE(Token, 1)
        REDUCE(Declarations, 0)
        REDUCE(Token, 0)
        SharedPtr<production::Production> BlockInstance = std::make_shared<production::Block>
                (TokenInstance_0->line, TokenInstance_0, DeclarationsInstance_0,
                 TokenInstance_1);
        productions.push_back(BlockInstance);
    }

    void Parser::reduceByRepeatStmt() {
        REDUCE(Token, 4)              ///< ";"
        REDUCE(Token, 3)              ///< ")"
        REDUCE(Expression, 0)         ///< expression
        REDUCE(Token, 2)              ///< "("
        REDUCE(Token, 1)              ///< "until"
        REDUCE(Statement, 0)          ///< statement
        REDUCE(Token, 0)              ///< "repeat"
        SharedPtr<production::Production> RepeatStmtInstance = std::make_shared<production::RepeatStmt>
                (TokenInstance_0->line, TokenInstance_0, StatementInstance_0,
                 TokenInstance_1, TokenInstance_2, ExpressionInstance_0,
                 TokenInstance_3, TokenInstance_4);
        productions.push_back(RepeatStmtInstance);
    }

    void Parser::reduceByParamList1() {
        REDUCE(Parameters, 0)
        REDUCE(Parameter, 0)
        SharedPtr<production::Production> ParamList1Instance = std::make_shared<production::ParamList1>
                (ParameterInstance_0->line, ParameterInstance_0, ParametersInstance_0);
        productions.push_back(ParamList1Instance);
    }

    void Parser::reduceByParamList2() {
        SharedPtr<production::Production> ParamList2Instance = std::make_shared<production::ParamList2>(0);
        productions.push_back(ParamList2Instance);
    }

    void Parser::reduceByParameters1() {
        REDUCE(Parameters, 0)
        REDUCE(Parameter, 0)
        REDUCE(Token, 0)
        SharedPtr<production::Production> Parameters1Instance = std::make_shared<production::Parameters1>
                (TokenInstance_0->line, TokenInstance_0, ParameterInstance_0,
                 ParametersInstance_0);
        productions.push_back(Parameters1Instance);
    }

    void Parser::reduceByParameters2() {
        SharedPtr<production::Production> Parameters2Instance = std::make_shared<production::Parameters2>(0);
        productions.push_back(Parameters2Instance);
    }

    void Parser::reduceByParameter() {
        REDUCE(Var, 0)
        REDUCE(Type, 0)
        SharedPtr<production::Production> ParameterInstance = std::make_shared<production::Parameter>
                (TypeInstance_0->line, TypeInstance_0, VarInstance_0);
        productions.push_back(ParameterInstance);
    }

    void Parser::reduceByExpression() {
        REDUCE(Assignment, 0)
        SharedPtr<production::Production> ExpressionInstance = std::make_shared<production::Expression>
                (AssignmentInstance_0->line, AssignmentInstance_0);
        productions.push_back(ExpressionInstance);
    }

    void Parser::reduceByAssignment1() {
        REDUCE(Assignment, 0)
        REDUCE(Token, 0)
        REDUCE(Var, 0)
        SharedPtr<production::Production> Assignment1Instance = std::make_shared<production::Assignment1>
                (VarInstance_0->line, VarInstance_0, TokenInstance_0, AssignmentInstance_0);
        productions.push_back(Assignment1Instance);
    }

    void Parser::reduceByAssignment2() {
        REDUCE(Logic_or, 0)
        SharedPtr<production::Production> Assignment2Instance = std::make_shared<production::Assignment2>
                (Logic_orInstance_0->line, Logic_orInstance_0);
        productions.push_back(Assignment2Instance);
    }

    void Parser::reduceByLogic_or() {
        REDUCE(Logic_or_prime, 0)
        REDUCE(Logic_and, 0)
        SharedPtr<production::Production> Logic_orInstance = std::make_shared<production::Logic_or>
                (Logic_andInstance_0->line, Logic_andInstance_0, Logic_or_primeInstance_0);
        productions.push_back(Logic_orInstance);
    }

    void Parser::reduceByLogic_or_prime1() {
        REDUCE(Logic_or, 0)
        REDUCE(Token, 0)
        SharedPtr<production::Production> Logic_or_prime1Instance = std::make_shared<production::Logic_or_prime1>
                (TokenInstance_0->line, TokenInstance_0, Logic_orInstance_0);
        productions.push_back(Logic_or_prime1Instance);
    }

    void Parser::reduceByLogic_or_prime2() {
        SharedPtr<production::Production> Logic_or_prime2Instance = std::make_shared<production::Logic_or_prime2>(0);
        productions.push_back(Logic_or_prime2Instance);
    }

    void Parser::reduceByLogic_and() {
        REDUCE(Logic_and_prime, 0)
        REDUCE(Equality, 0)
        SharedPtr<production::Production> Logic_andInstance = std::make_shared<production::Logic_and>
                (EqualityInstance_0->line, EqualityInstance_0, Logic_and_primeInstance_0);
        productions.push_back(Logic_andInstance);
    }

    void Parser::reduceByLogic_and_prime1() {
        REDUCE(Logic_and, 0)
        REDUCE(Token, 0)
        SharedPtr<production::Production> Logic_and_prime1Instance = std::make_shared<production::Logic_and_prime1>
                (TokenInstance_0->line, TokenInstance_0, Logic_andInstance_0);
        productions.push_back(Logic_and_prime1Instance);
    }

    void Parser::reduceByLogic_and_prime2() {
        SharedPtr<production::Production> Logic_and_prime2Instance = std::make_shared<production::Logic_and_prime2>(0);
        productions.push_back(Logic_and_prime2Instance);
    }

    void Parser::reduceByEquality() {
        REDUCE(Equality_prime, 0)
        REDUCE(Comparison, 0)
        SharedPtr<production::Production> EqualityInstance = std::make_shared<production::Equality>
                (ComparisonInstance_0->line, ComparisonInstance_0, Equality_primeInstance_0);
        productions.push_back(EqualityInstance);
    }

    void Parser::reduceByEquality_prime1() {
        REDUCE(Equality, 0)
        REDUCE(Token, 0)
        SharedPtr<production::Production> Equality_prime1Instance = std::make_shared<production::Equality_prime1>
                (TokenInstance_0->line, TokenInstance_0, EqualityInstance_0);
        productions.push_back(Equality_prime1Instance);
    }

    void Parser::reduceByEquality_prime2() {
        REDUCE(Equality, 0)
        REDUCE(Token, 0)
        SharedPtr<production::Production> Equality_prime2Instance = std::make_shared<production::Equality_prime2>
                (TokenInstance_0->line, TokenInstance_0, EqualityInstance_0);
        productions.push_back(Equality_prime2Instance);
    }

    void Parser::reduceByEquality_prime3() {
        SharedPtr<production::Production> Equality_prime3Instance = std::make_shared<production::Equality_prime3>(0);
        productions.push_back(Equality_prime3Instance);
    }

    void Parser::reduceByComparison() {
        REDUCE(Comparison_prime, 0)
        REDUCE(Term, 0)
        SharedPtr<production::Production> ComparisonInstance = std::make_shared<production::Comparison>
                (TermInstance_0->line, TermInstance_0, Comparison_primeInstance_0);
        productions.push_back(ComparisonInstance);
    }

    void Parser::reduceByComparison_prime1() {
        REDUCE(Comparison, 0)
        REDUCE(Token, 0)
        SharedPtr<production::Production> Comparison_prime1Instance = std::make_shared<production::Comparison_prime1>
                (TokenInstance_0->line, TokenInstance_0, ComparisonInstance_0);
        productions.push_back(Comparison_prime1Instance);
    }

    void Parser::reduceByComparison_prime2() {
        REDUCE(Comparison, 0)
        REDUCE(Token, 0)
        SharedPtr<production::Production> Comparison_prime2Instance = std::make_shared<production::Comparison_prime2>
                (TokenInstance_0->line, TokenInstance_0, ComparisonInstance_0);
        productions.push_back(Comparison_prime2Instance);
    }

    void Parser::reduceByComparison_prime3() {
        REDUCE(Comparison, 0)
        REDUCE(Token, 0)
        SharedPtr<production::Production> Comparison_prime3Instance = std::make_shared<production::Comparison_prime3>
                (TokenInstance_0->line, TokenInstance_0, ComparisonInstance_0);
        productions.push_back(Comparison_prime3Instance);
    }

    void Parser::reduceByComparison_prime4() {
        REDUCE(Comparison, 0)
        REDUCE(Token, 0)
        SharedPtr<production::Production> Comparison_prime4Instance = std::make_shared<production::Comparison_prime4>
                (TokenInstance_0->line, TokenInstance_0, ComparisonInstance_0);
        productions.push_back(Comparison_prime4Instance);
    }

    void Parser::reduceByComparison_prime5() {
        SharedPtr<production::Production> Comparison_prime5Instance = std::make_shared<production::Comparison_prime5>(
                0);
        productions.push_back(Comparison_prime5Instance);
    }

    void Parser::reduceByTerm() {
        REDUCE(Term_prime, 0)
        REDUCE(Factor, 0)
        SharedPtr<production::Production> TermInstance = std::make_shared<production::Term>
                (FactorInstance_0->line, FactorInstance_0, Term_primeInstance_0);
        productions.push_back(TermInstance);
    }

    void Parser::reduceByTerm_prime1() {
        REDUCE(Term, 0)
        REDUCE(Token, 0)
        SharedPtr<production::Production> Term_prime1Instance = std::make_shared<production::Term_prime1>
                (TokenInstance_0->line, TokenInstance_0, TermInstance_0);
        productions.push_back(Term_prime1Instance);
    }

    void Parser::reduceByTerm_prime2() {
        REDUCE(Term, 0)
        REDUCE(Token, 0)
        SharedPtr<production::Production> Term_prime2Instance = std::make_shared<production::Term_prime2>
                (TokenInstance_0->line, TokenInstance_0,TermInstance_0);
        productions.push_back(Term_prime2Instance);
    }

    void Parser::reduceByTerm_prime3() {
        SharedPtr<production::Production> Term_prime3Instance = std::make_shared<production::Term_prime3>(0);
        productions.push_back(Term_prime3Instance);
    }

    void Parser::reduceByFactor() {
        REDUCE(Factor_prime, 0)
        REDUCE(Incr_exp, 0)
        SharedPtr<production::Production> FactorInstance = std::make_shared<production::Factor>
                (Incr_expInstance_0->line, Incr_expInstance_0, Factor_primeInstance_0);
        productions.push_back(FactorInstance);
    }

    void Parser::reduceByFactor_prime1() {
        REDUCE(Factor, 0)
        REDUCE(Token, 0)
        SharedPtr<production::Production> Factor_prime1Instance = std::make_shared<production::Factor_prime1>
                (TokenInstance_0->line, TokenInstance_0,FactorInstance_0);
        productions.push_back(Factor_prime1Instance);
    }

    void Parser::reduceByFactor_prime2() {
        REDUCE(Factor, 0)
        REDUCE(Token, 0)
        SharedPtr<production::Production> Factor_prime2Instance = std::make_shared<production::Factor_prime2>
                (TokenInstance_0->line, TokenInstance_0,FactorInstance_0);
        productions.push_back(Factor_prime2Instance);
    }

    void Parser::reduceByFactor_prime3() {
        REDUCE(Factor, 0)
        REDUCE(Token, 0)
        SharedPtr<production::Production> Factor_prime3Instance = std::make_shared<production::Factor_prime3>
                (TokenInstance_0->line, TokenInstance_0,FactorInstance_0);
        productions.push_back(Factor_prime3Instance);
    }

    void Parser::reduceByFactor_prime4() {
        SharedPtr<production::Production> Factor_prime4Instance = std::make_shared<production::Factor_prime4>(0);
        productions.push_back(Factor_prime4Instance);
    }

    void Parser::reduceByIncr_exp() {
        REDUCE(Incr_op, 0)
        REDUCE(Unary, 0)
        SharedPtr<production::Production> Incr_expInstance = std::make_shared<production::Incr_exp>
                (UnaryInstance_0->line, UnaryInstance_0, Incr_opInstance_0);
        productions.push_back(Incr_expInstance);
    }

    void Parser::reduceByIncr_op1() {
        REDUCE(Incr_op, 0)
        REDUCE(Token, 0)
        SharedPtr<production::Production> Incr_op1Instance = std::make_shared<production::Incr_op1>
                (TokenInstance_0->line, TokenInstance_0, Incr_opInstance_0);
        productions.push_back(Incr_op1Instance);
    }

    void Parser::reduceByIncr_op2() {
        REDUCE(Incr_op, 0)
        REDUCE(Token, 0)
        SharedPtr<production::Production> Incr_op2Instance = std::make_shared<production::Incr_op2>
                (TokenInstance_0->line, TokenInstance_0, Incr_opInstance_0);
        productions.push_back(Incr_op2Instance);
    }

    void Parser::reduceByIncr_op3() {
        SharedPtr<production::Production> Incr_op3Instance = std::make_shared<production::Incr_op3>(0);
        productions.push_back(Incr_op3Instance);
    }

    void Parser::reduceByUnary1() {
        REDUCE(Unary, 0)
        REDUCE(Token, 0)
        SharedPtr<production::Production> Unary1Instance = std::make_shared<production::Unary1>
                (TokenInstance_0->line, TokenInstance_0, UnaryInstance_0);
        productions.push_back(Unary1Instance);
    }

    void Parser::reduceByUnary2() {
        REDUCE(Unary, 0)
        REDUCE(Token, 0)
        SharedPtr<production::Production> Unary2Instance = std::make_shared<production::Unary2>
                (TokenInstance_0->line, TokenInstance_0, UnaryInstance_0);
        productions.push_back(Unary2Instance);
    }

    void Parser::reduceByUnary3() {
        REDUCE(Call, 0)
        SharedPtr<production::Production> Unary3Instance = std::make_shared<production::Unary3>
                (CallInstance_0->line, CallInstance_0);
        productions.push_back(Unary3Instance);
    }

    void Parser::reduceByCall() {
        REDUCE(Call_suffix, 0)
        REDUCE(Primary, 0)
        SharedPtr<production::Production> CallInstance = std::make_shared<production::Call>
                (PrimaryInstance_0->line, PrimaryInstance_0, Call_suffixInstance_0);
        productions.push_back(CallInstance);
    }

    void Parser::reduceByCall_suffix1() {
        REDUCE(Call_suffix, 0)
        REDUCE(Token, 1)
        REDUCE(ArgList, 0)
        REDUCE(Token, 0)
        SharedPtr<production::Production> Call_suffix1Instance = std::make_shared<production::Call_suffix1>
                (TokenInstance_0->line, TokenInstance_0, ArgListInstance_0,
                 TokenInstance_1, Call_suffixInstance_0);
        productions.push_back(Call_suffix1Instance);
    }

    void Parser::reduceByCall_suffix2() {
        SharedPtr<production::Production> Call_suffix2Instance = std::make_shared<production::Call_suffix2>(0);
        productions.push_back(Call_suffix2Instance);
    }

    void Parser::reduceByArgList1() {
        REDUCE(Arguments, 0)
        REDUCE(Expression, 0)
        SharedPtr<production::Production> ArgList1Instance = std::make_shared<production::ArgList1>
                (ExpressionInstance_0->line, ExpressionInstance_0, ArgumentsInstance_0);
        productions.push_back(ArgList1Instance);
    }

    void Parser::reduceByArgList2() {
        SharedPtr<production::Production> ArgList2Instance = std::make_shared<production::ArgList2>(0);
        productions.push_back(ArgList2Instance);
    }

    void Parser::reduceByArguments1() {
        REDUCE(Arguments, 0)
        REDUCE(Expression, 0)
        REDUCE(Token, 0)
        SharedPtr<production::Production> Arguments1Instance = std::make_shared<production::Arguments1>
                (TokenInstance_0->line, TokenInstance_0, ExpressionInstance_0,
                 ArgumentsInstance_0);
        productions.push_back(Arguments1Instance);
    }

    void Parser::reduceByArguments2() {
        SharedPtr<production::Production> Arguments2Instance = std::make_shared<production::Arguments2>(0);
        productions.push_back(Arguments2Instance);
    }

    void Parser::reduceByPrimary1() {
        REDUCE(ConstVal, 0)
        SharedPtr<production::Production> Primary1Instance = std::make_shared<production::Primary1>
                (ConstValInstance_0->line, ConstValInstance_0);
        productions.push_back(Primary1Instance);
    }

    void Parser::reduceByPrimary2() {
        REDUCE(Token, 1)
        REDUCE(Expression, 0)
        REDUCE(Token, 0)
        SharedPtr<production::Production> Primary2Instance = std::make_shared<production::Primary2>
                (TokenInstance_0->line, TokenInstance_0, ExpressionInstance_0,
                 TokenInstance_1);
        productions.push_back(Primary2Instance);
    }

    void Parser::reduceByPrimary3() {
        REDUCE(Var, 0)
        SharedPtr<production::Production> Primary3Instance = std::make_shared<production::Primary3>
                (VarInstance_0->line, VarInstance_0);
        productions.push_back(Primary3Instance);
    }

    void Parser::reduceByConstVal1() {
        REDUCE(Token, 0)
        SharedPtr<production::Production> ConstVal1Instance = std::make_shared<production::ConstVal1>
                (TokenInstance_0->line, TokenInstance_0);
        productions.push_back(ConstVal1Instance);
    }

    void Parser::reduceByConstVal2() {
        REDUCE(Token, 0)
        SharedPtr<production::Production> ConstVal2Instance = std::make_shared<production::ConstVal2>
                (TokenInstance_0->line, TokenInstance_0);
        productions.push_back(ConstVal2Instance);
    }

    void Parser::reduceByConstVal3() {
        REDUCE(Token, 0)
        SharedPtr<production::Production> ConstVal3Instance = std::make_shared<production::ConstVal3>
                (TokenInstance_0->line, TokenInstance_0);
        productions.push_back(ConstVal3Instance);
    }

    void Parser::reduceByConstVal4() {
        REDUCE(Token, 0)
        SharedPtr<production::Production> ConstVal4Instance = std::make_shared<production::ConstVal4>
                (TokenInstance_0->line, TokenInstance_0);
        productions.push_back(ConstVal4Instance);
    }

    void Parser::reduceByConstVal5() {
        REDUCE(Token, 0)
        SharedPtr<production::Production> ConstVal5Instance = std::make_shared<production::ConstVal5>
                (TokenInstance_0->line, TokenInstance_0);
        productions.push_back(ConstVal5Instance);
    }

    void Parser::reduceByConstVal6() {
        REDUCE(Token, 0)
        SharedPtr<production::Production> ConstVal6Instance = std::make_shared<production::ConstVal6>
                (TokenInstance_0->line, TokenInstance_0);
        productions.push_back(ConstVal6Instance);
    }

    void Parser::reduceByVar() {
        REDUCE(VarSuffix, 0)
        REDUCE(Token, 0)
        SharedPtr<production::Production> VarInstance = std::make_shared<production::Var>
                (TokenInstance_0->line, TokenInstance_0, VarSuffixInstance_0);
        productions.push_back(VarInstance);
    }

    void Parser::reduceByVarSuffix1() {
        REDUCE(VarSuffix, 0)
        REDUCE(Token, 1)
        REDUCE(Expression, 0)
        REDUCE(Token, 0)
        SharedPtr<production::Production> VarSuffix1Instance = std::make_shared<production::VarSuffix1>
                (TokenInstance_0->line, TokenInstance_0, ExpressionInstance_0,
                 TokenInstance_1, VarSuffixInstance_0);
        productions.push_back(VarSuffix1Instance);
    }

    void Parser::reduceByVarSuffix2() {
        SharedPtr<production::Production> VarSuffix2Instance = std::make_shared<production::VarSuffix2>(0);
        productions.push_back(VarSuffix2Instance);
    }


    List<Parser::VoidFuncPtr> Parser::ReduceFunctions = {
            &Parser::reduceByS,
            &Parser::reduceByProgram,
            &Parser::reduceByDeclarations1,
            &Parser::reduceByDeclarations2,
            &Parser::reduceByDeclaration1,
            &Parser::reduceByDeclaration2,
            &Parser::reduceByDeclaration3,
            &Parser::reduceByStatement1,
            &Parser::reduceByStatement2,
            &Parser::reduceByStatement3,
            &Parser::reduceByStatement4,
            &Parser::reduceByStatement5,
            &Parser::reduceByStatement6,
            &Parser::reduceByStatement7,
            &Parser::reduceByStatement8,
            &Parser::reduceByStatement9,
            &Parser::reduceByBreakStmt,
            &Parser::reduceByContinueStmt,
            &Parser::reduceByReturnStmt,
            &Parser::reduceByFunDecl,
            &Parser::reduceByVarDecl,
            &Parser::reduceByVarDef,
            &Parser::reduceByVarDefs1,
            &Parser::reduceByVarDefs2,
            &Parser::reduceByVarInit1,
            &Parser::reduceByVarInit2,
            &Parser::reduceByType1,
            &Parser::reduceByType2,
            &Parser::reduceByType3,
            &Parser::reduceByType4,
            &Parser::reduceByType5,
            &Parser::reduceByType6,
            &Parser::reduceByExprStmt1,
            &Parser::reduceByExprStmt2,
            &Parser::reduceByIfStmt,
            &Parser::reduceByElseBranch1,
            &Parser::reduceByElseBranch2,
            &Parser::reduceByWhileStmt,
            &Parser::reduceByForStmt1,
            &Parser::reduceByForStmt2,
            &Parser::reduceByForStmt3,
            &Parser::reduceByForStmt4,
            &Parser::reduceByBlock,
            &Parser::reduceByRepeatStmt,
            &Parser::reduceByParamList1,
            &Parser::reduceByParamList2,
            &Parser::reduceByParameters1,
            &Parser::reduceByParameters2,
            &Parser::reduceByParameter,
            &Parser::reduceByExpression,
            &Parser::reduceByAssignment1,
            &Parser::reduceByAssignment2,
            &Parser::reduceByLogic_or,
            &Parser::reduceByLogic_or_prime1,
            &Parser::reduceByLogic_or_prime2,
            &Parser::reduceByLogic_and,
            &Parser::reduceByLogic_and_prime1,
            &Parser::reduceByLogic_and_prime2,
            &Parser::reduceByEquality,
            &Parser::reduceByEquality_prime1,
            &Parser::reduceByEquality_prime2,
            &Parser::reduceByEquality_prime3,
            &Parser::reduceByComparison,
            &Parser::reduceByComparison_prime1,
            &Parser::reduceByComparison_prime2,
            &Parser::reduceByComparison_prime3,
            &Parser::reduceByComparison_prime4,
            &Parser::reduceByComparison_prime5,
            &Parser::reduceByTerm,
            &Parser::reduceByTerm_prime1,
            &Parser::reduceByTerm_prime2,
            &Parser::reduceByTerm_prime3,
            &Parser::reduceByFactor,
            &Parser::reduceByFactor_prime1,
            &Parser::reduceByFactor_prime2,
            &Parser::reduceByFactor_prime3,
            &Parser::reduceByFactor_prime4,
            &Parser::reduceByIncr_exp,
            &Parser::reduceByIncr_op1,
            &Parser::reduceByIncr_op2,
            &Parser::reduceByIncr_op3,
            &Parser::reduceByUnary1,
            &Parser::reduceByUnary2,
            &Parser::reduceByUnary3,
            &Parser::reduceByCall,
            &Parser::reduceByCall_suffix1,
            &Parser::reduceByCall_suffix2,
            &Parser::reduceByArgList1,
            &Parser::reduceByArgList2,
            &Parser::reduceByArguments1,
            &Parser::reduceByArguments2,
            &Parser::reduceByPrimary1,
            &Parser::reduceByPrimary2,
            &Parser::reduceByPrimary3,
            &Parser::reduceByConstVal1,
            &Parser::reduceByConstVal2,
            &Parser::reduceByConstVal3,
            &Parser::reduceByConstVal4,
            &Parser::reduceByConstVal5,
            &Parser::reduceByConstVal6,
            &Parser::reduceByVar,
            &Parser::reduceByVarSuffix1,
            &Parser::reduceByVarSuffix2
    };

}

#undef REDUCE//(P, index)