

#ifndef ROBIN_PRODUCTION_H
#define ROBIN_PRODUCTION_H

#include <utility>

#include "../common.h"
#include "../token/token.h"
#include "../ast/symbol.h"

namespace production {
    class S;

    class Program;

    class Declarations;

    class Declaration;

    class Statement;

    class BreakStmt;

    class ContinueStmt;

    class ReturnStmt;

    class FunDecl;

    class VarDecl;

    class VarDef;

    class VarDefs;

    class VarInit;

    class Type;

    class IfStmt;

    class ElseBranch;

    class ExprStmt;

    class WhileStmt;

    class ForStmt;

    class Block;

    class RepeatStmt;

    class ParamList;

    class Parameters;

    class Parameter;

    class Expression;

    class Assignment;

    class Logic_or;

    class Logic_or_prime;

    class Logic_and;

    class Logic_and_prime;

    class Equality;

    class Equality_prime;

    class Comparison;

    class Comparison_prime;

    class Term;

    class Term_prime;

    class Factor;

    class Factor_prime;

    class Incr_exp;

    class Incr_op;

    class Unary;

    class Call;

    class Call_suffix;

    class ArgList;

    class Arguments;

    class Primary;

    class ConstVal;

    class Var;

    class VarSuffix;

    class Token;


    class Production {
    public:
        static Map<token::TokenType, symbol::Symbol> tokenToSym;

        symbol::Symbol thisSymbol = symbol::Symbol::BASE;

        virtual String toString() = 0;

        virtual ~Production() = default;
    };


    class S : public Production {
    public:
        size_t line;
        SharedPtr<Program> program;

        S(size_t line, SharedPtr<Program> program)
                : line(line), program(std::move(program)) { thisSymbol = symbol::Symbol::S; }

        String toString() override { return String{"S"}; }
    };


    class Program : public Production {
    public:
        size_t line;
        SharedPtr<Declarations> declarations;

        Program(size_t line, SharedPtr<Declarations> declarations)
                : line(line), declarations(std::move(declarations)){ thisSymbol = symbol::Symbol::program; }

        String toString() override { return String{"Program"}; }
    };


    class Declarations : public Production {
    public:
        size_t line;

        explicit Declarations(size_t line) : line(line) { thisSymbol = symbol::Symbol::declarations; }

        ~Declarations() override = default;

        String toString() override { return String{"Declarations"}; }
    };

    class Declarations1 : public Declarations {
    public:
        SharedPtr<Declaration> declaration;
        SharedPtr<Declarations> declarations;

        Declarations1(size_t line, SharedPtr<Declaration> declaration, SharedPtr<Declarations> declarations)
                : Declarations(line),
                  declaration(std::move(declaration)),
                  declarations(std::move(declarations)) {}
    };


    class Declarations2 : public Declarations {
    public:
        explicit Declarations2(size_t line) : Declarations(line) {}
    };


    class Declaration : public Production {
    public:
        size_t line;

        explicit Declaration(size_t line) : line(line) { thisSymbol = symbol::Symbol::declaration; }

        ~Declaration() override = default;

        String toString() override { return String{"Declaration"}; }
    };

    class Declaration1 : public Declaration {
    public:
        SharedPtr<FunDecl> funDecl;

        Declaration1(size_t line, SharedPtr<FunDecl> funDecl) : Declaration(line), funDecl(std::move(funDecl)) {}
    };


    class Declaration2 : public Declaration {
    public:
        SharedPtr<VarDecl> varDecl;

        Declaration2(size_t line, SharedPtr<VarDecl> varDecl) : Declaration(line), varDecl(std::move(varDecl)) {}
    };


    class Declaration3 : public Declaration {
    public:
        SharedPtr<Statement> statement;

        Declaration3(size_t line, SharedPtr<Statement> statement)
                : Declaration(line), statement(std::move(statement)) {}
    };


    class Statement : public Production {
    public:
        size_t line;

        explicit Statement(size_t line) : line(line) { thisSymbol = symbol::Symbol::statement; }

        ~Statement() override = default;

        String toString() override { return String{"Statement"}; }
    };

    class Statement1 : public Statement {
    public:
        SharedPtr<BreakStmt> breakStmt;

        Statement1(size_t line, SharedPtr<BreakStmt> breakStmt) : Statement(line), breakStmt(std::move(breakStmt)) {}
    };


    class Statement2 : public Statement {
    public:
        SharedPtr<ContinueStmt> continueStmt;

        Statement2(size_t line, SharedPtr<ContinueStmt> continueStmt)
                : Statement(line), continueStmt(std::move(continueStmt)) {}
    };


    class Statement3 : public Statement {
    public:
        SharedPtr<ReturnStmt> returnStmt;

        Statement3(size_t line, SharedPtr<ReturnStmt> returnStmt)
                : Statement(line), returnStmt(std::move(returnStmt)) {}
    };


    class Statement4 : public Statement {
    public:
        SharedPtr<ExprStmt> exprStmt;

        Statement4(size_t line, SharedPtr<ExprStmt> exprStmt) : Statement(line), exprStmt(std::move(exprStmt)) {}
    };


    class Statement5 : public Statement {
    public:
        SharedPtr<IfStmt> ifStmt;

        Statement5(size_t line, SharedPtr<IfStmt> ifStmt) : Statement(line), ifStmt(std::move(ifStmt)) {}
    };


    class Statement6 : public Statement {
    public:
        SharedPtr<WhileStmt> whileStmt;

        Statement6(size_t line, SharedPtr<WhileStmt> whileStmt) : Statement(line), whileStmt(std::move(whileStmt)) {}
    };


    class Statement7 : public Statement {
    public:
        SharedPtr<RepeatStmt> repeatStmt;

        Statement7(size_t line, SharedPtr<RepeatStmt> repeatStmt)
                : Statement(line), repeatStmt(std::move(repeatStmt)) {}
    };


    class Statement8 : public Statement {
    public:
        SharedPtr<Block> block;

        Statement8(size_t line, SharedPtr<Block> block) : Statement(line), block(std::move(block)) {}
    };

    class Statement9 : public Statement {
    public:
        SharedPtr<ForStmt> forStmt;

        Statement9(size_t line, SharedPtr<ForStmt> forStmt) : Statement(line), forStmt(std::move(forStmt)) {}
    };


    class BreakStmt : public Production {
    public:
        size_t line;
        SharedPtr<Token> token_BREAK;
        SharedPtr<Token> token_SEMICOLON;

