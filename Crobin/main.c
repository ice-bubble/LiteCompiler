#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./src/common.h"
#include "./src/scanner/scanner.h"


#ifdef DEBUG_TRACE_EXECUTION

#include "./src/debug/debug.h"

#endif

static void repl() {
    Scanner scanner;
    char line[1024];
    for (;;) {
        printf("> ");

        if (!fgets(line, sizeof(line), stdin)) {
            printf("\n");
            break;
        }
        initScanner(&scanner, line);
        scanTokens(&scanner);
    }
}

static char *readFile(const char *path) {
    FILE *file = fopen(path, "rb");

    if (file == NULL) {
        fprintf(stderr, "Could not open file \"%s\".\n", path);
        exit(74);
    }

    fseek(file, 0L, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);

    char *buffer = NEW(char, fileSize + 1);

    if (buffer == NULL) {
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
    Scanner scanner;
    initScanner(&scanner, source);
    scanTokens(&scanner);
    free(source);
}

int main(int argc, const char *argv[]) {
    if (argc == 1) {
        repl();
    } else if (argc == 2) {
        runFile(argv[1]);
    } else {
        fprintf(stderr, "Usage: clox [path]\n");
        exit(64);
    }

    return 0;
}