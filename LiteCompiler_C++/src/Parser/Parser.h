#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <string>

#include "../Token/Token.h"

// 定义产生式结构
struct Production
{
    NonTerminal left; // 产生式左部
    int rightLength; // 产生式右部长度
};

// SLR(1)分析器
class Parser
{
public:
    Parser();

    void parse(const std::vector<Token> &tokens);

private:
    static std::map<int, std::map<TokenType, std::string> > parseTable;
    static std::map<int, std::map<NonTerminal, int> > gotoTable; // GOTO表
    static std::vector<Production> productions; // 存储所有的产生式

    void shift(std::stack<int> &stateStack, std::stack<Token> &symbolStack, int newState, const Token &token);

    void reduce(std::stack<int> &stateStack, std::stack<Token> &symbolStack, int productionNumber);

    bool isNumber(const std::string &str);

    void printSymbolStack(const std::stack<Token> &symbolStack);

    void printStateStack(const std::stack<int> &stateStack);

    std::string getNonTerminalName(NonTerminal nonTerminal);
};

#endif //PARSER_H
