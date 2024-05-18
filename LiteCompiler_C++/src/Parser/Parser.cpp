#include "Parser.h"

// SLR(1)分析表，Parser类的静态成员变量
std::map<int, std::map<TokenType, std::string> > Parser::parseTable = {
    {
        0,
        {
            {TokenType::MINUS, "s5"},
            {TokenType::PLUS, ""},
            {TokenType::DIVIDE, ""},
            {TokenType::MULTIPLY, ""},
            {TokenType::MOD, ""},
            {TokenType::INTEGER, "s7"},
            {TokenType::FLOAT, "s7"},
            {TokenType::IDENTIFIER, "s7"},
            {TokenType::LEFT_PAREN, "s8"},
            {TokenType::RIGHT_PAREN, "r2"},
            {TokenType::KEYWORD_EOF, "r2"}
        }
    },

    {
        1,
        {
            {TokenType::MINUS, ""},
            {TokenType::PLUS, ""},
            {TokenType::DIVIDE, ""},
            {TokenType::MULTIPLY, ""},
            {TokenType::MOD, ""},
            {TokenType::INTEGER, ""},
            {TokenType::FLOAT, ""},
            {TokenType::IDENTIFIER, ""},
            {TokenType::LEFT_PAREN, ""},
            {TokenType::RIGHT_PAREN, ""},
            {TokenType::KEYWORD_EOF, "acc"}
        }
    },

    {
        2,
        {
            {TokenType::MINUS, ""},
            {TokenType::PLUS, ""},
            {TokenType::DIVIDE, ""},
            {TokenType::MULTIPLY, ""},
            {TokenType::MOD, ""},
            {TokenType::INTEGER, ""},
            {TokenType::FLOAT, ""},
            {TokenType::IDENTIFIER, ""},
            {TokenType::LEFT_PAREN, ""},
            {TokenType::RIGHT_PAREN, "r1"},
            {TokenType::KEYWORD_EOF, "r1"}
        }
    },

    {
        3,
        {
            {TokenType::MINUS, "s10"},
            {TokenType::PLUS, "s11"},
            {TokenType::DIVIDE, ""},
            {TokenType::MULTIPLY, ""},
            {TokenType::MOD, ""},
            {TokenType::INTEGER, ""},
            {TokenType::FLOAT, ""},
            {TokenType::IDENTIFIER, ""},
            {TokenType::LEFT_PAREN, ""},
            {TokenType::RIGHT_PAREN, "r6"},
            {TokenType::KEYWORD_EOF, "r6"}
        }
    },

    {
        4,
        {
            {TokenType::MINUS, "r11"},
            {TokenType::PLUS, "r11"},
            {TokenType::DIVIDE, "s13"},
            {TokenType::MULTIPLY, "s14"},
            {TokenType::MOD, "s15"},
            {TokenType::INTEGER, ""},
            {TokenType::FLOAT, ""},
            {TokenType::IDENTIFIER, ""},
            {TokenType::LEFT_PAREN, ""},
            {TokenType::RIGHT_PAREN, "r11"},
            {TokenType::KEYWORD_EOF, "r11"}
        }
    },

    {
        5,
        {
            {TokenType::MINUS, "s5"},
            {TokenType::PLUS, ""},
            {TokenType::DIVIDE, ""},
            {TokenType::MULTIPLY, ""},
            {TokenType::MOD, ""},
            {TokenType::INTEGER, "s7"},
            {TokenType::FLOAT, "s7"},
            {TokenType::IDENTIFIER, "s7"},
            {TokenType::LEFT_PAREN, "s8"},
            {TokenType::RIGHT_PAREN, ""},
            {TokenType::KEYWORD_EOF, ""}
        }
    },
    {
        6,
        {
            {TokenType::MINUS, "r13"},
            {TokenType::PLUS, "r13"},
            {TokenType::DIVIDE, "r13"},
            {TokenType::MULTIPLY, "r13"},
            {TokenType::MOD, "r13"},
            {TokenType::INTEGER, ""},
            {TokenType::FLOAT, ""},
            {TokenType::IDENTIFIER, ""},
            {TokenType::LEFT_PAREN, ""},
            {TokenType::RIGHT_PAREN, "r13"},
            {TokenType::KEYWORD_EOF, "r13"}
        }
    },
    {
        7,
        {
            {TokenType::MINUS, "r14"},
            {TokenType::PLUS, "r14"},
            {TokenType::DIVIDE, "r14"},
            {TokenType::MULTIPLY, "r14"},
            {TokenType::MOD, "r14"},
            {TokenType::INTEGER, ""},
            {TokenType::FLOAT, ""},
            {TokenType::IDENTIFIER, ""},
            {TokenType::LEFT_PAREN, ""},
            {TokenType::RIGHT_PAREN, "r14"},
            {TokenType::KEYWORD_EOF, "r14"}
        }
    },

    {
        8,
        {
            {TokenType::MINUS, "s5"},
            {TokenType::PLUS, ""},
            {TokenType::DIVIDE, ""},
            {TokenType::MULTIPLY, ""},
            {TokenType::MOD, ""},
            {TokenType::INTEGER, "s7"},
            {TokenType::FLOAT, "s7"},
            {TokenType::IDENTIFIER, "s7"},
            {TokenType::LEFT_PAREN, "s8"},
            {TokenType::RIGHT_PAREN, "r2"},
            {TokenType::KEYWORD_EOF, "r2"}
        }
    },

    {
        9,
        {
            {TokenType::MINUS, ""},
            {TokenType::PLUS, ""},
            {TokenType::DIVIDE, ""},
            {TokenType::MULTIPLY, ""},
            {TokenType::MOD, ""},
            {TokenType::INTEGER, ""},
            {TokenType::FLOAT, ""},
            {TokenType::IDENTIFIER, ""},
            {TokenType::LEFT_PAREN, ""},
            {TokenType::RIGHT_PAREN, "r3"},
            {TokenType::KEYWORD_EOF, "r3"}
        }
    },

    {
        10,
        {
            {TokenType::MINUS, "s5"},
            {TokenType::PLUS, ""},
            {TokenType::DIVIDE, ""},
            {TokenType::MULTIPLY, ""},
            {TokenType::MOD, ""},
            {TokenType::INTEGER, "s7"},
            {TokenType::FLOAT, "s7"},
            {TokenType::IDENTIFIER, "s7"},
            {TokenType::LEFT_PAREN, "s8"},
            {TokenType::RIGHT_PAREN, ""},
            {TokenType::KEYWORD_EOF, ""}
        }
    },

    {
        11,
        {
            {TokenType::MINUS, "s5"},
            {TokenType::PLUS, ""},
            {TokenType::DIVIDE, ""},
            {TokenType::MULTIPLY, ""},
            {TokenType::MOD, ""},
            {TokenType::INTEGER, "s7"},
            {TokenType::FLOAT, "s7"},
            {TokenType::IDENTIFIER, "s7"},
            {TokenType::LEFT_PAREN, "s8"},
            {TokenType::RIGHT_PAREN, ""},
            {TokenType::KEYWORD_EOF, ""}
        }
    },

    {
        12,
        {
            {TokenType::MINUS, "r7"},
            {TokenType::PLUS, "r7"},
            {TokenType::DIVIDE, ""},
            {TokenType::MULTIPLY, ""},
            {TokenType::MOD, ""},
            {TokenType::INTEGER, ""},
            {TokenType::FLOAT, ""},
            {TokenType::IDENTIFIER, ""},
            {TokenType::LEFT_PAREN, ""},
            {TokenType::RIGHT_PAREN, "r7"},
            {TokenType::KEYWORD_EOF, "r7"}
        }
    },

    {
        13,
        {
            {TokenType::MINUS, "s5"},
            {TokenType::PLUS, ""},
            {TokenType::DIVIDE, ""},
            {TokenType::MULTIPLY, ""},
            {TokenType::MOD, ""},
            {TokenType::INTEGER, "s7"},
            {TokenType::FLOAT, "s7"},
            {TokenType::IDENTIFIER, "s7"},
            {TokenType::LEFT_PAREN, "s8"},
            {TokenType::RIGHT_PAREN, ""},
            {TokenType::KEYWORD_EOF, ""}
        }
    },

    {
        14,
        {
            {TokenType::MINUS, "s5"},
            {TokenType::PLUS, ""},
            {TokenType::DIVIDE, ""},
            {TokenType::MULTIPLY, ""},
            {TokenType::MOD, ""},
            {TokenType::INTEGER, "s7"},
            {TokenType::FLOAT, "s7"},
            {TokenType::IDENTIFIER, "s7"},
            {TokenType::LEFT_PAREN, "s8"},
            {TokenType::RIGHT_PAREN, ""},
            {TokenType::KEYWORD_EOF, ""}
        }
    },

    {
        15,
        {
            {TokenType::MINUS, "s5"},
            {TokenType::PLUS, ""},
            {TokenType::DIVIDE, ""},
            {TokenType::MULTIPLY, ""},
            {TokenType::MOD, ""},
            {TokenType::INTEGER, "s7"},
            {TokenType::FLOAT, "s7"},
            {TokenType::IDENTIFIER, "s7"},
            {TokenType::LEFT_PAREN, "s8"},
            {TokenType::RIGHT_PAREN, ""},
            {TokenType::KEYWORD_EOF, ""}
        }
    },

    {
        16,
        {
            {TokenType::MINUS, "r12"},
            {TokenType::PLUS, "r12"},
            {TokenType::DIVIDE, "r12"},
            {TokenType::MULTIPLY, "r12"},
            {TokenType::MOD, "r12"},
            {TokenType::INTEGER, ""},
            {TokenType::FLOAT, ""},
            {TokenType::IDENTIFIER, ""},
            {TokenType::LEFT_PAREN, ""},
            {TokenType::RIGHT_PAREN, "r12"},
            {TokenType::KEYWORD_EOF, "r12"}
        }
    },

    {
        17,
        {
            {TokenType::MINUS, ""},
            {TokenType::PLUS, ""},
            {TokenType::DIVIDE, ""},
            {TokenType::MULTIPLY, ""},
            {TokenType::MOD, ""},
            {TokenType::INTEGER, ""},
            {TokenType::FLOAT, ""},
            {TokenType::IDENTIFIER, ""},
            {TokenType::LEFT_PAREN, ""},
            {TokenType::RIGHT_PAREN, "s23"},
            {TokenType::KEYWORD_EOF, ""}
        }
    },

    {
        18,
        {
            {TokenType::MINUS, "s10"},
            {TokenType::PLUS, "s11"},
            {TokenType::DIVIDE, ""},
            {TokenType::MULTIPLY, ""},
            {TokenType::MOD, ""},
            {TokenType::INTEGER, ""},
            {TokenType::FLOAT, ""},
            {TokenType::IDENTIFIER, ""},
            {TokenType::LEFT_PAREN, ""},
            {TokenType::RIGHT_PAREN, "r6"},
            {TokenType::KEYWORD_EOF, "r6"}
        }
    },

    {
        19,
        {
            {TokenType::MINUS, "s10"},
            {TokenType::PLUS, "s11"},
            {TokenType::DIVIDE, ""},
            {TokenType::MULTIPLY, ""},
            {TokenType::MOD, ""},
            {TokenType::INTEGER, ""},
            {TokenType::FLOAT, ""},
            {TokenType::IDENTIFIER, ""},
            {TokenType::LEFT_PAREN, ""},
            {TokenType::RIGHT_PAREN, "r6"},
            {TokenType::KEYWORD_EOF, "r6"}
        }
    },

    {
        20,
        {
            {TokenType::MINUS, "r11"},
            {TokenType::PLUS, "r11"},
            {TokenType::DIVIDE, "s13"},
            {TokenType::MULTIPLY, "s14"},
            {TokenType::MOD, "s15"},
            {TokenType::INTEGER, ""},
            {TokenType::FLOAT, ""},
            {TokenType::IDENTIFIER, ""},
            {TokenType::LEFT_PAREN, ""},
            {TokenType::RIGHT_PAREN, "r11"},
            {TokenType::KEYWORD_EOF, "r11"}
        }
    },

    {
        21,
        {
            {TokenType::MINUS, "r11"},
            {TokenType::PLUS, "r11"},
            {TokenType::DIVIDE, "s13"},
            {TokenType::MULTIPLY, "s14"},
            {TokenType::MOD, "s15"},
            {TokenType::INTEGER, ""},
            {TokenType::FLOAT, ""},
            {TokenType::IDENTIFIER, ""},
            {TokenType::LEFT_PAREN, ""},
            {TokenType::RIGHT_PAREN, "r11"},
            {TokenType::KEYWORD_EOF, "r11"}
        }
    },

    {
        22,
        {
            {TokenType::MINUS, "r11"},
            {TokenType::PLUS, "r11"},
            {TokenType::DIVIDE, "s13"},
            {TokenType::MULTIPLY, "s14"},
            {TokenType::MOD, "s15"},
            {TokenType::INTEGER, ""},
            {TokenType::FLOAT, ""},
            {TokenType::IDENTIFIER, ""},
            {TokenType::LEFT_PAREN, ""},
            {TokenType::RIGHT_PAREN, "r11"},
            {TokenType::KEYWORD_EOF, "r11"}
        }
    },

    {
        23,
        {
            {TokenType::MINUS, "r15"},
            {TokenType::PLUS, "r15"},
            {TokenType::DIVIDE, "r15"},
            {TokenType::MULTIPLY, "r15"},
            {TokenType::MOD, "r15"},
            {TokenType::INTEGER, ""},
            {TokenType::FLOAT, ""},
            {TokenType::IDENTIFIER, ""},
            {TokenType::LEFT_PAREN, ""},
            {TokenType::RIGHT_PAREN, "r15"},
            {TokenType::KEYWORD_EOF, "r15"}
        }
    },

    {
        24,
        {
            {TokenType::MINUS, ""},
            {TokenType::PLUS, ""},
            {TokenType::DIVIDE, ""},
            {TokenType::MULTIPLY, ""},
            {TokenType::MOD, ""},
            {TokenType::INTEGER, ""},
            {TokenType::FLOAT, ""},
            {TokenType::IDENTIFIER, ""},
            {TokenType::LEFT_PAREN, ""},
            {TokenType::RIGHT_PAREN, "r4"},
            {TokenType::KEYWORD_EOF, "r4"}
        }
    },

    {
        25,
        {
            {TokenType::MINUS, ""},
            {TokenType::PLUS, ""},
            {TokenType::DIVIDE, ""},
            {TokenType::MULTIPLY, ""},
            {TokenType::MOD, ""},
            {TokenType::INTEGER, ""},
            {TokenType::FLOAT, ""},
            {TokenType::IDENTIFIER, ""},
            {TokenType::LEFT_PAREN, ""},
            {TokenType::RIGHT_PAREN, "r5"},
            {TokenType::KEYWORD_EOF, "r5"}
        }
    },

    {
        26,
        {
            {TokenType::MINUS, "r8"},
            {TokenType::PLUS, "r8"},
            {TokenType::DIVIDE, ""},
            {TokenType::MULTIPLY, ""},
            {TokenType::MOD, ""},
            {TokenType::INTEGER, ""},
            {TokenType::FLOAT, ""},
            {TokenType::IDENTIFIER, ""},
            {TokenType::LEFT_PAREN, ""},
            {TokenType::RIGHT_PAREN, "r8"},
            {TokenType::KEYWORD_EOF, "r8"}
        }
    },

    {
        27,
        {
            {TokenType::MINUS, "r9"},
            {TokenType::PLUS, "r9"},
            {TokenType::DIVIDE, ""},
            {TokenType::MULTIPLY, ""},
            {TokenType::MOD, ""},
            {TokenType::INTEGER, ""},
            {TokenType::FLOAT, ""},
            {TokenType::IDENTIFIER, ""},
            {TokenType::LEFT_PAREN, ""},
            {TokenType::RIGHT_PAREN, "r9"},
            {TokenType::KEYWORD_EOF, "r9"}
        }
    },

    {
        28,
        {
            {TokenType::MINUS, "r10"},
            {TokenType::PLUS, "r10"},
            {TokenType::DIVIDE, ""},
            {TokenType::MULTIPLY, ""},
            {TokenType::MOD, ""},
            {TokenType::INTEGER, ""},
            {TokenType::FLOAT, ""},
            {TokenType::IDENTIFIER, ""},
            {TokenType::LEFT_PAREN, ""},
            {TokenType::RIGHT_PAREN, "r10"},
            {TokenType::KEYWORD_EOF, "r10"}
        }
    }

};

