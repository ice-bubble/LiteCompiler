//
// Created by icelake on 24-4-22.
//

#ifndef ROBIN_LEXER_H
#define ROBIN_LEXER_H

#include "../common.h"
#include "../token/token.h"

namespace Lexer {
    class Lexer {
    private:
        std::string source;
        std::vector<Token::Token> tokens;

        size_t start = 0;
        size_t current = 0;
        size_t line = 1;
        static std::map<std::string, Token::TokenType> keywords;

    public:
        Lexer(std::string source);

        std::vector<Token::Token> scanTokens();

    private:
        void scanToken();

        void _identifier();

        void _real();

        void _number();

        void _string();

        void slash();

        bool match(char expected);

        char peek();

        char peekNext();

        static bool isAlpha(char c);

        static bool isAlphaNumeric(char c);

        static bool isDigit(char c);

        bool isAtEnd();

        char advance();

        void addToken(Token::TokenType type);

        void addToken(Token::TokenType type, const Object &literal);
    };

}


#endif //ROBIN_LEXER_H
