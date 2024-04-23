//
// Created by icelake on 24-4-22.
//

#include "lexer.h"

#include <utility>
#include "../error/error.h"

namespace Lexer {
    std::map<std::string, Token::TokenType> Lexer::keywords = {
            {"and",      Token::TOKEN_AND},
            {"break",    Token::TOKEN_BREAK},
            {"class",    Token::TOKEN_CLASS},
            {"continue", Token::TOKEN_CONTINUE},
            {"double",   Token::TOKEN_DOUBLE},
            {"else",     Token::TOKEN_ELSE},
            {"false",    Token::TOKEN_FALSE},
            {"for",      Token::TOKEN_FOR},
            {"function", Token::TOKEN_FUNCTION},
            {"if",       Token::TOKEN_IF},
            {"integer",  Token::TOKEN_INTEGER},
            {"nil",      Token::TOKEN_NIL},
            {"not",      Token::TOKEN_NOT},
            {"or",       Token::TOKEN_OR},
            {"print",    Token::TOKEN_PRINT},
            {"return",   Token::TOKEN_RETURN},
            {"super",    Token::TOKEN_SUPER},
            {"this",     Token::TOKEN_THIS},
            {"true",     Token::TOKEN_TRUE},
            {"var",      Token::TOKEN_VAR},
            {"while",    Token::TOKEN_WHILE}
    };

    Lexer::Lexer(std::string source) {
        this->source = std::move(source);
    }

    std::vector<Token::Token> Lexer::scanTokens() {
        while (!isAtEnd()) {

            start = current;
            scanToken();
        }
        tokens.emplace_back(Token::TOKEN_EOF, "", std::any{}, line);
        return tokens;
    }


    void Lexer::scanToken() {
        char c = advance();
        if (isDigit(c)) return _number();
        if (isAlpha(c))return _identifier();
        switch (c) {
            case '(':
                return addToken(Token::TOKEN_LEFT_PAREN);
            case ')':
                return addToken(Token::TOKEN_RIGHT_PAREN);
            case '[':
                return addToken(Token::TOKEN_LEFT_BRACKET);
            case ']':
                return addToken(Token::TOKEN_RIGHT_BRACKET);
            case '{':
                return addToken(Token::TOKEN_LEFT_BRACE);
            case '}':
                return addToken(Token::TOKEN_RIGHT_BRACE);
            case ',':
                return addToken(Token::TOKEN_COMMA);
            case '.':
                if (isDigit(peek())) return _real();
                return addToken(Token::TOKEN_DOT);
            case '-':
                return addToken(Token::TOKEN_MINUS);
            case '+':
                return addToken(Token::TOKEN_PLUS);
            case '%':
                return addToken(Token::TOKEN_MOD);
            case ';':
                return addToken(Token::TOKEN_SEMICOLON);
            case '*':
                return addToken(Token::TOKEN_STAR);
            case '#':
                while (peek() != '\n' && !isAtEnd()) advance();
                break;
            case '|':
                if (match('|')) return addToken(Token::TOKEN_OR);
                break;
            case '&':
                if (match('&')) return addToken(Token::TOKEN_AND);
                break;
            case '!':
                return addToken(match('=') ? Token::TOKEN_NOT_EQUAL : Token::TOKEN_NOT);
            case '=':
                return addToken(match('=') ? Token::TOKEN_EQUAL_EQUAL : Token::TOKEN_EQUAL);
            case '<':
                return addToken(match('=') ? Token::TOKEN_LESS_EQUAL : Token::TOKEN_LESS);
            case '>':
                return addToken(match('=') ? Token::TOKEN_GREATER_EQUAL : Token::TOKEN_GREATER);
            case '/':
                return slash();
            case '"':
                return _string();
            case '\n':
                line++;
                return;
            case ' ':
            case '\r':
            case '\t':
                return;
        }
        std::string UnexpectedChar(1, c);
        error(line, "Unexpected character '" + UnexpectedChar + "'.");
    }

    void Lexer::_identifier() {
        while (isAlphaNumeric(peek())) advance();

        std::string text = source.substr(start, current - start);
        auto it = keywords.find(text);
        if (it == keywords.end()) {
            addToken(Token::TOKEN_IDENTIFIER);
            return;
        }
        addToken(it->second);
    }

    void Lexer::_real() {
        while (isDigit(peek())) advance();
        addToken(Token::TOKEN_REAL, std::stod(source.substr(start, current - start)));
    }

    void Lexer::_number() {
        while (isDigit(peek())) advance();

        // Look for a fractional part.
        if (peek() == '.' && isDigit(peekNext())) {
            // Consume the "."
            advance();

            while (isDigit(peek())) advance();
            addToken(Token::TOKEN_REAL, std::stod(source.substr(start, current - start)));
            return;
        }

        addToken(Token::TOKEN_INT,
                 static_cast<long>(std::stod(source.substr(start, current - start))));
    }

    void Lexer::_string() {
        while (peek() != '"' && !isAtEnd()) {
            if (peek() == '\n') line++;
            advance();
        }

        if (isAtEnd()) {
            error(line, "Unterminated string.");
            return;
        }

        // The closing ".
        advance();

        // Trim the surrounding quotes.
        std::string value = source.substr(start + 1, current - start - 2);
        addToken(Token::TOKEN_STRING, value);
    }

    void Lexer::slash() {
        if (match('/')) {
            // A comment goes until the end of the line.
            while (peek() != '\n' && !isAtEnd()) advance();
        } else if (match('*')) {
            while (true) {
                if (isAtEnd()) {
                    error(line, "Unterminated comment.");
                    return;
                }
                char nextChar = advance();

                if (nextChar == '\n')
                    line++;

                if (nextChar == '*' && peek() == '/') {
                    advance();
                    break;
                }
            }
        } else {
            addToken(Token::TOKEN_SLASH);
        }
    }

    bool Lexer::match(char expected) {
        if (isAtEnd()) return false;
        if (source[current] != expected) return false;

        current++;
        return true;
    }

    char Lexer::peek() {
        if (isAtEnd()) return '\0';
        return source[current];
    }

    char Lexer::peekNext() {
        if (current + 1 >= source.length()) return '\0';
        return source[current + 1];
    }

    bool Lexer::isAlpha(char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
    }

    bool Lexer::isAlphaNumeric(char c) {
        return isAlpha(c) || isDigit(c);
    }

    bool Lexer::isDigit(char c) {
        return c >= '0' && c <= '9';
    }

    bool Lexer::isAtEnd() {
        return current >= source.length();
    }

    char Lexer::advance() {
        current++;
        return source[current - 1];
    }

    void Lexer::addToken(Token::TokenType type) {
        addToken(type, std::any{});
    }

    void Lexer::addToken(Token::TokenType type, const Object &literal) {
        std::string lexeme = source.substr(start, current - start);
        tokens.emplace_back(type, lexeme, literal, line);
    }

}