// GOTO表，Parser类的静态成员变量
std::map<int, std::map<NonTerminal, int> > Parser::gotoTable = {
    // GOTO表初始化内容
    {
        0,
        {
            {NonTerminal::EXPRESSION, 1},
            {NonTerminal::TERM, 2},
            {NonTerminal::FACTOR, 3},
            {NonTerminal::UNARY, 4},
            {NonTerminal::PRIMARY, 6}
        }
    },

    {
        3,
        {
            {NonTerminal::TERM_PRIME, 9}
        }
    },

    {
        4,
        {
            {NonTerminal::FACTOR_PRIME, 12}
        }
    },

    {
        5,
        {
            {NonTerminal::UNARY, 16},
            {NonTerminal::PRIMARY, 6}
        }
    },

    {
        8,
        {
            {NonTerminal::EXPRESSION, 17},
            {NonTerminal::TERM, 2},
            {NonTerminal::FACTOR, 3},
            {NonTerminal::UNARY, 4},
            {NonTerminal::PRIMARY, 6}
        }
    },

    {
        10,
        {
            {NonTerminal::FACTOR, 18},
            {NonTerminal::UNARY, 4},
            {NonTerminal::PRIMARY, 6}
        }
    },

    {
        11,
        {
            {NonTerminal::FACTOR, 19},
            {NonTerminal::UNARY, 4},
            {NonTerminal::PRIMARY, 6}
        }
    },

    {
        13,
        {
            {NonTerminal::UNARY, 20},
            {NonTerminal::PRIMARY, 6}
        }
    },

    {
        14,
        {
            {NonTerminal::UNARY, 21},
            {NonTerminal::PRIMARY, 6}
        }
    },

    {
        15,
        {
            {NonTerminal::UNARY, 22},
            {NonTerminal::PRIMARY, 6}
        }
    },

    {
        18,
        {
            {NonTerminal::TERM_PRIME, 24}
        }
    },

    {
        19,
        {
            {NonTerminal::TERM_PRIME, 25}
        }
    },

    {
        20,
        {
            {NonTerminal::FACTOR_PRIME, 26}
        }
    },

    {
        21,
        {
            {NonTerminal::FACTOR_PRIME, 27}
        }
    },

    {
        22,
        {
            {NonTerminal::FACTOR_PRIME, 28}
        }
    }

};