        BreakStmt(size_t line, SharedPtr<Token> token_BREAK, SharedPtr<Token> token_SEMICOLON)
                : line(line),
                  token_BREAK(std::move(token_BREAK)),
                  token_SEMICOLON(std::move(token_SEMICOLON)) { thisSymbol = symbol::Symbol::breakStmt; }

        String toString() override { return String{"BreakStmt"}; }
    };


    class ContinueStmt : public Production {
    public:
        size_t line;
        SharedPtr<Token> token_CONTINUE;
        SharedPtr<Token> token_SEMICOLON;

        ContinueStmt(size_t line, SharedPtr<Token> token_CONTINUE, SharedPtr<Token> token_SEMICOLON)
                : line(line),
                  token_CONTINUE(std::move(token_CONTINUE)),
                  token_SEMICOLON(std::move(token_SEMICOLON)) { thisSymbol = symbol::Symbol::continueStmt; }

        String toString() override { return String{"ContinueStmt"}; }
    };


    class ReturnStmt : public Production {
    public:
        size_t line;
        SharedPtr<Token> token_RETURN;
        SharedPtr<ExprStmt> exprStmt;

        ReturnStmt(size_t line, SharedPtr<Token> token_RETURN, SharedPtr<ExprStmt> exprStmt)
                : line(line),
                  token_RETURN(std::move(token_RETURN)),
                  exprStmt(std::move(exprStmt)) { thisSymbol = symbol::Symbol::returnStmt; }

        String toString() override { return String{"ReturnStmt"}; }
    };


    class FunDecl : public Production {
    public:
        size_t line;
        SharedPtr<Token> token_IDENTIFIER;
        SharedPtr<Token> token_EQUAL;
        SharedPtr<Token> token_FUNCTION;
        SharedPtr<Token> token_LEFT_PAREN;
        SharedPtr<ParamList> paramList;
        SharedPtr<Token> token_RIGHT_PAREN;
        SharedPtr<Block> block;

        FunDecl(size_t line, SharedPtr<Token> token_IDENTIFIER, SharedPtr<Token> token_EQUAL,
                SharedPtr<Token> token_FUNCTION, SharedPtr<Token> token_LEFT_PAREN, SharedPtr<ParamList> paramList,
                SharedPtr<Token> token_RIGHT_PAREN, SharedPtr<Block> block)
                : line(line),
                  token_IDENTIFIER(std::move(token_IDENTIFIER)),
                  token_EQUAL(std::move(token_EQUAL)),
                  token_FUNCTION(std::move(token_FUNCTION)),
                  token_LEFT_PAREN(std::move(token_LEFT_PAREN)),
                  paramList(std::move(paramList)),
                  token_RIGHT_PAREN(std::move(token_RIGHT_PAREN)),
                  block(std::move(block)) { thisSymbol = symbol::Symbol::funDecl; }

        String toString() override { return String{"FunDecl"}; }
    };


    class VarDecl : public Production {
    public:
        size_t line;
        SharedPtr<Type> type;
        SharedPtr<VarDef> varDef;
        SharedPtr<VarDefs> varDefs;
        SharedPtr<Token> token_SEMICOLON;

        VarDecl(size_t line, SharedPtr<Type> type, SharedPtr<VarDef> varDef, SharedPtr<VarDefs> varDefs,
                SharedPtr<Token> token_SEMICOLON)
                : line(line),
                  type(std::move(type)),
                  varDef(std::move(varDef)),
                  varDefs(std::move(varDefs)),
                  token_SEMICOLON(std::move(token_SEMICOLON)) { thisSymbol = symbol::Symbol::varDecl; }

        String toString() override { return String{"VarDecl"}; }
    };


    class VarDef : public Production {
    public:
        size_t line;
        SharedPtr<Var> var;
        SharedPtr<VarInit> varInit;

        VarDef(size_t line, SharedPtr<Var> var, SharedPtr<VarInit> varInit)
                : line(line), var(std::move(var)),
                  varInit(std::move(varInit)) { thisSymbol = symbol::Symbol::varDef; }

        String toString() override { return String{"VarDef"}; }
    };


    class VarDefs : public Production {
    public:
        size_t line;

        explicit VarDefs(size_t line) : line(line) { thisSymbol = symbol::Symbol::varDefs; }

        ~VarDefs() override = default;

        String toString() override { return String{"VarDefs"}; }
    };

    class VarDefs1 : public VarDefs {
    public:
        SharedPtr<Token> token_COMMA;
        SharedPtr<VarDef> varDef;
        SharedPtr<VarDefs> varDefs;

        VarDefs1(size_t line, SharedPtr<Token> token_COMMA, SharedPtr<VarDef> varDef, SharedPtr<VarDefs> varDefs)
                : VarDefs(line),
                  token_COMMA(std::move(token_COMMA)),
                  varDef(std::move(varDef)),
                  varDefs(std::move(varDefs)) {}
    };


    class VarDefs2 : public VarDefs {
    public:
        explicit VarDefs2(size_t line) : VarDefs(line) {}
    };


    class VarInit : public Production {
    public:
        size_t line;

        explicit VarInit(size_t line) : line(line) { thisSymbol = symbol::Symbol::varInit; }

        ~VarInit() override = default;

        String toString() override { return String{"VarInit"}; }
    };

    class VarInit1 : public VarInit {
    public:
        SharedPtr<Token> token_EQUAL;
        SharedPtr<Expression> expression;

        VarInit1(size_t line, SharedPtr<Token> token_EQUAL, SharedPtr<Expression> expression)
                : VarInit(line),
                  token_EQUAL(std::move(token_EQUAL)),
                  expression(std::move(expression)) {}
    };


    class VarInit2 : public VarInit {
    public:
        explicit VarInit2(size_t line) : VarInit(line) {}
    };


    class Type : public Production {
    public:
        size_t line;

        explicit Type(size_t line) : line(line) { thisSymbol = symbol::Symbol::type; }

        ~Type() override = default;

        String toString() override { return String{"Type"}; }
    };

    class Type1 : public Type {
    public:
        SharedPtr<Token> token_INTEGER;

        Type1(size_t line, SharedPtr<Token> token_INTEGER) : Type(line), token_INTEGER(std::move(token_INTEGER)) {}
    };


    class Type2 : public Type {
    public:
        SharedPtr<Token> token_DOUBLE;

