#include <iostream>
#include "src/lexer/lexer.h"

#ifdef DEBUG_FLAG
#include "src/debug/debug.h"
#endif

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
        printRequestedTokenList(tokenList);
#endif
    }
}

static char *readFile(const char *path) {
    FILE *file = fopen(path, "rb");

    if (file == nullptr) {
        fprintf(stderr, "Could not open file \"%s\".\n", path);
        exit(74);
    }

    fseek(file, 0L, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);
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

    buffer[bytesRead] = '\0';

    fclose(file);
    return buffer;
}

static void runFile(const char *path) {
    char *source = readFile(path);
    Lexer::Lexer lexer = Lexer::Lexer(source);
    std::vector<Token::Token> tokenList = lexer.scanTokens();
#ifdef DEBUG_PRINT_TOKENLIST
    printRequestedTokenList(tokenList);
#endif

}

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
