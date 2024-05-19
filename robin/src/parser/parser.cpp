//
// Created by icelake on 24-5-16.
//

#include "../error/error.h"
#include "parser.h"

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

    void Parser::printInfo(const String &message) {
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
            std::cerr << "ReducedProduction's index " << index << "is out of range" << std::endl;
            hasError = true;
            return false;
        }
    }


    Parser::Parser(List<token::Token> tokens) : tokens(std::move(tokens)) {}

    List<SharedPtr<production::Production>> Parser::parserAst() {
        stateStack.push(0);
        while (true) {
            //preAction,先处理goto操作;
            if (!productions.empty()) {
                symbol::Symbol preSymbol = productions.back()->thisSymbol;
                State preState = stateStack.top();
                auto preAction = slrTable.find({preState, preSymbol});
                if (preAction->second.type == symbol::Type::Goto) {
                    printInfo("before goto");
                    stateStack.push(preAction->second.state);
                }
            }

            //action,处理shift,reduce,accept,error操作;
            if (isAtTokenListEnd()) {
                std::cerr << "reach the end of tokenList! Input is parsed! But there are some problems." << std::endl;
                hasError = true;
                return productions;
            }
            token::Token token = peek();
            symbol::Symbol currentSymbol = production::Production::tokenToSym[token.getType()];
            State currentState = stateStack.top();
            auto action = slrTable.find({currentState, currentSymbol});

            switch (action->second.type) {
                case symbol::Type::Shift: {
                    printInfo("before shift");
                    if (isAtTokenListEnd()) {
                        std::cerr << "reach the end of tokenList! Input is parsed! But there are some problems." << std::endl;
                        hasError = true;
                        return productions;
                    }
                    if (action == slrTable.end()) {
                        reportParserError(this, tokens[currentToken], "this token is not in the SLR Table");
                        hasError = true;
                        break;
                    }
                    token::Token thisToken = advance();
                    stateStack.push(action->second.state);
                    productions.push_back(std::make_shared<production::Token>(thisToken.getLine(), thisToken));
                    break;
                }
                case symbol::Type::Reduce:
                    printInfo("before reduce");
                    callReduceFunctionByIndex(action->second.state);
                    break;
                case symbol::Type::Accept:
                    printInfo("before accept");
                    if (hasError) {
                        std::cerr << "Input is parsed! But there are some problems." << std::endl;
                    } else
                        std::cout << "Input is successfully parsed!" << std::endl;
                    return productions;
                case symbol::Type::Error:
                    printInfo("before reportParserError");
                    if (isAtTokenListEnd()) {
                        std::cerr << "reach the end of tokenList! Input is parsed! But there are some problems." << std::endl;
                        hasError = true;
                        return productions;
                    }
                    reportParserError(this, tokens[currentToken], "Syntax Error at this token");
                    advance();
                    break;
                default:
                    std::cerr << "enter the reportParserError goto branch in action" << std::endl;
                    hasError = true;
            }
        }
        std::cerr << "enter the reportParserError branch" << std::endl;
        return productions;
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


}
