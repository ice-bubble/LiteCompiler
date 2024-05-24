//
// Created by icelake on 24-4-23.
//

#include "error.h"

void error(size_t line, std::string message)
{
    std::cerr << "[line: " << line << "] Error:" << message << std::endl;
}

void error(size_t line, std::string message, std::string &error_output)
{
    std::cerr << "[line: " << line << "] Error:" << message << std::endl;
    error_output += "[line: ";
    error_output += std::to_string(line);
    error_output += "] Error:";
    error_output += message;
    error_output += "\n";
}

bool error(const int currentState, Token currentToken, std::stack<Token> &symbolStack, std::string &error_output)
{
    switch(currentState)
    {
        case 0:
        {
            std::string emsg = "Expect a declaration or statement here.";
            error(currentToken.getLineNum(), emsg, error_output);
            return false;
        }break;
        case 8:
        {
            std::string emsg = "Expect variable define here.";
            error(currentToken.getLineNum(), emsg, error_output);
            return false;
        }break;
        case 24:
        {
            std::string emsg = "Expect ';' after 'break'.";
            error(currentToken.getLineNum(), emsg, error_output);
            size_t curr_line = currentToken.getLineNum();
            symbolStack.push(Token(TokenType::SEMICOLON,";",curr_line));
            return true;
        }break;
        case 25:
        {
            std::string emsg = "Expect ';' after 'continue'.";
            error(currentToken.getLineNum(), emsg, error_output);
            size_t curr_line = currentToken.getLineNum();
            symbolStack.push(Token(TokenType::SEMICOLON,";",curr_line));
            return true;
        }break;
        case 26:
        {
            std::string emsg = "Expect expression-statement here.";
            error(currentToken.getLineNum(), emsg, error_output);
            return false;
        }break;
        case 27:
        {
            std::string emsg = "Expect ';' after pression.";
            error(currentToken.getLineNum(), emsg, error_output);
            size_t curr_line = currentToken.getLineNum();
            symbolStack.push(Token(TokenType::SEMICOLON,";",curr_line));
            return true;
        }break;
        case 29:
        {
            std::string emsg = "Expect '(' after 'if'.";
            error(currentToken.getLineNum(), emsg, error_output);
            size_t curr_line = currentToken.getLineNum();
            symbolStack.push(Token(TokenType::LEFT_PAREN,"(",curr_line));
            return true;
        }break;
        case 30:
        {
            std::string emsg = "Expect '(' after 'while'.";
            error(currentToken.getLineNum(), emsg, error_output);
            size_t curr_line = currentToken.getLineNum();
            symbolStack.push(Token(TokenType::LEFT_PAREN,"(",curr_line));
            return true;
        }break;
        case 31:
        {
            std::string emsg = "Expect a statement here.";
            error(currentToken.getLineNum(), emsg, error_output);
            return false;
        }break;
        case 33:
        {
            std::string emsg = "Expect '(' after 'for'.";
            error(currentToken.getLineNum(), emsg, error_output);
            size_t curr_line = currentToken.getLineNum();
            symbolStack.push(Token(TokenType::LEFT_PAREN,"(",curr_line));
            return true;
        }break;
        case 44:
        {
            std::string emsg = "Expect a unary here."; // 期望一元表达式
            error(currentToken.getLineNum(), emsg, error_output);
            return false;
        }break;
        case 45:
        {
            std::string emsg = "Expect a unary here.";
            error(currentToken.getLineNum(), emsg, error_output);
            return false;
        }break;
        case 49:
        {
            std::string emsg = "Expect a expression here.";
            error(currentToken.getLineNum(), emsg, error_output);
            return false;
        }break;
        case 57:
        {
            std::string emsg = "Expect 'function' after '='.";
            error(currentToken.getLineNum(), emsg, error_output);
            size_t curr_line = currentToken.getLineNum();
            symbolStack.push(Token(TokenType::KEYWORD_FUNCTION,"function",curr_line));
            return true;
        }break;
        case 59:
        {
            std::string emsg = "Expect a expression here.";
            error(currentToken.getLineNum(), emsg, error_output);
            return false;
        }break;
        case 67:
        {
            std::string emsg = "Expect a expression here.";
            error(currentToken.getLineNum(), emsg, error_output);
            return false;
        }break;
        case 68:
        {
            std::string emsg = "Expect a expression here.";
            error(currentToken.getLineNum(), emsg, error_output);
            return false;
        }break;
        case 69:
        {
            std::string emsg = "Expect 'until' here.";
            error(currentToken.getLineNum(), emsg, error_output);
            size_t curr_line = currentToken.getLineNum();
            symbolStack.push(Token(TokenType::KEYWORD_UNTIL,"until",curr_line));
            return true;
        }break;
        case 70:
        {
            std::string emsg = "Expect '}' here.";
            error(currentToken.getLineNum(), emsg, error_output);
            size_t curr_line = currentToken.getLineNum();
            symbolStack.push(Token(TokenType::RIGHT_BRACE,"}",curr_line));
            return true;
        }break;
        case 71:
        {
            std::string emsg = "Expect a variable-declaration or expression-statement here.";
            error(currentToken.getLineNum(), emsg, error_output);
            return false;
        }break;
        case 72:
        {
            std::string emsg = "Expect a variable or assignment-expression or a higher priority expression here.";
            error(currentToken.getLineNum(), emsg, error_output);
            return false;
        }break;
        case 74:
        {
            std::string emsg = "Expect a logic_or-expression or a higher priority expression here.";
            error(currentToken.getLineNum(), emsg, error_output);
            return false;
        }break;
        case 76:
        {
            std::string emsg = "Expect a logic_and-expression or a higher priority expression here.";
            error(currentToken.getLineNum(), emsg, error_output);
            return false;
        }break;
        case 78:
        {
            std::string emsg = "Expect a equality-expression or a higher priority expression here.";
            error(currentToken.getLineNum(), emsg, error_output);
            return false;
        }break;
        case 79:
        {
            std::string emsg = "Expect a equality-expression or a higher priority expression here.";
            error(currentToken.getLineNum(), emsg, error_output);
            return false;
        }break;
        case 81:
        {
            std::string emsg = "Expect a comparison-expression or a higher priority expression here.";
            error(currentToken.getLineNum(), emsg, error_output);
            return false;
        }break;
        case 82:
        {
            std::string emsg = "Expect a comparison-expression or a higher priority expression here.";
            error(currentToken.getLineNum(), emsg, error_output);
            return false;
        }break;
        case 83:
        {
            std::string emsg = "Expect a comparison-expression or a higher priority expression here.";
            error(currentToken.getLineNum(), emsg, error_output);
            return false;
        }break;
        case 84:
        {
            std::string emsg = "Expect a comparison-expression or a higher priority expression here.";
            error(currentToken.getLineNum(), emsg, error_output);
            return false;
        }break;
        case 86:
        {
            std::string emsg = "Expect a term-expression or a higher priority expression here.";
            error(currentToken.getLineNum(), emsg, error_output);
            return false;
        }break;
        case 87:
        {
            std::string emsg = "Expect a term-expression or a higher priority expression here.";
            error(currentToken.getLineNum(), emsg, error_output);
            return false;
        }break;
        case 89:
        {
            std::string emsg = "Expect a factor-expression or a higher priority expression here.";
            error(currentToken.getLineNum(), emsg, error_output);
            return false;
        }break;
        case 90:
        {
            std::string emsg = "Expect a factor-expression or a higher priority expression here.";
            error(currentToken.getLineNum(), emsg, error_output);
            return false;
        }break;
        case 91:
        {
            std::string emsg = "Expect a factor-expression or a higher priority expression here.";
            error(currentToken.getLineNum(), emsg, error_output);
            return false;
        }break;
        case 100:
        {
            std::string emsg = "Expect ')' here.";
            error(currentToken.getLineNum(), emsg, error_output);
            size_t curr_line = currentToken.getLineNum();
            symbolStack.push(Token(TokenType::RIGHT_PAREN,")",curr_line));
            return true;
        }break;
        case 101:
        {
            std::string emsg = "Expect '(' after 'function'.";
            error(currentToken.getLineNum(), emsg, error_output);
            size_t curr_line = currentToken.getLineNum();
            symbolStack.push(Token(TokenType::LEFT_PAREN,"(",curr_line));
            return true;
        }break;
        case 102:
        {
            std::string emsg = "Expect ']' after expression.";
            error(currentToken.getLineNum(), emsg, error_output);
            size_t curr_line = currentToken.getLineNum();
            symbolStack.push(Token(TokenType::RIGHT_BRACKET,"]",curr_line));
            return true;
        }break;
        case 103:
        {
            std::string emsg = "Expect ';' here.";
            error(currentToken.getLineNum(), emsg, error_output);
            size_t curr_line = currentToken.getLineNum();
            symbolStack.push(Token(TokenType::SEMICOLON,";",curr_line));
            return true;
        }break;
        case 104:
        {
            std::string emsg = "Expect variable define here.";
            error(currentToken.getLineNum(), emsg, error_output);
            return false;
        }break;
        case 106:
        {
            std::string emsg = "Expect a expression here.";
            error(currentToken.getLineNum(), emsg, error_output);
            return false;
        }break;
        case 107:
        {
            std::string emsg = "Expect ')' here.";
            error(currentToken.getLineNum(), emsg, error_output);
            size_t curr_line = currentToken.getLineNum();
            symbolStack.push(Token(TokenType::RIGHT_PAREN,")",curr_line));
            return true;
        }break;
        case 108:
        {
            std::string emsg = "Expect ')' here.";
            error(currentToken.getLineNum(), emsg, error_output);
            size_t curr_line = currentToken.getLineNum();
            symbolStack.push(Token(TokenType::RIGHT_PAREN,")",curr_line));
            return true;
        }break;
        case 109:
        {
            std::string emsg = "Expect '(' after 'until'.";
            error(currentToken.getLineNum(), emsg, error_output);
            size_t curr_line = currentToken.getLineNum();
            symbolStack.push(Token(TokenType::LEFT_PAREN,"(",curr_line));
            return true;
        }break;
        case 111:
        {
            std::string emsg = "Expect expression-statement here.";
            error(currentToken.getLineNum(), emsg, error_output);
            return false;
        }break;
        case 112:
        {
            std::string emsg = "Expect expression-statement here.";
            error(currentToken.getLineNum(), emsg, error_output);
            return false;
        }break;
        case 129:
        {
            std::string emsg = "Expect ')' in the end of function call.";
            error(currentToken.getLineNum(), emsg, error_output);
            size_t curr_line = currentToken.getLineNum();
            symbolStack.push(Token(TokenType::RIGHT_PAREN,")",curr_line));
            return true;
        }break;
        case 137:
        {
            std::string emsg = "Expect a statement here.";
            error(currentToken.getLineNum(), emsg, error_output);
            return false;
        }break;
        case 138:
        {
            std::string emsg = "Expect a statement here.";
            error(currentToken.getLineNum(), emsg, error_output);
            return false;
        }break;
        case 139:
        {
            std::string emsg = "Expect a expression here.";
            error(currentToken.getLineNum(), emsg, error_output);
            return false;
        }break;
        case 140:
        {
            std::string emsg = "Expect a expression or ')' here.";
            error(currentToken.getLineNum(), emsg, error_output);
            return false;
        }break;
        case 141:
        {
            std::string emsg = "Expect a expression or ')' here.";
            error(currentToken.getLineNum(), emsg, error_output);
            return false;
        }break;
        case 144:
        {
            std::string emsg = "Expect a expression here.";
            error(currentToken.getLineNum(), emsg, error_output);
            return false;
        }break;
        case 145:
        {
            std::string emsg = "Expect ')' in the end of parameters list.";
            error(currentToken.getLineNum(), emsg, error_output);
            size_t curr_line = currentToken.getLineNum();
            symbolStack.push(Token(TokenType::RIGHT_PAREN,")",curr_line));
            return true;
        }break;
        case 147:
        {
            std::string emsg = "Expect variable here.";
            error(currentToken.getLineNum(), emsg, error_output);
            return false;
        }break;
        case 152:
        {
            std::string emsg = "Expect ')' after 'expression'.";
            error(currentToken.getLineNum(), emsg, error_output);
            size_t curr_line = currentToken.getLineNum();
            symbolStack.push(Token(TokenType::RIGHT_PAREN,")",curr_line));
            return true;
        }break;
        case 153:
        {
            std::string emsg = "Expect a statement here.";
            error(currentToken.getLineNum(), emsg, error_output);
            return false;
        }break;
        case 154:
        {
            std::string emsg = "Expect ')' after 'expression'.";
            error(currentToken.getLineNum(), emsg, error_output);
            size_t curr_line = currentToken.getLineNum();
            symbolStack.push(Token(TokenType::RIGHT_PAREN,")",curr_line));
            return true;
        }break;
        case 155:
        {
            std::string emsg = "Expect a statement here.";
            error(currentToken.getLineNum(), emsg, error_output);
            return false;
        }break;
        case 156:
        {
            std::string emsg = "Expect ')' after 'expression'.";
            error(currentToken.getLineNum(), emsg, error_output);
            size_t curr_line = currentToken.getLineNum();
            symbolStack.push(Token(TokenType::RIGHT_PAREN,")",curr_line));
            return true;
        }break;
        case 159:
        {
            std::string emsg = "Expect '{' here.";
            error(currentToken.getLineNum(), emsg, error_output);
            size_t curr_line = currentToken.getLineNum();
            symbolStack.push(Token(TokenType::LEFT_BRACE,"{",curr_line));
            return true;
        }break;
        case 161:
        {
            std::string emsg = "Expect a parameter define here.";
            error(currentToken.getLineNum(), emsg, error_output);
            return false;
        }break;
        case 164:
        {
            std::string emsg = "Expect a statement here.";
            error(currentToken.getLineNum(), emsg, error_output);
            return false;
        }break;
        case 165:
        {
            std::string emsg = "Expect ';' in the end of repeatStmt.";
            error(currentToken.getLineNum(), emsg, error_output);
            size_t curr_line = currentToken.getLineNum();
            symbolStack.push(Token(TokenType::SEMICOLON,";",curr_line));
            return true;
        }break;
        case 167:
        {
            std::string emsg = "Expect a statement here.";
            error(currentToken.getLineNum(), emsg, error_output);
            return false;
        }break;
        case 169:
        {
            std::string emsg = "Expect a statement here.";
            error(currentToken.getLineNum(), emsg, error_output);
            return false;
        }break;
        default:
        {
            std::cerr << "[Line: " << currentToken.getLineNum() << "] Syntax Error!  Token: " << currentToken.getValue() << std::endl;
            printf("\n\n");
            error_output += "[Line: ";
            error_output += std::to_string(currentToken.getLineNum());
            error_output += "] Syntax Error!  Token: ";
            error_output += currentToken.getValue();
            error_output += "\n";
            return false;
        }break;
    }
}