        Type2(size_t line, SharedPtr<Token> token_DOUBLE) : Type(line), token_DOUBLE(std::move(token_DOUBLE)) {}
    };


    class Type3 : public Type {
    public:
        SharedPtr<Token> token_STRING;

        Type3(size_t line, SharedPtr<Token> token_STRING) : Type(line), token_STRING(std::move(token_STRING)) {}
    };


    class Type4 : public Type {
    public:
        SharedPtr<Token> token_BOOL;

        Type4(size_t line, SharedPtr<Token> token_BOOL) : Type(line), token_BOOL(std::move(token_BOOL)) {}
    };


    class Type5 : public Type {
    public:
        SharedPtr<Token> token_CHAR;

        Type5(size_t line, SharedPtr<Token> token_CHAR) : Type(line), token_CHAR(std::move(token_CHAR)) {}
    };


    class Type6 : public Type {
    public:
        SharedPtr<Token> token_VAR;

        Type6(size_t line, SharedPtr<Token> token_VAR) : Type(line), token_VAR(std::move(token_VAR)) {}
    };


    class ExprStmt : public Production {
    public:
        size_t line;

        explicit ExprStmt(size_t line) : line(line) { thisSymbol = symbol::Symbol::exprStmt; }

        ~ExprStmt() override = default;

        String toString() override { return String{"ExprStmt"}; }
    };

    class ExprStmt1 : public ExprStmt {
    public:
        SharedPtr<Expression> expression;
        SharedPtr<Token> token_SEMICOLON;

        ExprStmt1(size_t line, SharedPtr<Expression> expression, SharedPtr<Token> token_SEMICOLON)
                : ExprStmt(line),
                  expression(std::move(expression)),
                  token_SEMICOLON(std::move(token_SEMICOLON)) {}
    };


    class ExprStmt2 : public ExprStmt {
    public:
        SharedPtr<Token> token_SEMICOLON;

        ExprStmt2(size_t line, SharedPtr<Token> token_SEMICOLON)
                : ExprStmt(line), token_SEMICOLON(std::move(token_SEMICOLON)) {}
    };


    class IfStmt : public Production {
    public:
        size_t line;
        SharedPtr<Token> token_IF;
        SharedPtr<Token> token_LEFT_PAREN;
        SharedPtr<Expression> expression;
        SharedPtr<Token> token_RIGHT_PAREN;
        SharedPtr<Statement> statement;
        SharedPtr<ElseBranch> elseBranch;

        IfStmt(size_t line, SharedPtr<Token> token_IF, SharedPtr<Token> token_LEFT_PAREN,
               SharedPtr<Expression> expression, SharedPtr<Token> token_RIGHT_PAREN, SharedPtr<Statement> statement,
               SharedPtr<ElseBranch> elseBranch)
                : line(line),
                  token_IF(std::move(token_IF)),
                  token_LEFT_PAREN(std::move(token_LEFT_PAREN)),
                  expression(std::move(expression)),
                  token_RIGHT_PAREN(std::move(token_RIGHT_PAREN)),
                  statement(std::move(statement)),
                  elseBranch(std::move(elseBranch)) { thisSymbol = symbol::Symbol::ifStmt; }

        String toString() override { return String{"IfStmt"}; }
    };


    class ElseBranch : public Production {
    public:
        size_t line;

        explicit ElseBranch(size_t line) : line(line) { thisSymbol = symbol::Symbol::elseBranch; }

        ~ElseBranch() override = default;

        String toString() override { return String{"ElseBranch"}; }
    };

    class ElseBranch1 : public ElseBranch {
    public:
        SharedPtr<Token> token_ELSE;
        SharedPtr<Statement> statement;

        ElseBranch1(size_t line, SharedPtr<Token> token_ELSE, SharedPtr<Statement> statement)
                : ElseBranch(line),
                  token_ELSE(std::move(token_ELSE)),
                  statement(std::move(statement)) {}
    };


    class ElseBranch2 : public ElseBranch {
    public:
        explicit ElseBranch2(size_t line) : ElseBranch(line) {}
    };


    class WhileStmt : public Production {
    public:
        size_t line;
        SharedPtr<Token> token_WHILE;
        SharedPtr<Token> token_LEFT_PAREN;
        SharedPtr<Expression> expression;
        SharedPtr<Token> token_RIGHT_PAREN;
        SharedPtr<Statement> statement;

        WhileStmt(size_t line, SharedPtr<Token> token_WHILE, SharedPtr<Token> token_LEFT_PAREN,
                  SharedPtr<Expression> expression, SharedPtr<Token> token_RIGHT_PAREN, SharedPtr<Statement> statement)
                : line(line),
                  token_WHILE(std::move(token_WHILE)),
                  token_LEFT_PAREN(std::move(token_LEFT_PAREN)),
                  expression(std::move(expression)),
                  token_RIGHT_PAREN(std::move(token_RIGHT_PAREN)),
                  statement(std::move(statement)) { thisSymbol = symbol::Symbol::whileStmt; }

        String toString() override { return String{"WhileStmt"}; }
    };


    class ForStmt : public Production {
    public:
        size_t line;

        explicit ForStmt(size_t line) : line(line) { thisSymbol = symbol::Symbol::forStmt; }

        ~ForStmt() override = default;

        String toString() override { return String{"ForStmt"}; }
    };

    class ForStmt1 : public ForStmt {
    public:
        SharedPtr<Token> token_FOR;
        SharedPtr<Token> token_LEFT_PAREN;
        SharedPtr<VarDecl> varDecl;
        SharedPtr<ExprStmt> exprStmt;
        SharedPtr<Token> token_RIGHT_PAREN;
        SharedPtr<Statement> statement;

        ForStmt1(size_t line, SharedPtr<Token> token_FOR, SharedPtr<Token> token_LEFT_PAREN, SharedPtr<VarDecl> varDecl,
                 SharedPtr<ExprStmt> exprStmt, SharedPtr<Token> token_RIGHT_PAREN, SharedPtr<Statement> statement)
                : ForStmt(line), token_FOR(std::move(token_FOR)), token_LEFT_PAREN(std::move(token_LEFT_PAREN)),
                  varDecl(std::move(varDecl)), exprStmt(std::move(exprStmt)),
                  token_RIGHT_PAREN(std::move(token_RIGHT_PAREN)), statement(std::move(statement)) {}
    };