// 产生式表，Parser类的静态成员变量
std::vector<Production> Parser::productions = {
    {NonTerminal::S, 1},// 0: S -> expression
    {NonTerminal::EXPRESSION, 1},// 1: expression -> term
    {NonTerminal::EXPRESSION, 0},// 2: expression -> ''
    {NonTerminal::TERM, 2},// 3: term -> factor term_prime
    {NonTerminal::TERM_PRIME, 3},// 4: term_prime -> "-" factor term_prime
    {NonTerminal::TERM_PRIME, 3},// 5: term_prime -> "+" factor term_prime
    {NonTerminal::TERM_PRIME, 0},// 6: term_prime -> ''
    {NonTerminal::FACTOR, 2},// 7: factor -> unary factor_prime
    {NonTerminal::FACTOR_PRIME, 3},// 8: factor_prime -> "/" unary factor_prime
    {NonTerminal::FACTOR_PRIME, 3},// 9: factor_prime -> "*" unary factor_prime
    {NonTerminal::FACTOR_PRIME, 3},// 10: factor_prime -> "%" unary factor_prime
    {NonTerminal::FACTOR_PRIME, 0},// 11: factor_prime -> ''
    {NonTerminal::UNARY, 2},// 12: unary -> "-" unary
    {NonTerminal::UNARY, 1},// 13: unary -> primary
    {NonTerminal::PRIMARY, 1},// 14: primary -> number
    {NonTerminal::PRIMARY, 3},// 15: primary -> "(" expression ")"
};

