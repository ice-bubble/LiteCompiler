

#ifndef ROBIN_PRODUCTION_H
#define ROBIN_PRODUCTION_H

#include "symboltable.h"
#include "type.h"
#include "../common.h"
#include "../token/token.h"
#include "../ast/symbol.h"
#include "../sema/sema.h"

namespace production {

    enum Usage {
        reference,
        define
    };

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


    void mergeUniqueIntoA(List<size_t> *a, List<size_t> *b);

    class Production {
    public:
        static Map<token::TokenType, symbol::Symbol> tokenToSym;

        symbol::Symbol thisSymbol = symbol::Symbol::BASE;

        virtual void visit(sema::Sema *semaAna) = 0;

        static String autoConversion(String originName, ast::IdentifierType originType,
                                     ast::IdentifierType expectType, size_t line, sema::Sema *semaAna);

        static Pair<String, ast::IdentifierType> autoConversion(String leftName, ast::IdentifierType leftType,
                                                                String rightName, ast::IdentifierType rightType,
                                                                String op, size_t line, sema::Sema *semaAna);

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

        void visit(sema::Sema *semaAna) override;
    };


    class Program : public Production {
    public:
        size_t line;
        SharedPtr<Declarations> declarations;

        Program(size_t line, SharedPtr<Declarations> declarations)
                : line(line), declarations(std::move(declarations)) { thisSymbol = symbol::Symbol::program; }

        String toString() override { return String{"Program"}; }

        void visit(sema::Sema *semaAna) override;
    };


    class Declarations : public Production {
    public:
        size_t line;

        SharedPtr<ast::Type> returnType;
        List<size_t> *code1Jmp = nullptr;
        List<size_t> *nextJmp = nullptr;

        explicit Declarations(size_t line) : line(line) { thisSymbol = symbol::Symbol::declarations; }

        ~Declarations() override = default;

        String toString() override { return String{"Declarations"}; }

        void visit(sema::Sema *semaAna) override;
    };

    class Declarations1 : public Declarations {
    public:
        SharedPtr<Declaration> declaration;
        SharedPtr<Declarations> declarations;

        Declarations1(size_t line, SharedPtr<Declaration> declaration, SharedPtr<Declarations> declarations)
                : Declarations(line),
                  declaration(std::move(declaration)),
                  declarations(std::move(declarations)) {}

        void visit(sema::Sema *semaAna) override;
    };


    class Declarations2 : public Declarations {
    public:
        explicit Declarations2(size_t line) : Declarations(line) {}

        void visit(sema::Sema *semaAna) override;
    };


    class Declaration : public Production {
    public:
        size_t line;

        SharedPtr<ast::Type> returnType;
        List<size_t> *code1Jmp = nullptr;
        List<size_t> *nextJmp = nullptr;

        explicit Declaration(size_t line) : line(line) { thisSymbol = symbol::Symbol::declaration; }

        ~Declaration() override = default;

        String toString() override { return String{"Declaration"}; }

        void visit(sema::Sema *semaAna) override;
    };

    class Declaration1 : public Declaration {
    public:
        SharedPtr<FunDecl> funDecl;

        Declaration1(size_t line, SharedPtr<FunDecl> funDecl)
                : Declaration(line), funDecl(std::move(funDecl)) {}

        void visit(sema::Sema *semaAna) override;
    };


    class Declaration2 : public Declaration {
    public:
        SharedPtr<VarDecl> varDecl;

        Declaration2(size_t line, SharedPtr<VarDecl> varDecl)
                : Declaration(line), varDecl(std::move(varDecl)) {}

        void visit(sema::Sema *semaAna) override;
    };


    class Declaration3 : public Declaration {
    public:
        SharedPtr<Statement> statement;

        Declaration3(size_t line, SharedPtr<Statement> statement)
                : Declaration(line), statement(std::move(statement)) {}

        void visit(sema::Sema *semaAna) override;
    };


    class Statement : public Production {
    public:
        size_t line;

        SharedPtr<ast::Type> returnType;
        List<size_t> *code1Jmp = nullptr;
        List<size_t> *nextJmp = nullptr;

        explicit Statement(size_t line) : line(line) { thisSymbol = symbol::Symbol::statement; }

        ~Statement() override = default;

        String toString() override { return String{"Statement"}; }

        void visit(sema::Sema *semaAna) override;
    };

    class Statement1 : public Statement {
    public:
        SharedPtr<BreakStmt> breakStmt;

        Statement1(size_t line, SharedPtr<BreakStmt> breakStmt)
                : Statement(line), breakStmt(std::move(breakStmt)) {}

        void visit(sema::Sema *semaAna) override;
    };


    class Statement2 : public Statement {
    public:
        SharedPtr<ContinueStmt> continueStmt;

        Statement2(size_t line, SharedPtr<ContinueStmt> continueStmt)
                : Statement(line), continueStmt(std::move(continueStmt)) {}

        void visit(sema::Sema *semaAna) override;
    };


    class Statement3 : public Statement {
    public:
        SharedPtr<ReturnStmt> returnStmt;

        Statement3(size_t line, SharedPtr<ReturnStmt> returnStmt)
                : Statement(line), returnStmt(std::move(returnStmt)) {}

        void visit(sema::Sema *semaAna) override;
    };


    class Statement4 : public Statement {
    public:
        SharedPtr<ExprStmt> exprStmt;

        Statement4(size_t line, SharedPtr<ExprStmt> exprStmt)
                : Statement(line), exprStmt(std::move(exprStmt)) {}

        void visit(sema::Sema *semaAna) override;
    };


    class Statement5 : public Statement {
    public:
        SharedPtr<IfStmt> ifStmt;

        Statement5(size_t line, SharedPtr<IfStmt> ifStmt)
                : Statement(line), ifStmt(std::move(ifStmt)) {}

        void visit(sema::Sema *semaAna) override;
    };