    class ForStmt2 : public ForStmt {
    public:
        SharedPtr<Token> token_FOR;
        SharedPtr<Token> token_LEFT_PAREN;
        SharedPtr<VarDecl> varDecl;
        SharedPtr<ExprStmt> exprStmt;
        SharedPtr<Expression> expression;
        SharedPtr<Token> token_RIGHT_PAREN;
        SharedPtr<Statement> statement;

        ForStmt2(size_t line, SharedPtr<Token> token_FOR, SharedPtr<Token> token_LEFT_PAREN, SharedPtr<VarDecl> varDecl,
                 SharedPtr<ExprStmt> exprStmt, SharedPtr<Expression> expression, SharedPtr<Token> token_RIGHT_PAREN,
                 SharedPtr<Statement> statement)
                : ForStmt(line),
                  token_FOR(std::move(token_FOR)),
                  token_LEFT_PAREN(std::move(token_LEFT_PAREN)),
                  varDecl(std::move(varDecl)),
                  exprStmt(std::move(exprStmt)),
                  expression(std::move(expression)),
                  token_RIGHT_PAREN(std::move(token_RIGHT_PAREN)),
                  statement(std::move(statement)) {}
    };


    class ForStmt3 : public ForStmt {
    public:
        SharedPtr<Token> token_FOR;
        SharedPtr<Token> token_LEFT_PAREN;
        SharedPtr<ExprStmt> exprStmt1;
        SharedPtr<ExprStmt> exprStmt2;
        SharedPtr<Token> token_RIGHT_PAREN;
        SharedPtr<Statement> statement;

        ForStmt3(size_t line, SharedPtr<Token> token_FOR, SharedPtr<Token> token_LEFT_PAREN,
                 SharedPtr<ExprStmt> exprStmt1, SharedPtr<ExprStmt> exprStmt2, SharedPtr<Token> token_RIGHT_PAREN,
                 SharedPtr<Statement> statement)
                : ForStmt(line),
                  token_FOR(std::move(token_FOR)),
                  token_LEFT_PAREN(std::move(token_LEFT_PAREN)),
                  exprStmt1(std::move(exprStmt1)),
                  exprStmt2(std::move(exprStmt2)),
                  token_RIGHT_PAREN(std::move(token_RIGHT_PAREN)),
                  statement(std::move(statement)) {}
    };


    class ForStmt4 : public ForStmt {
    public:
        SharedPtr<Token> token_FOR;
        SharedPtr<Token> token_LEFT_PAREN;
        SharedPtr<ExprStmt> exprStmt1;
        SharedPtr<ExprStmt> exprStmt2;
        SharedPtr<Expression> expression;
        SharedPtr<Token> token_RIGHT_PAREN;
        SharedPtr<Statement> statement;

        ForStmt4(size_t line, SharedPtr<Token> token_FOR, SharedPtr<Token> token_LEFT_PAREN,
                 SharedPtr<ExprStmt> exprStmt1, SharedPtr<ExprStmt> exprStmt2, SharedPtr<Expression> expression,
                 SharedPtr<Token> token_RIGHT_PAREN, SharedPtr<Statement> statement)
                : ForStmt(line),
                  token_FOR(std::move(token_FOR)),
                  token_LEFT_PAREN(std::move(token_LEFT_PAREN)),
                  exprStmt1(std::move(exprStmt1)),
                  exprStmt2(std::move(exprStmt2)),
                  expression(std::move(expression)),
                  token_RIGHT_PAREN(std::move(token_RIGHT_PAREN)),
                  statement(std::move(statement)) {}
    };


    class Block : public Production {
    public:
        size_t line;
        SharedPtr<Token> token_LEFT_BRACE;
        SharedPtr<Declarations> declarations;
        SharedPtr<Token> token_RIGHT_BRACE;

        Block(size_t line, SharedPtr<Token> token_LEFT_BRACE, SharedPtr<Declarations> declarations,
              SharedPtr<Token> token_RIGHT_BRACE)
                : line(line),
                  token_LEFT_BRACE(std::move(token_LEFT_BRACE)),
                  declarations(std::move(declarations)),
                  token_RIGHT_BRACE(std::move(token_RIGHT_BRACE)) { thisSymbol = symbol::Symbol::block; }

        String toString() override { return String{"Block"}; }
    };


    class RepeatStmt : public Production {
    public:
        size_t line;
        SharedPtr<Token> token_REPEAT;
        SharedPtr<Statement> statement;
        SharedPtr<Token> token_UNTIL;
        SharedPtr<Token> token_LEFT_PAREN;
        SharedPtr<Expression> expression;
        SharedPtr<Token> token_RIGHT_PAREN;
        SharedPtr<Token> token_SEMICOLON;

        RepeatStmt(size_t line, SharedPtr<Token> token_REPEAT, SharedPtr<Statement> statement,
                   SharedPtr<Token> token_UNTIL, SharedPtr<Token> token_LEFT_PAREN, SharedPtr<Expression> expression,
                   SharedPtr<Token> token_RIGHT_PAREN, SharedPtr<Token> token_SEMICOLON)
                : line(line),
                  token_REPEAT(std::move(token_REPEAT)),
                  statement(std::move(statement)),
                  token_UNTIL(std::move(token_UNTIL)),
                  token_LEFT_PAREN(std::move(token_LEFT_PAREN)),
                  expression(std::move(expression)),
                  token_RIGHT_PAREN(std::move(token_RIGHT_PAREN)),
                  token_SEMICOLON(std::move(token_SEMICOLON)) { thisSymbol = symbol::Symbol::repeatStmt; }

        String toString() override { return String{"RepeatStmt"}; }
    };


    class ParamList : public Production {
    public:
        size_t line;

        explicit ParamList(size_t line) : line(line) { thisSymbol = symbol::Symbol::paramList; }

        ~ParamList() override = default;

        String toString() override { return String{"ParamList"}; }
    };

    class ParamList1 : public ParamList {
    public:
        SharedPtr<Parameter> parameter;
        SharedPtr<Parameters> parameters;

        ParamList1(size_t line, SharedPtr<Parameter> parameter, SharedPtr<Parameters> parameters)
                : ParamList(line),
                  parameter(std::move(parameter)),
                  parameters(std::move(parameters)) {}
    };


    class ParamList2 : public ParamList {
    public:
        explicit ParamList2(size_t line) : ParamList(line) {}
    };


    class Parameters : public Production {
    public:
        size_t line;

