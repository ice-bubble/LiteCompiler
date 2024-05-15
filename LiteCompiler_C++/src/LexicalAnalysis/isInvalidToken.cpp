#include "./isInvalidToken.h"

bool isInvalidToken(const Token& token)
{
    return token.getType() == TokenType::INVALID ||
           token.getType() == TokenType::EMPTY ||
           token.getValue() == "\n" ||
           token.getValue() == "\0" ||
           token.getValue() == "\t";
}