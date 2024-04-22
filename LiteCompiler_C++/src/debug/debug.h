//
// Created by Ice-bubble on 24-4-21.
//

#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <vector>
#include "../Token/Token.h"

class Debug
{
public:
    static void printTokens(const std::vector<Token> &tokens);
};

#endif // DEBUG_H