Parser::Parser() {}

// 实现shift操作
void Parser::shift(std::stack<int> &stateStack, std::stack<Token> &symbolStack, int newState, const Token &token)
{
    stateStack.push(newState);
    symbolStack.push(token);
    printSymbolStack(symbolStack); // 打印符号栈
    std::cout << "\t Shift: Pushed state " << newState << " and token " << token.getValue() << " to the stack." << std::endl;
}

void Parser::reduce(std::stack<int> &stateStack, std::stack<Token> &symbolStack, int productionNumber)
{
    const Production &production = productions[productionNumber];

    // 根据产生式右部长度进行pop操作
    for (int i = 0; i < production.rightLength; ++i)
    {
        stateStack.pop();
        symbolStack.pop();
    }

    // 栈不为空时，获取当前状态
    if (stateStack.empty())
    {
        std::cerr << "Error: State stack is empty after pop operations." << std::endl;
        return;
    }

    // 获取当前状态
    int currentState = stateStack.top();
    NonTerminal nonTerminal = production.left; // 产生式左部

    // 推入新的状态
    if (gotoTable[currentState].find(nonTerminal) == gotoTable[currentState].end())
    {
        std::cerr << "Error: No transition for non-terminal " << getNonTerminalName(nonTerminal) << " from state " << currentState << std::endl;
        return;
    }

    int newState = gotoTable[currentState][nonTerminal];
    stateStack.push(newState);

    if (symbolStack.empty())
    {
        size_t curLine = 1; // 暂时设置为 1
        symbolStack.push(Token(nonTerminal, this->getNonTerminalName(nonTerminal),curLine));
    }
    else
    {
        // 将产生式左部非终结符推入符号栈
        size_t curLine = symbolStack.top().getLineNum();
        symbolStack.push(Token(nonTerminal, this->getNonTerminalName(nonTerminal),curLine));
    }

    // 打印符号栈
    printSymbolStack(symbolStack);

    std::cout << "\t Reducing using production: " << productionNumber << " (" << getNonTerminalName(production.left) << " -> " << production.rightLength << " symbols)" << std::endl;
}


