/**
 * @file debug.cpp
 * @brief debug函数的实现。
 * @author lzy
 * @date 24-4-23
 */

#include "debug.h"

void printTokenList(const std::vector<Token::Token> &tokenList) {
    for (const auto &token: tokenList) {
        std::cout << token.toString() << std::endl;
    }
}

void printRequestedTokenList(const std::vector<Token::Token> &tokenList) {
    for (const auto &token: tokenList) {
        const std::string &val = token.getLexeme();
        if (token.getType() == Token::TOKEN_STRING) {
            std::cout << "<STRING, " << val << ">" << std::endl;
        } else if (token.getType() == Token::TOKEN_INT) {
            std::cout << "<INT, " << val << ">" << std::endl;
        } else if (token.getType() == Token::TOKEN_REAL) {
            std::string stdval;
            if (val[0] == '.') stdval = "0" + val;
            else if (val[val.size()-1]=='.') stdval=val+'0';
            else stdval = val;
            std::cout << "<REAL, " << stdval << ">" << std::endl;
        } else if (token.getType() == Token::TOKEN_IDENTIFIER) {
            std::cout << "<id, " << val << ">" << std::endl;
        } else {
            if (token.getType() == Token::TOKEN_EOF) return;
            std::cout << "<" << val << ">" << std::endl;
        }
    }
}