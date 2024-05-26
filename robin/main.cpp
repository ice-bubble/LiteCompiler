/**
 * @file main.cpp
 * @brief 主函数
 * @date 24-4-22
 */

#include "src/common.h"

#include "src/token/token.h"
#include "src/lexer/lexer.h"
#include "src/parser/parser.h"
#include "src/ast/production.h"

#ifdef DEBUG

#include "src/debug/debug.h"

#endif

/**
 * @brief REPL（交互式解释器）循环。
 *
 * 用户可以在控制台输入代码，并对其进行词法分析,按下ctrl+C强制退出。
 *
 */
static void repl() {

    char line[1024];
    parser::Parser::slrTableInit();
    for (;;) {
        printf("> ");

        if (!fgets(line, sizeof(line), stdin)) {
            printf("\n");
            break;
        }
        lexer::Lexer lexer = lexer::Lexer(line);
        List<token::Token> tokenlist = lexer.scanTokens();

        printTokenList(tokenlist);
        if (lexer.hasError)
            std::cerr << "There are lexical errors in the source code" << std::endl;
        lexer.hasError = false;

        parser::Parser parser = parser::Parser(tokenlist);
        List<SharedPtr<production::Production>> ast = parser.parserAst();
        if (parser.hasError)
            std::cerr << "There are syntax errors in the source code" << std::endl;
    }
}

/**
 * @brief 读取文件内容并返回其内容。
 * @param path 要读取的文件路径。
 * @return std::string 文件内容的字符串形式。
 */
String readFile(const String &path) {
    std::ifstream file(path, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Failed to open file: " + path);
    }

    std::stringstream buffer;
    buffer << file.rdbuf(); // 将文件内容读入缓冲区
    return buffer.str();    // 返回缓冲区内容作为字符串
}

/**
 * @brief 运行指定路径的文件，并进行词法分析。
 *
 * 这个函数打开指定路径的文件，将文件内容传递给词法分析器进行处理，并打印词法分析结果（可选）。
 * 如果文件无法打开或词法分析出现异常，将会捕获异常并输出错误信息，然后退出程序。
 *
 * @param path 要运行的文件路径。
 */
static void runFile(const String &path) {
    String source;
    try {
        // 读取文件内容
        source = readFile(path);

    } catch (const std::exception &e) {
        // 捕获异常并输出错误信息
        std::cerr << e.what() << std::endl << 1 << std::endl;

        // 退出程序，返回错误状态码 74
        exit(74);
    }
    // 创建词法分析器并进行词法分析
    parser::Parser::slrTableInit();
    lexer::Lexer lexer(source);
    List<token::Token> tokenlist = lexer.scanTokens();

    //打印词法分析结果
    printTokenList(tokenlist);
    if (lexer.hasError)
        std::cerr << "There are lexical errors in the source code" << std::endl;

    parser::Parser parser = parser::Parser(tokenlist);
    List<SharedPtr<production::Production>> ast = parser.parserAst();
    if (parser.hasError)
        std::cerr << "There are syntax errors in the source code" << std::endl;
}


/**
 * @brief 主函数，用于处理命令行参数和启动交互式解释器或运行文件。
 *
 * @param argc 命令行参数数量。
 * @param argv 命令行参数数组。
 * @return int 程序执行结果。
 */
int main(int argc, const char *argv[]) {
    if (argc == 1) {
        repl();
    } else if (argc == 2) {
        runFile(argv[1]);
    } else {
        std::cerr << "Usage: robin [path]" << std::endl;
        exit(64);
    }

    return 0;
}