    class Statement6 : public Statement {
    public:
        SharedPtr<WhileStmt> whileStmt;

        Statement6(size_t line, SharedPtr<WhileStmt> whileStmt)
                : Statement(line), whileStmt(std::move(whileStmt)) {}

        void visit(sema::Sema *semaAna) override;
    };


    class Statement7 : public Statement {
    public:
        SharedPtr<RepeatStmt> repeatStmt;

        Statement7(size_t line, SharedPtr<RepeatStmt> repeatStmt)
                : Statement(line), repeatStmt(std::move(repeatStmt)) {}

        void visit(sema::Sema *semaAna) override;
    };


    class Statement8 : public Statement {
    public:
        SharedPtr<Block> block;

        Statement8(size_t line, SharedPtr<Block> block) : Statement(line), block(std::move(block)) {}

        void visit(sema::Sema *semaAna) override;
    };

    class Statement9 : public Statement {
    public:
        SharedPtr<ForStmt> forStmt;

        Statement9(size_t line, SharedPtr<ForStmt> forStmt) : Statement(line), forStmt(std::move(forStmt)) {}

        void visit(sema::Sema *semaAna) override;
    };


    class BreakStmt : public Production {
    public:
        size_t line;
        SharedPtr<Token> token_BREAK;
        SharedPtr<Token> token_SEMICOLON;

        List<size_t> *nextJmp = nullptr;

        BreakStmt(size_t line, SharedPtr<Token> token_BREAK, SharedPtr<Token> token_SEMICOLON)
                : line(line),
                  token_BREAK(std::move(token_BREAK)),
                  token_SEMICOLON(std::move(token_SEMICOLON)) { thisSymbol = symbol::Symbol::breakStmt; }

        String toString() override { return String{"BreakStmt"}; }

        void visit(sema::Sema *semaAna) override;
    };


    class ContinueStmt : public Production {
    public:
        size_t line;
        SharedPtr<Token> token_CONTINUE;
        SharedPtr<Token> token_SEMICOLON;

        List<size_t> *code1Jmp = nullptr;

        ContinueStmt(size_t line, SharedPtr<Token> token_CONTINUE, SharedPtr<Token> token_SEMICOLON)
                : line(line),
                  token_CONTINUE(std::move(token_CONTINUE)),
                  token_SEMICOLON(std::move(token_SEMICOLON)) { thisSymbol = symbol::Symbol::continueStmt; }

        String toString() override { return String{"ContinueStmt"}; }

        void visit(sema::Sema *semaAna) override;
    };


    class ReturnStmt : public Production {
    public:
        size_t line;
        SharedPtr<Token> token_RETURN;
        SharedPtr<ExprStmt> exprStmt;

        SharedPtr<ast::Type> returnType;

        ReturnStmt(size_t line, SharedPtr<Token> token_RETURN, SharedPtr<ExprStmt> exprStmt)
                : line(line),
                  token_RETURN(std::move(token_RETURN)),
                  exprStmt(std::move(exprStmt)) { thisSymbol = symbol::Symbol::returnStmt; }

        String toString() override { return String{"ReturnStmt"}; }

        void visit(sema::Sema *semaAna) override;
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

        String id;
        SharedPtr<ast::Type> returnType;

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

        void visit(sema::Sema *semaAna) override;
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

        void visit(sema::Sema *semaAna) override;
    };


    class VarDef : public Production {
    public:
        size_t line;
        SharedPtr<Var> var;
        SharedPtr<VarInit> varInit;

        String width = "0";
        SharedPtr<ast::Type> type;

        VarDef(size_t line, SharedPtr<Var> var, SharedPtr<VarInit> varInit)
                : line(line), var(std::move(var)),
                  varInit(std::move(varInit)) { thisSymbol = symbol::Symbol::varDef; }

        String toString() override { return String{"VarDef"}; }

        void visit(sema::Sema *semaAna) override;
    };


    class VarDefs : public Production {
    public:
        size_t line;

        String width = "0";
        SharedPtr<ast::Type> type;

        explicit VarDefs(size_t line) : line(line) { thisSymbol = symbol::Symbol::varDefs; }

        ~VarDefs() override = default;

        String toString() override { return String{"VarDefs"}; }

        void visit(sema::Sema *semaAna) override;
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

        void visit(sema::Sema *semaAna) override;
    };


    class VarDefs2 : public VarDefs {
    public:
        explicit VarDefs2(size_t line) : VarDefs(line) {}

        void visit(sema::Sema *semaAna) override;
    };


    class VarInit : public Production {
    public:
        size_t line;

        SharedPtr<ast::Type> type;
        String val;

        explicit VarInit(size_t line) : line(line) { thisSymbol = symbol::Symbol::varInit; }

        ~VarInit() override = default;

        String toString() override { return String{"VarInit"}; }

        void visit(sema::Sema *semaAna) override;
    };

    class VarInit1 : public VarInit {
    public:
        SharedPtr<Token> token_EQUAL;
        SharedPtr<Expression> expression;

        VarInit1(size_t line, SharedPtr<Token> token_EQUAL, SharedPtr<Expression> expression)
                : VarInit(line),
                  token_EQUAL(std::move(token_EQUAL)),
                  expression(std::move(expression)) {}

        void visit(sema::Sema *semaAna) override;
    };


    class VarInit2 : public VarInit {
    public:
        explicit VarInit2(size_t line) : VarInit(line) {}

        void visit(sema::Sema *semaAna) override;
    };


    class Type : public Production {
    public:
        size_t line;

        String width = "0";
        SharedPtr<ast::Type> type;

        explicit Type(size_t line) : line(line) { thisSymbol = symbol::Symbol::type; }

        ~Type() override = default;

        String toString() override { return String{"Type"}; }

        void visit(sema::Sema *semaAna) override;
    };