        explicit Parameters(size_t line) : line(line) { thisSymbol = symbol::Symbol::parameters; }

        ~Parameters() override = default;

        String toString() override { return String{"Parameters"}; }
    };

    class Parameters1 : public Parameters {
    public:
        SharedPtr<Token> token_COMMA;
        SharedPtr<Parameter> parameter;
        SharedPtr<Parameters> parameters;

        Parameters1(size_t line, SharedPtr<Token> token_COMMA, SharedPtr<Parameter> parameter,
                    SharedPtr<Parameters> parameters) : Parameters(line),
                                                        token_COMMA(std::move(token_COMMA)),
                                                        parameter(std::move(parameter)),
                                                        parameters(std::move(parameters)) {}
    };


    class Parameters2 : public Parameters {
    public:
        explicit Parameters2(size_t line) : Parameters(line) {}
    };


    class Parameter : public Production {
    public:
        size_t line;
        SharedPtr<Type> type;
        SharedPtr<Var> var;

        Parameter(size_t line, SharedPtr<Type> type, SharedPtr<Var> var)
                : line(line),
                  type(std::move(type)), var(std::move(var)) { thisSymbol = symbol::Symbol::parameter; }

        String toString() override { return String{"Parameter"}; }
    };


    class Expression : public Production {
    public:
        size_t line;
        SharedPtr<Assignment> assignment;

        Expression(size_t line, SharedPtr<Assignment> assignment)
                : line(line),
                  assignment(std::move(assignment)) { thisSymbol = symbol::Symbol::expression; }

        String toString() override { return String{"Expression"}; }
    };


    class Assignment : public Production {
    public:
        size_t line;

        explicit Assignment(size_t line) : line(line) { thisSymbol = symbol::Symbol::assignment; }

        ~Assignment() override = default;

        String toString() override { return String{"Assignment"}; }
    };

    class Assignment1 : public Assignment {
    public:
        SharedPtr<Var> var;
        SharedPtr<Token> token_EQUAL;
        SharedPtr<Assignment> assignment;

        Assignment1(size_t line, SharedPtr<Var> var, SharedPtr<Token> token_EQUAL, SharedPtr<Assignment> assignment)
                : Assignment(line),
                  var(std::move(var)),
                  token_EQUAL(std::move(token_EQUAL)),
                  assignment(std::move(assignment)) {}
    };


    class Assignment2 : public Assignment {
    public:
        SharedPtr<Logic_or> logic_or;

        Assignment2(size_t line, SharedPtr<Logic_or> logic_or) : Assignment(line), logic_or(std::move(logic_or)) {}
    };


    class Logic_or : public Production {
    public:
        size_t line;
        SharedPtr<Logic_and> logic_and;
        SharedPtr<Logic_or_prime> logic_or_prime;

        Logic_or(size_t line, SharedPtr<Logic_and> logic_and, SharedPtr<Logic_or_prime> logic_or_prime)
                : line(line),
                  logic_and(std::move(logic_and)),
                  logic_or_prime(std::move(logic_or_prime)) { thisSymbol = symbol::Symbol::logic_or; }

        String toString() override { return String{"Logic_or"}; }
    };


    class Logic_or_prime : public Production {
    public:
        size_t line;

        explicit Logic_or_prime(size_t line) : line(line) { thisSymbol = symbol::Symbol::logic_or_prime; }

        ~Logic_or_prime() override = default;

        String toString() override { return String{"Logic_or_prime"}; }
    };

    class Logic_or_prime1 : public Logic_or_prime {
    public:
        SharedPtr<Token> token_OR;
        SharedPtr<Logic_or> logic_or;

        Logic_or_prime1(size_t line, SharedPtr<Token> token_OR, SharedPtr<Logic_or> logic_or)
                : Logic_or_prime(line), token_OR(std::move(token_OR)), logic_or(std::move(logic_or)) {}
    };


    class Logic_or_prime2 : public Logic_or_prime {
    public:
        explicit Logic_or_prime2(size_t line) : Logic_or_prime(line) {}
    };


    class Logic_and : public Production {
    public:
        size_t line;
        SharedPtr<Equality> equality;
        SharedPtr<Logic_and_prime> logic_and_prime;

        Logic_and(size_t line, SharedPtr<Equality> equality, SharedPtr<Logic_and_prime> logic_and_prime)
                : line(line),
                  equality(std::move(equality)),
                  logic_and_prime(std::move(logic_and_prime)) { thisSymbol = symbol::Symbol::logic_and; }

        String toString() override { return String{"Logic_and"}; }
    };


    class Logic_and_prime : public Production {
    public:
        size_t line;

        explicit Logic_and_prime(size_t line) : line(line) { thisSymbol = symbol::Symbol::logic_and_prime; }

        ~Logic_and_prime() override = default;

        String toString() override { return String{"Logic_and_prime"}; }
    };

    class Logic_and_prime1 : public Logic_and_prime {
    public:
        SharedPtr<Token> token_AND;
        SharedPtr<Logic_and> logic_and;

        Logic_and_prime1(size_t line, SharedPtr<Token> token_AND, SharedPtr<Logic_and> logic_and)
                : Logic_and_prime(line), token_AND(std::move(token_AND)), logic_and(std::move(logic_and)) {}
    };


    class Logic_and_prime2 : public Logic_and_prime {
    public:
        explicit Logic_and_prime2(size_t line) : Logic_and_prime(line) {}
    };


    class Equality : public Production {
    public:
        size_t line;
        SharedPtr<Comparison> comparison;
        SharedPtr<Equality_prime> equality_prime;

        Equality(size_t line, SharedPtr<Comparison> comparison, SharedPtr<Equality_prime> equality_prime)
                : line(line),
                  comparison(std::move(comparison)),
                  equality_prime(std::move(equality_prime)) { thisSymbol = symbol::Symbol::equality; }

        String toString() override { return String{"Equality"}; }
    };


    class Equality_prime : public Production {
    public:
        size_t line;

        explicit Equality_prime(size_t line) : line(line) { thisSymbol = symbol::Symbol::equality_prime; }

        ~Equality_prime() override = default;

        String toString() override { return String{"Equality_prime"}; }
    };

    class Equality_prime1 : public Equality_prime {
    public:
        SharedPtr<Token> token_NOT_EQUAL;
        SharedPtr<Equality> equality;