// 判断字符串是否为数字
bool Parser::isNumber(const std::string &str)
{
    for (char const &c: str)
    {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}

// 打印符号栈内容
void Parser::printSymbolStack(const std::stack<Token> &symbolStack)
{
    std::stack<Token> tempStack = symbolStack;
    std::vector<Token> symbols;

    while (!tempStack.empty())
    {
        symbols.push_back(tempStack.top());
        tempStack.pop();
    }

    std::cout << "Symbol Stack: ";
    for (auto it = symbols.rbegin(); it != symbols.rend(); ++it)
    {
        std::cout << it->getValue() << " ";
    }
    // std::cout << std::endl;
}

// 实现语法分析函数
void Parser::parse(const std::vector<Token> &tokens)
{
    std::stack<int> stateStack;
    std::stack<Token> symbolStack;
    stateStack.push(0);

    size_t index = 0;
    while (index < tokens.size())
    {
        if (stateStack.empty())
        {
            std::cerr << "Error: State stack is empty." << std::endl;
            return;
        }

        int currentState = stateStack.top();
        Token currentToken = tokens[index];
        TokenType tokenType = currentToken.getType();

        if (parseTable[currentState].find(tokenType) == parseTable[currentState].end())
        {
            std::cerr << "Syntax Error at token " << currentToken.getValue() << std::endl;
            return;
        }

        std::string action = parseTable[currentState][tokenType];

        if (action[0] == 's')
        {
            int newState = std::stoi(action.substr(1));
            shift(stateStack, symbolStack, newState, currentToken);
            ++index;
        }
        else if (action[0] == 'r')
        {
            int productionNumber = std::stoi(action.substr(1));
            reduce(stateStack, symbolStack, productionNumber);
        }
        else if (action == "acc")
        {
            std::cout << "Parsing succeeded!" << std::endl;
            return;
        }
    }
}

// 获取非终结符名称
std::string Parser::getNonTerminalName(NonTerminal nonTerminal)
{
    switch (nonTerminal)
    {
        case NonTerminal::S: return "S";
        case NonTerminal::EXPRESSION: return "EXPRESSION";
        case NonTerminal::TERM: return "TERM";
        case NonTerminal::TERM_PRIME: return "TERM_PRIME";
        case NonTerminal::FACTOR: return "FACTOR";
        case NonTerminal::FACTOR_PRIME: return "FACTOR_PRIME";
        case NonTerminal::UNARY: return "UNARY";
        case NonTerminal::PRIMARY: return "PRIMARY";

        default: return "UNKNOWN";
    }
}