    class Type1 : public Type {
    public:
        SharedPtr<Token> token_INTEGER;

        Type1(size_t line, SharedPtr<Token> token_INTEGER) : Type(line), token_INTEGER(std::move(token_INTEGER)) {}

        void visit(sema::Sema *semaAna) override;
    };


    class Type2 : public Type {
    public:
        SharedPtr<Token> token_DOUBLE;

        Type2(size_t line, SharedPtr<Token> token_DOUBLE) : Type(line), token_DOUBLE(std::move(token_DOUBLE)) {}

        void visit(sema::Sema *semaAna) override;
    };


    class Type3 : public Type {
    public:
        SharedPtr<Token> token_STRING;

        Type3(size_t line, SharedPtr<Token> token_STRING) : Type(line), token_STRING(std::move(token_STRING)) {}

        void visit(sema::Sema *semaAna) override;
    };


    class Type4 : public Type {
    public:
        SharedPtr<Token> token_BOOL;

        Type4(size_t line, SharedPtr<Token> token_BOOL) : Type(line), token_BOOL(std::move(token_BOOL)) {}

        void visit(sema::Sema *semaAna) override;
    };


    class Type5 : public Type {
    public:
        SharedPtr<Token> token_CHAR;

        Type5(size_t line, SharedPtr<Token> token_CHAR) : Type(line), token_CHAR(std::move(token_CHAR)) {}

        void visit(sema::Sema *semaAna) override;
    };


    class Type6 : public Type {
    public:
        SharedPtr<Token> token_VAR;

        Type6(size_t line, SharedPtr<Token> token_VAR) : Type(line), token_VAR(std::move(token_VAR)) {}

        void visit(sema::Sema *semaAna) override;
    };


    class ExprStmt : public Production {
    public:
        size_t line;

        String val;
        SharedPtr<ast::Type> type;
        SharedPtr<ast::Type> returnType;
        bool jmp = false;
        List<size_t> *trueJmp = nullptr;
        List<size_t> *falseJmp = nullptr;

        explicit ExprStmt(size_t line) : line(line) { thisSymbol = symbol::Symbol::exprStmt; }

        ~ExprStmt() override = default;

        String toString() override { return String{"ExprStmt"}; }

        void visit(sema::Sema *semaAna) override;
    };

    class ExprStmt1 : public ExprStmt {
    public:
        SharedPtr<Expression> expression;
        SharedPtr<Token> token_SEMICOLON;

        ExprStmt1(size_t line, SharedPtr<Expression> expression, SharedPtr<Token> token_SEMICOLON)
                : ExprStmt(line),
                  expression(std::move(expression)),
                  token_SEMICOLON(std::move(token_SEMICOLON)) {}

        void visit(sema::Sema *semaAna) override;
    };


    class ExprStmt2 : public ExprStmt {
    public:
        SharedPtr<Token> token_SEMICOLON;

        ExprStmt2(size_t line, SharedPtr<Token> token_SEMICOLON)
                : ExprStmt(line), token_SEMICOLON(std::move(token_SEMICOLON)) {}

        void visit(sema::Sema *semaAna) override;
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

        SharedPtr<ast::Type> returnType;
        List<size_t> *code1Jmp = nullptr;
        List<size_t> *nextJmp = nullptr;

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

        void visit(sema::Sema *semaAna) override;
    };


    class ElseBranch : public Production {
    public:
        size_t line;

        SharedPtr<ast::Type> returnType;
        List<size_t> *code1Jmp = nullptr;
        List<size_t> *nextJmp = nullptr;
        bool ifExist=false;

        explicit ElseBranch(size_t line) : line(line) { thisSymbol = symbol::Symbol::elseBranch; }

        ~ElseBranch() override = default;

        String toString() override { return String{"ElseBranch"}; }

        void visit(sema::Sema *semaAna) override;
    };

    class ElseBranch1 : public ElseBranch {
    public:
        SharedPtr<Token> token_ELSE;
        SharedPtr<Statement> statement;

        ElseBranch1(size_t line, SharedPtr<Token> token_ELSE, SharedPtr<Statement> statement)
                : ElseBranch(line),
                  token_ELSE(std::move(token_ELSE)),
                  statement(std::move(statement)) {}

        void visit(sema::Sema *semaAna) override;
    };


    class ElseBranch2 : public ElseBranch {
    public:
        explicit ElseBranch2(size_t line) : ElseBranch(line) {}

        void visit(sema::Sema *semaAna) override;
    };


    class WhileStmt : public Production {
    public:
        size_t line;
        SharedPtr<Token> token_WHILE;
        SharedPtr<Token> token_LEFT_PAREN;
        SharedPtr<Expression> expression;
        SharedPtr<Token> token_RIGHT_PAREN;
        SharedPtr<Statement> statement;

        SharedPtr<ast::Type> returnType;

        WhileStmt(size_t line, SharedPtr<Token> token_WHILE, SharedPtr<Token> token_LEFT_PAREN,
                  SharedPtr<Expression> expression, SharedPtr<Token> token_RIGHT_PAREN, SharedPtr<Statement> statement)
                : line(line),
                  token_WHILE(std::move(token_WHILE)),
                  token_LEFT_PAREN(std::move(token_LEFT_PAREN)),
                  expression(std::move(expression)),
                  token_RIGHT_PAREN(std::move(token_RIGHT_PAREN)),
                  statement(std::move(statement)) { thisSymbol = symbol::Symbol::whileStmt; }

        String toString() override { return String{"WhileStmt"}; }

        void visit(sema::Sema *semaAna) override;
    };


    class ForStmt : public Production {
    public:
        size_t line;

        SharedPtr<ast::Type> returnType;

        explicit ForStmt(size_t line) : line(line) { thisSymbol = symbol::Symbol::forStmt; }

        ~ForStmt() override = default;

        String toString() override { return String{"ForStmt"}; }

