//
// Created by Ice-bubble on 24-4-21.
//
#include "debug.h"

void Debug::printTokens(const std::vector<Token> &tokens)
{
    for (const Token &token: tokens)
    {
        if (token.getType() != TokenType::EMPTY && token.getValue() != "\n" && token.getValue() != "\0" && token.getValue() != "\t")
        {
            std::cout << "<";
            switch (token.getType())
            {
                case TokenType::IDENTIFIER:
                    std::cout << "id, ";
                    break;
                case TokenType::INTEGER:
                    std::cout << "INT, ";
                    break;
                case TokenType::FLOAT:
                    std::cout << "REAL, ";
                    break;
                // case TokenType::SEMICOLON:
                //     std::cout << "Semicolon";
                //     break;
                // case TokenType::ASSIGNMENT:
                //     std::cout << "Assignment";
                //     break;
                // case TokenType::PLUS:
                //     std::cout << "Plus";
                //     break;
                // case TokenType::PLUS_FORWARD:
                //     std::cout << "Plus Forward";
                //     break;
                // case TokenType::MINUS:
                //     std::cout << "Minus";
                //     break;
                // case TokenType::MINUS_FORWARD:
                //     std::cout << "Minus Forward";
                //     break;
                // case TokenType::MULTIPLY:
                //     std::cout << "Multiply";
                //     break;
                // case TokenType::MULTIPLY_FORWARD:
                //     std::cout << "Multiply Forward";
                //     break;
                // case TokenType::DIVIDE:
                //     std::cout << "Divide";
                //     break;
                // case TokenType::DIVIDE_FORWARD:
                //     std::cout << "Divide Forward";
                //     break;
                // case TokenType::AND:
                //     std::cout << "And";
                //     break;
                // case TokenType::AND_FORWARD:
                //     std::cout << "And Forward";
                //     break;
                // case TokenType::LOGICAL_AND:
                //     std::cout << "Logical And";
                //     break;
                // case TokenType::OR:
                //     std::cout << "Or";
                //     break;
                // case TokenType::OR_FORWARD:
                //     std::cout << "Or Forward";
                //     break;
                // case TokenType::LOGICAL_OR:
                //     std::cout << "Logical Or";
                //     break;
                // case TokenType::XOR:
                //     std::cout << "Xor";
                //     break;
                // case TokenType::XOR_FORWARD:
                //     std::cout << "Xor Forward";
                //     break;
                // case TokenType::NOT:
                //     std::cout << "Not";
                //     break;
                // case TokenType::EQUAL:
                //     std::cout << "Equal";
                //     break;
                // case TokenType::LEFT_PAREN:
                //     std::cout << "Left Parenthesis";
                //     break;
                // case TokenType::RIGHT_PAREN:
                //     std::cout << "Right Parenthesis";
                //     break;
                // case TokenType::LEFT_BRACKET:
                //     std::cout << "Left Bracket";
                //     break;
                // case TokenType::RIGHT_BRACKET:
                //     std::cout << "Right Bracket";
                //     break;
                // case TokenType::LEFT_BRACE:
                //     std::cout << "Left Brace";
                //     break;
                // case TokenType::RIGHT_BRACE:
                //     std::cout << "Right Brace";
                //     break;
                // case TokenType::D_MARKS:
                //     std::cout << "Double Marks";
                //     break;
                // case TokenType::S_MARKS:
                //     std::cout << "Single Marks";
                //     break;
                // case TokenType::MEMBER:
                //     std::cout << "Member";
                //     break;
                case TokenType::INVALID:
                    if (token.getValue() != "\n" && token.getValue() != "\0" && token.getValue() != "\t")
                        std::cout << "Error: " << "<Invalid, ";
                    break;
                default:
                    break;
            }
        }
        if (token.getType() != TokenType::EMPTY && token.getValue() != "\n" && token.getValue() != "\0" && token.getValue() != "\t")
            std::cout << token.getValue() << ">" << std::endl;
    }
}