        Equality_prime1(size_t line, SharedPtr<Token> token_NOT_EQUAL, SharedPtr<Equality> equality)
                : Equality_prime(line),
                  token_NOT_EQUAL(std::move(token_NOT_EQUAL)),
                  equality(std::move(equality)) {}
    };


    class Equality_prime2 : public Equality_prime {
    public:
        SharedPtr<Token> token_EQUAL_EQUAL;
        SharedPtr<Equality> equality;

        Equality_prime2(size_t line, SharedPtr<Token> token_EQUAL_EQUAL, SharedPtr<Equality> equality)
                : Equality_prime(line),
                  token_EQUAL_EQUAL(std::move(token_EQUAL_EQUAL)),
                  equality(std::move(equality)) {}
    };


    class Equality_prime3 : public Equality_prime {
    public:
        explicit Equality_prime3(size_t line) : Equality_prime(line) {}
    };


    class Comparison : public Production {
    public:
        size_t line;
        SharedPtr<Term> term;
        SharedPtr<Comparison_prime> comparison_prime;

        Comparison(size_t line, SharedPtr<Term> term, SharedPtr<Comparison_prime> comparison_prime)
                : line(line),
                  term(std::move(term)),
                  comparison_prime(std::move(comparison_prime)) { thisSymbol = symbol::Symbol::comparison; }

        String toString() override { return String{"Comparison"}; }
    };


    class Comparison_prime : public Production {
    public:
        size_t line;

        explicit Comparison_prime(size_t line) : line(line) { thisSymbol = symbol::Symbol::comparison_prime; }

        ~Comparison_prime() override = default;

        String toString() override { return String{"Comparison_prime"}; }
    };

    class Comparison_prime1 : public Comparison_prime {
    public:
        SharedPtr<Token> token_GREATER;
        SharedPtr<Comparison> comparison;

        Comparison_prime1(size_t line, SharedPtr<Token> token_GREATER, SharedPtr<Comparison> comparison)
                : Comparison_prime(line), token_GREATER(std::move(token_GREATER)), comparison(std::move(comparison)) {}
    };


    class Comparison_prime2 : public Comparison_prime {
    public:
        SharedPtr<Token> token_GREATER_EQUAL;
        SharedPtr<Comparison> comparison;

        Comparison_prime2(size_t line, SharedPtr<Token> token_GREATER_EQUAL, SharedPtr<Comparison> comparison)
                : Comparison_prime(line),
                  token_GREATER_EQUAL(std::move(token_GREATER_EQUAL)),
                  comparison(std::move(comparison)) {}
    };


    class Comparison_prime3 : public Comparison_prime {
    public:
        SharedPtr<Token> token_LESS;
        SharedPtr<Comparison> comparison;

        Comparison_prime3(size_t line, SharedPtr<Token> token_LESS, SharedPtr<Comparison> comparison)
                : Comparison_prime(line),
                  token_LESS(std::move(token_LESS)),
                  comparison(std::move(comparison)) {}
    };


    class Comparison_prime4 : public Comparison_prime {
    public:
        SharedPtr<Token> token_LESS_EQUAL;
        SharedPtr<Comparison> comparison;

        Comparison_prime4(size_t line, SharedPtr<Token> token_LESS_EQUAL, SharedPtr<Comparison> comparison)
                : Comparison_prime(line),
                  token_LESS_EQUAL(std::move(token_LESS_EQUAL)),
                  comparison(std::move(comparison)) {}
    };


    class Comparison_prime5 : public Comparison_prime {
    public:
        explicit Comparison_prime5(size_t line) : Comparison_prime(line) {}
    };


    class Term : public Production {
    public:
        size_t line;
        SharedPtr<Factor> factor;
        SharedPtr<Term_prime> term_prime;

        Term(size_t line, SharedPtr<Factor> factor, SharedPtr<Term_prime> term_prime)
                : line(line),
                  factor(std::move(factor)),
                  term_prime(std::move(term_prime)) { thisSymbol = symbol::Symbol::term; }

        String toString() override { return String{"Term"}; }
    };


    class Term_prime : public Production {
    public:
        size_t line;

        explicit Term_prime(size_t line) : line(line) { thisSymbol = symbol::Symbol::term_prime; }

        ~Term_prime() override = default;

        String toString() override { return String{"Term_prime"}; }
    };

    class Term_prime1 : public Term_prime {
    public:
        SharedPtr<Token> token_MINUS;
        SharedPtr<Term> term;

        Term_prime1(size_t line, SharedPtr<Token> token_MINUS, SharedPtr<Term> term)
                : Term_prime(line), token_MINUS(std::move(token_MINUS)), term(std::move(term)) {}
    };


    class Term_prime2 : public Term_prime {
    public:
        SharedPtr<Token> token_PLUS;
        SharedPtr<Term> term;

        Term_prime2(size_t line, SharedPtr<Token> token_PLUS, SharedPtr<Term> term)
                : Term_prime(line), token_PLUS(std::move(token_PLUS)), term(std::move(term)) {}
    };


    class Term_prime3 : public Term_prime {
    public:
        explicit Term_prime3(size_t line) : Term_prime(line) {}
    };


    class Factor : public Production {
    public:
        size_t line;
        SharedPtr<Incr_exp> incr_exp;
        SharedPtr<Factor_prime> factor_prime;

        Factor(size_t line, SharedPtr<Incr_exp> incr_exp, SharedPtr<Factor_prime> factor_prime)
                : line(line),
                  incr_exp(std::move(incr_exp)),
                  factor_prime(std::move(factor_prime)) { thisSymbol = symbol::Symbol::factor; }

        String toString() override { return String{"Factor"}; }
    };


    class Factor_prime : public Production {
    public:
        size_t line;

        explicit Factor_prime(size_t line) : line(line) { thisSymbol = symbol::Symbol::factor_prime; }

        ~Factor_prime() override = default;

        String toString() override { return String{"Factor_prime"}; }
    };

    class Factor_prime1 : public Factor_prime {
    public:
        SharedPtr<Token> token_DIV;
        SharedPtr<Factor> factor;

        Factor_prime1(size_t line, SharedPtr<Token> token_DIV, SharedPtr<Factor> factor)
                : Factor_prime(line), token_DIV(std::move(token_DIV)), factor(std::move(factor)) {}
    };


    class Factor_prime2 : public Factor_prime {
    public:
        SharedPtr<Token> token_STAR;
        SharedPtr<Factor> factor;

