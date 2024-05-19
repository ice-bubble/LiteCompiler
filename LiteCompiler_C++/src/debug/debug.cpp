//
// Created by Ice-bubble on 24-4-21.
//
#include "debug.h"

/*
*    注意！！输出到文件和输出到终端的输出函数是不同的，如有修改输出格式请一并修改其对应的函数
*    函数对应关系：
*    Debug::printTokens         <-->    Debug::getAllTokens
*    Debug::printSymbolTokens   <-->    Debug::getAllSymbolTokens
*    Lexer::printKeyword        <-->    Lexer::getAllKeyword
*/


void Debug::repl()
{
    char input_only_one_line[1024];
    std::vector<Token> tokens;
    for (;;)
    {
        printf("> ");

        if (!fgets(input_only_one_line, sizeof(input_only_one_line), stdin) || input_only_one_line[0] == EOF)
        {
            printf("\n");
            break;
        }

        // 创建Lexer类对象
        Lexer lexer(input_only_one_line);

        // 词法分析
        lexer.LexicalAnalyze(tokens);

        tokens.erase(std::remove_if(tokens.begin(), tokens.end(), isInvalidToken),tokens.end());    // 删除词法分析后产生的无效标记
        size_t eofLineNum = (tokens.empty() ? 1 : tokens.back().getLineNum() + 1);          // 文件结束符EOF的行号
        tokens.push_back(Token(TokenType::EOF_EOF, "EOF", eofLineNum));           // 在记号流的末尾增加一个EOF类型的Token，表示输入的结束
        tokens.push_back(Token(TokenType::KEYWORD_EOF, "$", eofLineNum));           // 在记号流的末尾增加一个EOF类型的Token，表示输入的结束

        // 输出本行代码含有的标记（Token）
        Debug::printTokens(tokens);


        printf("\n");
        // 输出符号表（KEYWORD和IDENTIFIER）
        // Debug::printSymbolTokens(tokens);

        // 语法分析
        Parser parser;
        parser.parse(tokens);


        std::vector<Token>().swap(tokens); // 清空本次的Token

    }
}


void Debug::printTokens(const std::vector<Token> &tokens)
{
    for (const Token &token: tokens)
    {
        std::cout << "Line: " << token.getLineNum() << " <";
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
            case TokenType::STRING:
                std::cout << "STRING, ";
            break;
            case TokenType::KEYWORD_EOF:
                std::cout << "EOF, ";
            break;
            default:
                break;
        }
        std::cout << token.getValue() << ">" << std::endl;
    }
}

void Debug::printSymbolTokens(const std::vector<Token> &tokens)
{
    //输出全部Keyword
    Lexer::printKeyword();
    std::vector<std::string> identifiers;
    for (const Token &token: tokens)
    {
        if (token.getType() != TokenType::INVALID && token.getType() != TokenType::EMPTY &&
            token.getValue() != "\n" && token.getValue() != "\0" && token.getValue() != "\t")
        {
            // 获取标记的TYPE，匹配IDENTIFIER则存储
            if (token.getType() == TokenType::IDENTIFIER)
            {
                identifiers.push_back(token.getValue());
            }
        }
    }

    // 去除重复元素
    identifiers = removeDuplicates(identifiers);

    // 输出标识符
    for (const auto &identifier: identifiers)
    {
        std::cout << "IDENTIFIER " << identifier << std::endl;
    }
}

std::string Debug::getAllSymbolTokens(const std::vector<Token> &tokens)
{
    std::string output;

    // 获取所有Keyword按照格式拼接而成的字符串
    output = Lexer::getAllKeyword();

    std::unordered_set<std::string> identifiers;
    for (const Token &token: tokens)
    {
        if (token.getType() != TokenType::INVALID && token.getType() != TokenType::EMPTY &&
            token.getValue() != "\n" && token.getValue() != "\0" && token.getValue() != "\t")
        {
            // 存储 IDENTIFIER
            if (token.getType() == TokenType::IDENTIFIER)
            {
                identifiers.insert(token.getValue());
            }
        }
    }

    // IDENTIFIER需要输出的内容拼接进字符串
    for (const auto &identifier: identifiers)
    {
        output += "IDENTIFIER " + identifier + '\n';
    }

    return output;
}

std::string Debug::getAllTokens(const std::vector<Token> &tokens)
{
    std::string output;
    for (const Token &token: tokens)
    {
        if (token.getType() != TokenType::INVALID && token.getType() != TokenType::EMPTY &&
            token.getValue() != "\n" && token.getValue() != "\0" && token.getValue() != "\t")
        {
            output += "<";
            switch (token.getType())
            {
                case TokenType::IDENTIFIER:
                    output += "id, ";
                    break;
                case TokenType::INTEGER:
                    output += "INT, ";
                    break;
                case TokenType::FLOAT:
                    output += "REAL, ";
                    break;
                case TokenType::STRING:
                    output += "STRING, ";
                    break;
                case TokenType::KEYWORD_EOF:
                    output += "EOF, ";
                    break;
                // Add other cases as needed
                default:
                    break;
            }
        }
        if (token.getType() != TokenType::INVALID && token.getType() != TokenType::EMPTY &&
            token.getValue() != "\n" && token.getValue() != "\0" && token.getValue() != "\t")
        {
            output += token.getValue() + ">" + '\n';
        }
    }
    return output;
}

// 去除重复元素函数
std::vector<std::string> removeDuplicates(const std::vector<std::string> &input)
{
    std::unordered_set<std::string> seen;
    std::vector<std::string> result;

    for (const std::string &element: input)
    {
        // 如果元素第一次出现，将其添加到结果中并记录在集合中
        if (seen.find(element) == seen.end())
        {
            result.push_back(element);
            seen.insert(element);
        }
    }

    return result;
}
