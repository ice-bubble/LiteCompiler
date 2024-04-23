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
    FileHandler fileHandler;
    std::string errorMessage;
    std::string filename(argv[1]); // 传递文件名
    if (!fileHandler.readFile(filename, input, errorMessage))
    {
        std::cerr << "Error reading file: " << errorMessage << std::endl;
        return 1;
    }
    // 进行词法分析
    Lexer lexer(input);
    if (!lexer.LexicalAnalyze(tokens))
    {
        std::cerr << "Lexical Error!" << std::endl;
    }

    // 输出标记
    Debug::printTokens(tokens);

    return 0;
}
