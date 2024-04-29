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
    std::string input;
    std::vector<Token> tokens;
    std::string errorMessage;
    std::string filename; // 需要读取的文件
    std::string filename_w; // 标记（Token）需要写入的文件【OUT】
    std::string filename_sym; // 符号表（KEYWORD和IDENTIFIER）需要写入的文件【SYM】
    std::string output; // 需要输出的数据

    if (argc == 1) // 采用交互式终端输入输出
    {
        Debug::repl();
        return 0; // 交互式终端的执行方式不从文件读取数据，也不输出到文件
    }
    else if (argc == 2) // 输入文件采用主函数传递参数
    {
        filename = argv[1]; // 输入文件路径
        filename_w = "miniRC_out.txt"; // 标记（Token）需要写入的文件
        filename_sym = "miniRC_sym.txt"; // 符号表（KEYWORD和IDENTIFIER）需要写入的文件
    }
    else if (argc == 4) // 输入输出文件均采用主函数传递参数
    {
        filename = argv[1]; // 输入文件路径
        filename_w = argv[2]; // 输出文件1路径【标记（Token）需要写入的文件】
        filename_sym = argv[3]; // 输出文件2路径【符号表（KEYWORD和IDENTIFIER）需要写入的文件】
    }
    else
    {
        std::cerr << "Usage: " << argv[0] << " <input_file> "<< std::endl;
        std::cerr << "OR" <<std::endl;
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file_1> <output_file_2>" << std::endl;
        return 1;
    }

    // 读取文件
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
    output = Debug::getAllTokens(tokens); // 获取需要写入的数据【标记（Token）】
    if (!FileHandler::writeFile(filename_w, output, errorMessage))
    {
        std::cerr << errorMessage << std::endl;
        return 1;
    }
    output = Debug::getAllSymbolTokens(tokens); // 获取需要写入的数据【符号表（KEYWORD和IDENTIFIER）】
    if (!FileHandler::writeFile(filename_sym, output, errorMessage))
    {
        std::cerr << errorMessage << std::endl;
        return 1;
    }
}