        void visit(sema::Sema *semaAna) override;
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

        void visit(sema::Sema *semaAna) override;
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

        void visit(sema::Sema *semaAna) override;
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

        void visit(sema::Sema *semaAna) override;
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

        void visit(sema::Sema *semaAna) override;
    };


    class Block : public Production {
    public:
        size_t line;
        SharedPtr<Token> token_LEFT_BRACE;
        SharedPtr<Declarations> declarations;
        SharedPtr<Token> token_RIGHT_BRACE;

        SharedPtr<ast::Type> returnType;
        List<size_t> *code1Jmp = nullptr;
        List<size_t> *nextJmp = nullptr;

        Block(size_t line, SharedPtr<Token> token_LEFT_BRACE, SharedPtr<Declarations> declarations,
              SharedPtr<Token> token_RIGHT_BRACE)
                : line(line),
                  token_LEFT_BRACE(std::move(token_LEFT_BRACE)),
                  declarations(std::move(declarations)),
                  token_RIGHT_BRACE(std::move(token_RIGHT_BRACE)) { thisSymbol = symbol::Symbol::block; }

        String toString() override { return String{"Block"}; }

        void visit(sema::Sema *semaAna) override;
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

        SharedPtr<ast::Type> returnType;

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

        void visit(sema::Sema *semaAna) override;
    };


    class ParamList : public Production {
    public:
        size_t line;

        explicit ParamList(size_t line) : line(line) { thisSymbol = symbol::Symbol::paramList; }

        ~ParamList() override = default;

        String toString() override { return String{"ParamList"}; }

        void visit(sema::Sema *semaAna) override;
    };

    class ParamList1 : public ParamList {
    public:
        SharedPtr<Parameter> parameter;
        SharedPtr<Parameters> parameters;

        ParamList1(size_t line, SharedPtr<Parameter> parameter, SharedPtr<Parameters> parameters)
                : ParamList(line),
                  parameter(std::move(parameter)),
                  parameters(std::move(parameters)) {}

        void visit(sema::Sema *semaAna) override;
    };


    class ParamList2 : public ParamList {
    public:
        explicit ParamList2(size_t line) : ParamList(line) {}

        void visit(sema::Sema *semaAna) override;
    };


    class Parameters : public Production {
    public:
        size_t line;

        explicit Parameters(size_t line) : line(line) { thisSymbol = symbol::Symbol::parameters; }

        ~Parameters() override = default;

        String toString() override { return String{"Parameters"}; }

        void visit(sema::Sema *semaAna) override;
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

        void visit(sema::Sema *semaAna) override;
    };


    class Parameters2 : public Parameters {
    public:
        explicit Parameters2(size_t line) : Parameters(line) {}

        void visit(sema::Sema *semaAna) override;
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

        void visit(sema::Sema *semaAna) override;
    };


    class Expression : public Production {
    public:
        size_t line;
        SharedPtr<Assignment> assignment;

        SharedPtr<ast::Type> type;
        String val;
        bool jmp = false;
        List<size_t> *trueJmp = nullptr;
        List<size_t> *falseJmp = nullptr;

        Expression(size_t line, SharedPtr<Assignment> assignment)
                : line(line),
                  assignment(std::move(assignment)) { thisSymbol = symbol::Symbol::expression; }

        String toString() override { return String{"Expression"}; }

        void visit(sema::Sema *semaAna) override;
    };


    class Assignment : public Production {
    public:
        size_t line;

        SharedPtr<ast::Type> type;
        String val;
        bool jmp = false;
        List<size_t> *trueJmp = nullptr;
        List<size_t> *falseJmp = nullptr;

        explicit Assignment(size_t line) : line(line) { thisSymbol = symbol::Symbol::assignment; }

        ~Assignment() override = default;

        String toString() override { return String{"Assignment"}; }

        void visit(sema::Sema *semaAna) override;
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

        void visit(sema::Sema *semaAna) override;
    };


    class Assignment2 : public Assignment {
    public:
        SharedPtr<Logic_or> logic_or;

        Assignment2(size_t line, SharedPtr<Logic_or> logic_or) : Assignment(line), logic_or(std::move(logic_or)) {}

        void visit(sema::Sema *semaAna) override;
    };


    class Logic_or : public Production {
    public:
        size_t line;
        SharedPtr<Logic_and> logic_and;
        SharedPtr<Logic_or_prime> logic_or_prime;

        SharedPtr<ast::Type> type;
        String val;
        bool jmp = false;
        List<size_t> *trueJmp = nullptr;
        List<size_t> *falseJmp = nullptr;

        Logic_or(size_t line, SharedPtr<Logic_and> logic_and, SharedPtr<Logic_or_prime> logic_or_prime)
                : line(line),
                  logic_and(std::move(logic_and)),
                  logic_or_prime(std::move(logic_or_prime)) { thisSymbol = symbol::Symbol::logic_or; }

        String toString() override { return String{"Logic_or"}; }

        void visit(sema::Sema *semaAna) override;
    };


    class Logic_or_prime : public Production {
    public:
        size_t line;

        SharedPtr<ast::Type> type;
        String val;
        String op;
        bool jmp = false;
        List<size_t> *trueJmp = nullptr;
        List<size_t> *falseJmp = nullptr;

        explicit Logic_or_prime(size_t line) : line(line) { thisSymbol = symbol::Symbol::logic_or_prime; }

        ~Logic_or_prime() override = default;

        String toString() override { return String{"Logic_or_prime"}; }

        void visit(sema::Sema *semaAna) override;
    };

    class Logic_or_prime1 : public Logic_or_prime {
    public:
        SharedPtr<Token> token_OR;
        SharedPtr<Logic_or> logic_or;

        Logic_or_prime1(size_t line, SharedPtr<Token> token_OR, SharedPtr<Logic_or> logic_or)
                : Logic_or_prime(line), token_OR(std::move(token_OR)), logic_or(std::move(logic_or)) {}