        Factor_prime2(size_t line, SharedPtr<Token> token_STAR, SharedPtr<Factor> factor)
                : Factor_prime(line), token_STAR(std::move(token_STAR)), factor(std::move(factor)) {}
    };


    class Factor_prime3 : public Factor_prime {
    public:
        SharedPtr<Token> token_MOD;
        SharedPtr<Factor> factor;

        Factor_prime3(size_t line, SharedPtr<Token> token_MOD, SharedPtr<Factor> factor)
                : Factor_prime(line), token_MOD(std::move(token_MOD)), factor(std::move(factor)) {}
    };


    class Factor_prime4 : public Factor_prime {
    public:
        explicit Factor_prime4(size_t line) : Factor_prime(line) {}
    };


    class Incr_exp : public Production {
    public:
        size_t line;
        SharedPtr<Unary> unary;
        SharedPtr<Incr_op> incr_op;

        Incr_exp(size_t line, SharedPtr<Unary> unary, SharedPtr<Incr_op> incr_op)
                : line(line),
                  unary(std::move(unary)),
                  incr_op(std::move(incr_op)) { thisSymbol = symbol::Symbol::incr_exp; }

        String toString() override { return String{"Incr_exp"}; }
    };


    class Incr_op : public Production {
    public:
        size_t line;

        explicit Incr_op(size_t line) : line(line) { thisSymbol = symbol::Symbol::incr_op; }

        ~Incr_op() override = default;

        String toString() override { return String{"Incr_op"}; }
    };

    class Incr_op1 : public Incr_op {
    public:
        SharedPtr<Token> token_DOUBLE_ADD;
        SharedPtr<Incr_op> incr_op;

        Incr_op1(size_t line, SharedPtr<Token> token_DOUBLE_ADD, SharedPtr<Incr_op> incr_op)
                : Incr_op(line),
                  token_DOUBLE_ADD(std::move(token_DOUBLE_ADD)),
                  incr_op(std::move(incr_op)) {}
    };


    class Incr_op2 : public Incr_op {
    public:
        SharedPtr<Token> token_DOUBLE_MINUS;
        SharedPtr<Incr_op> incr_op;

        Incr_op2(size_t line, SharedPtr<Token> token_DOUBLE_MINUS, SharedPtr<Incr_op> incr_op)
                : Incr_op(line),
                  token_DOUBLE_MINUS(std::move(token_DOUBLE_MINUS)),
                  incr_op(std::move(incr_op)) {}
    };


    class Incr_op3 : public Incr_op {
    public:
        explicit Incr_op3(size_t line) : Incr_op(line) {}
    };


    class Unary : public Production {
    public:
        size_t line;

        explicit Unary(size_t line) : line(line) { thisSymbol = symbol::Symbol::unary; }

        ~Unary() override = default;

        String toString() override { return String{"Unary"}; }
    };

    class Unary1 : public Unary {
    public:
        SharedPtr<Token> token_NOT;
        SharedPtr<Unary> unary;

        Unary1(size_t line, SharedPtr<Token> token_NOT, SharedPtr<Unary> unary)
                : Unary(line),
                  token_NOT(std::move(token_NOT)),
                  unary(std::move(unary)) {}
    };


    class Unary2 : public Unary {
    public:
        SharedPtr<Token> token_MINUS;
        SharedPtr<Unary> unary;

        Unary2(size_t line, SharedPtr<Token> token_MINUS, SharedPtr<Unary> unary)
                : Unary(line),
                  token_MINUS(std::move(token_MINUS)),
                  unary(std::move(unary)) {}
    };


    class Unary3 : public Unary {
    public:
        SharedPtr<Call> call;

        Unary3(size_t line, SharedPtr<Call> call) : Unary(line), call(std::move(call)) {}
    };


    class Call : public Production {
    public:
        size_t line;
        SharedPtr<Primary> primary;
        SharedPtr<Call_suffix> call_suffix;

        Call(size_t line, SharedPtr<Primary> primary, SharedPtr<Call_suffix> call_suffix)
                : line(line),
                  primary(std::move(primary)),
                  call_suffix(std::move(call_suffix)) { thisSymbol = symbol::Symbol::call; }

        String toString() override { return String{"Call"}; }
    };


    class Call_suffix : public Production {
    public:
        size_t line;

        explicit Call_suffix(size_t line) : line(line) { thisSymbol = symbol::Symbol::call_suffix; }

        ~Call_suffix() override = default;

        String toString() override { return String{"Call_suffix"}; }
    };

    class Call_suffix1 : public Call_suffix {
    public:
        SharedPtr<Token> token_LEFT_PAREN;
        SharedPtr<ArgList> argList;
        SharedPtr<Token> token_RIGHT_PAREN;
        SharedPtr<Call_suffix> call_suffix;

        Call_suffix1(size_t line, SharedPtr<Token> token_LEFT_PAREN, SharedPtr<ArgList> argList,
                     SharedPtr<Token> token_RIGHT_PAREN, SharedPtr<Call_suffix> call_suffix)
                : Call_suffix(line),
                  token_LEFT_PAREN(std::move(token_LEFT_PAREN)),
                  argList(std::move(argList)),
                  token_RIGHT_PAREN(std::move(token_RIGHT_PAREN)),
                  call_suffix(std::move(call_suffix)) {}
    };


    class Call_suffix2 : public Call_suffix {
    public:
        explicit Call_suffix2(size_t line) : Call_suffix(line) {}
    };


    class ArgList : public Production {
    public:
        size_t line;

        explicit ArgList(size_t line) : line(line) { thisSymbol = symbol::Symbol::argList; }

        ~ArgList() override = default;

        String toString() override { return String{"ArgList"}; }
    };

    class ArgList1 : public ArgList {
    public:
        SharedPtr<Expression> expression;
        SharedPtr<Arguments> arguments;

        ArgList1(size_t line, SharedPtr<Expression> expression, SharedPtr<Arguments> arguments)
                : ArgList(line),
                  expression(std::move(expression)),
                  arguments(std::move(arguments)) {}
    };


    class ArgList2 : public ArgList {
    public:
        explicit ArgList2(size_t line) : ArgList(line) {}
    };


    class Arguments : public Production {
    public:
        size_t line;

        explicit Arguments(size_t line)
                : line(line) { thisSymbol = symbol::Symbol::arguments; }

        ~Arguments() override = default;

