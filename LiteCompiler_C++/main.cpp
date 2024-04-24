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
        std::cerr << errorMessage << std::endl;
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

    // 输出符号表（KEYWORD和IDENTIFIER）
    Debug::printSymbolTokens(tokens);


    // 写入文件
    // std::string filename_w(argv[2]); // 传递文件名【需要写入的文件】
    std::string filename_w; // 需要写入的文件
    std::string output; // 需要输出的数据

    // filename_w = "F:\\学习\\编译系统设计实践\\实验1\\实验1(testcase)\\miniRC_3_out.txt"; // 标记（Token）需要写入的文件
    filename_w = "miniRC_3_out.txt"; // 标记（Token）需要写入的文件
    output = Debug::getAllTokens(tokens); // 获取需要写入的数据【标记（Token）】
    if (!FileHandler::writeFile(filename_w, output, errorMessage))
    {
        std::cerr << errorMessage << std::endl;
        return 1;
    }

    // filename_w = "F:\\学习\\编译系统设计实践\\实验1\\实验1(testcase)\\miniRC_3_sym.txt"; // 符号表（KEYWORD和IDENTIFIER）需要写入的文件
    filename_w = "miniRC_3_sym.txt"; // 符号表（KEYWORD和IDENTIFIER）需要写入的文件
    output = Debug::getAllSymbolTokens(tokens); // 获取需要写入的数据【符号表（KEYWORD和IDENTIFIER）】
    if (!FileHandler::writeFile(filename_w, output, errorMessage))
    {
        std::cerr << errorMessage << std::endl;
        return 1;
    }
    return 0;
}