        void visit(sema::Sema *semaAna) override;
    };


    class Logic_or_prime2 : public Logic_or_prime {
    public:
        explicit Logic_or_prime2(size_t line) : Logic_or_prime(line) {}

        void visit(sema::Sema *semaAna) override;
    };


    class Logic_and : public Production {
    public:
        size_t line;
        SharedPtr<Equality> equality;
        SharedPtr<Logic_and_prime> logic_and_prime;

        SharedPtr<ast::Type> type;
        String val;
        bool jmp = false;
        List<size_t> *trueJmp = nullptr;
        List<size_t> *falseJmp = nullptr;

        Logic_and(size_t line, SharedPtr<Equality> equality, SharedPtr<Logic_and_prime> logic_and_prime)
                : line(line),
                  equality(std::move(equality)),
                  logic_and_prime(std::move(logic_and_prime)) { thisSymbol = symbol::Symbol::logic_and; }

        String toString() override { return String{"Logic_and"}; }

        void visit(sema::Sema *semaAna) override;
    };


    class Logic_and_prime : public Production {
    public:
        size_t line;

        SharedPtr<ast::Type> type;
        String val;
        String op;
        bool jmp = false;
        List<size_t> *trueJmp = nullptr;
        List<size_t> *falseJmp = nullptr;

        explicit Logic_and_prime(size_t line) : line(line) { thisSymbol = symbol::Symbol::logic_and_prime; }

        ~Logic_and_prime() override = default;

        String toString() override { return String{"Logic_and_prime"}; }

        void visit(sema::Sema *semaAna) override;
    };

    class Logic_and_prime1 : public Logic_and_prime {
    public:
        SharedPtr<Token> token_AND;
        SharedPtr<Logic_and> logic_and;

        Logic_and_prime1(size_t line, SharedPtr<Token> token_AND, SharedPtr<Logic_and> logic_and)
                : Logic_and_prime(line), token_AND(std::move(token_AND)), logic_and(std::move(logic_and)) {}

        void visit(sema::Sema *semaAna) override;
    };


    class Logic_and_prime2 : public Logic_and_prime {
    public:
        explicit Logic_and_prime2(size_t line) : Logic_and_prime(line) {}

        void visit(sema::Sema *semaAna) override;
    };


    class Equality : public Production {
    public:
        size_t line;
        SharedPtr<Comparison> comparison;
        SharedPtr<Equality_prime> equality_prime;

        SharedPtr<ast::Type> type;
        String val;

        Equality(size_t line, SharedPtr<Comparison> comparison, SharedPtr<Equality_prime> equality_prime)
                : line(line),
                  comparison(std::move(comparison)),
                  equality_prime(std::move(equality_prime)) { thisSymbol = symbol::Symbol::equality; }

        String toString() override { return String{"Equality"}; }

        void visit(sema::Sema *semaAna) override;
    };


    class Equality_prime : public Production {
    public:
        size_t line;

        SharedPtr<ast::Type> type;
        String val;
        String op;

        explicit Equality_prime(size_t line) : line(line) { thisSymbol = symbol::Symbol::equality_prime; }

        ~Equality_prime() override = default;

        String toString() override { return String{"Equality_prime"}; }

        void visit(sema::Sema *semaAna) override;
    };

    class Equality_prime1 : public Equality_prime {
    public:
        SharedPtr<Token> token_NOT_EQUAL;
        SharedPtr<Equality> equality;

        Equality_prime1(size_t line, SharedPtr<Token> token_NOT_EQUAL, SharedPtr<Equality> equality)
                : Equality_prime(line),
                  token_NOT_EQUAL(std::move(token_NOT_EQUAL)),
                  equality(std::move(equality)) {}

        void visit(sema::Sema *semaAna) override;
    };


    class Equality_prime2 : public Equality_prime {
    public:
        SharedPtr<Token> token_EQUAL_EQUAL;
        SharedPtr<Equality> equality;

        Equality_prime2(size_t line, SharedPtr<Token> token_EQUAL_EQUAL, SharedPtr<Equality> equality)
                : Equality_prime(line),
                  token_EQUAL_EQUAL(std::move(token_EQUAL_EQUAL)),
                  equality(std::move(equality)) {}

        void visit(sema::Sema *semaAna) override;
    };


    class Equality_prime3 : public Equality_prime {
    public:
        explicit Equality_prime3(size_t line) : Equality_prime(line) {}

        void visit(sema::Sema *semaAna) override;
    };


    class Comparison : public Production {
    public:
        size_t line;
        SharedPtr<Term> term;
        SharedPtr<Comparison_prime> comparison_prime;

        SharedPtr<ast::Type> type;
        String val;

        Comparison(size_t line, SharedPtr<Term> term, SharedPtr<Comparison_prime> comparison_prime)
                : line(line),
                  term(std::move(term)),
                  comparison_prime(std::move(comparison_prime)) { thisSymbol = symbol::Symbol::comparison; }

        String toString() override { return String{"Comparison"}; }

        void visit(sema::Sema *semaAna) override;
    };


    class Comparison_prime : public Production {
    public:
        size_t line;

        SharedPtr<ast::Type> type;
        String val;
        String op;

        explicit Comparison_prime(size_t line) : line(line) { thisSymbol = symbol::Symbol::comparison_prime; }

        ~Comparison_prime() override = default;

        String toString() override { return String{"Comparison_prime"}; }

        void visit(sema::Sema *semaAna) override;
    };

    class Comparison_prime1 : public Comparison_prime {
    public:
        SharedPtr<Token> token_GREATER;
        SharedPtr<Comparison> comparison;

        Comparison_prime1(size_t line, SharedPtr<Token> token_GREATER, SharedPtr<Comparison> comparison)
                : Comparison_prime(line),
                  token_GREATER(std::move(token_GREATER)),
                  comparison(std::move(comparison)) {}

