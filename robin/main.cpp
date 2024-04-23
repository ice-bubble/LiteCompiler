/**
 * @file main.cpp
 * @brief 主函数
 * @author lzy
 * @date 24-4-22
 */

#include <iostream>
#include "src/lexer/lexer.h"

#ifdef DEBUG_FLAG
#include "src/debug/debug.h"
#endif

/**
 * @brief REPL（交互式解释器）循环。用户可以在控制台输入代码，并对其进行词法分析。
 */
static void repl() {

    char line[1024];
    for (;;) {
        printf("> ");

        if (!fgets(line, sizeof(line), stdin)) {
            printf("\n");
            break;
        }
        Lexer::Lexer lexer = Lexer::Lexer(line);
        std::vector<Token::Token> tokenList = lexer.scanTokens();
#ifdef DEBUG_PRINT_TOKENLIST
        printTokenList(tokenList);
#endif
    }
}

/**
 * @brief 读取文件内容并返回其内容。
 * @param path 要读取的文件路径。
 * @return char* 文件内容的字符指针。
 * @throw std::bad_alloc 内存不足时抛出异常。
 */
static char *readFile(const char *path) {
    // 打开文件
    FILE *file = fopen(path, "rb");

    if (file == nullptr) {
        fprintf(stderr, "Could not open file \"%s\".\n", path);
        exit(74);
    }

    // 获取文件大小
    fseek(file, 0L, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);

    // 分配内存并读取文件内容
    char *buffer;
    try {
        buffer = new char[fileSize + 1];
    } catch (const std::bad_alloc &e) {
        fprintf(stderr, "Not enough memory to read \"%s\".\n", path);
        exit(74);
    }


    size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);

    if (bytesRead < fileSize) {
        fprintf(stderr, "Could not read file \"%s\".\n", path);
        exit(74);
    }

    // 添加字符串结束符
    buffer[bytesRead] = '\0';

    // 关闭文件并返回文件内容
    fclose(file);
    return buffer;
}

/**
 * @brief 运行指定路径的文件。对其进行词法分析。
 * @param path 要运行的文件路径。
 */
static void runFile(const char *path) {
    char *source = readFile(path);
    Lexer::Lexer lexer = Lexer::Lexer(source);
    std::vector<Token::Token> tokenList = lexer.scanTokens();
#ifdef DEBUG_PRINT_TOKENLIST
    printTokenList(tokenList);
#endif

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
        fprintf(stderr, "Usage: robin [path]\n");
        exit(64);
    }

    return 0;
}
