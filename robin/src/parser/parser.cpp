//
// Created by icelake on 24-5-16.
//

#include "parser.h"

namespace parser {

    void Parser::printProductionStack() {
        std::cout << "Symbol Stack: ";
        for (const auto &it: productions) {
            std::cout << it->toString() << " ";
        }
        std::cout << std::endl;
    }

    void Parser::printStateStack() {
        std::cout << "State Stack: ";
        List<State> auxStateList;
        while (!stateStack.empty()) {
            auxStateList.push_back(stateStack.top());
            stateStack.pop();
        }
        for (auto s: auxStateList) {
            std::cout << s << " ";
            stateStack.push(s);
        }
        std::cout << std::endl;
    }

    bool Parser::callReduceFunctionByIndex(size_t index) {
        if (index < ReduceFunctions.size()) {
            (this->*ReduceFunctions[index])();
            return true;
        } else {
            std::cerr << "ReducedProduction's index " << index << "is out of range" << std::endl;
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
                    stateStack.push(preAction->second.state);
                }
            }

            //action,然后处理shift,reduce,accept,error操作;
            if (isAtTokenListEnd()) {
                std::cerr << "reach the end of tokenList! Failed to parse." << std::endl;
                return productions;
            }
            token::Token token = peek();
            symbol::Symbol currentSymbol = production::Production::tokenToSym[token.getType()];
            State currentState = stateStack.top();
            auto action = slrTable.find({currentState, currentSymbol});

            if (action == slrTable.end()) {
                error(tokens[currentToken], "this token is not in the SLR Table");
                break;
            }
            switch (action->second.type) {
                case symbol::Type::Shift: {
                    token::Token thisToken = advance();
                    stateStack.push(action->second.state);
                    productions.push_back(std::make_shared<production::Token>(thisToken.getLine(), thisToken));
                    printStateStack();
                    printProductionStack();
                    break;
                }
                case symbol::Type::Reduce:
                    callReduceFunctionByIndex(action->second.state);
                    printStateStack();
                    printProductionStack();
                    break;
                case symbol::Type::Accept:
                    std::cout << "Input is successfully parsed!" << std::endl;
                    return productions;
                case symbol::Type::Error:
                    error(tokens[currentToken], "Syntax error at this token");
                    advance();
                    printStateStack();
                    printProductionStack();
                    break;
                default:
                    std::cerr << "enter the error goto branch in action" << std::endl;
            }
        }
        std::cerr << "enter the error branch" << std::endl;
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