        void visit(sema::Sema *semaAna) override;
    };


    class Comparison_prime2 : public Comparison_prime {
    public:
        SharedPtr<Token> token_GREATER_EQUAL;
        SharedPtr<Comparison> comparison;

        Comparison_prime2(size_t line, SharedPtr<Token> token_GREATER_EQUAL, SharedPtr<Comparison> comparison)
                : Comparison_prime(line),
                  token_GREATER_EQUAL(std::move(token_GREATER_EQUAL)),
                  comparison(std::move(comparison)) {}

        void visit(sema::Sema *semaAna) override;
    };


    class Comparison_prime3 : public Comparison_prime {
    public:
        SharedPtr<Token> token_LESS;
        SharedPtr<Comparison> comparison;

        Comparison_prime3(size_t line, SharedPtr<Token> token_LESS, SharedPtr<Comparison> comparison)
                : Comparison_prime(line),
                  token_LESS(std::move(token_LESS)),
                  comparison(std::move(comparison)) {}

        void visit(sema::Sema *semaAna) override;
    };


    class Comparison_prime4 : public Comparison_prime {
    public:
        SharedPtr<Token> token_LESS_EQUAL;
        SharedPtr<Comparison> comparison;

        Comparison_prime4(size_t line, SharedPtr<Token> token_LESS_EQUAL, SharedPtr<Comparison> comparison)
                : Comparison_prime(line),
                  token_LESS_EQUAL(std::move(token_LESS_EQUAL)),
                  comparison(std::move(comparison)) {}

        void visit(sema::Sema *semaAna) override;
    };


    class Comparison_prime5 : public Comparison_prime {
    public:
        explicit Comparison_prime5(size_t line) : Comparison_prime(line) {}

        void visit(sema::Sema *semaAna) override;
    };


    class Term : public Production {
    public:
        size_t line;
        SharedPtr<Factor> factor;
        SharedPtr<Term_prime> term_prime;

        SharedPtr<ast::Type> type;
        String val;

        Term(size_t line, SharedPtr<Factor> factor, SharedPtr<Term_prime> term_prime)
                : line(line),
                  factor(std::move(factor)),
                  term_prime(std::move(term_prime)) { thisSymbol = symbol::Symbol::term; }

        String toString() override { return String{"Term"}; }

        void visit(sema::Sema *semaAna) override;
    };


    class Term_prime : public Production {
    public:
        size_t line;

        SharedPtr<ast::Type> type;
        String val;
        String op;

        explicit Term_prime(size_t line) : line(line) { thisSymbol = symbol::Symbol::term_prime; }

        ~Term_prime() override = default;

        String toString() override { return String{"Term_prime"}; }

        void visit(sema::Sema *semaAna) override;
    };

    class Term_prime1 : public Term_prime {
    public:
        SharedPtr<Token> token_MINUS;
        SharedPtr<Term> term;

        Term_prime1(size_t line, SharedPtr<Token> token_MINUS, SharedPtr<Term> term)
                : Term_prime(line), token_MINUS(std::move(token_MINUS)), term(std::move(term)) {}

        void visit(sema::Sema *semaAna) override;
    };


    class Term_prime2 : public Term_prime {
    public:
        SharedPtr<Token> token_PLUS;
        SharedPtr<Term> term;

        Term_prime2(size_t line, SharedPtr<Token> token_PLUS, SharedPtr<Term> term)
                : Term_prime(line), token_PLUS(std::move(token_PLUS)), term(std::move(term)) {}

        void visit(sema::Sema *semaAna) override;
    };


    class Term_prime3 : public Term_prime {
    public:
        explicit Term_prime3(size_t line) : Term_prime(line) {}

        void visit(sema::Sema *semaAna) override;
    };


    class Factor : public Production {
    public:
        size_t line;
        SharedPtr<Incr_exp> incr_exp;
        SharedPtr<Factor_prime> factor_prime;

        SharedPtr<ast::Type> type;
        String val;

        Factor(size_t line, SharedPtr<Incr_exp> incr_exp, SharedPtr<Factor_prime> factor_prime)
                : line(line),
                  incr_exp(std::move(incr_exp)),
                  factor_prime(std::move(factor_prime)) { thisSymbol = symbol::Symbol::factor; }

        String toString() override { return String{"Factor"}; }

        void visit(sema::Sema *semaAna) override;
    };


    class Factor_prime : public Production {
    public:
        size_t line;

        SharedPtr<ast::Type> type;
        String val;
        String op;

        explicit Factor_prime(size_t line) : line(line) { thisSymbol = symbol::Symbol::factor_prime; }

        ~Factor_prime() override = default;

        String toString() override { return String{"Factor_prime"}; }

        void visit(sema::Sema *semaAna) override;
    };

    class Factor_prime1 : public Factor_prime {
    public:
        SharedPtr<Token> token_DIV;
        SharedPtr<Factor> factor;

        Factor_prime1(size_t line, SharedPtr<Token> token_DIV, SharedPtr<Factor> factor)
                : Factor_prime(line), token_DIV(std::move(token_DIV)), factor(std::move(factor)) {}

        void visit(sema::Sema *semaAna) override;
    };


    class Factor_prime2 : public Factor_prime {
    public:
        SharedPtr<Token> token_STAR;
        SharedPtr<Factor> factor;

        Factor_prime2(size_t line, SharedPtr<Token> token_STAR, SharedPtr<Factor> factor)
                : Factor_prime(line), token_STAR(std::move(token_STAR)), factor(std::move(factor)) {}

        void visit(sema::Sema *semaAna) override;
    };


    class Factor_prime3 : public Factor_prime {
    public:
        SharedPtr<Token> token_MOD;
        SharedPtr<Factor> factor;

