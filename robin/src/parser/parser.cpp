

#include "../error/error.h"
#include "parser.h"

#define ERRORRETURN(msg)        std::cerr << msg << std::endl;       \
                                hasError = true;                     \
                                return productions;                  \

namespace parser {

    void Parser::printProductionStack() {
        std::cout << "Symbol Stack: ";
        if (productions.empty()) return;
        for (const auto &it: productions) {
            std::cout << it->toString() << " ";
        }
        std::cout << std::endl;
    }

    void Parser::printStateStack() {
        std::cout << "State Stack: ";
        if (stateStack.empty()) return;
        std::stack<State> tempStack;
        while (!stateStack.empty()) {
            tempStack.push(stateStack.top());
            stateStack.pop();
        }

        // 从辅助栈中依次取出元素并打印
        while (!tempStack.empty()) {
            std::cout << tempStack.top() << " ";
            stateStack.push(tempStack.top());
            tempStack.pop();
        }

        std::cout << std::endl;
    }

    void Parser::printInfo(StringView message) {
        std::cout << std::endl << message << std::endl;
        printStateStack();
        printProductionStack();
        std::cout << std::endl;
    }

    bool Parser::callReduceFunctionByIndex(size_t index) {
        if (index < ReduceFunctions.size()) {
            (this->*ReduceFunctions[index])();
            return true;
        } else {
            fmt::print(stderr, "ReducedProduction's index {} is out of range\n", index);
            hasError = true;
            return false;
        }
    }


    Parser::Parser(List<token::Token> tokens) : tokens(std::move(tokens)) {}

    List<SharedPtr<production::Production>> Parser::parserAst() {
        stateStack.push(0);
        while (true) {
#ifdef PRINT_PARSER_PROCESS
            printInfo("enter loop");
#endif
            //preAction,先处理goto操作;
            if (!productions.empty()) {
                symbol::Symbol preSymbol = productions.back()->thisSymbol;
                State preState = stateStack.top();
                auto preAction = slrTable.find({preState, preSymbol});
                if (preAction->second.type == symbol::Type::Goto) {
                    //printInfo("before goto");
                    stateStack.push(preAction->second.state);
                }
            }

            //action,处理shift,reduce,accept,error操作;
            if (isAtTokenListEnd()) { ERRORRETURN("reach the end of tokenList! Input is parsed!") }
            symbol::Symbol currentSymbol = production::Production::tokenToSym[peek().getType()];
            State currentState = stateStack.top();

            // 消除冲突
            if (currentState == 7 && currentSymbol == symbol::Symbol::EQUAL) {
                token::Token nextToken = peekNext();
                if (nextToken.getType() == token::TokenType::TOKEN_FUNCTION) {
                    slrTable[{7, symbol::Symbol::EQUAL}] = {symbol::Type::Shift, 57};
                } else {
                    slrTable[{7, symbol::Symbol::EQUAL}] = {symbol::Type::Reduce, 102};
                }
            }
            auto action = slrTable.find({currentState, currentSymbol});

            if (action == slrTable.end()) {
                reportParserError(this, tokens[currentToken],
                                  "this token is not in the SLR Table");
                hasError = true;
                return productions;
            }


            switch (action->second.type) {
                case symbol::Type::Shift: {
#ifdef PRINT_PARSER_PROCESS
                    printInfo("before shift");
#endif
                    if (isAtTokenListEnd()) { ERRORRETURN("reach the end of tokenList! Input is parsed!") }

                    token::Token thisToken = advance();
                    stateStack.push(action->second.state);
                    productions.push_back(std::make_shared<production::Token>(thisToken.getLine(), thisToken));
                    break;
                }
                case symbol::Type::Reduce:
#ifdef PRINT_PARSER_PROCESS
                    printInfo("before reduce");
#endif
                    //规约，出错直接结束语法分析
                    if (!callReduceFunctionByIndex(action->second.state))
                        return productions;
                    break;
                case symbol::Type::Accept:
#ifdef PRINT_PARSER_PROCESS
                    printInfo("before accept");
#endif
                    fmt::print("\nInput is parsed!\n");
                    return productions;
                case symbol::Type::Error:
                    printInfo("before reportParserError");
                    if (isAtTokenListEnd()) { ERRORRETURN("reach the end of tokenList! Input is parsed!") }
                    if (!errorProcess(action->second.state)) {
                        ERRORRETURN("reach the end of tokenList or ended due to unexpected error")
                    }
                    break;
                default:
                ERRORRETURN("enter the reportParserError goto branch in action")
            }
        }
    }

    bool Parser::isAtTokenListEnd() {
        return currentToken >= tokens.size();
    }

    token::Token Parser::advance() {
        currentToken++;
        return tokens[currentToken - 1];
    }

    token::Token Parser::peek() {
        return tokens[currentToken];
    }

    token::Token Parser::peekNext() {
        if (currentToken + 1 >= tokens.size())
            return {token::TOKEN_EOF, "", std::any{}, 0};
        return tokens[currentToken + 1];
    }


    Map<Pair<State, symbol::Symbol>, Action> Parser::slrTable = {};

    void Parser::slrTableInit() {
        slrTableInit1();
        slrTableInit2();
        slrTableInit3();
        slrTableInit4();
        slrTableInit5();
        slrTableInit6();
        slrTableInit7();
        slrTableInit8();
        slrTableInit9();
    }

}

#undef ERRORRETURN//(msg)