//
// Created by icelake on 24-4-14.
//

#ifndef CROBIN_SCANNER_H
#define CROBIN_SCANNER_H

#include "../token/token.h"


typedef struct {
    const char *start;
    const char *current;
    int line;
} Scanner;

void initScanner(Scanner *scanner, const char *source);

void scanTokens(Scanner *scanner, TokenList *tokenlist);

Token scanToken(Scanner *scanner);

#endif //CROBIN_SCANNER_H