        Factor_prime3(size_t line, SharedPtr<Token> token_MOD, SharedPtr<Factor> factor)
                : Factor_prime(line), token_MOD(std::move(token_MOD)), factor(std::move(factor)) {}

        void visit(sema::Sema *semaAna) override;
    };


    class Factor_prime4 : public Factor_prime {
    public:
        explicit Factor_prime4(size_t line) : Factor_prime(line) {}

        void visit(sema::Sema *semaAna) override;
    };


    class Incr_exp : public Production {
    public:
        size_t line;
        SharedPtr<Unary> unary;
        SharedPtr<Incr_op> incr_op;

        SharedPtr<ast::Type> type;
        String val;

        Incr_exp(size_t line, SharedPtr<Unary> unary, SharedPtr<Incr_op> incr_op)
                : line(line),
                  unary(std::move(unary)),
                  incr_op(std::move(incr_op)) { thisSymbol = symbol::Symbol::incr_exp; }

        String toString() override { return String{"Incr_exp"}; }

        void visit(sema::Sema *semaAna) override;
    };


    class Incr_op : public Production {
    public:
        size_t line;

        bool ifUsed = false;
        int val = 0;

        explicit Incr_op(size_t line) : line(line) { thisSymbol = symbol::Symbol::incr_op; }

        ~Incr_op() override = default;

        String toString() override { return String{"Incr_op"}; }

        void visit(sema::Sema *semaAna) override;
    };

    class Incr_op1 : public Incr_op {
    public:
        SharedPtr<Token> token_DOUBLE_ADD;
        SharedPtr<Incr_op> incr_op;

        Incr_op1(size_t line, SharedPtr<Token> token_DOUBLE_ADD, SharedPtr<Incr_op> incr_op)
                : Incr_op(line),
                  token_DOUBLE_ADD(std::move(token_DOUBLE_ADD)),
                  incr_op(std::move(incr_op)) {}

        void visit(sema::Sema *semaAna) override;
    };


    class Incr_op2 : public Incr_op {
    public:
        SharedPtr<Token> token_DOUBLE_MINUS;
        SharedPtr<Incr_op> incr_op;

        Incr_op2(size_t line, SharedPtr<Token> token_DOUBLE_MINUS, SharedPtr<Incr_op> incr_op)
                : Incr_op(line),
                  token_DOUBLE_MINUS(std::move(token_DOUBLE_MINUS)),
                  incr_op(std::move(incr_op)) {}

        void visit(sema::Sema *semaAna) override;
    };


    class Incr_op3 : public Incr_op {
    public:
        explicit Incr_op3(size_t line) : Incr_op(line) {}

        void visit(sema::Sema *semaAna) override;
    };


    class Unary : public Production {
    public:
        size_t line;

        SharedPtr<ast::Type> type;
        String val;

        explicit Unary(size_t line) : line(line) { thisSymbol = symbol::Symbol::unary; }

        ~Unary() override = default;

        String toString() override { return String{"Unary"}; }

        void visit(sema::Sema *semaAna) override;
    };

    class Unary1 : public Unary {
    public:
        SharedPtr<Token> token_NOT;
        SharedPtr<Unary> unary;

        Unary1(size_t line, SharedPtr<Token> token_NOT, SharedPtr<Unary> unary)
                : Unary(line),
                  token_NOT(std::move(token_NOT)),
                  unary(std::move(unary)) {}

        void visit(sema::Sema *semaAna) override;
    };


    class Unary2 : public Unary {
    public:
        SharedPtr<Token> token_MINUS;
        SharedPtr<Unary> unary;

        Unary2(size_t line, SharedPtr<Token> token_MINUS, SharedPtr<Unary> unary)
                : Unary(line),
                  token_MINUS(std::move(token_MINUS)),
                  unary(std::move(unary)) {}

        void visit(sema::Sema *semaAna) override;
    };


    class Unary3 : public Unary {
    public:
        SharedPtr<Call> call;

        Unary3(size_t line, SharedPtr<Call> call) : Unary(line), call(std::move(call)) {}

        void visit(sema::Sema *semaAna) override;
    };


    class Call : public Production {
    public:
        size_t line;
        SharedPtr<Primary> primary;
        SharedPtr<Call_suffix> call_suffix;

        SharedPtr<ast::Type> type;
        String val;

        Call(size_t line, SharedPtr<Primary> primary, SharedPtr<Call_suffix> call_suffix)
                : line(line),
                  primary(std::move(primary)),
                  call_suffix(std::move(call_suffix)) { thisSymbol = symbol::Symbol::call; }

        String toString() override { return String{"Call"}; }

        void visit(sema::Sema *semaAna) override;
    };


    class Call_suffix : public Production {
    public:
        size_t line;

        SharedPtr<ast::Type> type;
        String val;
        String callee;
        bool isExist = false;

        explicit Call_suffix(size_t line) : line(line) { thisSymbol = symbol::Symbol::call_suffix; }

        ~Call_suffix() override = default;

        String toString() override { return String{"Call_suffix"}; }

        void visit(sema::Sema *semaAna) override;
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

        void visit(sema::Sema *semaAna) override;
    };


    class Call_suffix2 : public Call_suffix {
    public:
        explicit Call_suffix2(size_t line) : Call_suffix(line) {}

        void visit(sema::Sema *semaAna) override;
    };


    class ArgList : public Production {
    public:
        size_t line;

        int sum = 0;

        explicit ArgList(size_t line) : line(line) { thisSymbol = symbol::Symbol::argList; }

        ~ArgList() override = default;

        String toString() override { return String{"ArgList"}; }

        void visit(sema::Sema *semaAna) override;
    };

    class ArgList1 : public ArgList {
    public:
        SharedPtr<Expression> expression;
        SharedPtr<Arguments> arguments;

        ArgList1(size_t line, SharedPtr<Expression> expression, SharedPtr<Arguments> arguments)
                : ArgList(line),
                  expression(std::move(expression)),
                  arguments(std::move(arguments)) {}

