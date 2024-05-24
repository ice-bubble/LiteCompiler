//
// Created by icelake on 24-5-24.
//
#include "parser.h"
#include "../error/error.h"

namespace parser {

    Map<State, String> Parser::errorMessage = {
            {-1,  "Here is a syntax error"},
            {8,   "Expect variable define here."},
            {24,  "Expect ';' after 'break'."},
            {25,  "Expect ';' after 'continue'."},
            {26,  "Expect expression-statement here."},
            {27,  "Expect ';' after expression."},
            {29,  "Expect '(' after 'if'."},
            {30,  "Expect '(' after 'while'."},
            {31,  "Expect a statement here."},
            {33,  "Expect '(' after 'for'."},
            {44,  "Expect a unary here."},
            {45,  "Expect a unary here."},
            {49,  "Expect a expression here."},
            {57,  "Expect 'function' after '='."},
            {59,  "Expect a expression here."},
            {67,  "Expect a expression here."},
            {68,  "Expect a expression here."},
            {69,  "Expect 'until' here."},
            {70,  "Expect '}' here."},
            {71,  "Expect a variable-declaration or expression-statement here."},
            {72,  "Expect a variable or assignment-expression or a higher priority expression here."},
            {74,  "Expect a logic_or-expression or a higher priority expression here."},
            {76,  "Expect a logic_and-expression or a higher priority expression here."},
            {78,  "Expect a equality-expression or a higher priority expression here."},
            {79,  "Expect a equality-expression or a higher priority expression here."},
            {81,  "Expect a comparison-expression or a higher priority expression here."},
            {82,  "Expect a comparison-expression or a higher priority expression here."},
            {83,  "Expect a comparison-expression or a higher priority expression here."},
            {84,  "Expect a comparison-expression or a higher priority expression here."},
            {86,  "Expect a term-expression or a higher priority expression here."},
            {87,  "Expect a term-expression or a higher priority expression here."},
            {89,  "Expect a factor-expression or a higher priority expression here."},
            {90,  "Expect a factor-expression or a higher priority expression here."},
            {91,  "Expect a factor-expression or a higher priority expression here."},
            {100, "Expect ')' here."},
            {101, "Expect '(' after 'function'."},
            {102, "Expect ']' after expression."},
            {103, "Expect ';' here."},
            {104, "Expect variable define here."},
            {106, "Expect a expression here."},
            {107, "Expect ')' here."},
            {108, "Expect ')' here."},
            {109, "Expect '(' after 'until'."},
            {111, "Expect expression-statement here."},
            {112, "Expect expression-statement here."},
            {129, "Expect ')' in the end of function call."},
            {137, "Expect a statement here."},
            {138, "Expect a statement here."},
            {139, "Expect a expression here."},
            {140, "Expect a expression or ')' here."},
            {141, "Expect a expression or ')' here."},
            {144, "Expect a expression here."},
            {145, "Expect ')' in the end of parameters list."},
            {147, "Expect variable here."},
            {152, "Expect ')' after 'expression'."},
            {153, "Expect a statement here."},
            {154, "Expect ')' after 'expression'."},
            {155, "Expect a statement here."},
            {156, "Expect ')' after 'expression'."},
            {159, "Expect '{' here."},
            {161, "Expect a parameter define here."},
            {164, "Expect a statement here."},
            {165, "Expect ';' in the end of repeatStmt."},
            {167, "Expect a statement here."},
            {169, "Expect a statement here."},
    };

    Map<State, State>Parser::errorStateToExpectState = {
            {24,  63},
            {25,  64},
            {27,  66},
            {103, 134},
            {165, 174},
            {57,  101},
            {29,  67},
            {30,  68},
            {33,  71},
            {101, 132},
            {109, 139},
            {69,  109},
            {159, 32},
            {70,  110},
            {100, 131},
            {107, 137},
            {108, 138},
            {152, 165},
            {154, 167},
            {156, 169},
            {129, 142},
            {145, 159},
            {102, 133}
    };

    void Parser::addTokenToProductionsAndStack(token::TokenType type, const std::string &lexeme, int errorState) {
        token::Token tmpToken{static_cast<token::TokenType>(type), lexeme, Object{}, 0};
        SharedPtr<production::Production> production = std::make_shared<production::Token>(0, tmpToken);
        productions.push_back(production);
        stateStack.push(errorStateToExpectState[errorState]);
    }

    bool Parser::errorProcess(State errorState) {
        reportParserError(this, tokens[currentToken], errorMessage[errorState]);
        printInfo("error here");
        switch (errorState) {
            case -1:
            case 8:
            case 26:
            case 31:
            case 44:
            case 45:
            case 49:
            case 59:
            case 67:
            case 68:
            case 71:
            case 72:
            case 74:
            case 76:
            case 78:
            case 79:
            case 81:
            case 82:
            case 83:
            case 84:
            case 86:
            case 87:
            case 89:
            case 90:
            case 91:
            case 104:
            case 106:
            case 137:
            case 138:
            case 139:
            case 140:
            case 141:
            case 111:
            case 112:
            case 144:
            case 147:
            case 153:
            case 155:
            case 161:
            case 164:
            case 167:
            case 169:
                while (true) {
                    if (isAtTokenListEnd()) return false;
                    advance();
                    printInfo("in error process");
                    symbol::Symbol currentSymbol = production::Production::tokenToSym[peek().getType()];
                    std::cout<<peek().toString()<<std::endl;
                    State currentState = stateStack.top();
                    auto action = slrTable.find({currentState, currentSymbol});
                    if (action->second.type != symbol::Error) { return true; }
                }
            case 24:
            case 25:
            case 27:
            case 103:
            case 165:
                addTokenToProductionsAndStack(token::TOKEN_SEMICOLON, ";", errorState);
                return true;
            case 57:
                addTokenToProductionsAndStack(token::TOKEN_FUNCTION, "function", errorState);
                return true;
            case 29:
            case 30:
            case 33:
            case 101:
            case 109:
                addTokenToProductionsAndStack(token::TOKEN_LEFT_PAREN, "(", errorState);
                return true;
            case 69:
                addTokenToProductionsAndStack(token::TOKEN_UNTIL, "until", errorState);
                return true;
            case 159:
                addTokenToProductionsAndStack(token::TOKEN_LEFT_BRACE, "{", errorState);
                return true;
            case 70:
                addTokenToProductionsAndStack(token::TOKEN_RIGHT_BRACE, "}", errorState);
                return true;
            case 100:
            case 107:
            case 108:
            case 152:
            case 154:
            case 156:
            case 129:
            case 145:
                addTokenToProductionsAndStack(token::TOKEN_RIGHT_PAREN, ")", errorState);
                return true;
            case 102:
                addTokenToProductionsAndStack(token::TOKEN_RIGHT_BRACKET, "]", errorState);
                return true;
            default:
                return false;
        }
    }

}
