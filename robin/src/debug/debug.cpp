/**
 * @file debug.cpp
 * @brief debug函数的实现。
 * @date 24-4-23
 */

#include "debug.h"

void printTokenList(const List<token::Token> &tokenlist) {
    for (const auto &token: tokenlist) {
        std::cout << token.toString() << std::endl;
    }
}

void printRequestedTokenList(const List<token::Token> &tokenlist) {
    for (const auto &token: tokenlist) {
        const String &val = token.getLexeme();
        if (token.getType() == token::TOKEN_STRING) {
            std::cout << "<STRING, " << val << ">" << std::endl;
        } else if (token.getType() == token::TOKEN_INT) {
            std::cout << "<INT, " << val << ">" << std::endl;
        } else if (token.getType() == token::TOKEN_REAL) {
            String stdval;
            if (val[0] == '.') stdval = "0" + val;
            else if (val[val.size()-1]=='.') stdval=val+'0';
            else stdval = val;
            std::cout << "<REAL, " << stdval << ">" << std::endl;
        } else if (token.getType() == token::TOKEN_IDENTIFIER) {
            std::cout << "<id, " << val << ">" << std::endl;
        } else {
            if (token.getType() == token::TOKEN_EOF) return;
            std::cout << "<" << val << ">" << std::endl;
        }
    }
}

void printSymbolTable(const List<token::Token>& tokenlist){
    std::vector<String> symbolTable;
    for (const auto& t :tokenlist) {
        if (t.getType() == token::TOKEN_IDENTIFIER){
            insertToSymbolTable(t,symbolTable);
        }
    }
    for (auto t :symbolTable) {
        std::cout<<"IDENTIFIER "<<t<<std::endl;
    }
}

void insertToSymbolTable(const token::Token& t, List<String>& symboltable){
    for (const auto& item:symboltable) {
        if (t.getLiteralString()==item) return;
    }
    symboltable.push_back(t.getLexeme());
}