        String toString() override { return String{"Arguments"}; }
    };

    class Arguments1 : public Arguments {
    public:
        SharedPtr<Token> token_COMMA;
        SharedPtr<Expression> expression;
        SharedPtr<Arguments> arguments;

        Arguments1(size_t line, SharedPtr<Token> token_COMMA, SharedPtr<Expression> expression,
                   SharedPtr<Arguments> arguments) : Arguments(line),
                                                     token_COMMA(std::move(token_COMMA)),
                                                     expression(std::move(expression)),
                                                     arguments(std::move(arguments)) {}
    };


    class Arguments2 : public Arguments {
    public:
        explicit Arguments2(size_t line) : Arguments(line) {}
    };


    class Primary : public Production {
    public:
        size_t line;

        explicit Primary(size_t line)
                : line(line) { thisSymbol = symbol::Symbol::primary; }

        ~Primary() override = default;

        String toString() override { return String{"Primary"}; }
    };

    class Primary1 : public Primary {
    public:
        SharedPtr<ConstVal> constVal;

        Primary1(size_t line, SharedPtr<ConstVal> constVal)
                : Primary(line), constVal(std::move(constVal)) {}
    };


    class Primary2 : public Primary {
    public:
        SharedPtr<Token> token_LEFT_PAREN;
        SharedPtr<Expression> expression;
        SharedPtr<Token> token_RIGHT_PAREN;

        Primary2(size_t line, SharedPtr<Token> token_LEFT_PAREN, SharedPtr<Expression> expression,
                 SharedPtr<Token> token_RIGHT_PAREN) : Primary(line),
                                                       token_LEFT_PAREN(std::move(token_LEFT_PAREN)),
                                                       expression(std::move(expression)),
                                                       token_RIGHT_PAREN(std::move(token_RIGHT_PAREN)) {}
    };


    class Primary3 : public Primary {
    public:
        SharedPtr<Var> var;

        Primary3(size_t line, SharedPtr<Var> var)
                : Primary(line), var(std::move(var)) {}
    };


    class ConstVal : public Production {
    public:
        size_t line;

        explicit ConstVal(size_t line)
                : line(line) { thisSymbol = symbol::Symbol::constVal; }

        ~ConstVal() override = default;

        String toString() override { return String{"ConstVal"}; }
    };

    class ConstVal1 : public ConstVal {
    public:
        SharedPtr<Token> token_TRUE;

        ConstVal1(size_t line, SharedPtr<Token> token_TRUE)
                : ConstVal(line), token_TRUE(std::move(token_TRUE)) {}
    };


    class ConstVal2 : public ConstVal {
    public:
        SharedPtr<Token> token_FALSE;

        ConstVal2(size_t line, SharedPtr<Token> token_FALSE)
                : ConstVal(line), token_FALSE(std::move(token_FALSE)) {}
    };


    class ConstVal3 : public ConstVal {
    public:
        SharedPtr<Token> token_NIL;

        ConstVal3(size_t line, SharedPtr<Token> token_NIL)
                : ConstVal(line), token_NIL(std::move(token_NIL)) {}
    };


    class ConstVal4 : public ConstVal {
    public:
        SharedPtr<Token> token_INT_;

        ConstVal4(size_t line, SharedPtr<Token> token_INT_)
                : ConstVal(line), token_INT_(std::move(token_INT_)) {}
    };


    class ConstVal5 : public ConstVal {
    public:
        SharedPtr<Token> token_REAL_;

        ConstVal5(size_t line, SharedPtr<Token> token_REAL_)
                : ConstVal(line), token_REAL_(std::move(token_REAL_)) {}
    };


    class ConstVal6 : public ConstVal {
    public:
        SharedPtr<Token> token_STRING_;

        ConstVal6(size_t line, SharedPtr<Token> token_STRING_)
                : ConstVal(line), token_STRING_(std::move(token_STRING_)) {}
    };


    class Var : public Production {
    public:
        size_t line;
        SharedPtr<Token> token_IDENTIFIER;
        SharedPtr<VarSuffix> varSuffix;

        Var(size_t line, SharedPtr<Token> token_IDENTIFIER, SharedPtr<VarSuffix> varSuffix)
                : line(line),
                  token_IDENTIFIER(std::move(token_IDENTIFIER)),
                  varSuffix(std::move(varSuffix)) { thisSymbol = symbol::Symbol::var; }

        String toString() override { return String{"Var"}; }
    };


    class VarSuffix : public Production {
    public:
        size_t line;

        explicit VarSuffix(size_t line) : line(line) { thisSymbol = symbol::Symbol::varSuffix; }

        ~VarSuffix() override = default;

        String toString() override { return String{"VarSuffix"}; }
    };

    class VarSuffix1 : public VarSuffix {
    public:
        SharedPtr<Token> token_LEFT_BRACKET;
        SharedPtr<Expression> expression;
        SharedPtr<Token> token_RIGHT_BRACKET;
        SharedPtr<VarSuffix> varSuffix;

        VarSuffix1(size_t line, SharedPtr<Token> token_LEFT_BRACKET, SharedPtr<Expression> expression,
                   SharedPtr<Token> token_RIGHT_BRACKET, SharedPtr<VarSuffix> varSuffix)
                : VarSuffix(line),
                  token_LEFT_BRACKET(std::move(token_LEFT_BRACKET)),
                  expression(std::move(expression)),
                  token_RIGHT_BRACKET(std::move(token_RIGHT_BRACKET)),
                  varSuffix(std::move(varSuffix)) {}
    };


    class VarSuffix2 : public VarSuffix {
    public:
        explicit VarSuffix2(size_t line) : VarSuffix(line) {}
    };


    //////接下来是token对应的production类
    class Token : public Production {
    public:
        size_t line;
        token::Token thisToken;

        Token(size_t line, token::Token thisToken) : line(line), thisToken(
                std::move(thisToken)) { thisSymbol = tokenToSym[thisToken.getType()]; }

        String toString() override {
            if (thisToken.getType() == token::TokenType::TOKEN_INT_ ||
                thisToken.getType() == token::TokenType::TOKEN_REAL_ ||
                thisToken.getType() == token::TokenType::TOKEN_STRING_)
                return thisToken.getLiteralString();
            else if (thisToken.getType() == token::TokenType::TOKEN_EOF)
                return "EOF";
            return thisToken.getLexeme();
        }
    };

}

#endif //ROBIN_PRODUCTION_H
