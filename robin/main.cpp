#include "src/common.h"

#include "src/token/token.h"
#include "src/lexer/lexer.h"
#include "src/parser/parser.h"
#include "src/ast/production.h"
#include "src/sema/sema.h"
#include "src/debug/debug.h"

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
#ifdef PRINT_TOKENLIST
        printTokenList(tokenlist);
#endif
        if (lexer.hasError)
            std::cerr << "There are lexical errors in the source code" << std::endl;
        lexer.hasError = false;

        parser::Parser parser = parser::Parser(tokenlist);
        List<SharedPtr<production::Production>> ast = parser.parserAst();
        if (parser.hasError)
            std::cerr << "There are syntax errors in the source code" << std::endl;
        else {
            sema::Sema sema = sema::Sema(ast[0]);
            List<String> irCode = sema.generateIRCODE();
            printIRCODE(irCode);
        }
    }
}

String readFile(const String &path) {
    std::ifstream file(path, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Failed to open file: " + path);
    }

    std::stringstream buffer;
    buffer << file.rdbuf(); // 将文件内容读入缓冲区
    return buffer.str();    // 返回缓冲区内容作为字符串
}

static void runFile(const String &path) {
    String source;
    try {
        // 读取文件内容
        source = readFile(path);

    } catch (const std::exception &e) {
        // 捕获异常并输出错误信息
        std::cerr << e.what() << std::endl << std::endl;

        // 退出程序，返回错误状态码 74
        exit(74);
    }
    // 创建词法分析器并进行词法分析
    parser::Parser::slrTableInit();
    lexer::Lexer lexer(source);
    List<token::Token> tokenlist = lexer.scanTokens();

#ifdef PRINT_TOKENLIST
    //打印词法分析结果
    printTokenList(tokenlist);
#endif
    if (lexer.hasError)
        std::cerr << "There are lexical errors in the source code" << std::endl;

    parser::Parser parser = parser::Parser(tokenlist);
    List<SharedPtr<production::Production>> ast = parser.parserAst();
    if (parser.hasError)
        std::cerr << "There are syntax errors in the source code" << std::endl;
    else {
        sema::Sema sema = sema::Sema(ast[0]);
        List<String> irCode = sema.generateIRCODE();
        printIRCODE(irCode);
    }
}

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
