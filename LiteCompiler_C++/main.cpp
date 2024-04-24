#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "./src/debug/debug.h"
#include "./src/Token/Token.h"
#include "./src/LexicalAnalysis/Lexer.h"
#include "./src/FileHandler/FileHandler.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::string input;
    std::vector<Token> tokens;

    // 读取文件
    std::string errorMessage;
    std::string filename(argv[1]); // 传递文件名
    if (!FileHandler::readFile(filename, input, errorMessage))
    {
        std::cerr << "Error reading file: " << errorMessage << std::endl;
        return 1;
    }
    // 进行词法分析
    Lexer lexer(input);
    if (!lexer.LexicalAnalyze(tokens))
        std::cerr << "The code exists above Lexical Error!\n" << std::endl;
    else
        std::cout << "No Lexical Error in the code!\n" << std::endl;
    // 输出标记（Token）
    Debug::printTokens(tokens);

    // 输出KEYWORD和IDENTIFIER
    Debug::printsymbolTokens(tokens);

    return 0;
}
