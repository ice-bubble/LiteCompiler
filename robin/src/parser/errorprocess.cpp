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
            {8,   62},
            {24,  63},
            {25,  64},
            {26,  28},
            {27,  66},
            {29,  67},
            {30,  68},
            {31,  28},
            {33,  71},
            {44,  52},
            {45,  52},
            {49,  52},
            {57,  101},
            {59,  52},
            {67,  52},
            {68,  52},
            {69,  109},
            {70,  110},
            {71,  28},
            {72,  52},
            {74,  52},
            {76,  52},
            {78,  52},
            {79,  52},
            {81,  52},
            {82,  52},
            {83,  52},
            {84,  52},
            {86,  52},
            {87,  52},
            {89,  52},
            {90,  52},
            {91,  52},
            {100, 131},
            {101, 132},
            {102, 133},
            {103, 134},
            {104, 62},
            {106, 52},
            {107, 137},
            {108, 138},
            {109, 139},
            {111, 28},
            {112, 28},
            {129, 142},
            {137, 28},
            {138, 28},
            {139, 52},
            {140, 155},
            {141, 155},
            {144, 52},
            {145, 159},
            {147, 62},
            {152, 165},
            {153, 28},
            {154, 167},
            {155, 28},
            {156, 169},
            {159, 32},
            {161, 23},
            {164, 28},
            {165, 174},
            {167, 28},
            {169, 28},
    };

    void Parser::addTokenToProductionsAndStack(token::TokenType type, const std::string &lexeme, int errorState) {
        token::Token tmpToken{static_cast<token::TokenType>(type), lexeme, Object{}, 0};
        SharedPtr<production::Production> production = std::make_shared<production::Token>(0, tmpToken);
        productions.push_back(production);
        stateStack.push(errorStateToExpectState[errorState]);
    }

    bool Parser::errorProcess(State errorState) {
        reportParserError(this, tokens[currentToken], errorMessage[errorState]);
#ifdef PRINT_PARSER_PROCESS
        printInfo("error here");
#endif
        switch (errorState) {
            case -1:
                while (true) {
                    if (isAtTokenListEnd()) return false;
                    advance();
#ifdef PRINT_PARSER_PROCESS
                    printInfo("in error process");
#endif
                    symbol::Symbol currentSymbol = production::Production::tokenToSym[peek().getType()];
                    std::cout << peek().toString() << std::endl;
                    State currentState = stateStack.top();
                    auto action = slrTable.find({currentState, currentSymbol});
                    if (action->second.type != symbol::Error) { return true; }
                }
            case 44:
            case 45:
            case 49:
            case 59:
            case 67:
            case 68:
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
            case 106:
            case 139:
            case 144:
                addTokenToProductionsAndStack(token::TOKEN_NIL, "nil", errorState);
                return true;
            case 24:
            case 25:
            case 26:
            case 27:
            case 31:
            case 71:
            case 103:
            case 111:
            case 112:
            case 137:
            case 138:
            case 153:
            case 155:
            case 164:
            case 165:
            case 167:
            case 169:
                addTokenToProductionsAndStack(token::TOKEN_SEMICOLON, ";", errorState);
                return true;
            case 100:
            case 107:
            case 108:
            case 152:
            case 154:
            case 156:
            case 129:
            case 140:
            case 141:
            case 145:
                addTokenToProductionsAndStack(token::TOKEN_RIGHT_PAREN, ")", errorState);
                return true;
            case 29:
            case 30:
            case 33:
            case 101:
            case 109:
                addTokenToProductionsAndStack(token::TOKEN_LEFT_PAREN, "(", errorState);
                return true;
            case 8:
            case 104:
            case 147:
                addTokenToProductionsAndStack(token::TOKEN_IDENTIFIER, "temp", errorState);
                return true;
            case 57:
                addTokenToProductionsAndStack(token::TOKEN_FUNCTION, "function", errorState);
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
            case 102:
                addTokenToProductionsAndStack(token::TOKEN_RIGHT_BRACKET, "]", errorState);
                return true;
            case 161:
                addTokenToProductionsAndStack(token::TOKEN_VAR, "var", errorState);
                callReduceFunctionByIndex(31);
                stateStack.push(147);
                addTokenToProductionsAndStack(token::TOKEN_IDENTIFIER, "temp", 147);
                return true;
            default:
                return false;
        }
    }

}