        void visit(sema::Sema *semaAna) override;
    };


    class ArgList2 : public ArgList {
    public:
        explicit ArgList2(size_t line) : ArgList(line) {}

        void visit(sema::Sema *semaAna) override;
    };


    class Arguments : public Production {
    public:
        size_t line;

        int sum = 0;

        explicit Arguments(size_t line)
                : line(line) { thisSymbol = symbol::Symbol::arguments; }

        ~Arguments() override = default;

        String toString() override { return String{"Arguments"}; }

        void visit(sema::Sema *semaAna) override;
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

        void visit(sema::Sema *semaAna) override;
    };


    class Arguments2 : public Arguments {
    public:
        explicit Arguments2(size_t line) : Arguments(line) {}

        void visit(sema::Sema *semaAna) override;
    };


    class Primary : public Production {
    public:
        size_t line;

        SharedPtr<ast::Type> type;
        String val;

        explicit Primary(size_t line)
                : line(line) { thisSymbol = symbol::Symbol::primary; }

        ~Primary() override = default;

        String toString() override { return String{"Primary"}; }

        void visit(sema::Sema *semaAna) override;
    };

    class Primary1 : public Primary {
    public:
        SharedPtr<ConstVal> constVal;

        Primary1(size_t line, SharedPtr<ConstVal> constVal)
                : Primary(line), constVal(std::move(constVal)) {}

        void visit(sema::Sema *semaAna) override;
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

        void visit(sema::Sema *semaAna) override;
    };


    class Primary3 : public Primary {
    public:
        SharedPtr<Var> var;

        Primary3(size_t line, SharedPtr<Var> var)
                : Primary(line), var(std::move(var)) {}

        void visit(sema::Sema *semaAna) override;
    };


    class ConstVal : public Production {
    public:
        size_t line;

        SharedPtr<ast::Type> type;
        String val;

        explicit ConstVal(size_t line)
                : line(line) { thisSymbol = symbol::Symbol::constVal; }

        ~ConstVal() override = default;

        String toString() override { return String{"ConstVal"}; }

        void visit(sema::Sema *semaAna) override;
    };

    class ConstVal1 : public ConstVal {
    public:
        SharedPtr<Token> token_TRUE;

        ConstVal1(size_t line, SharedPtr<Token> token_TRUE)
                : ConstVal(line), token_TRUE(std::move(token_TRUE)) {}

        void visit(sema::Sema *semaAna) override;
    };


    class ConstVal2 : public ConstVal {
    public:
        SharedPtr<Token> token_FALSE;

        ConstVal2(size_t line, SharedPtr<Token> token_FALSE)
                : ConstVal(line), token_FALSE(std::move(token_FALSE)) {}

        void visit(sema::Sema *semaAna) override;
    };


    class ConstVal3 : public ConstVal {
    public:
        SharedPtr<Token> token_NIL;

        ConstVal3(size_t line, SharedPtr<Token> token_NIL)
                : ConstVal(line), token_NIL(std::move(token_NIL)) {}

        void visit(sema::Sema *semaAna) override;
    };


    class ConstVal4 : public ConstVal {
    public:
        SharedPtr<Token> token_INT_;

        ConstVal4(size_t line, SharedPtr<Token> token_INT_)
                : ConstVal(line), token_INT_(std::move(token_INT_)) {}

        void visit(sema::Sema *semaAna) override;
    };


    class ConstVal5 : public ConstVal {
    public:
        SharedPtr<Token> token_REAL_;

        ConstVal5(size_t line, SharedPtr<Token> token_REAL_)
                : ConstVal(line), token_REAL_(std::move(token_REAL_)) {}

        void visit(sema::Sema *semaAna) override;
    };


    class ConstVal6 : public ConstVal {
    public:
        SharedPtr<Token> token_STRING_;

        ConstVal6(size_t line, SharedPtr<Token> token_STRING_)
                : ConstVal(line), token_STRING_(std::move(token_STRING_)) {}

        void visit(sema::Sema *semaAna) override;
    };


    class Var : public Production {
    public:
        size_t line;
        SharedPtr<Token> token_IDENTIFIER;
        SharedPtr<VarSuffix> varSuffix;

        String w = "0";
        SharedPtr<ast::Type> t;
        String width = "0";
        SharedPtr<ast::Type> type;
        String offset = "0";
        String id;
        String val;
        Usage usage = Usage::reference;

        Var(size_t line, SharedPtr<Token> token_IDENTIFIER, SharedPtr<VarSuffix> varSuffix)
                : line(line),
                  token_IDENTIFIER(std::move(token_IDENTIFIER)),
                  varSuffix(std::move(varSuffix)) { thisSymbol = symbol::Symbol::var; }

        String toString() override { return String{"Var"}; }

        void visit(sema::Sema *semaAna) override;
    };


    class VarSuffix : public Production {
    public:
        size_t line;

        String w = "0";
        SharedPtr<ast::Type> t;
        String width = "0";
        SharedPtr<ast::Type> type;
        SharedPtr<ast::Type> returnType;
        String len = "0";
        String length = "0";
        String offset = "0";
        Usage usage = Usage::reference;


        explicit VarSuffix(size_t line) : line(line) { thisSymbol = symbol::Symbol::varSuffix; }

        ~VarSuffix() override = default;

        String toString() override { return String{"VarSuffix"}; }

        void visit(sema::Sema *semaAna) override;
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

        void visit(sema::Sema *semaAna) override;
    };


    class VarSuffix2 : public VarSuffix {
    public:
        explicit VarSuffix2(size_t line) : VarSuffix(line) {}

        void visit(sema::Sema *semaAna) override;
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

        void visit(sema::Sema *semaAna) override;
    };

}

#endif //ROBIN_PRODUCTION_H
